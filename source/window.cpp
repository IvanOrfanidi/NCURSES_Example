#include <window.h>

Tm_Window::Tm_Window(const Tm_Config Config)
    : m_pWindow(nullptr)
    , m_Config(Config)
{
    Create();
    m_nNumPairColor = m_nCounterOfInstances + 1;
    SetTextColorAndWindowsColor();

    UpdateName();
    const size_t nSize = (m_Config.m_nHeight - 2) * (m_Config.m_nWidth - 2);
    m_vTextBuffer.reserve(nSize);
    m_vTextBuffer.resize(nSize);

    std::fill(m_vTextBuffer.begin(), m_vTextBuffer.end(), ' ');

    AddSubscriber(this);
    Refresh();
}

Tm_Window::~Tm_Window()
{
    if (m_pWindow != nullptr) {
        wbkgd(m_pWindow, COLOR_PAIR(PAIR_OF_COLORS_OF_MAIN_WINDOW));
        color_set(1, NULL);
        Clear();
        RemoveSubscriber(this);
        UpdateAllWindows();
        delwin(m_pWindow);
    }
}

void Tm_Window::SetTextColorAndWindowsColor() const
{
    init_pair(m_nNumPairColor, m_Config.m_nTextColor, m_Config.m_nWinColor);
    wbkgd(m_pWindow, COLOR_PAIR(m_nNumPairColor));
    wcolor_set(m_pWindow, m_nNumPairColor, NULL);
}

void Tm_Window::UpdateName() const
{
    if (!m_Config.m_strName.empty()) {
        mvwaddstr(m_pWindow, 0, POSITION_WINDOW_NAME, m_Config.m_strName.data());
    }
}

void Tm_Window::UpdateText() const
{
    size_t j = 0;
    for (int i = 1; i < m_Config.m_nHeight - 1; ++i) {
        for (int n = 1; n < m_Config.m_nWidth - 1; ++n) {
            char arrSumb[2] = { '\0', '\0' };
            arrSumb[0] = m_vTextBuffer[j++];
            mvwaddstr(m_pWindow, i, n, arrSumb);
        }
    }
    Refresh();
}

void Tm_Window::SetName(const std::string& strName)
{
    m_Config.m_strName = strName;
    UpdateName();
}

void Tm_Window::SetTextByPosition(const std::string& strText, int nPositionY, int nPositionX)
{
    const size_t nPosition = (nPositionY * (m_Config.m_nWidth - 2)) + nPositionX;
    std::copy(strText.cbegin(), strText.cend(), m_vTextBuffer.begin() + nPosition);
    UpdateText();
}

void Tm_Window::Create()
{
    m_pWindow = newwin(m_Config.m_nHeight, m_Config.m_nWidth, m_Config.m_nPositionY, m_Config.m_nPositionX);
    box(m_pWindow, 0, 0);
}

void Tm_Window::Clear()
{
    std::fill(m_vTextBuffer.begin(), m_vTextBuffer.end(), ' ');
    UpdateText();
}

void Tm_Window::Update()
{
    delwin(m_pWindow);
    Create();
    SetTextColorAndWindowsColor();
    UpdateName();
    UpdateText();
}
