#include <main_window.h>

#include <algorithm>
#include <iostream>

MainWindow::MainWindow()
{
    if (initscr() == nullptr) {
        throw std::runtime_error("Cannot initialising ncurses");
    }

    if (_counterOfInstances++ == 0) {
        cbreak();
        nonl();
        echoDisable();
        setAppearanceOfCursor(CursorMode::INVISIBLE);
        refresh();
        start_color();

        init_pair(1, DefaultColor::FRONT, DefaultColor::BACK);
        _ptrMainWindow = newwin(LINES, COLS, 0, 0);
        wbkgd(_ptrMainWindow, COLOR_PAIR(PAIR_OF_COLORS_OF_MAIN_WINDOW));
        color_set(1, NULL);
        wrefresh(_ptrMainWindow);
    }
}

MainWindow::~MainWindow()
{
    if (--_counterOfInstances == 0) {
        endwin();
    }
}

void MainWindow::echoEnable() const
{
    echo();
}

void MainWindow::echoDisable() const
{
    noecho();
}

void MainWindow::addSubscriber(MainWindow* const ptrWindow)
{
    _windows.push_back(ptrWindow);
}

void MainWindow::removeSubscriber(MainWindow* const ptrWindow)
{
    _windows.erase(std::find(_windows.begin(), _windows.end(), ptrWindow));
}

void MainWindow::setAppearanceOfCursor(CursorMode cursor) const
{
    curs_set(static_cast<int>(cursor));
}

void MainWindow::updateAllWindows() const
{
    for (auto const ptrWindow : _windows) {
        ptrWindow->update();
    }
}