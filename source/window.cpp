#include <window.h>

Window::Window(const Height height,
    const Width width,
    const PositionY positionY,
    const PositionX positionX,
    const Color::Text textColor,
    const Color::Windowin windowinColor,
    const std::string name)
    : _ptrWindow(nullptr)
    , _height(height)
    , _width(width)
    , _positionY(positionY)
    , _positionX(positionX)
    , _textColor(textColor)
    , _windowinColor(windowinColor)
    , _name(std::move(name))
    , _pairColor(_counterOfInstances + 1)
{
    create();
    setTextColorAndWindowsColor();

    updateName();
    const size_t size = (_height.value() - 2) * (_width.value() - 2);
    _textBuffer.resize(size);

    std::fill(_textBuffer.begin(), _textBuffer.end(), ' ');

    addSubscriber(this);
    refresh();
}

Window::~Window()
{
    if (_ptrWindow != nullptr) {
        wbkgd(_ptrWindow, COLOR_PAIR(PAIR_OF_COLORS_OF_MAIN_WINDOW));
        color_set(1, NULL);
        clear();
        removeSubscriber(this);
        updateAllWindows();
        delwin(_ptrWindow);
    }
}

void Window::setTextColorAndWindowsColor() const
{
    init_pair(_pairColor, _textColor.value(), _windowinColor.value());
    wbkgd(_ptrWindow, COLOR_PAIR(_pairColor));
    wcolor_set(_ptrWindow, _pairColor, NULL);
}

void Window::updateName() const
{
    if (!_name.empty()) {
        mvwaddstr(_ptrWindow, 0, POSITION_WINDOW_NAME, _name.data());
    }
}

void Window::updateText() const
{
    size_t j = 0;
    for (int i = 1; i < _height.value() - 1; ++i) {
        for (int n = 1; n < _width.value() - 1; ++n) {
            char arrSumb[2] = { '\0', '\0' };
            arrSumb[0] = _textBuffer[j++];
            mvwaddstr(_ptrWindow, i, n, arrSumb);
        }
    }
    refresh();
}

void Window::setName(const std::string& name)
{
    _name = name;
    updateName();
}

void Window::setTextByPosition(const std::string& text, int positionY, int positionX)
{
    const size_t position = (positionY * (_width.value() - 2)) + positionX;
    std::copy(text.cbegin(), text.cend(), _textBuffer.begin() + position);
    updateText();
}

void Window::create()
{
    _ptrWindow = newwin(_height.value(), _width.value(), _positionY.value(), _positionX.value());
    box(_ptrWindow, 0, 0);
}

void Window::clear()
{
    std::fill(_textBuffer.begin(), _textBuffer.end(), ' ');
    updateText();
}

void Window::update()
{
    delwin(_ptrWindow);
    create();
    setTextColorAndWindowsColor();
    updateName();
    updateText();
}

void Window::refresh() const
{
    wrefresh(_ptrWindow);
}