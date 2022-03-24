#include "Display.h"

#include "clib/u8g2.h"

#include <iostream>

Display::Display(u8g2_t *u8g2):
  u8g2(u8g2)
{}
Display::Display(const Display& other):
    u8g2(other.u8g2)
{
}
Display& Display::operator=(Display& other) noexcept
{
    auto ptr = other.u8g2;
    other.u8g2 = this->u8g2;
    this->u8g2 = ptr;
    return *this;
}
Display::~Display()
{
    delete u8g2;
}

void Display::SetFont(const uint8_t* fontName)
{
    u8g2_SetFont(u8g2, fontName);
}

void Display::SetColor(bool value)
{
    u8g2_SetDrawColor(u8g2, value ? 1 : 0);
}
void Display::DrawString(uint16_t x, uint16_t y, const char* content)
{
    u8g2_DrawStr(u8g2, x, y, content);
}
void Display::DrawPixel(uint16_t x, uint16_t y)
{
    u8g2_DrawPixel(u8g2, x, y);
}
void Display::DrawHline(uint16_t x, uint16_t y, uint16_t length)
{
    u8g2_DrawHLine(u8g2, x, y, length);
}
void Display::DrawVline(uint16_t x, uint16_t y, uint16_t length)
{
    u8g2_DrawVLine(u8g2, x, y, length);
}

void Display::Update(Displayer f) {
    this->FirstPage();
    do {
        f(this);
    } while (this->NextPage());
}

void Display::FirstPage()
{
    u8g2_FirstPage(u8g2);
}
bool Display::NextPage()
{
    return u8g2_NextPage(u8g2) == 1 ? true : false;
}

Display::Iterator::Iterator(Display* display):
    display(display)
{
    std::cout << "start iterator with " << (display == nullptr ? "null" : "non-null" ) << std::endl;
    if (this->display != nullptr)
        u8g2_FirstPage(this->display->u8g2);
}
Display const & Display::Iterator::operator*() const
{
    std::cout << "  operator*" << std::endl;
    return *display;
}
Display::Iterator const & Display::Iterator::operator++()
{
    std::cout << "  increment iterator?" << std::endl;
    if (u8g2_NextPage(this->display->u8g2) == 0) {
        std::cout << "  iterator end" << std::endl;
        this->display = nullptr;
    }
    std::cout << "  increment iterator" << std::endl;
    return *this;
}
bool Display::Iterator::operator!=(Iterator const& other) const
{
    std::cout << "  iterator test: " << (this->display != other.display ? "true" : "false") << std::endl;
    return this->display != other.display;
}

Display::Iterator::Iterator(const Display::Iterator& other):
    display(other.display)
{
    std::cout << "copy" << std::endl;
}
Display::Iterator& Display::Iterator::operator=(Display::Iterator& other) noexcept
{
    std::cout << "copy assignment" << std::endl;
    Iterator* i = new Iterator(other.display);
    return *i;
}
