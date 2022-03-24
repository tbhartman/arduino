#pragma once

#include "Display.h"

#include "TestDisplayContents.h"

#include <vector>
#include <string>

class TestDisplay : public Display
{
  public:
    TestDisplay() = delete;
    ~TestDisplay();
    TestDisplay(u8g2_struct* u8g2);
    TestDisplayContents const& GetContents() const;
  private:
    TestDisplayContents contents;
    friend struct TDAccessor;
};
