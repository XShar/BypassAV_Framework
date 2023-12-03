#include "helper.h"

/*
 * Работает только при отключенной оптимизации в проекте
 */

DWORD FakeIat()
{
    // Получение количества миллисекунд с момента запуска системы
    DWORD tickCount = GetTickCount();

    // Невозможное if-условие, которое никогда не выполнится
    if (tickCount < 0) {
        // Случайные доброжелательные WinAPI
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

