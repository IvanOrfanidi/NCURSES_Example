#include <iostream>
#include <main_window.h>

size_t Tm_MainWindow::m_nCounterOfInstances = 0;
WINDOW* Tm_MainWindow::m_pMainWindow = nullptr;
std::vector<Tm_MainWindow*> Tm_MainWindow::m_vptrWindows;

Tm_MainWindow::Tm_MainWindow()
{
    if (initscr() == nullptr) {
        throw std::runtime_error("Cannot initialising ncurses");
    }

    if (m_nCounterOfInstances++ == 0) {
        cbreak();
        nonl();
        SetEcho(false);
        SetAppearanceOfCursor(En_CursorMode::INVISIBLE);
        refresh();
        start_color();

        init_pair(1, En_DefaultColor::FRONT, En_DefaultColor::BACK);
        m_pMainWindow = newwin(LINES, COLS, 0, 0);
        wbkgd(m_pMainWindow, COLOR_PAIR(PAIR_OF_COLORS_OF_MAIN_WINDOW));
        color_set(1, NULL);
        wrefresh(m_pMainWindow);
    }
}

Tm_MainWindow::~Tm_MainWindow()
{
    if (--m_nCounterOfInstances == 0) {
        endwin();
    }
}

void Tm_MainWindow::UpdateAllWindows() const
{
    for (auto const ptrWindowItem : m_vptrWindows) {
        ptrWindowItem->Update();
    }
}