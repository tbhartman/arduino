#include "Screen.h"

#include "clib/u8g2.h"

#include <iostream>

#include "Contents.h"

using namespace Display;

Screen::Screen(u8g2_t *u8g2):
  u8g2(u8g2)
{}
Screen::Screen(const Screen& other):
    u8g2(other.u8g2)
{
}
Screen& Screen::operator=(Screen& other) noexcept
{
    auto ptr = other.u8g2;
    other.u8g2 = this->u8g2;
    this->u8g2 = ptr;
    return *this;
}
Screen::~Screen()
{
    this->u8g2 = nullptr;
}

void Screen::SetFont(const uint8_t* fontName)
{
    u8g2_SetFont(u8g2, fontName);
}

void Screen::SetColor(bool value)
{
    u8g2_SetDrawColor(u8g2, value ? 1 : 0);
}
void Screen::DrawString(uint16_t x, uint16_t y, const char* content)
{
    u8g2_DrawStr(u8g2, x, y, content);
}
void Screen::DrawPixel(uint16_t x, uint16_t y)
{
    u8g2_DrawPixel(u8g2, x, y);
}
void Screen::DrawHline(uint16_t x, uint16_t y, uint16_t length)
{
    u8g2_DrawHLine(u8g2, x, y, length);
}
void Screen::DrawVline(uint16_t x, uint16_t y, uint16_t length)
{
    u8g2_DrawVLine(u8g2, x, y, length);
}

void Screen::Update(Updater f) {
    this->FirstPage();
    do {
        f(this);
    } while (this->NextPage());
}

void Screen::Apply(uint16_t x, uint16_t y, Contents::Reader* r) {
    for (size_t i = 0; i < r->Width(); i++)
    {
        for (size_t j = 0; j < r->Height(); j++)
        {
            if (r->At(i,j)) {
                this->DrawPixel(x+i, y+j);
            }
        }
    }
}

void Screen::FirstPage()
{
    u8g2_FirstPage(u8g2);
}
bool Screen::NextPage()
{
    return u8g2_NextPage(u8g2) == 1 ? true : false;
}

Screen::Iterator::Iterator(Screen* display):
    display(display)
{
    std::cout << "start iterator with " << (display == nullptr ? "null" : "non-null" ) << std::endl;
    if (this->display != nullptr)
        u8g2_FirstPage(this->display->u8g2);
}
Screen const & Screen::Iterator::operator*() const
{
    std::cout << "  operator*" << std::endl;
    return *display;
}
Screen::Iterator const & Screen::Iterator::operator++()
{
    std::cout << "  increment iterator?" << std::endl;
    if (u8g2_NextPage(this->display->u8g2) == 0) {
        std::cout << "  iterator end" << std::endl;
        this->display = nullptr;
    }
    std::cout << "  increment iterator" << std::endl;
    return *this;
}
bool Screen::Iterator::operator!=(Iterator const& other) const
{
    std::cout << "  iterator test: " << (this->display != other.display ? "true" : "false") << std::endl;
    return this->display != other.display;
}

Screen::Iterator::Iterator(const Screen::Iterator& other):
    display(other.display)
{
    std::cout << "copy" << std::endl;
}
Screen::Iterator& Screen::Iterator::operator=(Screen::Iterator& other) noexcept
{
    std::cout << "copy assignment" << std::endl;
    Iterator* i = new Iterator(other.display);
    return *i;
}
