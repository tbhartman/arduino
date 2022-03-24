#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "blinker.h"

#include "clib/u8g2.h"
#include "toU8i.h"
#include "stdio.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "util/TestDisplay.h"
#include "util/IsScreen.h"
#include "util/fonts.h"


void a(u8g2_t *u8g2) {
}

TEST_CASE( "My function works" ) {
    u8g2_t u8g2;
    // u8g2_Setup_ssd1306_i2c_128x32_univision_1((u8g2_t *)&u8g2, U8G2_R0, u8x8_dummy_cb, u8x8_dummy_cb);
    u8g2_Setup_ssd1306_i2c_128x32_univision_1((u8g2_t *)&u8g2, U8G2_R0, u8x8_dummy_cb, u8x8_dummy_cb);
    // u8x8_Setup(&u8x8, u8x8_d_ssd1306_128x32_univision, u8x8_cad_ssd13xx_fast_i2c,);

    TestDisplay t(&u8g2);

    t.Update([](Display* d){
        d->SetFont(Fonts::s5x8::mf);
        d->DrawString(0, 8+4, "ABCDEFG");
        d->DrawString(10, 16+4, "ABCDEFG");
        d->DrawString(20, 24+4, "ABCDEFG");
        d->DrawString(30, 32+4, "ABCDEFG");
        d->DrawPixel(1, 3);
        d->DrawVline(8,0,32);
        d->DrawHline(0,8,8);
        d->DrawHline(0,16,8);
        d->DrawHline(0,24,8);
    });
    
    CHECK_THAT(t.GetContents(), IsScreen("screen"));
    CHECK(1 == 0);
    std::cout << "end write" << std::endl;
}
