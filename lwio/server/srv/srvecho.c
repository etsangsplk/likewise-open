/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * -*- mode: c, c-basic-offset: 4 -*- */

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

#include "includes.h"

static
NTSTATUS
SrvMarshallEchoResponse(
    PSMB_SRV_CONNECTION pConnection,
    PSMB_PACKET         pSmbResponse,
    USHORT              usUid,
    USHORT              usMid,
    USHORT              usSequenceNumber,
    PBYTE               pEchoBlob,
    USHORT              ulEchoBlobLength
    );

NTSTATUS
SrvProcessEchoAndX(
    PLWIO_SRV_CONTEXT pContext
    )
{
    NTSTATUS ntStatus = 0;
    USHORT   iEchoCount = 0;
    PSMB_PACKET pSmbResponse = NULL;
    PECHO_REQUEST_HEADER pEchoHeader = NULL; // Do not Free
    PBYTE       pEchoBlob = NULL; // Do Not Free
    PSMB_SRV_CONNECTION pConnection = pContext->pConnection;
    PSMB_PACKET         pSmbRequest = pContext->pRequest;

    ntStatus = WireUnmarshallEchoRequest(
                    pSmbRequest->pParams,
                    pSmbRequest->bufferLen - pSmbRequest->bufferUsed,
                    &pEchoHeader,
                    &pEchoBlob);
    BAIL_ON_NT_STATUS(ntStatus);

    // If echo count is zero, no response is sent
    if (!pEchoHeader->echoCount)
    {
        goto cleanup;
    }

    ntStatus = SMBPacketAllocate(
                        pConnection->hPacketAllocator,
                        &pSmbResponse);
    BAIL_ON_NT_STATUS(ntStatus);

    ntStatus = SMBPacketBufferAllocate(
                    pConnection->hPacketAllocator,
                    64 * 1024,
                    &pSmbResponse->pRawBuffer,
                    &pSmbResponse->bufferLen);
    BAIL_ON_NT_STATUS(ntStatus);

    for (; iEchoCount < pEchoHeader->echoCount; iEchoCount++)
    {
        SMBPacketResetBuffer(pSmbResponse);

        ntStatus = SrvMarshallEchoResponse(
                        pConnection,
                        pSmbResponse,
                        pSmbRequest->pSMBHeader->uid,
                        pSmbRequest->pSMBHeader->mid,
                        iEchoCount,
                        pEchoBlob,
                        pEchoHeader->byteCount);
        BAIL_ON_NT_STATUS(ntStatus);

        ntStatus = SrvConnectionWriteMessage(
                        pConnection,
                        pSmbResponse);
        BAIL_ON_NT_STATUS(ntStatus);
    }

cleanup:

    if (pSmbResponse)
    {
        SMBPacketFree(
            pConnection->hPacketAllocator,
            pSmbResponse);
    }

    return (ntStatus);

error:

    goto cleanup;
}

static
NTSTATUS
SrvMarshallEchoResponse(
    PSMB_SRV_CONNECTION pConnection,
    PSMB_PACKET         pSmbResponse,
    USHORT              usUid,
    USHORT              usMid,
    USHORT              usSequenceNumber,
    PBYTE               pEchoBlob,
    USHORT              usEchoBlobLength
    )
{
    NTSTATUS ntStatus = 0;
    PECHO_RESPONSE_HEADER pResponseHeader = NULL;
    PCSTR    pMinEchoBlob = "lwio";
    USHORT   usPackageByteCount = 0;

    ntStatus = SMBPacketMarshallHeader(
                pSmbResponse->pRawBuffer,
                pSmbResponse->bufferLen,
                COM_ECHO,
                0,
                TRUE,
                0,
                getpid(),
                usUid,
                usMid,
                FALSE,
                pSmbResponse);
    BAIL_ON_NT_STATUS(ntStatus);

    pSmbResponse->pSMBHeader->wordCount = 1;

    pResponseHeader = (ECHO_RESPONSE_HEADER*)pSmbResponse->pParams;
    pSmbResponse->pData = pSmbResponse->pParams + sizeof(ECHO_RESPONSE_HEADER);
    pSmbResponse->bufferUsed += sizeof(ECHO_RESPONSE_HEADER);

    pResponseHeader->sequenceNumber = usSequenceNumber;

    ntStatus = WireMarshallEchoResponseData(
                    pSmbResponse->pData,
                    pSmbResponse->bufferLen - pSmbResponse->bufferUsed,
                    (usEchoBlobLength > 4 ? pEchoBlob : (PBYTE)pMinEchoBlob),
                    (usEchoBlobLength > 4 ? usEchoBlobLength : strlen(pMinEchoBlob)),
                    &usPackageByteCount);
    BAIL_ON_NT_STATUS(ntStatus);

    pSmbResponse->pByteCount = &pResponseHeader->byteCount;
    *pSmbResponse->pByteCount = usPackageByteCount;
    pSmbResponse->bufferUsed += usPackageByteCount;

    ntStatus = SMBPacketMarshallFooter(pSmbResponse);
    BAIL_ON_NT_STATUS(ntStatus);

error:

    return ntStatus;
}

