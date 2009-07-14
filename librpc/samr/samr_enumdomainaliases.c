/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 */

/*
 * Copyright Likewise Software    2004-2008
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the license, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.  You should have received a copy
 * of the GNU Lesser General Public License along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 *
 * LIKEWISE SOFTWARE MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING
 * TERMS AS WELL.  IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT
 * WITH LIKEWISE SOFTWARE, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE
 * TERMS OF THAT SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE GNU
 * LESSER GENERAL PUBLIC LICENSE, NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU
 * HAVE QUESTIONS, OR WISH TO REQUEST A COPY OF THE ALTERNATE LICENSING
 * TERMS OFFERED BY LIKEWISE SOFTWARE, PLEASE CONTACT LIKEWISE SOFTWARE AT
 * license@likewisesoftware.com
 */

/*
 * Copyright (C) Likewise Software. All rights reserved.
 *
 * Module Name:
 *
 *        samr_enumdomainaliases.c
 *
 * Abstract:
 *
 *        Remote Procedure Call (RPC) Client Interface
 *
 *        SamrEnumDomainAliases function
 *
 * Authors: Rafal Szczesniak (rafal@likewise.com)
 */

#include "includes.h"


NTSTATUS
SamrEnumDomainAliases(
    IN  handle_t      hSamrBinding,
    IN  PolicyHandle *phDomain,
    IN  PUINT32       pResume,
    IN  UINT32        AccountFlags,
    OUT PWSTR       **pppwszNames,
    OUT PUINT32      *ppRids,
    OUT PUINT32       pCount
    )
{
    NTSTATUS ntStatus = STATUS_SUCCESS;
    NTSTATUS ntRetStatus = STATUS_SUCCESS;
    UINT32 Count = 0;
    UINT32 Resume = 0;
    RidNameArray *pEntries = NULL;
    PWSTR *ppwszNames = NULL;
    UINT32 *pRids = NULL;

    BAIL_ON_INVALID_PTR(hSamrBinding, ntStatus);
    BAIL_ON_INVALID_PTR(phDomain, ntStatus);
    BAIL_ON_INVALID_PTR(pResume, ntStatus);
    BAIL_ON_INVALID_PTR(pppwszNames, ntStatus);
    BAIL_ON_INVALID_PTR(ppRids, ntStatus);
    BAIL_ON_INVALID_PTR(pCount, ntStatus);

    Resume = *pResume;

    DCERPC_CALL(ntStatus, _SamrEnumDomainAliases(hSamrBinding,
                                                 phDomain,
                                                 &Resume,
                                                 AccountFlags,
                                                 &pEntries,
                                                 &Count));

    /* Preserve returned status code */
    ntRetStatus = ntStatus;

    /* Status other than success doesn't have to mean failure here */
    if (ntStatus != STATUS_SUCCESS &&
        ntStatus != STATUS_MORE_ENTRIES) {
        BAIL_ON_NT_STATUS(ntStatus);
    }

    if (pEntries) {
        ntStatus = SamrAllocateNamesAndRids(&ppwszNames,
                                            &pRids,
                                            pEntries);
        BAIL_ON_NT_STATUS(ntStatus);
    }

    *pResume     = Resume;
    *pCount      = Count;
    *pppwszNames = ppwszNames;
    *ppRids      = pRids;

cleanup:
    if (pEntries) {
        SamrFreeStubRidNameArray(pEntries);
    }

    if (ntStatus == STATUS_SUCCESS &&
        (ntRetStatus == STATUS_SUCCESS ||
         ntRetStatus == STATUS_MORE_ENTRIES)) {
        ntStatus = ntRetStatus;
    }

    return ntStatus;

error:
    if (ppwszNames) {
        SamrFreeMemory((void*)ppwszNames);
    }

    if (pRids) {
        SamrFreeMemory((void*)pRids);
    }

    *pResume     = 0;
    *pCount      = 0;
    *pppwszNames = NULL;
    *ppRids      = NULL;
    goto cleanup;
}


/*
local variables:
mode: c
c-basic-offset: 4
indent-tabs-mode: nil
tab-width: 4
end:
*/
