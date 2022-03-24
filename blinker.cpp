#include "blinker.h"

#include "clib/u8g2.h"

int test(int a, int b) {
    return a + b;
}

void test2(u8g2_t *u8g2) {
    u8g2_SetFont(u8g2, u8g2_font_helvB08_tr);
    u8g2_DrawStr(u8g2, 4, 15, "Hello World!");
    u8g2_SetFont(u8g2, u8g2_font_helvB08_tr);
    u8g2_DrawStr(u8g2, 4, 30, "uptime: 1s");
}
