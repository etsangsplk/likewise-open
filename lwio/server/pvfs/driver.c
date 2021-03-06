/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*-
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * Editor Settings: expandtabs and use 4 spaces for indentation */

/*
 * Copyright Likewise Software
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.  You should have received a copy of the GNU General
 * Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * LIKEWISE SOFTWARE MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING
 * TERMS AS WELL.  IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT
 * WITH LIKEWISE SOFTWARE, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE
 * TERMS OF THAT SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE GNU
 * GENERAL PUBLIC LICENSE, NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU
 * HAVE QUESTIONS, OR WISH TO REQUEST A COPY OF THE ALTERNATE LICENSING
 * TERMS OFFERED BY LIKEWISE SOFTWARE, PLEASE CONTACT LIKEWISE SOFTWARE AT
 * license@likewisesoftware.com
 */

/*
 * Copyright (C) Likewise Software. All rights reserved.
 *
 * Module Name:
 *
 *        driver.c
 *
 * Abstract:
 *
 *        Likewise Posix File System Driver (PVFS)
 *
 *        Driver Entry Function
 *
 * Authors: Gerald Carter <gcarter@likewise.com>
 */

#include "pvfs.h"

/* Forward declarations */

static
VOID
PvfsDriverShutdown(
    IN IO_DRIVER_HANDLE DriverHandle
    );

static
NTSTATUS
PvfsDriverDispatch(
    IN IO_DEVICE_HANDLE DeviceHandle,
    IN PIRP pIrp
    );

static
NTSTATUS
PvfsDriverInitialize(
    VOID
    );

static
NTSTATUS
PvfsCreateDriverState(
    PPVFS_DRIVER_STATE State
    );

static
VOID
PvfsDestroyDriverState(
    PPVFS_DRIVER_STATE State
    );

/************************************************************
  **********************************************************/

NTSTATUS
IO_DRIVER_ENTRY(pvfs)(
    IN IO_DRIVER_HANDLE DriverHandle,
    IN ULONG InterfaceVersion
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;
    IO_DEVICE_HANDLE deviceHandle = NULL;

    if (IO_DRIVER_ENTRY_INTERFACE_VERSION != InterfaceVersion)
    {
        ntError = STATUS_DEVICE_CONFIGURATION_ERROR;
        BAIL_ON_NT_STATUS(ntError);
    }

    ntError = IoDriverInitialize(DriverHandle,
                                 NULL,
                                 PvfsDriverShutdown,
                                 PvfsDriverDispatch);
    BAIL_ON_NT_STATUS(ntError);

    ntError = IoDeviceCreate(&deviceHandle,
                             DriverHandle,
                             "pvfs",
                             NULL);
    BAIL_ON_NT_STATUS(ntError);

    gPvfsDriverState.IoDeviceHandle = deviceHandle;

    ntError = PvfsDriverInitialize();
    BAIL_ON_NT_STATUS(ntError);

cleanup:
    return ntError;

error:
    goto cleanup;
}


/************************************************************
 Driver Exit Function
 ***********************************************************/

static
VOID
PvfsDestroyUnixIdCache(
    IN OUT PPVFS_ID_CACHE_ENTRY CacheArray[],
    IN LONG Length
    );

static
VOID
PvfsDriverShutdown(
    IN IO_DRIVER_HANDLE DriverHandle
    )
{
    BOOLEAN driverLocked = FALSE;

    if (IsSetFlag(gPvfsDriverState.Flags, PVFS_STATE_FLAG_INITIALIZED))
    {
        LWIO_LOCK_MUTEX(driverLocked, &gPvfsDriverState.Mutex);

        PvfsPathCacheShutdown();
        PvfsShutdownQuota();

        LWIO_UNLOCK_MUTEX(driverLocked, &gPvfsDriverState.Mutex);

        PvfsDestroyDriverState(&gPvfsDriverState);

        ClearFlag(gPvfsDriverState.Flags, PVFS_STATE_FLAG_INITIALIZED);
    }

    IO_LOG_ENTER_LEAVE("");
}

static
VOID
PvfsDestroyUnixIdCache(
    IN OUT PPVFS_ID_CACHE_ENTRY CacheArray[],
    IN LONG Length
    )
{
    LONG i = 0;

    for (i=0; i<Length; i++)
    {
        if (CacheArray[i] != NULL)
        {
            RTL_FREE(&CacheArray[i]->pSid);
            PVFS_FREE(&CacheArray[i]);
        }
    }

    return;
}

////////////////////////////////////////////////////////////////////////

static
NTSTATUS
PvfsDriverDispatch(
    IN IO_DEVICE_HANDLE DeviceHandle,
    IN PIRP pIrp
    )
{
    NTSTATUS ntError = STATUS_SUCCESS;
    PPVFS_IRP_CONTEXT pIrpCtx = NULL;

    ntError = PvfsAllocateIrpContext(&pIrpCtx, pIrp);
    BAIL_ON_NT_STATUS(ntError);

    switch (pIrpCtx->pIrp->Type)
    {
        case IRP_TYPE_CREATE:
            // ntError = PvfsCreate(pIrpCtx);
            pIrpCtx->Callback = PvfsCreate;
            break;

        case IRP_TYPE_LOCK_CONTROL:
            pIrpCtx->Callback = PvfsLockControl;
            break;

        case IRP_TYPE_READ:
            pIrpCtx->Callback = PvfsRead;
            break;

        case IRP_TYPE_WRITE:
            pIrpCtx->Callback = PvfsWrite;
            break;

        case IRP_TYPE_SET_INFORMATION:
            pIrpCtx->Callback = PvfsSetInformationFile;
            break;

        case IRP_TYPE_QUERY_INFORMATION:
            pIrpCtx->Callback = PvfsQueryInformationFile;
            break;

        case IRP_TYPE_QUERY_DIRECTORY:
            pIrpCtx->Callback = PvfsQueryDirInformation;
            break;


        case IRP_TYPE_READ_DIRECTORY_CHANGE:
            pIrpCtx->Callback = PvfsReadDirectoryChange;
            break;


        case IRP_TYPE_QUERY_VOLUME_INFORMATION:
            pIrpCtx->Callback = PvfsQueryVolumeInformation;
            break;

        case IRP_TYPE_QUERY_SECURITY:
            pIrpCtx->Callback = PvfsQuerySecurityFile;
            break;

        case IRP_TYPE_SET_SECURITY:
            pIrpCtx->Callback = PvfsSetSecurityFile;
            break;

        case IRP_TYPE_FLUSH_BUFFERS:
            pIrpCtx->Callback = PvfsFlushBuffers;
            break;

        case IRP_TYPE_DEVICE_IO_CONTROL:
            pIrpCtx->Callback = PvfsDispatchDeviceIoControl;
            break;

        case IRP_TYPE_SET_VOLUME_INFORMATION:
            pIrpCtx->Callback = PvfsSetVolumeInformation;
            break;

        case IRP_TYPE_QUERY_QUOTA:
            pIrpCtx->Callback = PvfsQueryQuota;
            break;

        case IRP_TYPE_SET_QUOTA:
            pIrpCtx->Callback = PvfsSetQuota;
            break;

        case IRP_TYPE_CLOSE:
            pIrpCtx->Callback = PvfsClose;
            break;
        //
        // Special Cases...STATUS_PENDING has special meaning
        //

        case IRP_TYPE_FS_CONTROL:
            ntError = PvfsDispatchFsIoControl(pIrpCtx);
            break;

        //
        // Safety net
        //
        default:
            ntError = STATUS_INVALID_PARAMETER;
            break;
    }

    if (pIrpCtx->Callback)
    {
        ntError = PvfsScheduleIrpContext(pIrpCtx, FALSE);
    }

error:
    if (ntError != STATUS_PENDING)
    {
        pIrp->IoStatusBlock.Status = ntError;
    }

    PvfsReleaseIrpContext(&pIrpCtx);

    return ntError;
}

/************************************************************
 ***********************************************************/

static
NTSTATUS
PvfsDriverInitialize(
    VOID
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;

    if (IsSetFlag(gPvfsDriverState.Flags, PVFS_STATE_FLAG_INITIALIZED))
    {
        ntError = STATUS_SUCCESS;
        goto error;
    }

    ntError = PvfsConfigRegistryInit(&gPvfsDriverConfig);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsPathCacheInit();
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsCreateDriverState(&gPvfsDriverState);
    BAIL_ON_NT_STATUS(ntError);

    SetFlag(gPvfsDriverState.Flags, PVFS_STATE_FLAG_INITIALIZED);

error:
    return ntError;
}

////////////////////////////////////////////////////////////////////////

static
NTSTATUS
PvfsCreateDriverState(
    PPVFS_DRIVER_STATE State
    )
{
    NTSTATUS ntError = STATUS_SUCCESS;
    PLW_THREAD_POOL_ATTRIBUTES pThreadAttributes = NULL;

    ntError = PvfsSecurityInitMapSecurityCtx(&State->MapSecurityContext);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsCbTableInitialize(&State->ScbTable);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsCbTableInitialize(&State->FcbTable);
    BAIL_ON_NT_STATUS(ntError);

    // Create the worker thread pool.  Avoid any tasks threads for now

    ntError = LwRtlCreateThreadPoolAttributes(&pThreadAttributes);
    BAIL_ON_NT_STATUS(ntError);

    LwRtlSetThreadPoolAttribute(
        pThreadAttributes,
        LW_THREAD_POOL_OPTION_TASK_THREADS,
        0);

    ntError = LwRtlCreateThreadPool(&State->ThreadPool, pThreadAttributes);
    BAIL_ON_NT_STATUS(ntError);



error:
    if (!NT_SUCCESS(ntError))
    {
        PvfsDestroyDriverState(State);
    }

    if (pThreadAttributes)
    {
        LwRtlFreeThreadPoolAttributes(&pThreadAttributes);
    }

    return ntError;
}

////////////////////////////////////////////////////////////////////////

static
VOID
PvfsDestroyDriverState(
    PPVFS_DRIVER_STATE State
    )
{
    BOOLEAN driverLocked = FALSE;

    LWIO_LOCK_MUTEX(driverLocked, &State->Mutex);

    if (State->ThreadPool)
    {
        LwRtlFreeThreadPool(&State->ThreadPool);
    }


    PvfsDestroyUnixIdCache(State->UidCache.Cache, PVFS_MAX_MRU_SIZE);
    PvfsDestroyUnixIdCache(State->GidCache.Cache, PVFS_MAX_MRU_SIZE);

    if (State->MapSecurityContext)
    {
        PvfsSecurityShutdownMapSecurityCtx(&State->MapSecurityContext);
    }

    if (State->IoDeviceHandle)
    {
        IoDeviceDelete(&State->IoDeviceHandle);
    }

    PvfsCbTableDestroy(&State->ScbTable);
    PvfsCbTableDestroy(&State->FcbTable);

    LWIO_LOCK_MUTEX(driverLocked, &State->Mutex);

    pthread_mutex_destroy(&State->Mutex);

    return;
}
