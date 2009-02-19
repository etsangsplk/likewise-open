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
 *        smbfileapi.h
 *
 * Abstract:
 *
 *        SMB-specific API functions
 *
 * Authors: Krishna Ganugapati (krishnag@likewisesoftware.com)
 *          Brian Koropoff (bkoropoff@likewisesoftware.com)
 */

#ifndef __LW_IO_SMBFILEAPI_H__
#define __LW_IO_SMBFILEAPI_H__

#include <lwio/io-types.h>

LW_NTSTATUS
LwIoCtxGetSessionKey(
    LW_PIO_CONTEXT pContext,
    IO_FILE_HANDLE File,
    LW_PUSHORT pKeyLength,
    LW_PBYTE* ppKeyBuffer
    );

LW_NTSTATUS
LwIoCtxConnectNamedPipe(
    LW_PIO_CONTEXT pContext,
    IO_FILE_HANDLE File
    );

#ifndef LW_NO_THREADS

LW_NTSTATUS
LwIoGetSessionKey(
    IO_FILE_HANDLE File,
    LW_PUSHORT pKeyLength,
    LW_PBYTE* ppKeyBuffer
    );

LW_NTSTATUS
LwIoConnectNamedPipe(
    IO_FILE_HANDLE File
    );

#endif /* !LW_NO_THREADS */
    
#ifndef LW_STRICT_NAMESPACE

#define IoCtxGetSessionKey LwIoCtxGetSessionKey
#define IoCtxCreateNamedPipe LwIoCtxCreateNamedPipe

#ifndef LW_NO_THREADS

#define IoGetSessionKey LwIoGetSessionKey
#define IoCreateNamedPipe LwIoCreateNamedPipe

#endif /* !LW_NO_THREADS */

#endif /* !LW_STRICT_NAMESPACE */

#endif /* !__LW_IO_SMBFILEAPI_H__ */
