#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H

#include <algorithm>
#include <ncurses.h>
#include <vector>

enum class En_CursorMode {
    INVISIBLE = 0,
    NORMAL = 1,
    HIGH = 2
};

class Tm_MainWindow {
public:
    ~Tm_MainWindow();

    enum En_DefaultColor {
        FRONT = COLOR_BLACK,
        BACK = COLOR_BLACK
    };

    void SetEcho(bool lEcho) const
    {
        if (lEcho) {
            echo();
        } else {
            noecho();
        }
    }

    void SetAppearanceOfCursor(En_CursorMode enCursor) const
    {
        curs_set((int)enCursor);
    }

    void AddSubscriber(Tm_MainWindow* const pWindow)
    {
        m_vptrWindows.push_back(pWindow);
    }

    void RemoveSubscriber(Tm_MainWindow* const pWindow)
    {
        m_vptrWindows.erase(std::find(m_vptrWindows.begin(), m_vptrWindows.end(), pWindow));
    }

protected:
    static constexpr short PAIR_OF_COLORS_OF_MAIN_WINDOW = 1;

    Tm_MainWindow();

    virtual void Update() = 0;

    void UpdateAllWindows() const;

    static size_t m_nCounterOfInstances;
    static WINDOW* m_pMainWindow;

private:
    static std::vector<Tm_MainWindow*> m_vptrWindows;
};

#endif /* __MAIN_WINDOW_H */