#include "includes.h"

int
compute_md4_digest(
   PUCHAR puValue,
   DWORD dwValueLen,
   PUCHAR pMd4Digest);

NTSTATUS
ComputeSessionKeyMD5(
    PBYTE sharedSecret,
    DWORD sharedSecretLen,
    PBYTE cliNonce,
    DWORD cliNonceLen,
    PBYTE srvNonce,
    DWORD srvNonceLen,
    PBYTE sessionKey,
    DWORD sessionKeyLen);

NTSTATUS
ComputeSessionKeyAes(
    PBYTE sharedSecret,
    DWORD sharedSecretLen,
    PBYTE cliNonce,
    DWORD cliNonceLen,
    PBYTE srvNonce,
    DWORD srvNonceLen,
    PBYTE sessionKey,
    DWORD sessionKeyLen);

NTSTATUS
ComputeNetlogonCredentialAes(
    PBYTE challengeData,
    DWORD challengeDataLen,
    PBYTE key,
    DWORD keyLen,
    PBYTE credentialData,
    DWORD credentialDataLen);


NTSTATUS
ComputeSessionKeyDes(
    PBYTE sharedSecret,
    DWORD sharedSecretLen,
    PBYTE cliNonce,
    DWORD cliNonceLen,
    PBYTE srvNonce,
    DWORD srvNonceLen,
    PBYTE sessionKey,
    DWORD sessionKeyLen);

NTSTATUS
ComputeNetlogonCredentialDes(
    PBYTE sessionKey,
    DWORD sessionKeyLen,
    PBYTE inputChallenge,
    int inputChallengeLen,
    PBYTE retCredential,
    DWORD *retCredentialLen);


void printhex(unsigned char *hex, int hexlen)
{
    int i = 0;
    for (i=0; i<hexlen; i++)
    {
        printf("%02x ", hex[i]);
    }
}

int main(int argc, char *argv[])
{
#if 0
    unsigned char unicodePwd[] = {
 0x45, 0x00, 0x52, 0x00, 0x33, 0x00, 0x5d, 0x00, 0x31, 0x00, 0x26, 0x00, 0x4d, 0x00, 0x44, 0x00,
 0x22, 0x00, 0x59, 0x00, 0x76, 0x00, 0x7a, 0x00, 0x38, 0x00, 0x35, 0x00, 0x3b, 0x00, 0x35, 0x00,
 0x6a, 0x00, 0x5f, 0x00, 0x3c, 0x00, 0x3f, 0x00, 0x51, 0x00, 0x6c, 0x00, 0x34, 0x00, 0x4d, 0x00,
 0x36, 0x00, 0x67, 0x00, 0x78, 0x00, 0x7a, 0x00, 0x3c, 0x00, 0x50, 0x00, 0x3a, 0x00, 0x58, 0x00,
 0x5e, 0x00, 0x67, 0x00, 0x61, 0x00, 0x64, 0x00, 0x67, 0x00, 0x20, 0x00, 0x45, 0x00, 0x54, 0x00,
 0x44, 0x00, 0x32, 0x00, 0x38, 0x00, 0x28, 0x00, 0x38, 0x00, 0x59, 0x00, 0x62, 0x00, 0x5b, 0x00,
 0x26, 0x00, 0x52, 0x00, 0x71, 0x00, 0x23, 0x00, 0x25, 0x00, 0x46, 0x00, 0x5c, 0x00, 0x36, 0x00,
 0x3f, 0x00, 0x69, 0x00, 0x68, 0x00, 0x27, 0x00, 0x48, 0x00, 0x5c, 0x00, 0x4b, 0x00, 0x5e, 0x00,
 0x2b, 0x00, 0x29, 0x00, 0x75, 0x00, 0x5b, 0x00, 0x3a, 0x00, 0x34, 0x00, 0x33, 0x00, 0x5c, 0x00,
 0x46, 0x00, 0x3d, 0x00, 0x4d, 0x00, 0x51, 0x00, 0x57, 0x00, 0x4d, 0x00, 0x35, 0x00, 0x43, 0x00,
 0x34, 0x00, 0x54, 0x00, 0x32, 0x00, 0x38, 0x00, 0x3c, 0x00, 0x6b, 0x00, 0x29, 0x00, 0x3f, 0x00,
 0x49, 0x00, 0x48, 0x00, 0x4c, 0x00, 0x68, 0x00, 0x69, 0x00, 0x62, 0x00, 0x21, 0x00, 0x45, 0x00,
 0x27, 0x00, 0x51, 0x00, 0x66, 0x00, 0x26, 0x00, 0x64, 0x00, 0x5e, 0x00, 0x72, 0x00, 0x69, 0x00,
 0x60, 0x00, 0x3e, 0x00, 0x4c, 0x00, 0x36, 0x00, 0x4e, 0x00, 0x5f, 0x00, 0x31, 0x00, 0x5a, 0x00,
 0x2b, 0x00, 0x54, 0x00, 0x25, 0x00, 0x5d, 0x00, 0x33, 0x00, 0x31, 0x00, 0x3c, 0x00, 0x59, 0x00, };

    /* Wireshark capture: 25ff37b7271f71e5 */
    unsigned char clientChallengeCapture[] = {
 0x25, 0xff, 0x37, 0xb7, 0x27, 0x1f, 0x71, 0xe5 };

    /* Wireshark capture: 625b47779429cc8f */
    unsigned char serverChallengeCapture[] = {
 0x62, 0x5b, 0x47, 0x77, 0x94, 0x29, 0xcc, 0x8f };

    /* Wireshark capture: 1e8343321cfbee04 */
    unsigned char clientCredentialCapture[] = {
 0x1e, 0x83, 0x43, 0x32, 0x1c, 0xfb, 0xee, 0x04 };
#else
    unsigned char unicodePwd[] = {
 0x3a, 0x00, 0x54, 0x00, 0x2e, 0x00, 0x2a, 0x00, 0x3d, 0x00, 0x51, 0x00, 0x46, 0x00
, 0x3b, 0x00, 0x55, 0x00, 0x38, 0x00, 0x37, 0x00, 0x5a, 0x00, 0x72, 0x00, 0x64, 0x00, 0x59, 0x00
, 0x52, 0x00, 0x58, 0x00, 0x2b, 0x00, 0x4e, 0x00, 0x59, 0x00, 0x50, 0x00, 0x38, 0x00, 0x64, 0x00
, 0x20, 0x00, 0x74, 0x00, 0x72, 0x00, 0x52, 0x00, 0x5e, 0x00, 0x74, 0x00, 0x68, 0x00, 0x57, 0x00
, 0x69, 0x00, 0x5b, 0x00, 0x41, 0x00, 0x6c, 0x00, 0x52, 0x00, 0x37, 0x00, 0x2a, 0x00, 0x76, 0x00
, 0x78, 0x00, 0x47, 0x00, 0x56, 0x00, 0x38, 0x00, 0x46, 0x00, 0x46, 0x00, 0x78, 0x00, 0x56, 0x00
, 0x66, 0x00, 0x70, 0x00, 0x4d, 0x00, 0x5e, 0x00, 0x6c, 0x00, 0x28, 0x00, 0x6b, 0x00, 0x37, 0x00
, 0x45, 0x00, 0x2a, 0x00, 0x37, 0x00, 0x31, 0x00, 0x3c, 0x00, 0x22, 0x00, 0x3b, 0x00, 0x5f, 0x00
, 0x2b, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6b, 0x00, 0x5a, 0x00, 0x27, 0x00, 0x35, 0x00, 0x2d, 0x00
, 0x4a, 0x00, 0x77, 0x00, 0x28, 0x00, 0x71, 0x00, 0x5d, 0x00, 0x4a, 0x00, 0x3e, 0x00, 0x25, 0x00
, 0x7a, 0x00, 0x3f, 0x00, 0x43, 0x00, 0x5b, 0x00, 0x4a, 0x00, 0x39, 0x00, 0x39, 0x00, 0x34, 0x00
, 0x78, 0x00, 0x20, 0x00, 0x62, 0x00, 0x6f, 0x00, 0x4b, 0x00, 0x34, 0x00, 0x5c, 0x00, 0x57, 0x00
, 0x22, 0x00, 0x5a, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x6e, 0x00, 0x5d, 0x00, 0x5a, 0x00, 0x23, 0x00
, 0x3e, 0x00, 0x45, 0x00, 0x2a, 0x00, 0x42, 0x00, 0x2f, 0x00, 0x4c, 0x00, 0x58, 0x00, 0x4f, 0x00
, 0x66, 0x00, 0x50, 0x00, 0x40, 0x00, 0x34, 0x00, 0x47, 0x00, 0x69, 0x00, 0x30, 0x00, 0x6b, 0x00
, 0x53, 0x00, };

    /* Wireshark capture: 25ff37b7271f71e5 */
    unsigned char clientChallengeCapture[] = {
 0x10, 0xea, 0xfe, 0x49, 0x6e, 0x41, 0x54, 0x04 };

    /* Wireshark capture: 625b47779429cc8f */
    unsigned char serverChallengeCapture[] = {
 0x9e, 0xfd, 0xef, 0x47, 0x07, 0x9f, 0x37, 0xc0 };

    /* Wireshark capture: 1e8343321cfbee04 */
    unsigned char clientCredentialCapture[] = {
 0x56, 0xf0, 0x4b, 0xd4, 0xa4, 0xab, 0xf2, 0x0a };

    unsigned char serverCredentialCapture[] = {
 0xd8, 0xa2, 0x28, 0x1e, 0x02, 0x21, 0x03, 0x1d };

    unsigned char unicodePwdSamba4[] = {
  0x73, 0x00, 0x4f, 0x00, 0x62, 0x00, 0x54, 0x00, 0x6c, 0x00, 0x6e, 0x00, 0x2c, 0x00
, 0x6e, 0x00, 0x55, 0x00, 0x38, 0x00, 0x75, 0x00, 0x47, 0x00, 0x49, 0x00, 0x56, 0x00, 0x24, 0x00
, 0x20, 0x00, 0x78, 0x00, 0x69, 0x00, 0x5c, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x25, 0x00, 0x57, 0x00
, 0x23, 0x00, 0x3c, 0x00, 0x27, 0x00, 0x5c, 0x00, 0x65, 0x00, 0x37, 0x00, 0x5c, 0x00, 0x6a, 0x00
, 0x52, 0x00, 0x40, 0x00, 0x45, 0x00, 0x6f, 0x00, 0x37, 0x00, 0x62, 0x00, 0x6d, 0x00, 0x77, 0x00
, 0x3c, 0x00, 0x42, 0x00, 0x4e, 0x00, 0x35, 0x00, 0x55, 0x00, 0x4f, 0x00, 0x6c, 0x00, 0x65, 0x00
, 0x4a, 0x00, 0x31, 0x00, 0x6c, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x20, 0x00, 0x46, 0x00, 0x53, 0x00
, 0x2d, 0x00, 0x27, 0x00, 0x22, 0x00, 0x3d, 0x00, 0x4d, 0x00, 0x4b, 0x00, 0x74, 0x00, 0x28, 0x00
, 0x2e, 0x00, 0x6a, 0x00, 0x54, 0x00, 0x5a, 0x00, 0x64, 0x00, 0x74, 0x00, 0x60, 0x00, 0x76, 0x00
, 0x38, 0x00, 0x68, 0x00, 0x50, 0x00, 0x75, 0x00, 0x2e, 0x00, 0x37, 0x00, 0x52, 0x00, 0x4b, 0x00
, 0x28, 0x00, 0x5d, 0x00, 0x76, 0x00, 0x4d, 0x00, 0x5b, 0x00, 0x33, 0x00, 0x6e, 0x00, 0x6b, 0x00
, 0x49, 0x00, 0x47, 0x00, 0x58, 0x00, 0x60, 0x00, 0x7a, 0x00, 0x77, 0x00, 0x5c, 0x00, 0x26, 0x00
, 0x48, 0x00, 0x6c, 0x00, 0x29, 0x00, 0x64, 0x00, 0x23, 0x00, 0x25, 0x00, 0x4e, 0x00, 0x54, 0x00
, 0x60, 0x00, 0x69, 0x00, 0x73, 0x00, 0x67, 0x00, 0x6c, 0x00, 0x4c, 0x00, 0x29, 0x00, 0x46, 0x00
, 0x75, 0x00, 0x6d, 0x00, 0x72, 0x00, 0x24, 0x00, 0x5d, 0x00, 0x2b, 0x00, 0x70, 0x00, 0x4c, 0x00
, 0x64, 0x00, };
    unsigned char clientChallengeCaptureSamba4[] = {
 0x4e, 0x00, 0x47, 0xa6, 0x75, 0x8b, 0xeb, 0x79 };
    unsigned char serverChallengeCaptureSamba4[] = {
 0xa7, 0x4c, 0x75, 0x78, 0x56, 0xa3, 0xe0, 0x78 };
    unsigned char clientCredentialCaptureSamba4[] = {
 0xb4, 0x41, 0x72, 0x25, 0xbc, 0x7c, 0xbe, 0x59 };
    unsigned char serverCredentialCaptureSamba4[] = {
 0x5d, 0xe8, 0x64, 0xca, 0x7f, 0x58, 0x47, 0xe8 };
#endif

    unsigned char sessionKeyAes[16] = {0};
    unsigned char cliCredential[8] = {0};
    unsigned char srvCredential[8] = {0};

    unsigned char sessionKeyAesSamba4[16] = {0};
    unsigned char cliCredentialSamba4[8] = {0};
    unsigned char srvCredentialSamba4[8] = {0};
    NTSTATUS ntStatus = 0;

    ntStatus = ComputeSessionKeyAes(
                   unicodePwd,
                   sizeof(unicodePwd),
                   clientChallengeCapture,
                   sizeof(clientChallengeCapture),
                   serverChallengeCapture,
                   sizeof(serverChallengeCapture),
                   sessionKeyAes,
                   sizeof(sessionKeyAes));
    if (ntStatus)
    {
        printf("ComputeSessionKeyAes() failed\n");
    }
    else
    {
        printf("AES session key computed:\n");
        printhex(sessionKeyAes, sizeof(sessionKeyAes));
        printf("\n");
    }

    ntStatus = ComputeNetlogonCredentialAes(
                   clientChallengeCapture,
                   sizeof(clientChallengeCapture),
                   sessionKeyAes,
                   sizeof(sessionKeyAes),
                   cliCredential,
                   sizeof(cliCredential));
    if (ntStatus)
    {
        printf("ComputeNetlogonCredentialAes() failed\n");
    }
    else
    {
        printf("\n");
        printf("AES client credential computed:\n");
        printhex(cliCredential, sizeof(cliCredential));
        printf("\n");
        printf("AES client credential from W2K8 client:\n");
        printhex(clientCredentialCapture, sizeof(clientCredentialCapture));
        printf("\n");
        if (memcmp(cliCredential,
                   clientCredentialCapture,
                   sizeof(clientCredentialCapture)) == 0)
        {
            printf("SUCCESS: cliCredential matches!!!\n");
        }
    }

    ntStatus = ComputeNetlogonCredentialAes(
                   serverChallengeCapture,
                   sizeof(serverChallengeCapture),
                   sessionKeyAes,
                   sizeof(sessionKeyAes),
                   srvCredential,
                   sizeof(srvCredential));
    if (ntStatus)
    {
        printf("ComputeNetlogonCredentialAes() failed\n");
    }
    else
    {
        printf("\n");
        printf("AES server credential computed:\n");
        printhex(srvCredential, sizeof(srvCredential));
        printf("\n");
        printf("\n");
        printf("AES server credential packet capture :\n");
        printhex(serverCredentialCapture, sizeof(serverCredentialCapture));
        printf("\n");
    }

/* ======= Samba 4 join credential computation  ========= */
    ntStatus = ComputeSessionKeyAes(
                   unicodePwdSamba4,
                   sizeof(unicodePwdSamba4),
                   clientChallengeCaptureSamba4,
                   sizeof(clientChallengeCaptureSamba4),
                   serverChallengeCaptureSamba4,
                   sizeof(serverChallengeCaptureSamba4),
                   sessionKeyAesSamba4,
                   sizeof(sessionKeyAesSamba4));
    if (ntStatus)
    {
        printf("ComputeSessionKeyAes(samba4) failed\n");
    }
    else
    {
        printf("\n");
        printf("AES session key computed samba4:\n");
        printhex(sessionKeyAesSamba4, sizeof(sessionKeyAesSamba4));
        printf("\n");
    }

    ntStatus = ComputeNetlogonCredentialAes(
                   clientChallengeCaptureSamba4,
                   sizeof(clientChallengeCaptureSamba4),
                   sessionKeyAesSamba4,
                   sizeof(sessionKeyAesSamba4),
                   cliCredentialSamba4,
                   sizeof(cliCredentialSamba4));
    if (ntStatus)
    {
        printf("ComputeNetlogonCredentialAes(Samba4) failed\n");
    }
    else
    {
        printf("\n");
        printf("AES client credential computed Samba4:\n");
        printhex(cliCredentialSamba4, sizeof(cliCredentialSamba4));
        printf("\n");
        printf("AES client credential from W2K8 client Samba4:\n");
        printhex(clientCredentialCaptureSamba4, sizeof(clientCredentialCaptureSamba4));
        printf("\n");
        if (memcmp(cliCredentialSamba4,
                   clientCredentialCaptureSamba4,
                   sizeof(clientCredentialCaptureSamba4)) == 0)
        {
            printf("SUCCESS: cliCredential matches!!!\n");
        }
    }

    ntStatus = ComputeNetlogonCredentialAes(
                   serverChallengeCaptureSamba4,
                   sizeof(serverChallengeCaptureSamba4),
                   sessionKeyAesSamba4,
                   sizeof(sessionKeyAesSamba4),
                   srvCredentialSamba4,
                   sizeof(srvCredentialSamba4));
    if (ntStatus)
    {
        printf("ComputeNetlogonCredentialAes(Samba4) failed\n");
    }
    else
    {
        printf("\n");
        printf("AES server credential computed Samba4:\n");
        printhex(srvCredentialSamba4, sizeof(srvCredentialSamba4));
        printf("\n");
        printf("AES server credential packet capture Samba4:\n");
        printhex(serverCredentialCaptureSamba4, sizeof(serverCredentialCaptureSamba4));
        printf("\n");
    }
    return 0;
}
