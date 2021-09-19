#pragma once

#include <main_window.h>
#include <string>

class Window : private MainWindow {
public:
    struct Config {
        int height;
        int width;
        int positionY = 0;
        int positionX = 0;
        int textColor;
        int windowinColor;
        std::string name;
    };

    Window(const Config);

    ~Window();

    Window(Window&& other)
    {
        _ptrWindow = other._ptrWindow;
        _config = other._config;
        _textBuffer = std::move(other._textBuffer);

        removeSubscriber(&other);
        addSubscriber(this);

        other._ptrWindow = nullptr;
    }

    Window& operator=(Window&& other)
    {
        if (this != &other) {
            _ptrWindow = other._ptrWindow;
            _config = other._config;
            _textBuffer = std::move(other._textBuffer);

            removeSubscriber(&other);
            addSubscriber(this);

            other._ptrWindow = nullptr;
        }
        return *this;
    }

    void setName(const std::string&);

    void setTextByPosition(const std::string&, int, int);

    void refresh() const;

    void clear();

protected:
    virtual void update() override;

private:
    static constexpr int POSITION_WINDOW_NAME = 1;

    void create();

    void setTextColorAndWindowsColor() const;

    void updateName() const;

    void updateText() const;

    WINDOW* _ptrWindow;
    Config _config;
    short _pairColor;
    std::vector<char> _textBuffer;
};
