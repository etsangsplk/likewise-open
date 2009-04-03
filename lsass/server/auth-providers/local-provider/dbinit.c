/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * -*- mode: c, c-basic-offset: 4 -*- */

/*
 * Copyright Likewise Software    2004-2008
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
 *        lsassdb.c
 *
 * Abstract:
 *
 *        Likewise Security and Authentication Subsystem (LSASS)
 *
 *        Local Authentication Provider
 *
 *        User/Group Database Interface
 *
 * Authors: Krishna Ganugapati (krishnag@likewisesoftware.com)
 *          Sriram Nambakam (snambakam@likewisesoftware.com)
 */
#include "localprovider.h"

#define LW_ACCOUNT_DISABLED       1
#define LW_CANNOT_CHANGE_PASSWORD (1 << 1)
#define LW_PASSWORD_CANNOT_EXPIRE (1 << 2)
#define LW_ACCOUNT_LOCKED_OUT     (1 << 3)

#define LOCAL_USER_SID_FORMAT "S-1-22-1-%ld"
#define LOCAL_GROUP_SID_FORMAT "S-1-22-2-%ld"

void
LsaLPDbInitGlobals(
    void
    )
{
    pthread_rwlock_init(&g_dbLock, NULL);
}

//
// TODO: Implement a DB Handle Pool
//
DWORD
LsaLPDbOpen(
    PHANDLE phDb
    )
{
    DWORD dwError = 0;
    sqlite3* pDbHandle = NULL;

    dwError = sqlite3_open(LSASS_DB, &pDbHandle);
    BAIL_ON_LSA_ERROR(dwError);

    *phDb = (HANDLE)pDbHandle;

cleanup:

    return dwError;

error:

    *(phDb) = (HANDLE)NULL;

    if (pDbHandle) {
        sqlite3_close(pDbHandle);
    }

    goto cleanup;
}

void
LsaLPDbClose(
    HANDLE hDb
    )
{
    sqlite3* pDbHandle = (sqlite3*)hDb;
    if (pDbHandle) {
       sqlite3_close(pDbHandle);
    }
}

DWORD
LsaLPDbCreate(
    void
    )
{
    DWORD dwError = 0;
    HANDLE hDb = (HANDLE)NULL;
    sqlite3* pDbHandle = NULL;
    PSTR pszError = NULL;
    BOOLEAN bExists = FALSE;

    dwError = LsaCheckFileExists(LSASS_DB, &bExists);
    BAIL_ON_LSA_ERROR(dwError);

    // TODO: Implement an upgrade scenario
    if (bExists) {
       goto cleanup;
    }

    dwError = LsaCheckDirectoryExists(LSASS_DB_DIR, &bExists);
    BAIL_ON_LSA_ERROR(dwError);

    if (!bExists) {
        mode_t cacheDirMode = S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;

        /* Allow go+rx to the base LSASS folder */
        dwError = LsaCreateDirectory(LSASS_DB_DIR, cacheDirMode);
        BAIL_ON_LSA_ERROR(dwError);
    }

    /* restrict access to u+rwx to the db folder */
    dwError = LsaChangeOwnerAndPermissions(LSASS_DB_DIR, 0, 0, S_IRWXU);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = LsaLPDbOpen(&hDb);
    BAIL_ON_LSA_ERROR(dwError);

    pDbHandle = (sqlite3*)hDb;

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_GROUPMEMBERSHIP_TABLE,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_GROUPS_TABLE,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_GROUPS_INSERT_TRIGGER,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_GROUPS_DELETE_TRIGGER,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_USERS_TABLE,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_USERS_INSERT_TRIGGER,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = sqlite3_exec(pDbHandle,
                           DB_QUERY_CREATE_USERS_DELETE_TRIGGER,
                           NULL,
                           NULL,
                           &pszError);
    BAIL_ON_LSA_ERROR(dwError);

    dwError = LsaChangeOwnerAndPermissions(LSASS_DB, 0, 0, S_IRWXU);
    BAIL_ON_LSA_ERROR(dwError);

cleanup:

    if (hDb != (HANDLE)NULL) {
       LsaLPDbClose(hDb);
    }

    return dwError;

error:

    if (!IsNullOrEmptyString(pszError)) {
       LSA_LOG_ERROR("%s", pszError);
    }

    goto cleanup;
}
