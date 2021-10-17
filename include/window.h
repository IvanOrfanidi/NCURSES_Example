#pragma once

#include <main_window.h>
#include <string>

class Window : private MainWindow {
public:
    class Height {
    public:
        explicit Height(int value) noexcept
            : _value(value)
        {
        }

        int value() const noexcept
        {
            return _value;
        }

    private:
        int _value;
    };

    class Width {
    public:
        explicit Width(int value) noexcept
            : _value(value)
        {
        }

        int value() const noexcept
        {
            return _value;
        }

    private:
        int _value;
    };

    class PositionY {
    public:
        explicit PositionY(int value) noexcept
            : _value(value)
        {
        }

        int value() const noexcept
        {
            return _value;
        }

    private:
        int _value;
    };

    class PositionX {
    public:
        explicit PositionX(int value) noexcept
            : _value(value)
        {
        }

        int value() const noexcept
        {
            return _value;
        }

    private:
        int _value;
    };

    struct Color {
        class Text {
        public:
            Text() noexcept = default;
            Text(int value) noexcept
                : _value(value)
            {
            }

            int value() const noexcept
            {
                return _value;
            }

        private:
            int _value = COLOR_BLACK;
        };

        class Windowin {
        public:
            Windowin() noexcept = default;
            Windowin(int value) noexcept
                : _value(value)
            {
            }

            int value() const noexcept
            {
                return _value;
            }

        private:
            int _value = COLOR_WHITE;
        };
    };

    Window(const Height height,
        const Width width,
        const PositionY positionY,
        const PositionX positionX,
        const Color::Text textColor,
        const Color::Windowin windowinColor,
        const std::string name);

    ~Window();

    Window(Window&& other)
        : _ptrWindow(other._ptrWindow)
        , _height(other._height)
        , _width(other._width)
        , _positionY(other._positionY)
        , _positionX(other._positionX)
        , _textColor(other._textColor)
        , _windowinColor(other._windowinColor)
        , _name(std::move(other._name))
        , _pairColor(other._pairColor)
        , _textBuffer(std::move(other._textBuffer))
    {
        removeSubscriber(&other);
        addSubscriber(this);

        other._ptrWindow = nullptr;
    }

    Window& operator=(Window&& other)
    {
        if (this != &other) {
            _ptrWindow = other._ptrWindow;
            _height = other._height;
            _width = other._width;
            _positionY = other._positionY;
            _positionX = other._positionX;
            _textColor = other._textColor;
            _windowinColor = other._windowinColor;
            _name = std::move(other._name);
            _pairColor = other._pairColor;
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
    Height _height;
    Width _width;
    PositionY _positionY;
    PositionX _positionX;
    Color::Text _textColor;
    Color::Windowin _windowinColor;
    std::string _name;
    short _pairColor;
    std::vector<char> _textBuffer;
};
