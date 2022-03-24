#pragma once

#include <vector>
#include <string>

struct TestDisplayContents
{
    TestDisplayContents(uint16_t width, uint16_t height);
    TestDisplayContents(std::string filename);

    uint16_t Width;
    uint16_t Height;
    std::vector<bool> Data;

    void Clear();
    void Set(int x, int y, bool value);
    bool At(int x, int y) const;
    void Write(std::string filename) const;
};
