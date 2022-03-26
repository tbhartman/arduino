#include "MatchesScreen.h"
#include <sstream>

using namespace Display;

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

MatchesScreenMatcher::MatchesScreenMatcher(std::string fileBasename):
    basepath(fileBasename),
    reference(nullptr)
{
    std::string path(TOSTRING(TEST_SCREEN_OUTPUT));
    basepath = path + "/" + basepath;
    path = basepath + ".ref.u8i";
    reference = Contents::ReadFromFile(path);
}
MatchesScreenMatcher::MatchesScreenMatcher(const MatchesScreenMatcher &other):
    basepath(other.basepath)
{
    reference = Contents::ReadFromFile(basepath + ".ref.u8i");
}

bool MatchesScreenMatcher::match(TestScreen const& ts) const
{
    auto c = ts.GetContents();
    if (c == nullptr) {
        return false;
    }
    Contents::WriteToFile(basepath + ".out.u8i", c);

    if (reference.get() == nullptr) {
        return false;
    }
    if (reference->Width() != c->Width() || reference->Height() != c->Height()) {
        return false;
    }
    int diffs = 0;
    for (uint16_t i = 0; i < c->Width(); i++)
    {
        for (uint16_t j = 0; j < c->Height(); j++)
        {
            if( c->At(i,j) != reference->At(i,j)) diffs++;
        }
    }
    return diffs == 0;
}
std::string MatchesScreenMatcher::describe() const
{
    std::ostringstream buf;
    if (reference.get() == nullptr) {
        buf << "no reference at " << basepath << ".ref.u8i" << std::endl;
    } else {
        buf << "is screen sized " << reference->Width() << "x" << reference->Height() << std::endl;
        buf << "  output:    " << basepath << ".out.u8i" << std::endl;
    }
    return buf.str();
}

Display::MatchesScreenMatcher Display::MatchesScreen(std::string fileBasename) {
  return MatchesScreenMatcher(fileBasename);
}
