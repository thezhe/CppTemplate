#include <CppTemplate/CppTemplate.hpp>
#include <cassert>
#include <cstdlib>

#define assert_that(condition) assert((condition))

int main()
{
    CppTemplate cpp_template{};
    assert_that(&cpp_template);
    return EXIT_SUCCESS;
}
