#include "TestDisplayContents.h"

#include <iostream>
#include <fstream>

TestDisplayContents::TestDisplayContents(uint16_t width, uint16_t height):
    Width(width),
    Height(height)
{
    Data.resize(width*height);
}
TestDisplayContents::TestDisplayContents(std::string filename)
{
    
}

void TestDisplayContents::Clear()
{
    Data.clear();
}
void TestDisplayContents::Set(int x, int y, bool value)
{
    Data[y*Width+x] = value;
}
bool TestDisplayContents::At(int x, int y) const
{
    return Data[y*Width+x];
}
void TestDisplayContents::Write(std::string basename) const
{
    std::ofstream outfile{};
    outfile.open(basename + ".u8i");
    outfile.write("U8I", 3);
    uint8_t byteToWrite = 1;
    uint16_t version = 1;
    for (size_t i = 0; i <2; i++)
    {
        byteToWrite = version >> i*8;
        outfile.write((char*)&byteToWrite, 1);
    }

    // write little endian!
    uint32_t height = Height;
    uint32_t width = Width;
    for (size_t i = 0; i < 4; i++)
    {
        byteToWrite = width >> i*8;
        outfile.write((char*)&byteToWrite, 1);
    }
    for (size_t i = 0; i < 4; i++)
    {
        byteToWrite = height >> i*8;
        outfile.write((char*)&byteToWrite, 1);
    }

    // go through pixels ->, V
    int k = 0;
    byteToWrite = 0;
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            if ( k == 8 ) {
                outfile.write((char*)&byteToWrite, 1);
                k = 0;
            }
            byteToWrite = byteToWrite << 1;
            if ( Data.size() >= (j*width+i+1) && Data[j*width+i] ) {
                byteToWrite = byteToWrite | 1;
            }
            k++;
        }
    }
    if (k != 0) {
        while (k < 8)
        {
            byteToWrite = byteToWrite << 1;
        }
        outfile.write((char*)&byteToWrite, 1);
    }
    outfile.close();
}
