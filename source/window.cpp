#include <window.h>

Window::Window(const Config config)
    : _ptrWindow(nullptr)
    , _config(std::move(config))
    , _pairColor(_counterOfInstances + 1)
{
    create();
    setTextColorAndWindowsColor();

    updateName();
    const size_t size = (_config.height - 2) * (_config.width - 2);
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
    init_pair(_pairColor, _config.textColor, _config.windowinColor);
    wbkgd(_ptrWindow, COLOR_PAIR(_pairColor));
    wcolor_set(_ptrWindow, _pairColor, NULL);
}

void Window::updateName() const
{
    if (!_config.name.empty()) {
        mvwaddstr(_ptrWindow, 0, POSITION_WINDOW_NAME, _config.name.data());
    }
}

void Window::updateText() const
{
    size_t j = 0;
    for (int i = 1; i < _config.height - 1; ++i) {
        for (int n = 1; n < _config.width - 1; ++n) {
            char arrSumb[2] = { '\0', '\0' };
            arrSumb[0] = _textBuffer[j++];
            mvwaddstr(_ptrWindow, i, n, arrSumb);
        }
    }
    refresh();
}

void Window::setName(const std::string& name)
{
    _config.name = name;
    updateName();
}

void Window::setTextByPosition(const std::string& text, int positionY, int positionX)
{
    const size_t position = (positionY * (_config.width - 2)) + positionX;
    std::copy(text.cbegin(), text.cend(), _textBuffer.begin() + position);
    updateText();
}

void Window::create()
{
    _ptrWindow = newwin(_config.height, _config.width, _config.positionY, _config.positionX);
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