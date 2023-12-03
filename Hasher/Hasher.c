// Hasher.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

#define SEED        0xEDB88320

uint32_t crc32b(const uint8_t* str) {

    uint32_t    byte = 0x0,
        mask = 0x0,
        crc = 0xFFFFFFFF;
    int         i = 0x0,
        j = 0x0;

    while (str[i] != 0) {
        byte = str[i];
        crc = crc ^ byte;

        for (j = 7; j >= 0; j--) {
            mask = -1 * (crc & 1);
            crc = (crc >> 1) ^ (SEED & mask);
        }

        i++;
    }
    return ~crc;
}

#define HASH(API)	(crc32b((uint8_t*)API))

int main()
{
    printf("#define NtAllocateVirtualMemory_CRC32b 0x%0.8X \n", HASH("NtAllocateVirtualMemory"));
    printf("#define NtProtectVirtualMemory_CRC32b 0x%0.8X \n", HASH("NtProtectVirtualMemory"));
    printf("#define NtCreateThreadEx_CRC32b 0x%0.8X \n", HASH("NtCreateThreadEx"));

    printf("#define NtOpenFile_CRC32b 0x%0.8X \n", HASH("NtOpenFile"));
    printf("#define RtlInitUnicodeString_CRC32b 0x%0.8X \n", HASH("RtlInitUnicodeString"));
    printf("#define NtSetInformationFile_CRC32b 0x%0.8X \n", HASH("NtSetInformationFile"));

    printf("#define NtCreateSection_CRC32b 0x%0.8X \n", HASH("NtCreateSection"));
    printf("#define NtMapViewOfSection_CRC32b 0x%0.8X \n", HASH("NtMapViewOfSection"));
    printf("#define NtUnmapViewOfSection_CRC32b 0x%0.8X \n", HASH("NtUnmapViewOfSection"));

    printf("#define NtClose_CRC32b 0x%0.8X \n", HASH("NtClose"));
    printf("#define NtWaitForSingleObjec_CRC32b 0x%0.8X \n", HASH("NtWaitForSingleObjec"));
    printf("#define CloseHandle_CRC32b 0x%0.8X \n", HASH("CloseHandle")); 

    printf("#define NtWaitForSingleObject_CRC32b 0x%0.8X \n", HASH("NtWaitForSingleObject"));
    printf("#define NtDelayExecution_CRC32b 0x%0.8X \n", HASH("NtDelayExecution"));
    printf("#define NtQuerySystemInformation 0x%0.8X \n", HASH("NtQuerySystemInformation")); 

    // бесконечное ожидание
    WaitForSingleObject((HANDLE)-1, INFINITE);
}
