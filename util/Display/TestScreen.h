#pragma once

#include "Screen.h"

#include "TestContents.h"

#include <vector>
#include <string>

namespace Display {

class TestScreen : public Screen
{
  public:
    TestScreen() = delete;
    TestScreen(u8g2_struct* u8g2);
    virtual ~TestScreen();
    Contents::Reader const* GetContents() const;
  private:
    Contents::VectorWriter contents;
    friend struct TDAccessor;
};
}
