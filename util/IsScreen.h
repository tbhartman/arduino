#pragma once

#include "catch.hpp"
#include "TestDisplayContents.h"

class IsScreenMatcher : public Catch::MatcherBase<TestDisplayContents>
{
    std::string basename;

  public:
    IsScreenMatcher(std::string fileBasename);
    IsScreenMatcher(const IsScreenMatcher &other);

    virtual bool match(TestDisplayContents const&) const override final;
    virtual std::string describe() const override final;
};

extern IsScreenMatcher IsScreen(std::string fileBasename);
