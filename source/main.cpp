#include <stdio.h>
#include <stdlib.h>
#include <window.h>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Tm_Window win1({ 3, 10, 5, 0, COLOR_RED, COLOR_GREEN, "Win_1" });
    win1.SetTextByPosition("||||", 0, 4);
    getchar();

    Tm_Window win2({ 10, 10, 0, 12, COLOR_YELLOW, COLOR_MAGENTA, "Win_2" });
    win2.SetTextByPosition("Windows #1", 2, 0);
    getchar();

    {
        Tm_Window win3({ 8, 8, 0, 0, COLOR_GREEN, COLOR_BLUE, "Win_3" });
        win3.SetTextByPosition("Windows #2", 0, 0);
        getchar();
    }

    getchar();
    Tm_Window win4({ 3, 15, 0, 24, COLOR_GREEN, COLOR_RED, "Win_4" });
    win4.SetTextByPosition("||||||||", 0, 0);

    getchar();
    Tm_Window win5 = std::move(win1);
    win5.Clear();
    win5.SetTextByPosition("Win #5", 0, 0);
    getchar();

    return 0;
}
