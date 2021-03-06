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
 *        stream.c
 *
 * Abstract:
 *
 *        Likewise Posix File System Driver (PVFS)
 *
 *        Alternate Data Stream routines
 *
 * Authors: Gerald Carter <gcarter@likewise.com>
 *          Wei Fu <wfu@likewise.com>
 */

#include "pvfs.h"


////////////////////////////////////////////////////////////////////////

NTSTATUS
PvfsLookupStreamDirectoryPath(
    OUT PSTR *ppStreamDirectoryName,
    IN PPVFS_FILE_NAME pFileName
    )
{
    NTSTATUS ntError = STATUS_SUCCESS;
    PPVFS_FILE_NAME parentDirectoryName = NULL;
    PPVFS_FILE_NAME baseFileName = NULL;
    PSTR pszStreamDirname = NULL;

    PVFS_BAIL_ON_INVALID_FILENAME(pFileName, ntError);

    ntError = PvfsSplitFileNamePath(
                  &parentDirectoryName,
                  &baseFileName,
                  pFileName);
    BAIL_ON_NT_STATUS(ntError);

    ntError = LwRtlCStringAllocatePrintf(
                  &pszStreamDirname,
                  "%s/%s/%s",
                  PvfsGetCStringBaseFileName(parentDirectoryName),
                  PVFS_STREAM_METADATA_DIR_NAME,
                  PvfsGetCStringBaseFileName(baseFileName));
    BAIL_ON_NT_STATUS(ntError);

    *ppStreamDirectoryName = pszStreamDirname;

 error:
    if (!NT_SUCCESS(ntError))
    {
        if (pszStreamDirname)
        {
            LwRtlCStringFree(&pszStreamDirname);
        }
    }

    if (parentDirectoryName)
    {
        PvfsFreeFileName(parentDirectoryName);
    }
    if (baseFileName)
    {
        PvfsFreeFileName(baseFileName);
    }

     return ntError;
}

////////////////////////////////////////////////////////////////////////

NTSTATUS
PvfsLookupStreamDiskFileName(
    OUT PSTR* ppszDiskFilename,
    IN PPVFS_FILE_NAME pFileName
    )
{
    NTSTATUS ntError = STATUS_SUCCESS;
    PSTR pszDiskFilename = NULL;
    PSTR pszStreamDirname = NULL;

    PVFS_BAIL_ON_INVALID_FILENAME(pFileName, ntError);

    if (PvfsIsDefaultStreamName(pFileName))
    {
        ntError = LwRtlCStringDuplicate(&pszDiskFilename,
                                        PvfsGetCStringBaseFileName(pFileName));
        BAIL_ON_NT_STATUS(ntError);
    }
    else
    {
        ntError = PvfsLookupStreamDirectoryPath(&pszStreamDirname,
                                               pFileName);
        BAIL_ON_NT_STATUS(ntError);

        ntError = LwRtlCStringAllocatePrintf(
                      &pszDiskFilename,
                      "%s/%s",
                      pszStreamDirname,
                      PvfsGetCStringBaseStreamName(pFileName));
        BAIL_ON_NT_STATUS(ntError);
    }

    *ppszDiskFilename = pszDiskFilename;

cleanup:
    if (pszStreamDirname)
    {
        LwRtlCStringFree(&pszStreamDirname);
    }

    return ntError;

error:
    if (pszDiskFilename)
    {
        LwRtlCStringFree(&pszDiskFilename);
    }

    goto cleanup;
}

////////////////////////////////////////////////////////////////////////

NTSTATUS
PvfsEnumerateStreams(
    IN PPVFS_CCB pCcb,
    OUT PPVFS_FILE_NAME *ppStreamNames,
    OUT PLONG StreamCount
    )
{
    NTSTATUS ntError =  STATUS_SUCCESS;
    LONG streamNameListLength = 0;
    PPVFS_FILE_NAME streamNameList = NULL;
    PPVFS_FILE_NAME fileName = NULL;
    PPVFS_FILE_NAME parentDirectoryName = NULL;
    PPVFS_FILE_NAME baseFileName = NULL;
    PSTR pszTargetStreamDir = NULL;
    PPVFS_DIRECTORY_CONTEXT streamDirectoryContext = NULL;
    DIR *pDir = NULL;
    struct dirent *pDirEntry = NULL;
    struct dirent dirEntry = { 0 };
    LONG i = 0;
    LONG currentIndex = 0;

    if (!PvfsIsDefaultStream(pCcb->pScb))
    {
        // Enumeration is only valid on the base file object itself
        ntError = STATUS_INVALID_PARAMETER;
        BAIL_ON_NT_STATUS(ntError);
    }

    ntError = PvfsAllocateFileNameFromScb(&fileName, pCcb->pScb);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsSplitFileNamePath(
                  &parentDirectoryName,
                  &baseFileName,
                  fileName);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsLookupStreamDirectoryPath(&pszTargetStreamDir, fileName);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsAllocateMemory(
                  (PVOID*)&streamDirectoryContext,
                  sizeof(*streamDirectoryContext),
                  TRUE);
    BAIL_ON_NT_STATUS(ntError);

    ntError = PvfsSysOpenDir(
                  pszTargetStreamDir,
                  &streamDirectoryContext->pDir);
    if (ntError == STATUS_SUCCESS)
    {
        pDir = streamDirectoryContext->pDir;

        for (ntError = PvfsSysReadDir(pDir, &dirEntry, &pDirEntry);
             pDirEntry;
             ntError = PvfsSysReadDir(pDir, &dirEntry, &pDirEntry))
        {
            BAIL_ON_NT_STATUS(ntError);

            if (RtlCStringIsEqual(pDirEntry->d_name, ".", FALSE) ||
                RtlCStringIsEqual(pDirEntry->d_name, "..", FALSE))
            {
                continue;
            }

            ntError = PvfsDirContextAddEntry(streamDirectoryContext, pDirEntry->d_name);
            BAIL_ON_NT_STATUS(ntError);
        }
    }
    else if (STATUS_OBJECT_NAME_NOT_FOUND == ntError)
    {
        ntError = STATUS_SUCCESS;
    }
    BAIL_ON_NT_STATUS(ntError);

    if (!PVFS_IS_DIR(pCcb))
    {
        // Always include space for the default stream only for file not dir
        ntError = PvfsAllocateFileNameList(
                      &streamNameList,
                      streamDirectoryContext->dwNumEntries+1);
        BAIL_ON_NT_STATUS(ntError);

        ntError = PvfsAppendBuildFileName(
                      &streamNameList[currentIndex],
                      parentDirectoryName,
                      baseFileName);
        BAIL_ON_NT_STATUS(ntError);

        currentIndex++;
    }
    else if (streamDirectoryContext->dwNumEntries > 0)
    {
        ntError = PvfsAllocateFileNameList(
                      &streamNameList,
                      streamDirectoryContext->dwNumEntries);
        BAIL_ON_NT_STATUS(ntError);
    }

    for (i=0; i<streamDirectoryContext->dwNumEntries; i++)
    {
        ntError = PvfsAppendBuildFileName(
                      &streamNameList[currentIndex],
                      parentDirectoryName,
                      baseFileName);
        BAIL_ON_NT_STATUS(ntError);

        ntError = PvfsCopyStreamFileNameFromCString(
                      &streamNameList[currentIndex],
                      streamDirectoryContext->pDirEntries[i].pszFilename);
        BAIL_ON_NT_STATUS(ntError);

        currentIndex++;
    }

error:
    if (!NT_SUCCESS(ntError))
    {
        if (streamNameList)
        {
            PvfsFreeFileNameList(streamNameList, streamNameListLength);
        }
        currentIndex = 0;
        streamNameList = NULL;
    }

    *ppStreamNames = streamNameList;
    *StreamCount = currentIndex;

    if (pszTargetStreamDir)
    {
        LwRtlCStringFree(&pszTargetStreamDir);
    }

    if (parentDirectoryName)
    {
        PvfsFreeFileName(parentDirectoryName);
    }
    if (baseFileName)
    {
        PvfsFreeFileName(baseFileName);
    }
    if (fileName)
    {
        PvfsFreeFileName(fileName);
    }


    if (pDir)
    {
        PvfsSysCloseDir(pDir);
        streamDirectoryContext->pDir = NULL;
    }
    PvfsFreeDirectoryContext(streamDirectoryContext);

    return ntError;
}

////////////////////////////////////////////////////////////////////////

NTSTATUS
PvfsRemoveStreams(
    IN PPVFS_CCB pCcb
    )
{
    NTSTATUS ntError = STATUS_SUCCESS;
    PPVFS_FILE_NAME streamList = NULL;
    LONG streamCount = 0;
    LONG i = 0;

    ntError = PvfsEnumerateStreams(pCcb, &streamList, &streamCount);
    BAIL_ON_NT_STATUS(ntError);

    for (i=0; i<streamCount; i++)
    {
        // TODO: This likely needs support from an internal delete-pending
        // mechanism.  We'll assume for now that the share mode checks
        // are a safety net, but there could be open handles to these
        // stream still

        if (!PvfsIsDefaultStreamName(&streamList[i]))
        {
            // Only delete named streams
            ntError = PvfsSysRemoveByFileName(&streamList[i]);
            BAIL_ON_NT_STATUS(ntError);
        }
    }

    ntError = STATUS_SUCCESS;

error:
    if (streamList)
    {
        PvfsFreeFileNameList(streamList, streamCount);
    }

    return ntError;
}
