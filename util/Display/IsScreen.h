#pragma once

#include "catch.hpp"
#include "TestContents.h"

namespace Display {

class IsScreenMatcher : public Catch::MatcherBase<Contents::Reader>
{
    std::string basename;

  public:
    IsScreenMatcher(std::string fileBasename);
    IsScreenMatcher(const IsScreenMatcher &other);

    virtual bool match(Contents::Reader const&) const override final;
    virtual std::string describe() const override final;
};

extern IsScreenMatcher IsScreen(std::string fileBasename);

}
