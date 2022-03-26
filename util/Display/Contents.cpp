#include "Contents.h"

#include <iostream>

using namespace Display::Contents;

// StringReader requires U8Iv2
// example 4x4 image with four corners black
// bytes:
// 0       1       2       3       4       5       6       7       8       9
// |       |       |       |       |       |       |       |       |       |
// MAGIC------------------>WIDTH---------->HEIGHT--------->PIXELS---->>>   |<-- 0-fill to next byte
// |                       |              4|              41001000000001001
// U       8       I       000001000000000000000100000000001001000000001001
// bytes:  |       |       |       |       |       |       |       |       |
// 0x55    0x38    0x49    0x04    0x00    0x04    0x00    0x90    0x09

StringReader::StringReader():
  ptr(nullptr)
{
}
StringReader::StringReader(const char* s):
  ptr(s)
{
}
StringReader::StringReader(const StringReader& other):
  ptr(other.ptr)
{
}
StringReader& StringReader::operator=(const StringReader& other)
{
  this->ptr = other.ptr;
  return *this;
}
StringReader::StringReader(StringReader&& other):
  ptr(other.ptr)
{
}
StringReader& StringReader::operator=(StringReader&& other)
{
  this->ptr = other.ptr;
  return *this;
}
StringReader::~StringReader()
{
  this->ptr = nullptr;
}

uint16_t StringReader::Width() const
{
  uint16_t ret = 0;
  ret += (uint8_t)(*(this->ptr+6));
  ret = ret << 8;
  ret += (uint8_t)(*(this->ptr+5));
  return ret;
}
uint16_t StringReader::Height() const
{
  uint16_t ret = 0;
  ret += (uint8_t)(*(this->ptr+10));
  ret = ret << 8;
  ret += (uint8_t)(*(this->ptr+9));
  return ret;
}
bool StringReader::At(int x, int y) const
{
  int i = y*Width()+x;
  return (*(this->ptr+13+i/8) << i%8) & 0x80;
}
