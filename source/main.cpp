#include <stdio.h>
#include <stdlib.h>
#include <window.h>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Window win1({ 3, 15, 5, 0, COLOR_RED, COLOR_GREEN, "Win_1" });
    win1.setTextByPosition("Windows #1", 0, 0);
    getchar();

    Window win2({ 10, 15, 0, 16, COLOR_YELLOW, COLOR_MAGENTA, "Win_2" });
    win2.setTextByPosition("Windows #2", 2, 0);
    getchar();

    {
        Window win3({ 8, 15, 0, 0, COLOR_GREEN, COLOR_BLUE, "Win_3" });
        win3.setTextByPosition("Windows #3", 0, 0);
        getchar();
    }

    getchar();
    Window win4({ 3, 15, 0, 32, COLOR_GREEN, COLOR_RED, "Win_4" });
    win4.setTextByPosition("Windows #4", 0, 0);

    getchar();
    Window win5 = std::move(win1);
    win5.setName("Win_5");
    win5.setTextByPosition("Windows #5", 0, 0);

    getchar();

    return 0;
}
