/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 */

/*
 * Copyright Likewise Software    2004-2009
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
 *        samr_contexthandle.h
 *
 * Abstract:
 *
 *        Remote Procedure Call (RPC) Server Interface
 *
 *        Samr context handles
 *
 * Authors: Rafal Szczesniak (rafal@likewise.com)
 */

#ifndef _SAMR_CONTEXT_HANDLE_H_
#define _SAMR_CONTEXT_HANDLE_H_


enum SamrContextType {
    SamrContextConnect = 0,
    SamrContextDomain,
    SamrContextAccount
};


typedef struct samr_generic_context {
    enum SamrContextType    Type;
    LONG                    refcount;
} SAMR_GENERIC_CONTEXT, *PSAMR_GENERIC_CONTEXT;


typedef struct samr_connect_context {
    enum SamrContextType    Type;
    LONG                    refcount;
    PACCESS_TOKEN           pUserToken;
    HANDLE                  hDirectory;
} CONNECT_CONTEXT, *PCONNECT_CONTEXT;


typedef struct samr_domain_context {
    enum SamrContextType Type;
    LONG                 refcount;
    PWSTR                pwszDn;
    PWSTR                pwszDomainName;
    PSID                 pDomainSid;
    PCONNECT_CONTEXT     pConnCtx;
} DOMAIN_CONTEXT, *PDOMAIN_CONTEXT;


typedef struct samr_account_context {
    enum SamrContextType Type;
    LONG                 refcount;
    PWSTR                pwszName;
    DWORD                dwRid;
    PSID                 pSid;
    DWORD                dwAccountType;
    PDOMAIN_CONTEXT      pDomCtx;
} ACCOUNT_CONTEXT, *PACCOUNT_CONTEXT;


void
CONNECT_HANDLE_rundown(
    void *hContext
    );


void
DOMAIN_HANDLE_rundown(
    void *hContext
    );


void
ACCOUNT_HANDLE_rundown(
    void *hContext
    );


#endif /* _SAMR_CONTEXT_HANDLE_H_ */


/*
local variables:
mode: c
c-basic-offset: 4
indent-tabs-mode: nil
tab-width: 4
end:
*/
