#pragma once

#include <cstdint>

namespace Display {
namespace Contents {

class Reader
{
  public:
    virtual uint16_t Width() const = 0;
    virtual uint16_t Height() const = 0;
    virtual bool At(int x, int y) const = 0;
};

class Writer : public Reader
{
  public:
    virtual void Resize(int width, int height) = 0;
    virtual void Clear() = 0;
    virtual void Set(int x, int y, bool value) = 0;
};

class StringReader : public Reader
{
    const char* ptr;
  public:
    StringReader();
    StringReader(const char*);
    StringReader(const StringReader&);
    StringReader& operator=(const StringReader&);
    StringReader(StringReader&&);
    StringReader& operator=(StringReader&&);
    ~StringReader();

    virtual uint16_t Width() const override;
    virtual uint16_t Height() const override;
    virtual bool At(int x, int y) const override;
};

}
}
