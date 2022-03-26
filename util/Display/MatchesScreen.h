#pragma once

#include "../catch.hpp"
#include "TestScreen.h"
#include <memory>
#ifndef TEST_SCREEN_OUTPUT
#error Must define TEST_SCREEN_OUTPUT
#endif

namespace Display {

class MatchesScreenMatcher : public Catch::MatcherBase<TestScreen>
{
    std::string basepath;
    std::unique_ptr<Contents::Reader> reference;
  public:
    MatchesScreenMatcher(std::string fileBasename);
    MatchesScreenMatcher(const MatchesScreenMatcher &other);

    virtual bool match(TestScreen const&) const override final;
    virtual std::string describe() const override final;
};

extern MatchesScreenMatcher MatchesScreen(std::string fileBasename);

}
