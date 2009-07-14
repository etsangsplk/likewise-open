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
 * Abstract: SrvSvc interface binding (srvsvc component)
 *
 * Authors: Rafal Szczesniak (rafal@likewisesoftware.com)
 */

#include "includes.h"


RPCSTATUS
InitSrvSvcBindingDefault(
    handle_t         *phSrvSvcBinding,
    PCSTR             pszHostname,
    PIO_ACCESS_TOKEN  pAccessToken
    )
{
    RPCSTATUS rpcstatus = RPC_S_OK;
    char *prot_seq = (char*)SRVSVC_DEFAULT_PROT_SEQ;
    char *endpoint = (char*)SRVSVC_DEFAULT_ENDPOINT;
    char *uuid = NULL;
    char *options = NULL;
    handle_t hSrvSvcBinding = NULL;

    rpcstatus = InitSrvSvcBindingFull(&hSrvSvcBinding,
                                      prot_seq, pszHostname, endpoint,
                                      uuid, options, pAccessToken);
    goto_if_rpcstatus_not_success(rpcstatus, error);

    *phSrvSvcBinding = hSrvSvcBinding;

cleanup:
    return rpcstatus;

error:
    *phSrvSvcBinding = NULL;

    goto cleanup;
}


RPCSTATUS
InitSrvSvcBindingFull(
    handle_t *phSrvSvcBinding,
    const char *prot_seq,
    const char *hostname,
    const char *endpoint,
    const char *uuid,
    const char *options,
    PIO_ACCESS_TOKEN pAccessToken
    )
{
    RPCSTATUS rpcstatus = RPC_S_OK;
    RPCSTATUS st = RPC_S_OK;
    unsigned char *binding_string = NULL;
    unsigned char *ps   = NULL;
    unsigned char *ep   = NULL;
    unsigned char *u    = NULL;
    unsigned char *opts = NULL;
    unsigned char *addr = NULL;
    handle_t hSrvSvcBinding = NULL;
    rpc_transport_info_handle_t info;

    goto_if_invalid_param_rpcstatus(phSrvSvcBinding, cleanup);
    goto_if_invalid_param_rpcstatus(hostname, cleanup);
    goto_if_invalid_param_rpcstatus(prot_seq, cleanup);

    ps = (unsigned char*) strdup(prot_seq);
    goto_if_no_memory_rpcstatus(ps, error);

    if (endpoint != NULL) {
        ep = (unsigned char*) strdup(endpoint);
        goto_if_no_memory_rpcstatus(ep, error);
    }

    if (uuid != NULL) {
        u = (unsigned char*) strdup(uuid);
        goto_if_no_memory_rpcstatus(u, error);
    }

    if (options != NULL) {
        opts = (unsigned char*) strdup(options);
        goto_if_no_memory_rpcstatus(opts, error);
    }

    addr = (unsigned char*) strdup(hostname);
    goto_if_no_memory_rpcstatus(addr, error);

    rpc_string_binding_compose(u, ps, addr, ep, opts, &binding_string,
                               &rpcstatus);
    goto_if_rpcstatus_not_success(rpcstatus, error);

    rpc_binding_from_string_binding(binding_string, &hSrvSvcBinding,
                                    &rpcstatus);
    goto_if_rpcstatus_not_success(rpcstatus, error);

    rpc_smb_transport_info_from_lwio_token(pAccessToken,
                                           FALSE,
                                           &info,
                                           &rpcstatus);
    goto_if_rpcstatus_not_success(rpcstatus, error);
    
    rpc_binding_set_transport_info(hSrvSvcBinding,
                                   info,
                                   &rpcstatus);
    goto_if_rpcstatus_not_success(rpcstatus, error);

	info = NULL;

    rpc_ep_resolve_binding(hSrvSvcBinding, srvsvc_v3_0_c_ifspec, &rpcstatus);
    goto_if_rpcstatus_not_success(rpcstatus, error);

    *phSrvSvcBinding = hSrvSvcBinding;

cleanup:
    SAFE_FREE(ps);
    SAFE_FREE(ep);
    SAFE_FREE(u);
    SAFE_FREE(opts);
    SAFE_FREE(addr);

    if (binding_string) {
        rpc_string_free(&binding_string, &st);
    }

    if (rpcstatus == RPC_S_OK &&
        st != RPC_S_OK) {
        rpcstatus = st;
    }

    return rpcstatus;

error:
    if (hSrvSvcBinding) {
        rpc_binding_free(&hSrvSvcBinding, &st);
    }

    *phSrvSvcBinding = NULL;

    goto cleanup;
}


RPCSTATUS
FreeSrvSvcBinding(
    handle_t *binding
    )
{
    RPCSTATUS rpcstatus = RPC_S_OK;

    /* Free the binding itself */
    if (binding && *binding) {
	    rpc_binding_free(binding, &rpcstatus);
        goto_if_rpcstatus_not_success(rpcstatus, done);
    }

done:
    return rpcstatus;
}


/*
local variables:
mode: c
c-basic-offset: 4
indent-tabs-mode: nil
tab-width: 4
end:
*/
