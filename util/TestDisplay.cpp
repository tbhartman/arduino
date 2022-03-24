#include "TestDisplay.h"

#include "clib/u8g2.h"

#include <iostream>
#include <fstream>

static std::vector<TestDisplay*> test_displays;

struct TDAccessor {
    static bool Is(TestDisplay* td, u8x8_t* u8x8) {
        if (td == nullptr) {
            std::cout << "td is nullptr" << std::endl;
            return false;
        }
        std::cout << u8g2_GetU8x8(td->u8g2) << " " << u8x8 << std::endl;
        return u8g2_GetU8x8(td->u8g2) == u8x8;
    }
    static TestDisplayContents* GetContents(TestDisplay* td) {
        if (td == nullptr) {
            return nullptr;
        }
        return &td->contents;
    }
    static u8g2_struct* GetU8g2(TestDisplay* td) {
        if (td == nullptr) {
            return nullptr;
        }
        return td->u8g2;
    }
};

static uint8_t callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    if (msg != U8X8_MSG_DISPLAY_DRAW_TILE) {
        return 0;
    }

    // get the correct TestDisplay
    std::cout << "callback called" << std::endl;
    std::cout << "len(tds): " << test_displays.size() << std::endl;
    TestDisplay* td = nullptr;
    for (auto &&vp : test_displays)
    {
        td = vp;
        if (TDAccessor::Is(td, u8x8)) {
            break;
        }
    }
    if (td == nullptr) {
        std::cout << "match not found" << std::endl;
        return 0;
    }

    auto u8g2 = TDAccessor::GetU8g2(td);
    auto content = TDAccessor::GetContents(td);
    
    uint8_t *ptr = u8g2_GetBufferPtr(u8g2);
    uint8_t h = u8g2_GetBufferTileHeight(u8g2);
    uint8_t w = u8g2_GetBufferTileWidth(u8g2);

    content->Width = u8g2_GetDisplayWidth(u8g2);
    content->Height = u8g2_GetDisplayHeight(u8g2);
    content->Data.resize(content->Width*content->Height, false);

    uint8_t start = u8g2_GetBufferCurrTileRow(u8g2);

    // loop over tile row [0,h)
    for (uint8_t i = 0; i < h; i++)
    {
        // loop over pixel row [0,8)
        for (uint8_t k = 0; k < 8; k++)
        {
            // loop over tile column [0,w)
            for (uint8_t j = 0; j < w; j++)
            {
                // loop over pixel column [0,8)
                for (uint8_t m = 0; m < 8; m++)
                {
                    uint8_t byte = *(ptr + 8*(i*w+j)+m);
                    bool pixel = ((byte >> k) & 0x1) == 0x1;
                    // determine pixel x,y
                    int x = j*8+m;
                    int y = (start*8) + i*8+k;
                    content->Set(x,y,pixel);
                }
            }
        }
        
    }
    return 0;
}

TestDisplay::TestDisplay(u8g2_struct* u8g2):
    Display(u8g2),
    contents(u8g2_GetDisplayWidth(u8g2), u8g2_GetDisplayHeight(u8g2))
{
    test_displays.push_back(this);
    u8g2_InitDisplay(u8g2);
    u8g2_GetU8x8(u8g2)->display_cb = callback;
}

TestDisplay::~TestDisplay()
{
    for (size_t i = 0; i < test_displays.size(); i++)
    {
        if (test_displays[i] == this) {
            test_displays[i] = nullptr;
        }
    }
    delete u8g2;
}

TestDisplayContents const& TestDisplay::GetContents() const
{
    return contents;
}
