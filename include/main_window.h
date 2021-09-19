#pragma once

#include <ncurses.h>
#include <vector>

enum class CursorMode {
    INVISIBLE = 0,
    NORMAL = 1,
    HIGH = 2
};

class MainWindow {
public:
    virtual ~MainWindow();

    enum DefaultColor {
        FRONT = COLOR_BLACK,
        BACK = COLOR_BLACK
    };

    void echoEnable() const;

    void echoDisable() const;

    void setAppearanceOfCursor(CursorMode) const;

    void addSubscriber(MainWindow* const);

    void removeSubscriber(MainWindow* const);

protected:
    static constexpr short PAIR_OF_COLORS_OF_MAIN_WINDOW = 1;

    MainWindow();

    virtual void update() = 0;

    void updateAllWindows() const;

    inline static size_t _counterOfInstances = 0;
    inline static WINDOW* _ptrMainWindow = nullptr;

private:
    inline static std::vector<MainWindow*> _windows;
};
