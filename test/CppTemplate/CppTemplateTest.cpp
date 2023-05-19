#include <CppTemplate/CppTemplate.hpp>
#include <cassert>
#include <cstdlib>

#define assert_that(condition) assert((condition)) // NOLINT

int main() // NOLINT
{
    CppTemplate::CppTemplate cpp_template{};
    assert_that(&cpp_template);

    return EXIT_SUCCESS;
}
