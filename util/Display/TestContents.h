#pragma once

#include "Contents.h"
#include <vector>
#include <string>
#include <memory>

namespace Display {
namespace Contents {
class VectorWriter : public Writer
{
    uint16_t width;
    uint16_t height;
    std::vector<bool> Data;
public:
    VectorWriter(uint16_t width, uint16_t height);
    virtual ~VectorWriter() = default;

    virtual uint16_t Width() const override;
    virtual uint16_t Height() const override;
    virtual bool At(int x, int y) const override;
    virtual void Resize(int width, int height) override;
    virtual void Clear() override;
    virtual void Set(int x, int y, bool value) override;
};

extern std::unique_ptr<Reader> ReadFromFile(std::string filename);
extern void WriteToFile(std::string filename, Reader const* reader);

}
}
