#ifndef HELLHALL_H
#define HELLHALL_H

#include <Windows.h>

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef uint32_t UINT32_T;              // im boojie

#define NtAllocateVirtualMemory_CRC32b 0xE0762FEB
#define NtProtectVirtualMemory_CRC32b 0x5C2D1A97
#define NtCreateThreadEx_CRC32b 0x2073465A
#define NtCreateSection_CRC32b 0x9EEE4B80
#define NtMapViewOfSection_CRC32b 0xA4163EBC
#define NtUnmapViewOfSection_CRC32b 0x90483FF6
#define NtClose_CRC32b 0x0D09C750
#define NtWaitForSingleObject_CRC32b 0xDD554681
#define NtSetInformationFile_CRC32b 0x62EA7CB7
#define NtOpenFile_CRC32b 0xA1B1DC21
#define RtlInitUnicodeString_CRC32b 0x7AA7B69B
#define NtDelayExecution_CRC32b 0xF5A86278
#define NtQuerySystemInformation_CRC32b 0x97FD2398

typedef struct _SysFunc {

	PVOID       pInst;          // address of a 'syscall' instruction in ntdll.dll
	PBYTE       pAddress;       // address of the syscall 
	WORD        wSSN;           // syscall number
	UINT32_T    uHash;          // syscall name hash value

}SysFunc, * PSysFunc;

typedef struct _HellsHallStruct
{
	SysFunc NtAllocateVirtualMemory;
	SysFunc NtProtectVirtualMemory;
	SysFunc NtCreateThreadEx;
	SysFunc NtCreateSection;
	SysFunc NtMapViewOfSection;
	SysFunc NtUnmapViewOfSection;
	SysFunc NtClose;
	SysFunc NtWaitForSingleObject;
	SysFunc RtlInitUnicodeString;
	SysFunc NtSetInformationFile;
	SysFunc NtOpenFile;
	SysFunc NtDelayExecution;
	SysFunc NtQuerySystemInformation;
} HellsHallStruct, *pHellsHallStruct;

// STRING HASHING
uint32_t crc32b(const uint8_t* str);
#define HASH(API)	(crc32b((uint8_t*)API))

// FROM HellsHall.c
BOOL InitilizeSysFunc(IN UINT32_T uSysFuncHash);
VOID getSysFuncStruct(OUT PSysFunc psF);

// FROM AsmHell.asm
extern VOID SetConfig(WORD wSystemCall, PVOID pSyscallInst);
extern HellHall();


//  A MACRO TO MAKE STUFF CLEANER
#define SYSCALL(sF)(SetConfig(sF.wSSN, sF.pInst))

pHellsHallStruct GetHellsHallStruct();
BOOL HellsHallInit();

#endif // !HELLHALL_H







