#include "IsScreen.h"
#include <sstream>

IsScreenMatcher::IsScreenMatcher(std::string fileBasename):
    basename(fileBasename)
{
}
IsScreenMatcher::IsScreenMatcher(const IsScreenMatcher &other):
    basename(other.basename)
{
}

bool IsScreenMatcher::match(TestDisplayContents const& disp) const
{
    TestDisplayContents other(basename + ".ref.u8i");
    if (other.Width != disp.Width || other.Height != disp.Height) {
        return false;
    }
    int diffs = 0;
    for (size_t i = 0; i < disp.Data.size(); i++)
    {
        if( disp.Data[i] != other.Data[i]) diffs++;
    }
    return diffs != 0;
}
std::string IsScreenMatcher::describe() const
{
    TestDisplayContents other(basename + ".ref.u8i");
    std::ostringstream buf;
    buf << "is screen sized " << other.Width << "x" << other.Height;
    return buf.str();
}
IsScreenMatcher IsScreen(std::string fileBasename) {
  return IsScreenMatcher(fileBasename);
}
