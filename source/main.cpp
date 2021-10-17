#include <stdio.h>
#include <stdlib.h>
#include <window.h>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Window win1(Window::Height{ 3 },
        Window::Width{ 15 },
        Window::PositionY{ 5 },
        Window::PositionX{ 0 },
        Window::Color::Text{ COLOR_RED },
        Window::Color::Windowin{ COLOR_GREEN },
        "Win_1");
    win1.setTextByPosition("Windows #1", 0, 0);
    getchar();

    Window win2(Window::Height{ 10 },
        Window::Width{ 15 },
        Window::PositionY{ 0 },
        Window::PositionX{ 16 },
        Window::Color::Text{},
        Window::Color::Windowin{},
        "Win_2");
    win2.setTextByPosition("Windows #2", 2, 0);
    getchar();

    {
        Window win3(Window::Height{ 8 },
            Window::Width{ 15 },
            Window::PositionY{ 0 },
            Window::PositionX{ 0 },
            Window::Color::Text{ COLOR_GREEN },
            Window::Color::Windowin{ COLOR_BLUE },
            "Win_3");
        win3.setTextByPosition("Windows #3", 0, 0);
        getchar();
    }

    getchar();
    Window win4(Window::Height{ 3 },
        Window::Width{ 15 },
        Window::PositionY{ 0 },
        Window::PositionX{ 32 },
        Window::Color::Text{ COLOR_GREEN },
        Window::Color::Windowin{ COLOR_RED },
        "Win_4");
    win4.setTextByPosition("Windows #4", 0, 0);
    getchar();

    getchar();
    Window win5 = std::move(win1);
    win5.setName("Win_5");
    win5.setTextByPosition("Windows #5", 0, 0);

    getchar();

    return EXIT_SUCCESS;
}
