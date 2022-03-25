#pragma once

#include <cstdint>
#include <iostream>

struct u8g2_struct;

namespace Display {

namespace Contents {
  class Reader;
}

class Screen;

typedef void (*Updater)(Screen*);

class Screen
{
  public:
    Screen(u8g2_struct *u8g2);
    Screen(const Screen& other);
    Screen& operator=(Screen& other) noexcept;
    ~Screen();

    // would like to have for-range iterator...not working yet
    class Iterator {
        Screen* display;
      public:
        Iterator()=delete;
        Iterator(Screen* display);
        Iterator(const Iterator& other);
        Iterator& operator=(Iterator& other) noexcept;
        ~Iterator() = default;

        Screen const & operator*() const;
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
    void Update(Updater);
    void Apply(uint16_t x, uint16_t y, Contents::Reader* r);

    void SetFont(const uint8_t* fontName);
    void SetColor(bool);
    void DrawString(uint16_t x, uint16_t y, const char* content);
    void DrawPixel(uint16_t x, uint16_t y);
    void DrawHline(uint16_t x, uint16_t y, uint16_t length);
    void DrawVline(uint16_t x, uint16_t y, uint16_t length);
  protected:
    u8g2_struct* u8g2;
};

}
