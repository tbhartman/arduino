#include "TestContents.h"

#include <iostream>
#include <fstream>

using namespace Display::Contents;

VectorWriter::VectorWriter(uint16_t width, uint16_t height):
    width(width),
    height(height)
{
    Data.resize(width*height);
}
// VectorWriter::VectorWriter(std::string filename)
// {
// }
void VectorWriter::Resize(int width, int height)
{
    this->width = width;
    this->height = height;
    Data.resize(width*height);
}

uint16_t VectorWriter::Width() const
{
    return width;
}
uint16_t VectorWriter::Height() const
{
    return height;
}
void VectorWriter::Clear()
{
    Data.clear();
}
void VectorWriter::Set(int x, int y, bool value)
{
    Data[y*width+x] = value;
}
bool VectorWriter::At(int x, int y) const
{
    return Data[y*width+x];
}

void Display::Contents::WriteToFile(std::string filename, Reader const* reader)
{
    std::ofstream outfile{};
    outfile.open(filename + ".u8i");
    outfile.write("U8I", 3);
    uint8_t byteToWrite = 1;
    uint16_t version = 1;
    for (size_t i = 0; i <2; i++)
    {
        byteToWrite = version >> i*8;
        outfile.write((char*)&byteToWrite, 1);
    }

    // write little endian!
    uint32_t height = reader->Height();
    uint32_t width = reader->Width();
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
            if ( reader->At(i,j) ) {
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
