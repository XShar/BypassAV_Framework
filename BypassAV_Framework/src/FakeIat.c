#include "helper.h"

/*
 * �������� ������ ��� ����������� ����������� � �������
 */

DWORD FakeIat()
{
    // ��������� ���������� ����������� � ������� ������� �������
    DWORD tickCount = GetTickCount();

    // ����������� if-�������, ������� ������� �� ����������
    if (tickCount < 0) {
        // ��������� ���������������� WinAPI
        unsigned __int64 i = MessageBoxA(NULL, NULL, NULL, NULL);
        i = GetLastError();
        i = SetCriticalSectionSpinCount(NULL, NULL);
        i = GetWindowContextHelpId(NULL);
        i = GetWindowLongPtrW(NULL, NULL);
        i = RegisterClassW(NULL);
        i = IsWindowVisible(NULL);
        i = ConvertDefaultLocale(NULL);
        i = MultiByteToWideChar(NULL, NULL, NULL, NULL, NULL, NULL);
        i = IsDialogMessageW(NULL, NULL);
    }
    return tickCount;
}

