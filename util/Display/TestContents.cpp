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

static std::string read_file(std::string filename)
{
    const size_t read_size = 4096;
    auto stream = std::ifstream(filename);
    
    std::string ret;
    std::string buf(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {
        ret.append(buf, 0, stream.gcount());
    }
    ret.append(buf, 0, stream.gcount());
    return ret;
}

std::unique_ptr<Display::Contents::Reader> Display::Contents::ReadFromFile(std::string filename)
{

    auto data = read_file(filename);
    if (data.size() == 0) {
        return nullptr;
    }
    StringReader r(&data[0]);
    VectorWriter* vw = new VectorWriter(r.Width(), r.Height());
    for (uint16_t i = 0; i < r.Width(); i++)
    {
        for (uint16_t j = 0; j < r.Height(); j++)
        {
            vw->Set(i,j,r.At(i,j));
        }
    }
    std::unique_ptr<Display::Contents::Reader> ret;
    ret.reset(vw);
    return ret;
}
void Display::Contents::WriteToFile(std::string filename, Reader const* reader)
{
    std::ofstream outfile{};
    outfile.open(filename);
    if (outfile.fail()) {
        return;
    }
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
