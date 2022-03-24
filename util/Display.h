#pragma once

#include <cstdint>
#include <iostream>

struct u8g2_struct;
class Display;

typedef void (*Displayer)(Display*);

class Display
{
  public:
    Display(u8g2_struct *u8g2);
    Display(const Display& other);
    Display& operator=(Display& other) noexcept;
    ~Display();

    // would like to have for-range iterator...not working yet
    class Iterator {
        Display* display;
      public:
        Iterator()=delete;
        Iterator(Display* display);
        Iterator(const Iterator& other);
        Iterator& operator=(Iterator& other) noexcept;
        ~Iterator() = default;

        Display const & operator*() const;
        Iterator const & operator++();
        bool operator!=(Iterator const&) const;
    };
    inline Iterator begin() {
        std::cout << "begin()" << std::endl;
        return Iterator(this);
    }
    inline Iterator end() {
        std::cout << "end()" << std::endl;
        return Iterator(nullptr);
    }

    void FirstPage();
    bool NextPage();
    void Update(Displayer);

    void SetFont(const uint8_t* fontName);
    void SetColor(bool);
    void DrawString(uint16_t x, uint16_t y, const char* content);
    void DrawPixel(uint16_t x, uint16_t y);
    void DrawHline(uint16_t x, uint16_t y, uint16_t length);
    void DrawVline(uint16_t x, uint16_t y, uint16_t length);
  protected:
    u8g2_struct* u8g2;
};
