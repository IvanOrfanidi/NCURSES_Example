#ifndef __WINDOW_H
#define __WINDOW_H

#include <main_window.h>
#include <ncurses.h>
#include <string>

class Tm_Window : public Tm_MainWindow {
public:
    struct Tm_Config {
        int m_nHeight;
        int m_nWidth;
        int m_nPositionY = 0;
        int m_nPositionX = 0;
        int m_nTextColor;
        int m_nWinColor;
        std::string m_strName;
    };

    Tm_Window(const Tm_Config Config);

    ~Tm_Window();

    Tm_Window(Tm_Window&& other)
    {
        m_pWindow = other.m_pWindow;
        m_Config = other.m_Config;
        m_vTextBuffer = std::move(other.m_vTextBuffer);

        RemoveSubscriber(&other);
        AddSubscriber(this);

        other.m_pWindow = nullptr;
    }

    Tm_Window& operator=(Tm_Window&& other)
    {
        if (this != &other) {
            m_pWindow = other.m_pWindow;
            m_Config = other.m_Config;
            m_vTextBuffer = std::move(other.m_vTextBuffer);

            RemoveSubscriber(&other);
            AddSubscriber(this);

            other.m_pWindow = nullptr;
        }
        return *this;
    }

    void SetName(const std::string& strName);

    void SetTextByPosition(const std::string& strText, int nPositionY, int nPositionX);

    void Refresh() const
    {
        wrefresh(m_pWindow);
    }

    void Clear();

protected:
    void Update() override;

private:
    static constexpr int POSITION_WINDOW_NAME = 1;

    void Create();

    void SetTextColorAndWindowsColor() const;

    void UpdateName() const;

    void UpdateText() const;

    WINDOW* m_pWindow;
    Tm_Config m_Config;
    short m_nNumPairColor;
    std::vector<char> m_vTextBuffer;
};

#endif /* __WINDOW_H */