#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "blinker.h"

#include "clib/u8g2.h"
#include "stdio.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "util/Display/TestScreen.h"
#include "util/Display/IsScreen.h"
#include "util/fonts.h"

#include "img.h"


void a(u8g2_t *u8g2) {
}

TEST_CASE( "My function works" ) {
    u8g2_t u8g2;
    // u8g2_Setup_ssd1306_i2c_128x32_univision_1((u8g2_t *)&u8g2, U8G2_R0, u8x8_dummy_cb, u8x8_dummy_cb);
    u8g2_Setup_ssd1306_i2c_128x32_univision_1((u8g2_t *)&u8g2, U8G2_R0, u8x8_dummy_cb, u8x8_dummy_cb);
    // u8x8_Setup(&u8x8, u8x8_d_ssd1306_128x32_univision, u8x8_cad_ssd13xx_fast_i2c,);

    Display::TestScreen t(&u8g2);

    t.Update([](Display::Screen* d){
        d->SetFont(Fonts::s5x8::mf);
        d->DrawString(40, 8+4, "Hello Andrea");
        d->DrawString(50, 16+4, "ABCDEFG");
        d->DrawString(60, 24+4, "ABCDEFG");
        d->DrawString(70, 32+4, "ABCDEFG");
        d->DrawVline(15,0,32);
        d->DrawVline(31,0,32);
        d->DrawHline(0,15,32);
        auto r = Display::Contents::StringReader(Img::full_connection);
        d->Apply(0,0, &r);
        r = Display::Contents::StringReader(Img::half_connection);
        d->Apply(16,0, &r);
        r = Display::Contents::StringReader(Img::no_connection);
        d->Apply(0,16, &r);
    });
    Display::Contents::WriteToFile("testdata/screens/screen.out", t.GetContents());
    // CHECK_THAT(t.GetContents(), IsScreen("screen"));
    CHECK(1 == 0);
}
