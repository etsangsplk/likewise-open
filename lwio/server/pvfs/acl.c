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


/*
 * Copyright (C) Likewise Software. All rights reserved.
 *
 * Module Name:
 *
 *        acl.c
 *
 * Abstract:
 *
 *        Likewise Posix File System Driver (PVFS)
 *
 *        Supporting ACL routines
 *
 * Authors: Gerald Carter <gcarter@likewise.com>
 */

#include "pvfs.h"

/* Forward declarations */

static NTSTATUS
CreateDefaultSecDescFile(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDesc,
    IN OUT PULONG pSecDescLen
    );

static NTSTATUS
CreateDefaultSecDescDir(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDesc,
    IN OUT PULONG pSecDescLen
    );

static NTSTATUS
CreateDefaultSecDesc(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDescRelative,
    IN OUT PULONG pSecDescLen,
    BOOLEAN bIsDirectory
    );

static NTSTATUS
BuildDefaultDaclFile(
    PACL *ppDacl
    );

static NTSTATUS
BuildDefaultDaclDirectory(
    PACL *ppDacl
    );


/* File Globals */



/* Code */

/****************************************************************
 ***************************************************************/

NTSTATUS
PvfsGetSecurityDescriptorFile(
    IN PPVFS_CCB pCcb,
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDesc,
    IN OUT PULONG pSecDescLen
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;

#ifdef HAVE_EA_SUPPORT
    ntError = PvfsGetSecurityDescriptorFileXattr(pCcb,
                                                 SecInfo,
                                                 pSecDesc,
                                                 pSecDescLen);
#endif
    /* Fallback to generating a default secdesc */

    if (!NT_SUCCESS(ntError))
    {
        if (pCcb->CreateOptions & FILE_DIRECTORY_FILE) {
            ntError = CreateDefaultSecDescDir(SecInfo, pSecDesc, pSecDescLen);
        } else {
            ntError = CreateDefaultSecDescFile(SecInfo, pSecDesc, pSecDescLen);
        }
        BAIL_ON_NT_STATUS(ntError);
    }

    ntError = STATUS_SUCCESS;

cleanup:
    return ntError;

error:
    goto cleanup;

}

/****************************************************************
 ***************************************************************/

NTSTATUS
PvfsSetSecurityDescriptorFile(
    IN PPVFS_CCB pCcb,
    IN SECURITY_INFORMATION SecInfo,
    IN PSECURITY_DESCRIPTOR_RELATIVE pSecDescRelative,
    IN ULONG SecDescLen
    )
{
    NTSTATUS ntError = STATUS_ACCESS_DENIED;

#ifdef HAVE_EA_SUPPORT
    ntError = PvfsSetSecurityDescriptorFileXattr(pCcb,
                                                 SecInfo,
                                                 pSecDescRelative,
                                                 SecDescLen);
#endif
    BAIL_ON_NT_STATUS(ntError);

cleanup:
    return ntError;

error:
    goto cleanup;
}

/****************************************************************
 ***************************************************************/

VOID
PvfsFreeAbsoluteSecurityDescriptor(
    IN OUT PSECURITY_DESCRIPTOR_ABSOLUTE pSecDesc
    )
{
    /* Fixme:  Actually free the SD */
    return;
}


/****************************************************************
 ***************************************************************/

static NTSTATUS
CreateDefaultSecDescFile(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDesc,
    IN OUT PULONG pSecDescLen
    )
{
    return CreateDefaultSecDesc(SecInfo,
                                pSecDesc,
                                pSecDescLen,
                                FALSE /* not a directory */);
}

/****************************************************************
 ***************************************************************/

static NTSTATUS
CreateDefaultSecDescDir(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDesc,
    IN OUT PULONG pSecDescLen
    )
{
    return CreateDefaultSecDesc(SecInfo,
                                pSecDesc,
                                pSecDescLen,
                                TRUE /* is a directory */);
}

/****************************************************************
 ***************************************************************/

static NTSTATUS
CreateDefaultSecDesc(
    IN SECURITY_INFORMATION SecInfo,
    IN OUT PSECURITY_DESCRIPTOR_RELATIVE pSecDescRelative,
    IN OUT PULONG pSecDescLen,
    BOOLEAN bIsDirectory
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;
    PSECURITY_DESCRIPTOR_ABSOLUTE pSecDesc = NULL;
    PACL pDacl = NULL;
    PSID pSid = NULL;

    ntError= PvfsAllocateMemory((PVOID*)&pSecDesc,
                                SECURITY_DESCRIPTOR_ABSOLUTE_MIN_SIZE);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlCreateSecurityDescriptorAbsolute(pSecDesc,
                                                  SECURITY_DESCRIPTOR_REVISION);
    BAIL_ON_NT_STATUS(ntError);

    if (SecInfo & OWNER_SECURITY_INFORMATION)
    {
        /* Administrators */

        ntError = RtlAllocateSidFromCString(&pSid, "S-1-5-32-544");
        BAIL_ON_NT_STATUS(ntError);

        ntError = RtlSetOwnerSecurityDescriptor(pSecDesc,
                                                pSid,
                                                FALSE);
        BAIL_ON_NT_STATUS(ntError);

        pSid = NULL;
    }

    if (SecInfo & GROUP_SECURITY_INFORMATION)
    {
        /* Power Users */

        ntError = RtlAllocateSidFromCString(&pSid, "S-1-5-32-547");
        BAIL_ON_NT_STATUS(ntError);

        ntError = RtlSetGroupSecurityDescriptor(pSecDesc,
                                                pSid,
                                                FALSE);
        BAIL_ON_NT_STATUS(ntError);

        pSid = NULL;
    }

    if (SecInfo & DACL_SECURITY_INFORMATION)
    {
        if (bIsDirectory) {
            ntError = BuildDefaultDaclDirectory(&pDacl);
            BAIL_ON_NT_STATUS(ntError);
        } else {
            ntError = BuildDefaultDaclFile(&pDacl);
            BAIL_ON_NT_STATUS(ntError);
        }

        ntError = RtlSetDaclSecurityDescriptor(pSecDesc,
                                               TRUE,
                                               pDacl,
                                               FALSE);
        BAIL_ON_NT_STATUS(ntError);

        pDacl = NULL;
    }

    /* We don't do SACLs currently */

    /* All done */

    ntError = RtlAbsoluteToSelfRelativeSD(pSecDesc,
                                          pSecDescRelative,
                                          pSecDescLen);
    BAIL_ON_NT_STATUS(ntError);

cleanup:
    if (pSecDesc) {
        PvfsFreeAbsoluteSecurityDescriptor(pSecDesc);
    }

    return ntError;

error:

    PVFS_SAFE_FREE_MEMORY(pDacl);

    /* Use RtlFree for SIDs */
    RTL_FREE(&pSid);

    goto cleanup;
}

/****************************************************************
 ***************************************************************/

static NTSTATUS
BuildDefaultDaclFile(
    PACL *ppDacl
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;
    DWORD dwSizeDacl = 0;
    PSID pAdministratorsSid = NULL;
    PSID pUsersSid = NULL;
    PSID pEveryoneSid = NULL;
    DWORD dwSidCount = 0;
    PACL pDacl = NULL;

    /* Build SIDs */

    ntError = RtlAllocateSidFromCString(&pAdministratorsSid, "S-1-5-32-544");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    ntError = RtlAllocateSidFromCString(&pUsersSid, "S-1-5-32-545");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    ntError = RtlAllocateSidFromCString(&pEveryoneSid, "S-1-1-0");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    dwSizeDacl = ACL_HEADER_SIZE +
        dwSidCount * sizeof(ACCESS_ALLOWED_ACE) +
        RtlLengthSid(pAdministratorsSid) +
        RtlLengthSid(pUsersSid) +
        RtlLengthSid(pEveryoneSid) -
        dwSidCount * sizeof(ULONG);

    ntError= PvfsAllocateMemory((PVOID*)&pDacl, dwSizeDacl);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlCreateAcl(pDacl, dwSizeDacl, ACL_REVISION);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       0,
                                       FILE_ALL_ACCESS,
                                       pAdministratorsSid);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       0,
                                       FILE_GENERIC_WRITE | FILE_GENERIC_READ,
                                       pUsersSid);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       0,
                                       FILE_GENERIC_READ,
                                       pEveryoneSid);
    BAIL_ON_NT_STATUS(ntError);

    *ppDacl = pDacl;
    ntError = STATUS_SUCCESS;

cleanup:
    /* Use RtlFree for SIDs */

    RTL_FREE(&pAdministratorsSid);
    RTL_FREE(&pUsersSid);
    RTL_FREE(&pEveryoneSid);

    return ntError;

error:
    PVFS_SAFE_FREE_MEMORY(pDacl);

    goto cleanup;
}

/****************************************************************
 ***************************************************************/

static NTSTATUS
BuildDefaultDaclDirectory(
    PACL *ppDacl
    )
{
    NTSTATUS ntError = STATUS_UNSUCCESSFUL;
    DWORD dwSizeDacl = 0;
    PSID pAdministratorsSid = NULL;
    PSID pUsersSid = NULL;
    PSID pEveryoneSid = NULL;
    PSID pCreatorOwnerSid = NULL;
    DWORD dwSidCount = 0;
    PACL pDacl = NULL;

    /* Build SIDs */

    ntError = RtlAllocateSidFromCString(&pAdministratorsSid, "S-1-5-32-544");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    ntError = RtlAllocateSidFromCString(&pUsersSid, "S-1-5-32-545");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    ntError = RtlAllocateSidFromCString(&pEveryoneSid, "S-1-1-0");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    ntError = RtlAllocateSidFromCString(&pCreatorOwnerSid, "S-1-3-0");
    BAIL_ON_NT_STATUS(ntError);
    dwSidCount++;

    dwSizeDacl = ACL_HEADER_SIZE +
        dwSidCount * sizeof(ACCESS_ALLOWED_ACE) +
        RtlLengthSid(pAdministratorsSid) +
        RtlLengthSid(pUsersSid) +
        RtlLengthSid(pEveryoneSid) +
        RtlLengthSid(pCreatorOwnerSid) -
        dwSidCount * sizeof(ULONG);

    ntError= PvfsAllocateMemory((PVOID*)&pDacl, dwSizeDacl);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlCreateAcl(pDacl, dwSizeDacl, ACL_REVISION);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE,
                                       FILE_ALL_ACCESS,
                                       pAdministratorsSid);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE,
                                       FILE_GENERIC_WRITE | FILE_GENERIC_READ,
                                       pUsersSid);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       0,
                                       FILE_GENERIC_READ,
                                       pEveryoneSid);
    BAIL_ON_NT_STATUS(ntError);

    ntError = RtlAddAccessAllowedAceEx(pDacl,
                                       ACL_REVISION,
                                       OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
                                       FILE_ALL_ACCESS,
                                       pCreatorOwnerSid);
    BAIL_ON_NT_STATUS(ntError);

    *ppDacl = pDacl;
    ntError = STATUS_SUCCESS;

cleanup:
    /* Use RtlFree for SIDs */

    RTL_FREE(&pAdministratorsSid);
    RTL_FREE(&pUsersSid);
    RTL_FREE(&pEveryoneSid);
    RTL_FREE(&pCreatorOwnerSid);

    return ntError;

error:
    PVFS_SAFE_FREE_MEMORY(pDacl);

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

