#include <helper.h>
#include <HellsHall.h>

static HellsHallStruct S = { 0 };

BOOL HellsHallInit() 
{

	RtlSecureZeroMemory(&S, sizeof(HellsHallStruct));

	if (!InitilizeSysFunc(NtAllocateVirtualMemory_CRC32b))
	{
		PRINTA("Fail NtAllocateVirtualMemory init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtAllocateVirtualMemory);

	if (!InitilizeSysFunc(NtProtectVirtualMemory_CRC32b))
	{
		PRINTA("Fail NtProtectVirtualMemor init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtProtectVirtualMemory);

	if (!InitilizeSysFunc(NtCreateThreadEx_CRC32b))
	{
		PRINTA("Fail NtProtectVirtualMemory init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtCreateThreadEx);

	if (!InitilizeSysFunc(NtSetInformationFile_CRC32b))
	{
		PRINTA("Fail NtSetInformationFile init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtSetInformationFile);

	if (!InitilizeSysFunc(NtCreateSection_CRC32b))
	{
		PRINTA("Fail NtCreateSectio init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtCreateSection);

	if (!InitilizeSysFunc(NtMapViewOfSection_CRC32b))
	{
		PRINTA("Fail NtMapViewOfSection init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtMapViewOfSection);

	if (!InitilizeSysFunc(NtUnmapViewOfSection_CRC32b))
	{
		PRINTA("Fail NtUnmapViewOfSectio init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtUnmapViewOfSection);

	if (!InitilizeSysFunc(NtClose_CRC32b))
	{
		PRINTA("Fail NtClose init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtClose);

	if (!InitilizeSysFunc(NtWaitForSingleObject_CRC32b))
	{
		PRINTA("Fail NtWaitForSingleObject init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtWaitForSingleObject);

	if (!InitilizeSysFunc(NtOpenFile_CRC32b))
	{
		PRINTA("Fail NtWaitForSingleObject init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtOpenFile);

	if (!InitilizeSysFunc(NtDelayExecution_CRC32b))
	{
		PRINTA("Fail NtDelayExecution init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtDelayExecution);

	if (!InitilizeSysFunc(NtQuerySystemInformation_CRC32b))
	{
		PRINTA("Fail NtDelayExecution init \n");
		return FALSE;
	}
	getSysFuncStruct(&S.NtQuerySystemInformation);

	return TRUE;
}

pHellsHallStruct GetHellsHallStruct()
{
	return &S;
}
