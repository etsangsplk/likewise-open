/*
 * Copyright (c) Likewise Software.  All rights Reserved.
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
 * Module Name:
 *
 *        ntstatus-table.h
 *
 * Abstract:
 *
 *        NT status code information table
 *
 * Authors: Brian Koropoff (bkoropoff@likewisesoftware.com)
 *
 */

#define S NTSTATUS_CODE
S ( STATUS_SUCCESS, 0, "Success" )
S ( STATUS_MORE_ENTRIES, EAGAIN, "More data available" )
S ( STATUS_NOT_IMPLEMENTED, ENOTSUP, NULL )
S ( STATUS_INVALID_INFO_CLASS, -1, NULL )
S ( STATUS_INVALID_PARAMETER, EINVAL, "Invalid parameter passed" )
S ( STATUS_NO_MEMORY, ENOMEM, "Out of memory" )
S ( STATUS_INVALID_SID, EINVAL, NULL )
S ( STATUS_INSUFFICIENT_RESOURCES, ENOSPC, NULL )
S ( STATUS_UNHANDLED_EXCEPTION, -1, NULL )
S ( STATUS_ACCESS_DENIED, EACCES, "Access denied" )
S ( STATUS_NONE_MAPPED, -1, "Specified account has no mapping to a valid SID" )
S ( STATUS_CONNECTION_REFUSED, -1, NULL )
S ( STATUS_INVALID_ADDRESS, EFAULT, NULL )
S ( STATUS_INTERNAL_ERROR, -1, "Internal error" )
S ( STATUS_SOURCE_ELEMENT_EMPTY, -1, NULL )
S ( STATUS_WORKING_SET_QUOTA, -1, NULL )
S ( STATUS_DISK_CORRUPT_ERROR, -1, NULL )
S ( STATUS_COULD_NOT_INTERPRET, -1, NULL )
S ( STATUS_FILE_CORRUPT_ERROR, -1, NULL )
S ( STATUS_NOT_MAPPED_DATA, -1, NULL )
S ( STATUS_COMMITMENT_LIMIT, -1, NULL )
S ( STATUS_DLL_INIT_FAILED_LOGOFF, -1, NULL )
S ( STATUS_NO_TRUST_LSA_SECRET, -1, NULL )
S ( STATUS_DS_ADMIN_LIMIT_EXCEEDED, -1, NULL )
S ( STATUS_BUFFER_TOO_SMALL, -1, NULL )
S ( STATUS_NETLOGON_NOT_STARTED, -1, NULL )
S ( STATUS_FT_ORPHANING, -1, NULL )
S ( STATUS_UNHANDLED_EXCEPTION, -1, NULL )
S ( STATUS_DS_HAVE_PRIMARY_MEMBERS, -1, NULL )
S ( STATUS_LUIDS_EXHAUSTED, -1, NULL )
S ( STATUS_FLOAT_MULTIPLE_TRAPS, -1, NULL )
S ( STATUS_PIPE_EMPTY, -1, NULL )
S ( STATUS_WMI_INSTANCE_NOT_FOUND, -1, NULL )
S ( STATUS_FT_MISSING_MEMBER, -1, NULL )
S ( STATUS_FS_DRIVER_REQUIRED, -1, NULL )
S ( STATUS_PROPSET_NOT_FOUND, -1, NULL )
S ( STATUS_NO_MEDIA, -1, NULL )
S ( STATUS_BAD_DEVICE_TYPE, -1, NULL )
S ( STATUS_INVALID_GROUP_ATTRIBUTES, -1, NULL )
S ( STATUS_CANT_DISABLE_MANDATORY, -1, NULL )
S ( STATUS_POLICY_ONLY_IN_DS, -1, NULL )
S ( STATUS_VOLUME_NOT_UPGRADED, -1, NULL )
S ( STATUS_PASSWORD_EXPIRED, -1, NULL )
S ( STATUS_DISK_RESET_FAILED, -1, NULL )
S ( STATUS_TRANSACTION_NO_RELEASE, -1, NULL )
S ( STATUS_PNP_RESTART_ENUMERATION, -1, NULL )
S ( STATUS_INVALID_IMAGE_FORMAT, -1, NULL )
S ( STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY, -1, NULL )
S ( STATUS_INVALID_PARAMETER_10, -1, NULL )
S ( STATUS_NO_SUCH_GROUP, -1, NULL )
S ( STATUS_INVALID_MEMBER, -1, "Requested member is invalid" )
S ( STATUS_INVALID_SECURITY_DESCR, -1, NULL )
S ( STATUS_OBJECT_PATH_SYNTAX_BAD, -1, NULL )
S ( STATUS_DOMAIN_CTRLR_CONFIG_ERROR, -1, NULL )
S ( STATUS_MEMORY_NOT_ALLOCATED, -1, NULL )
S ( STATUS_VIRTUAL_CIRCUIT_CLOSED, -1, NULL )
S ( STATUS_REQUEST_NOT_ACCEPTED, -1, NULL )
S ( STATUS_ABIOS_LID_NOT_EXIST, -1, NULL )
S ( STATUS_NO_MATCH, -1, NULL )
S ( STATUS_REPLY_MESSAGE_MISMATCH, -1, NULL )
S ( STATUS_MUTANT_NOT_OWNED, -1, NULL )
S ( STATUS_REGISTRY_QUOTA_LIMIT, -1, NULL )
S ( STATUS_UNEXPECTED_MM_CREATE_ERR, -1, NULL )
S ( STATUS_PROCEDURE_NOT_FOUND, -1, NULL )
S ( STATUS_UNRECOGNIZED_MEDIA, -1, NULL )
S ( STATUS_INVALID_LDT_SIZE, -1, NULL )
S ( STATUS_INVALID_BLOCK_LENGTH, -1, NULL )
S ( STATUS_GUIDS_EXHAUSTED, -1, NULL )
S ( STATUS_DS_NO_ATTRIBUTE_OR_VALUE, -1, NULL )
S ( STATUS_SHARED_POLICY, -1, NULL )
S ( STATUS_RESOURCE_NAME_NOT_FOUND, -1, NULL )
S ( STATUS_INVALID_PARAMETER_8, -1, NULL )
S ( STATUS_DS_CANT_MOD_PRIMARYGROUPID, -1, NULL )
S ( STATUS_WMI_SET_FAILURE, -1, NULL )
S ( STATUS_INVALID_FILE_FOR_SECTION, -1, NULL )
S ( STATUS_NO_SUCH_ALIAS, -1, "Alias does not exist" )
S ( STATUS_NO_EFS, -1, NULL )
S ( STATUS_TOO_MANY_PAGING_FILES, -1, NULL )
S ( STATUS_SECTION_NOT_EXTENDED, -1, NULL )
S ( STATUS_NETWORK_UNREACHABLE, -1, NULL )
S ( STATUS_POSSIBLE_DEADLOCK, -1, NULL )
S ( STATUS_SECTION_TOO_BIG, -1, NULL )
S ( STATUS_CONNECTION_COUNT_LIMIT, -1, NULL )
S ( STATUS_DS_BUSY, -1, NULL )
S ( STATUS_UNABLE_TO_UNLOAD_MEDIA, -1, NULL )
S ( STATUS_DS_INVALID_ATTRIBUTE_SYNTAX, -1, NULL )
S ( STATUS_NO_SPOOL_SPACE, -1, NULL )
S ( STATUS_NOT_CLIENT_SESSION, -1, NULL )
S ( STATUS_INVALID_ACL, -1, NULL )
S ( STATUS_NOT_LOCKED, -1, NULL )
S ( STATUS_LOGIN_TIME_RESTRICTION, -1, NULL )
S ( STATUS_DEVICE_CONFIGURATION_ERROR, -1, NULL )
S ( STATUS_INSUFF_SERVER_RESOURCES, -1, NULL )
S ( STATUS_FILE_RENAMED, -1, NULL )
S ( STATUS_UNSUPPORTED_COMPRESSION, -1, NULL )
S ( STATUS_PROFILING_NOT_STARTED, -1, NULL )
S ( STATUS_REMOTE_SESSION_LIMIT, -1, NULL )
S ( STATUS_BAD_INITIAL_STACK, -1, NULL )
S ( STATUS_REINITIALIZATION_NEEDED, -1, NULL )
S ( STATUS_TOO_MANY_NODES, -1, NULL )
S ( STATUS_INVALID_PARAMETER_11, -1, NULL )
S ( STATUS_REGISTRY_CORRUPT, -1, NULL )
S ( STATUS_INVALID_PRIMARY_GROUP, -1, NULL )
S ( STATUS_TRUST_FAILURE, -1, NULL )
S ( STATUS_IO_DEVICE_ERROR, -1, NULL )
S ( STATUS_FILE_IS_OFFLINE, -1, NULL )
S ( STATUS_POWER_STATE_INVALID, -1, NULL )
S ( STATUS_RXACT_INVALID_STATE, -1, NULL )
S ( STATUS_PWD_TOO_SHORT, -1, NULL )
S ( STATUS_DRIVER_CANCEL_TIMEOUT, -1, NULL )
S ( STATUS_PAGEFILE_CREATE_FAILED, -1, NULL )
S ( STATUS_INVALID_UNWIND_TARGET, -1, NULL )
S ( STATUS_TOKEN_ALREADY_IN_USE, -1, NULL )
S ( STATUS_SYNCHRONIZATION_REQUIRED, -1, NULL )
S ( STATUS_CONVERT_TO_LARGE, -1, NULL )
S ( STATUS_ABIOS_INVALID_SELECTOR, -1, NULL )
S ( STATUS_DS_NO_RIDS_ALLOCATED, -1, NULL )
S ( STATUS_NO_USER_SESSION_KEY, -1, NULL )
S ( STATUS_NETWORK_ACCESS_DENIED, -1, NULL )
S ( STATUS_INVALID_NETWORK_RESPONSE, -1, NULL )
S ( STATUS_INVALID_QUOTA_LOWER, -1, NULL )
S ( STATUS_BAD_MASTER_BOOT_RECORD, -1, NULL )
S ( STATUS_IO_PRIVILEGE_FAILED, -1, NULL )
S ( STATUS_REDIRECTOR_STARTED, -1, NULL )
S ( STATUS_INVALID_OPLOCK_PROTOCOL, -1, NULL )
S ( STATUS_PASSWORD_RESTRICTION, -1, NULL )
S ( STATUS_INSUFFICIENT_POWER, -1, NULL )
S ( STATUS_PRINT_QUEUE_FULL, -1, NULL )
S ( STATUS_SHARING_PAUSED, -1, NULL )
S ( STATUS_LOGON_FAILURE, -1, NULL )
S ( STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT, -1, NULL )
S ( STATUS_PARTITION_FAILURE, -1, NULL )
S ( STATUS_DS_SENSITIVE_GROUP_VIOLATION, -1, NULL )
S ( STATUS_CONTROL_C_EXIT, -1, NULL )
S ( STATUS_INVALID_PARAMETER_1, -1, NULL )
S ( STATUS_CANCELLED, -1, NULL )
S ( STATUS_NO_TRACKING_SERVICE, -1, NULL )
S ( STATUS_ALLOCATE_BUCKET, -1, NULL )
S ( STATUS_MUTUAL_AUTHENTICATION_FAILED, -1, NULL )
S ( STATUS_BACKUP_CONTROLLER, -1, NULL )
S ( STATUS_RXACT_COMMIT_FAILURE, -1, NULL )
S ( STATUS_ORDINAL_NOT_FOUND, -1, NULL )
S ( STATUS_NO_EVENT_PAIR, -1, NULL )
S ( STATUS_IMAGE_MP_UP_MISMATCH, -1, NULL )
S ( STATUS_LOGON_SERVER_CONFLICT, -1, NULL )
S ( STATUS_NOT_COMMITTED, -1, NULL )
S ( STATUS_BAD_TOKEN_TYPE, -1, NULL )
S ( STATUS_INVALID_PARAMETER_2, -1, NULL )
S ( STATUS_INVALID_PARAMETER_7, -1, NULL )
S ( STATUS_NO_BROWSER_SERVERS_FOUND, -1, NULL )
S ( STATUS_LPC_REPLY_LOST, -1, NULL )
S ( STATUS_SHARED_IRQ_BUSY, -1, NULL )
S ( STATUS_REMOTE_RESOURCES, -1, NULL )
S ( STATUS_NO_TRUST_SAM_ACCOUNT, -1, NULL )
S ( STATUS_SECTION_NOT_IMAGE, -1, NULL )
S ( STATUS_WMI_GUID_NOT_FOUND, -1, NULL )
S ( STATUS_DISK_RECALIBRATE_FAILED, -1, NULL )
S ( STATUS_INVALID_ADDRESS_WILDCARD, -1, NULL )
S ( STATUS_VOLUME_DISMOUNTED, -1, NULL )
S ( STATUS_SERVER_NOT_DISABLED, -1, NULL )
S ( STATUS_OPLOCK_NOT_GRANTED, -1, NULL )
S ( STATUS_BAD_LOGON_SESSION_STATE, -1, NULL )
S ( STATUS_NOT_SAME_DEVICE, -1, NULL )
S ( STATUS_DEVICE_DATA_ERROR, -1, NULL )
S ( STATUS_TOO_MANY_NAMES, -1, NULL )
S ( STATUS_NOLOGON_SERVER_TRUST_ACCOUNT, -1, NULL )
S ( STATUS_REPARSE_ATTRIBUTE_CONFLICT, -1, NULL )
S ( STATUS_PIPE_CLOSING, -1, NULL )
S ( STATUS_QUOTA_EXCEEDED, -1, NULL )
S ( STATUS_SUSPEND_COUNT_EXCEEDED, -1, NULL )
S ( STATUS_DS_NO_MORE_RIDS, -1, NULL )
S ( STATUS_FILE_ENCRYPTED, -1, NULL )
S ( STATUS_EA_TOO_LARGE, -1, NULL )
S ( STATUS_ACCOUNT_RESTRICTION, -1, NULL )
S ( STATUS_INVALID_PARAMETER_12, -1, NULL )
S ( STATUS_ILLEGAL_ELEMENT_ADDRESS, -1, NULL )
S ( STATUS_INVALID_LDT_OFFSET, -1, NULL )
S ( STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER, -1, NULL )
S ( STATUS_JOURNAL_DELETE_IN_PROGRESS, -1, NULL )
S ( STATUS_MUTANT_LIMIT_EXCEEDED, -1, NULL )
S ( STATUS_FLOPPY_UNKNOWN_ERROR, -1, NULL )
S ( STATUS_INVALID_PLUGPLAY_DEVICE_PATH, -1, NULL )
S ( STATUS_ARRAY_BOUNDS_EXCEEDED, -1, NULL )
S ( STATUS_INVALID_LEVEL, -1, "Unsupported level requested" )
S ( STATUS_NOT_REGISTRY_FILE, -1, NULL )
S ( STATUS_WX86_INTERNAL_ERROR, -1, NULL )
S ( STATUS_TIMER_NOT_CANCELED, -1, NULL )
S ( STATUS_PORT_DISCONNECTED, -1, NULL )
S ( STATUS_DATA_ERROR, -1, NULL )
S ( STATUS_TIMER_RESOLUTION_NOT_SET, -1, NULL )
S ( STATUS_DISK_OPERATION_FAILED, -1, NULL )
S ( STATUS_CLIENT_SERVER_PARAMETERS_INVALID, -1, NULL )
S ( STATUS_RANGE_NOT_FOUND, -1, NULL )
S ( STATUS_NETWORK_BUSY, -1, NULL )
S ( STATUS_ACCESS_VIOLATION, -1, NULL )
S ( STATUS_UNABLE_TO_DELETE_SECTION, -1, NULL )
S ( STATUS_BAD_INITIAL_PC, -1, NULL )
S ( STATUS_CANT_OPEN_ANONYMOUS, -1, NULL )
S ( STATUS_INVALID_CID, -1, NULL )
S ( STATUS_NO_LOGON_SERVERS, -1, NULL )
S ( STATUS_BAD_WORKING_SET_LIMIT, -1, NULL )
S ( STATUS_PRIVILEGED_INSTRUCTION, -1, NULL )
S ( STATUS_IO_REPARSE_TAG_INVALID, -1, NULL )
S ( STATUS_APP_INIT_FAILURE, -1, NULL )
S ( STATUS_DEVICE_POWER_FAILURE, -1, NULL )
S ( STATUS_SERVER_DISABLED, -1, NULL )
S ( STATUS_CONNECTION_ABORTED, ETIMEDOUT, "The connection timed out." )
S ( STATUS_PORT_CONNECTION_REFUSED, -1, NULL )
S ( STATUS_WX86_FLOAT_STACK_CHECK, -1, NULL )
S ( STATUS_DS_INVALID_GROUP_TYPE, -1, NULL )
S ( STATUS_NAME_TOO_LONG, -1, NULL )
S ( STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER, -1, NULL )
S ( STATUS_REG_NAT_CONSUMPTION, -1, NULL )
S ( STATUS_ADDRESS_ALREADY_EXISTS, -1, NULL )
S ( STATUS_WMI_READ_ONLY, -1, NULL )
S ( STATUS_ACCESS_DENIED, -1, NULL )
S ( STATUS_INVALID_DOMAIN_ROLE, -1, NULL )
S ( STATUS_INVALID_IMAGE_WIN_16, -1, NULL )
S ( STATUS_END_OF_FILE, -1, NULL )
S ( STATUS_DUPLICATE_NAME, -1, NULL )
S ( STATUS_NOT_SUPPORTED_ON_SBS, -1, NULL )
S ( STATUS_USER_MAPPED_FILE, -1, NULL )
S ( STATUS_PARITY_ERROR, -1, NULL )
S ( STATUS_DOMAIN_EXISTS, -1, NULL )
S ( STATUS_FLOAT_INEXACT_RESULT, -1, NULL )
S ( STATUS_INVALID_IMAGE_NOT_MZ, -1, NULL )
S ( STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER, -1, NULL )
S ( STATUS_FLOAT_INVALID_OPERATION, -1, NULL )
S ( STATUS_IO_REPARSE_TAG_MISMATCH, -1, NULL )
S ( STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED, -1, NULL )
S ( STATUS_CANT_TERMINATE_SELF, -1, NULL )
S ( STATUS_SECRET_TOO_LONG, -1, NULL )
S ( STATUS_MAPPED_FILE_SIZE_ZERO, -1, NULL )
S ( STATUS_TRANSACTION_TIMED_OUT, -1, NULL )
S ( STATUS_CANT_ENABLE_DENY_ONLY, -1, NULL )
S ( STATUS_NO_SUCH_FILE, ENOENT, NULL )
S ( STATUS_INVALID_PARAMETER_3, -1, NULL )
S ( STATUS_PROFILING_AT_LIMIT, -1, NULL )
S ( STATUS_NO_TOKEN, -1, NULL )
S ( STATUS_INVALID_VIEW_SIZE, -1, NULL )
S ( STATUS_REQUEST_ABORTED, -1, NULL )
S ( STATUS_LOGON_TYPE_NOT_GRANTED, EACCES, NULL )
S ( STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT, -1, NULL )
S ( STATUS_PNP_REBOOT_REQUIRED, -1, NULL )
S ( STATUS_NO_SECURITY_ON_OBJECT, -1, NULL )
S ( STATUS_TRANSACTION_RESPONDED, -1, NULL )
S ( STATUS_ABIOS_NOT_PRESENT, -1, NULL )
S ( STATUS_DATA_LATE_ERROR, -1, NULL )
S ( STATUS_POLICY_OBJECT_NOT_FOUND, -1, NULL )
S ( STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER, -1, NULL )
S ( STATUS_ACCOUNT_LOCKED_OUT, -1, NULL )
S ( STATUS_VDM_HARD_ERROR, -1, NULL )
S ( STATUS_RESOURCE_DATA_NOT_FOUND, -1, NULL )
S ( STATUS_UNEXPECTED_IO_ERROR, -1, NULL )
S ( STATUS_FILE_INVALID, -1, NULL )
S ( STATUS_NOT_LOGON_PROCESS, -1, NULL )
S ( STATUS_EAS_NOT_SUPPORTED, -1, NULL )
S ( STATUS_SPECIAL_GROUP, -1, NULL )
S ( STATUS_TOO_LATE, -1, NULL )
S ( STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT, -1, NULL )
S ( STATUS_WRONG_PASSWORD_CORE, EINVAL, NULL )
S ( STATUS_DS_CANT_MOD_OBJ_CLASS, -1, NULL )
S ( STATUS_WRONG_VOLUME, -1, NULL )
S ( STATUS_CRC_ERROR, -1, NULL )
S ( STATUS_PORT_MESSAGE_TOO_LONG, -1, NULL )
S ( STATUS_DRIVER_UNABLE_TO_LOAD, -1, NULL )
S ( STATUS_FLOPPY_WRONG_CYLINDER, -1, NULL )
S ( STATUS_WMI_TRY_AGAIN, -1, NULL )
S ( STATUS_TRUSTED_RELATIONSHIP_FAILURE, -1, NULL )
S ( STATUS_INVALID_IMAGE_NE_FORMAT, -1, NULL )
S ( STATUS_LINK_FAILED, -1, NULL )
S ( STATUS_DLL_NOT_FOUND, -1, NULL )
S ( STATUS_ILLEGAL_INSTRUCTION, -1, NULL )
S ( STATUS_ONLY_IF_CONNECTED, -1, NULL )
S ( STATUS_TRANSACTION_NO_MATCH, -1, NULL )
S ( STATUS_NO_MORE_MATCHES, -1, NULL )
S ( STATUS_CONNECTION_INVALID, -1, NULL )
S ( STATUS_UNABLE_TO_LOCK_MEDIA, -1, NULL )
S ( STATUS_BAD_COMPRESSION_BUFFER, -1, NULL )
S ( STATUS_MEMBER_NOT_IN_GROUP, -1, NULL )
S ( STATUS_DEVICE_NOT_PARTITIONED, -1, NULL )
S ( STATUS_INVALID_PORT_ATTRIBUTES, -1, NULL )
S ( STATUS_DRIVER_INTERNAL_ERROR, -1, NULL )
S ( STATUS_IO_REPARSE_TAG_NOT_HANDLED, -1, NULL )
S ( STATUS_LOCAL_DISCONNECT, -1, NULL )
S ( STATUS_WMI_ITEMID_NOT_FOUND, -1, NULL )
S ( STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER, -1, NULL )
S ( STATUS_SAM_INIT_FAILURE, -1, NULL )
S ( STATUS_FILE_IS_A_DIRECTORY, -1, NULL )
S ( STATUS_INTEGER_OVERFLOW, -1, NULL )
S ( STATUS_CHILD_MUST_BE_VOLATILE, -1, NULL )
S ( STATUS_REMOTE_STORAGE_MEDIA_ERROR, -1, NULL )
S ( STATUS_ACCOUNT_DISABLED, -1, NULL )
S ( STATUS_DRIVER_ORDINAL_NOT_FOUND, -1, NULL )
S ( STATUS_CANNOT_LOAD_REGISTRY_FILE, -1, NULL )
S ( STATUS_ILLEGAL_FLOAT_CONTEXT, -1, NULL )
S ( STATUS_HANDLE_NOT_CLOSABLE, -1, NULL )
S ( STATUS_CTL_FILE_NOT_SUPPORTED, -1, NULL )
S ( STATUS_DRIVER_FAILED_SLEEP, -1, NULL )
S ( STATUS_INVALID_IMAGE_PROTECT, -1, NULL )
S ( STATUS_CORRUPT_SYSTEM_FILE, -1, NULL )
S ( STATUS_RESOURCE_LANG_NOT_FOUND, -1, NULL )
S ( STATUS_FLOAT_STACK_CHECK, -1, NULL )
S ( STATUS_WMI_NOT_SUPPORTED, -1, NULL )
S ( STATUS_ADDRESS_ALREADY_ASSOCIATED, -1, NULL )
S ( STATUS_OBJECT_NAME_NOT_FOUND, ENOENT, NULL )
S ( STATUS_BAD_NETWORK_PATH, -1, NULL )
S ( STATUS_LM_CROSS_ENCRYPTION_REQUIRED, -1, NULL )
S ( STATUS_UNABLE_TO_DECOMMIT_VM, -1, NULL )
S ( STATUS_TOO_MANY_OPENED_FILES, -1, NULL )
S ( STATUS_FLOAT_UNDERFLOW, -1, NULL )
S ( STATUS_PORT_UNREACHABLE, -1, NULL )
S ( STATUS_TOO_MANY_SIDS, -1, NULL )
S ( STATUS_NONEXISTENT_SECTOR, -1, NULL )
S ( STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED, -1, NULL )
S ( STATUS_INVALID_INFO_CLASS, -1, NULL )
S ( STATUS_ILLEGAL_FUNCTION, -1, NULL )
S ( STATUS_ILLEGAL_DLL_RELOCATION, -1, NULL )
S ( STATUS_INVALID_PAGE_PROTECTION, -1, NULL )
S ( STATUS_CONFLICTING_ADDRESSES, -1, NULL )
S ( STATUS_EA_CORRUPT_ERROR, -1, NULL )
S ( STATUS_OBJECT_TYPE_MISMATCH, -1, NULL )
S ( STATUS_FLOPPY_ID_MARK_NOT_FOUND, -1, NULL )
S ( STATUS_TOO_MANY_SESSIONS, -1, NULL )
S ( STATUS_FILE_NOT_ENCRYPTED, -1, NULL )
S ( STATUS_DS_CANT_ON_RDN, -1, NULL )
S ( STATUS_RESOURCE_TYPE_NOT_FOUND, -1, NULL )
S ( STATUS_FLOAT_MULTIPLE_FAULTS, -1, NULL )
S ( STATUS_USER_SESSION_DELETED, -1, NULL )
S ( STATUS_NO_RECOVERY_POLICY, -1, NULL )
S ( STATUS_FREE_VM_NOT_AT_BASE, -1, NULL )
S ( STATUS_TOO_MANY_ADDRESSES, -1, NULL )
S ( STATUS_KEY_HAS_CHILDREN, -1, NULL )
S ( STATUS_REMOTE_STORAGE_NOT_ACTIVE, -1, NULL )
S ( STATUS_NOT_A_DIRECTORY, -1, NULL )
S ( STATUS_NOT_SERVER_SESSION, -1, NULL )
S ( STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS, -1, NULL )
S ( STATUS_SAM_NEED_BOOTKEY_PASSWORD, -1, NULL )
S ( STATUS_DECRYPTION_FAILED, -1, NULL )
S ( STATUS_DFS_EXIT_PATH_FOUND, -1, NULL )
S ( STATUS_TRANSPORT_FULL, -1, NULL )
S ( STATUS_MEMBER_NOT_IN_ALIAS, -1, "Specified account is not an alias member" )
S ( STATUS_TOO_MANY_LINKS, -1, NULL )
S ( STATUS_DIRECTORY_SERVICE_REQUIRED, -1, NULL )
S ( STATUS_CONNECTION_IN_USE, -1, NULL )
S ( STATUS_NO_SUCH_DEVICE, -1, NULL )
S ( STATUS_DS_UNAVAILABLE, -1, NULL )
S ( STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS, -1, NULL )
S ( STATUS_INVALID_LOCK_SEQUENCE, -1, NULL )
S ( STATUS_PRIVILEGE_NOT_HELD, -1, NULL )
S ( STATUS_NT_CROSS_ENCRYPTION_REQUIRED, -1, NULL )
S ( STATUS_EVENTLOG_FILE_CORRUPT, -1, NULL )
S ( STATUS_UNDEFINED_CHARACTER, -1, NULL )
S ( STATUS_INVALID_HANDLE, -1, NULL )
S ( STATUS_LOG_FILE_FULL, -1, NULL )
S ( STATUS_INVALID_CONNECTION, -1, NULL )
S ( STATUS_INVALID_DISPOSITION, -1, NULL )
S ( STATUS_INVALID_SID, -1, NULL )
S ( STATUS_NONE_MAPPED, -1, NULL )
S ( STATUS_DATA_NOT_ACCEPTED, -1, NULL )
S ( STATUS_INVALID_BUFFER_SIZE, -1, NULL )
S ( STATUS_REDIRECTOR_NOT_STARTED, -1, NULL )
S ( STATUS_OBJECTID_EXISTS, -1, NULL )
S ( STATUS_INVALID_HW_PROFILE, -1, NULL )
S ( STATUS_DS_CANT_START, -1, NULL )
S ( STATUS_TOO_MANY_SECRETS, -1, NULL )
S ( STATUS_BAD_DLL_ENTRYPOINT, -1, NULL )
S ( STATUS_FLOAT_OVERFLOW, -1, NULL )
S ( STATUS_MISSING_SYSTEMFILE, -1, NULL )
S ( STATUS_MAGAZINE_NOT_PRESENT, -1, NULL )
S ( STATUS_INVALID_DEVICE_REQUEST, -1, NULL )
S ( STATUS_OBJECT_NAME_INVALID, -1, NULL )
S ( STATUS_NO_SUCH_PACKAGE, -1, NULL )
S ( STATUS_IMAGE_CHECKSUM_MISMATCH, -1, NULL )
S ( STATUS_NOINTERFACE, -1, NULL )
S ( STATUS_REPARSE_POINT_NOT_RESOLVED, -1, NULL )
S ( STATUS_LICENSE_VIOLATION, -1, NULL )
S ( STATUS_THREAD_NOT_IN_PROCESS, -1, NULL )
S ( STATUS_INVALID_LOGON_TYPE, -1, NULL )
S ( STATUS_CONNECTION_ACTIVE, -1, NULL )
S ( STATUS_SAM_NEED_BOOTKEY_FLOPPY, -1, NULL )
S ( STATUS_INVALID_READ_MODE, -1, NULL )
S ( STATUS_INCOMPATIBLE_FILE_MAP, -1, NULL )
S ( STATUS_ACCOUNT_EXPIRED, -1, NULL )
S ( STATUS_ILL_FORMED_PASSWORD, -1, NULL )
S ( STATUS_RANGE_LIST_CONFLICT, -1, NULL )
S ( STATUS_PROTOCOL_UNREACHABLE, -1, NULL )
S ( STATUS_PASSWORD_MUST_CHANGE, -1, NULL )
S ( STATUS_NO_EAS_ON_FILE, -1, NULL )
S ( STATUS_DS_GC_REQUIRED, -1, NULL )
S ( STATUS_STACK_OVERFLOW_READ, -1, NULL )
S ( STATUS_INSTRUCTION_MISALIGNMENT, -1, NULL )
S ( STATUS_NO_CALLBACK_ACTIVE, -1, NULL )
S ( STATUS_NOT_MAPPED_VIEW, -1, NULL )
S ( STATUS_PROFILING_NOT_STOPPED, -1, NULL )
S ( STATUS_INVALID_LOGON_HOURS, -1, NULL )
S ( STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN, -1, NULL )
S ( STATUS_MULTIPLE_FAULT_VIOLATION, -1, NULL )
S ( STATUS_INSUFFICIENT_RESOURCES, -1, NULL )
S ( STATUS_NO_SUCH_MEMBER, -1, "Specified account is not a member" )
S ( STATUS_REMOTE_NOT_LISTENING, -1, NULL )
S ( STATUS_SPECIAL_ACCOUNT, -1, NULL )
S ( STATUS_HOST_UNREACHABLE, -1, NULL )
S ( STATUS_THREAD_IS_TERMINATING, -1, NULL )
S ( STATUS_SEMAPHORE_LIMIT_EXCEEDED, -1, NULL )
S ( STATUS_LOST_WRITEBEHIND_DATA, -1, NULL )
S ( STATUS_KEY_DELETED, -1, NULL )
S ( STATUS_NO_USER_KEYS, -1, NULL )
S ( STATUS_INVALID_WORKSTATION, -1, NULL )
S ( STATUS_SHARING_VIOLATION, -1, NULL )
S ( STATUS_DS_SAM_INIT_FAILURE, -1, NULL )
S ( STATUS_SECTION_PROTECTION, -1, NULL )
S ( STATUS_COMMITMENT_MINIMUM, -1, NULL )
S ( STATUS_LOGON_SESSION_COLLISION, -1, NULL )
S ( STATUS_ALIAS_EXISTS, -1, NULL )
S ( STATUS_PIPE_NOT_AVAILABLE, -1, NULL )
S ( STATUS_DELETE_PENDING, -1, NULL )
S ( STATUS_REVISION_MISMATCH, -1, NULL )
S ( STATUS_PIPE_DISCONNECTED, -1, NULL )
S ( STATUS_INVALID_ADDRESS_COMPONENT, -1, NULL )
S ( STATUS_INTERNAL_DB_ERROR, -1, NULL )
S ( STATUS_USER_EXISTS, -1, NULL )
S ( STATUS_GENERIC_NOT_MAPPED, -1, NULL )
S ( STATUS_DS_INIT_FAILURE, -1, NULL )
S ( STATUS_DOMAIN_LIMIT_EXCEEDED, -1, NULL )
S ( STATUS_SERVER_SID_MISMATCH, -1, NULL )
S ( STATUS_INTERNAL_DB_CORRUPTION, -1, NULL )
S ( STATUS_IMAGE_ALREADY_LOADED, -1, NULL )
S ( STATUS_DOMAIN_TRUST_INCONSISTENT, -1, NULL )
S ( STATUS_NO_SUCH_LOGON_SESSION, -1, NULL )
S ( STATUS_OBJECT_PATH_INVALID, -1, NULL )
S ( STATUS_IN_PAGE_ERROR, -1, NULL )
S ( STATUS_INVALID_SYSTEM_SERVICE, -1, NULL )
S ( STATUS_ENTRYPOINT_NOT_FOUND, -1, NULL )
S ( STATUS_LICENSE_QUOTA_EXCEEDED, -1, NULL )
S ( STATUS_DUPLICATE_OBJECTID, -1, NULL )
S ( STATUS_JOURNAL_ENTRY_DELETED, -1, NULL )
S ( STATUS_STACK_OVERFLOW, -1, NULL )
S ( STATUS_INVALID_COMPUTER_NAME, -1, NULL )
S ( STATUS_INVALID_PARAMETER_5, -1, NULL )
S ( STATUS_VARIABLE_NOT_FOUND, -1, NULL )
S ( STATUS_INVALID_IMAGE_LE_FORMAT, -1, NULL )
S ( STATUS_DS_CROSS_DOM_MOVE_FAILED, -1, NULL )
S ( STATUS_JOURNAL_NOT_ACTIVE, -1, NULL )
S ( STATUS_PATH_NOT_COVERED, -1, NULL )
S ( STATUS_INVALID_PARAMETER_MIX, -1, NULL )
S ( STATUS_CANNOT_IMPERSONATE, -1, NULL )
S ( STATUS_FILE_LOCK_CONFLICT, -1, NULL )
S ( STATUS_OBJECT_PATH_NOT_FOUND, -1, NULL )
S ( STATUS_EVENTLOG_FILE_CHANGED, -1, NULL )
S ( STATUS_ABIOS_LID_ALREADY_OWNED, -1, NULL )
S ( STATUS_INVALID_PARAMETER_6, -1, NULL )
S ( STATUS_GRACEFUL_DISCONNECT, -1, NULL )
S ( STATUS_BAD_DESCRIPTOR_FORMAT, -1, NULL )
S ( STATUS_IP_ADDRESS_CONFLICT1, -1, NULL )
S ( STATUS_INVALID_OWNER, -1, NULL )
S ( STATUS_UNMAPPABLE_CHARACTER, -1, NULL )
S ( STATUS_LAST_ADMIN, -1, NULL )
S ( STATUS_NO_LOG_SPACE, -1, NULL )
S ( STATUS_NO_LDT, -1, NULL )
S ( STATUS_SYSTEM_IMAGE_BAD_SIGNATURE, -1, NULL )
S ( STATUS_NO_IMPERSONATION_TOKEN, -1, NULL )
S ( STATUS_NO_PAGEFILE, -1, NULL )
S ( STATUS_DEVICE_ALREADY_ATTACHED, -1, NULL )
S ( STATUS_DEVICE_NOT_READY, -1, NULL )
S ( STATUS_UNKNOWN_REVISION, -1, NULL )
S ( STATUS_INVALID_PIPE_STATE, -1, NULL )
S ( STATUS_NETWORK_CREDENTIAL_CONFLICT, -1, NULL )
S ( STATUS_DEVICE_REMOVED, -1, NULL )
S ( STATUS_AGENTS_EXHAUSTED, -1, NULL )
S ( STATUS_DRIVER_ENTRYPOINT_NOT_FOUND, -1, NULL )
S ( STATUS_INSTANCE_NOT_AVAILABLE, -1, NULL )
S ( STATUS_ENCRYPTION_FAILED, -1, NULL )
S ( STATUS_BAD_SERVICE_ENTRYPOINT, -1, NULL )
S ( STATUS_DATATYPE_MISALIGNMENT_ERROR, -1, NULL )
S ( STATUS_NO_SUCH_PRIVILEGE, -1, NULL )
S ( STATUS_INVALID_DOMAIN_STATE, -1, NULL )
S ( STATUS_LOCK_NOT_GRANTED, -1, NULL )
S ( STATUS_BAD_STACK, -1, NULL )
S ( STATUS_ABIOS_INVALID_LID, -1, NULL )
S ( STATUS_DS_GC_NOT_AVAILABLE, -1, NULL )
S ( STATUS_SPECIAL_USER, -1, NULL )
S ( STATUS_UNEXPECTED_MM_MAP_ERROR, -1, NULL )
S ( STATUS_RECOVERY_FAILURE, -1, NULL )
S ( STATUS_NO_MEMORY, -1, NULL )
S ( STATUS_IO_TIMEOUT, -1, NULL )
S ( STATUS_DLL_INIT_FAILED, -1, NULL )
S ( STATUS_FILE_CLOSED, -1, NULL )
S ( STATUS_ALLOTTED_SPACE_EXCEEDED, -1, NULL )
S ( STATUS_INTEGER_DIVIDE_BY_ZERO, -1, NULL )
S ( STATUS_UNEXPECTED_MM_EXTEND_ERR, -1, NULL )
S ( STATUS_DS_RIDMGR_INIT_ERROR, -1, NULL )
S ( STATUS_RESOURCE_NOT_OWNED, -1, NULL )
S ( STATUS_TOO_MANY_CONTEXT_IDS, -1, NULL )
S ( STATUS_UNWIND, -1, NULL )
S ( STATUS_NOT_A_REPARSE_POINT, -1, NULL )
S ( STATUS_LOGIN_WKSTA_RESTRICTION, -1, NULL )
S ( STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN, -1, NULL )
S ( STATUS_PAGEFILE_QUOTA, -1, NULL )
S ( STATUS_DOMAIN_CONTROLLER_NOT_FOUND, -1, NULL )
S ( STATUS_INVALID_PARAMETER, -1, NULL )
S ( STATUS_LOGON_SESSION_EXISTS, -1, NULL )
S ( STATUS_FILE_FORCED_CLOSED, -1, NULL )
S ( STATUS_EVENTLOG_CANT_START, -1, NULL )
S ( STATUS_UNEXPECTED_NETWORK_ERROR, -1, NULL )
S ( STATUS_BAD_INHERITANCE_ACL, -1, NULL )
S ( STATUS_INVALID_USER_BUFFER, -1, NULL )
S ( STATUS_PLUGPLAY_NO_DEVICE, -1, NULL )
S ( STATUS_REGISTRY_IO_FAILED, -1, NULL )
S ( STATUS_DEVICE_NOT_CONNECTED, -1, NULL )
S ( STATUS_MEMBER_IN_GROUP, -1, NULL )
S ( STATUS_DS_INCORRECT_ROLE_OWNER, -1, NULL )
S ( STATUS_INVALID_VOLUME_LABEL, -1, NULL )
S ( STATUS_DISK_FULL, -1, NULL )
S ( STATUS_TIME_DIFFERENCE_AT_DC, -1, NULL )
S ( STATUS_CONNECTION_RESET, -1, NULL )
S ( STATUS_NOT_EXPORT_FORMAT, -1, NULL )
S ( STATUS_UNSUCCESSFUL, -1, NULL )
S ( STATUS_TOO_MANY_THREADS, -1, NULL )
S ( STATUS_DIRECTORY_NOT_EMPTY, -1, NULL )
S ( STATUS_FILE_DELETED, -1, NULL )
S ( STATUS_NONCONTINUABLE_EXCEPTION, -1, NULL )
S ( STATUS_FILES_OPEN, -1, NULL )
S ( STATUS_INVALID_VARIANT, -1, NULL )
S ( STATUS_INSUFFICIENT_LOGON_INFO, -1, NULL )
S ( STATUS_TRANSACTION_INVALID_TYPE, -1, NULL )
S ( STATUS_INVALID_SUB_AUTHORITY, -1, NULL )
S ( STATUS_DATA_OVERRUN, -1, NULL )
S ( STATUS_TRANSACTION_INVALID_ID, -1, NULL )
S ( STATUS_CANNOT_DELETE, -1, NULL )
S ( STATUS_TOO_MANY_LUIDS_REQUESTED, -1, NULL )
S ( STATUS_MEMBER_IN_ALIAS, -1, "Specified account is already alias member" )
S ( STATUS_MAPPED_ALIGNMENT, -1, NULL )
S ( STATUS_FLOPPY_VOLUME, -1, NULL )
S ( STATUS_WRONG_EFS, -1, NULL )
S ( STATUS_PROCESS_IS_TERMINATING, -1, NULL )
S ( STATUS_DS_OBJ_CLASS_VIOLATION, -1, NULL )
S ( STATUS_PIPE_CONNECTED, -1, NULL )
S ( STATUS_TOO_MANY_COMMANDS, -1, NULL )
S ( STATUS_DS_CANT_ON_NON_LEAF, -1, NULL )
S ( STATUS_PIPE_LISTENING, -1, NULL )
S ( STATUS_DESTINATION_ELEMENT_FULL, -1, NULL )
S ( STATUS_PIPE_BROKEN, -1, NULL )
S ( STATUS_DIRECTORY_IS_A_REPARSE_POINT, -1, NULL )
S ( STATUS_EOM_OVERFLOW, -1, NULL )
S ( STATUS_NO_MEDIA_IN_DEVICE, -1, NULL )
S ( STATUS_FAIL_CHECK, -1, NULL )
S ( STATUS_DFS_UNAVAILABLE, -1, NULL )
S ( STATUS_TRUSTED_DOMAIN_FAILURE, -1, NULL )
S ( STATUS_PWD_HISTORY_CONFLICT, -1, NULL )
S ( STATUS_BAD_REMOTE_ADAPTER, -1, NULL )
S ( STATUS_LOGON_NOT_GRANTED, -1, NULL )
S ( STATUS_FULLSCREEN_MODE, -1, NULL )
S ( STATUS_REMOTE_DISCONNECT, -1, NULL )
S ( STATUS_IP_ADDRESS_CONFLICT2, -1, NULL )
S ( STATUS_OPEN_FAILED, -1, NULL )
S ( STATUS_REDIRECTOR_PAUSED, -1, NULL )
S ( STATUS_NO_SUCH_USER, -1, NULL )
S ( STATUS_MEMBERS_PRIMARY_GROUP, -1, NULL )
S ( STATUS_INVALID_PARAMETER_9, -1, NULL )
S ( STATUS_INFO_LENGTH_MISMATCH, -1, NULL )
S ( STATUS_EVALUATION_EXPIRATION, -1, NULL )
S ( STATUS_LINK_TIMEOUT, -1, NULL )
S ( STATUS_SYSTEM_PROCESS_TERMINATED, -1, NULL )
S ( STATUS_NONEXISTENT_EA_ENTRY, -1, NULL )
S ( STATUS_MESSAGE_NOT_FOUND, -1, NULL )
S ( STATUS_FLOPPY_BAD_REGISTERS, -1, NULL )
S ( STATUS_MARSHALL_OVERFLOW, -1, NULL )
S ( STATUS_QUOTA_LIST_INCONSISTENT, -1, NULL )
S ( STATUS_NO_GUID_TRANSLATION, -1, NULL )
S ( STATUS_SERIAL_NO_DEVICE_INITED, -1, NULL )
S ( STATUS_UNRECOGNIZED_VOLUME, -1, NULL )
S ( STATUS_NOT_FOUND, -1, NULL )
S ( STATUS_CANT_WAIT, -1, NULL )
S ( STATUS_IO_REPARSE_DATA_INVALID, -1, NULL )
S ( STATUS_RANGE_NOT_LOCKED, -1, NULL )
S ( STATUS_AUDIT_FAILED, -1, NULL )
S ( STATUS_BAD_FUNCTION_TABLE, -1, NULL )
S ( STATUS_INVALID_PORT_HANDLE, -1, NULL )
S ( STATUS_BAD_IMPERSONATION_LEVEL, -1, NULL )
S ( STATUS_INVALID_PARAMETER_4, -1, NULL )
S ( STATUS_ABIOS_SELECTOR_NOT_AVAILABLE, -1, NULL )
S ( STATUS_BAD_NETWORK_NAME, -1, NULL )
S ( STATUS_ABIOS_NOT_LID_OWNER, -1, NULL )
S ( STATUS_NOT_TINY_STREAM, -1, NULL )
S ( STATUS_PIPE_BUSY, -1, NULL )
S ( STATUS_INVALID_LDT_DESCRIPTOR, -1, NULL )
S ( STATUS_NO_SUCH_DOMAIN, -1, NULL )
S ( STATUS_OBJECT_NAME_COLLISION, -1, NULL )
S ( STATUS_BAD_VALIDATION_CLASS, -1, NULL )
S ( STATUS_PORT_ALREADY_SET, -1, NULL )
S ( STATUS_INVALID_ID_AUTHORITY, -1, NULL )
S ( STATUS_UNABLE_TO_FREE_VM, -1, NULL )
S ( STATUS_CONNECTION_DISCONNECTED, -1, NULL )
S ( STATUS_DEBUG_ATTACH_FAILED, -1, NULL )
S ( STATUS_TOO_MANY_GUIDS_REQUESTED, -1, NULL )
S ( STATUS_VALIDATE_CONTINUE, -1, NULL )
S ( STATUS_INVALID_ACCOUNT_NAME, -1, NULL )
S ( STATUS_PWD_TOO_RECENT, -1, NULL )
S ( STATUS_FOUND_OUT_OF_SCOPE, -1, NULL )
S ( STATUS_PRINT_CANCELLED, -1, NULL )
S ( STATUS_MORE_PROCESSING_REQUIRED, -1, NULL )
S ( STATUS_ALREADY_COMMITTED, -1, NULL )
S ( STATUS_ILL_FORMED_SERVICE_ENTRY, -1, NULL )
S ( STATUS_PAGEFILE_QUOTA_EXCEEDED, -1, NULL )
S ( STATUS_ILLEGAL_CHARACTER, -1, NULL )
S ( STATUS_FLOAT_DENORMAL_OPERAND, -1, NULL )
S ( STATUS_ADDRESS_CLOSED, -1, NULL )
S ( STATUS_GROUP_EXISTS, -1, NULL )
S ( STATUS_INVALID_DEVICE_STATE, -1, NULL )
S ( STATUS_NOT_SUPPORTED, -1, NULL )
S ( STATUS_ADAPTER_HARDWARE_ERROR, -1, NULL )
S ( STATUS_ADDRESS_NOT_ASSOCIATED, -1, NULL )
S ( STATUS_INVALID_SERVER_STATE, -1, NULL )
S ( STATUS_MEDIA_WRITE_PROTECTED, -1, NULL )
S ( STATUS_NET_WRITE_FAULT, -1, NULL )
S ( STATUS_ABIOS_INVALID_COMMAND, -1, NULL )
S ( STATUS_DEVICE_DOES_NOT_EXIST, -1, NULL )
S ( STATUS_TRANSACTION_ABORTED, -1, NULL )
S ( STATUS_WRONG_PASSWORD, EINVAL, NULL )
S ( STATUS_FLOAT_DIVIDE_BY_ZERO, -1, NULL )
S ( STATUS_CANT_ACCESS_DOMAIN_INFO, -1, NULL )
S ( STATUS_DEVICE_PROTOCOL_ERROR, -1, NULL )
#undef S
