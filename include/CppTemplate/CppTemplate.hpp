#pragma once

/*!
 * @brief Default class
 */
namespace CppTemplate
{

class CppTemplate
{
public:
    CppTemplate() = default;
    CppTemplate(CppTemplate&&) = default;
    CppTemplate(const CppTemplate&) = default;
    CppTemplate& operator=(CppTemplate&&) = default;      // NOLINT
    CppTemplate& operator=(const CppTemplate&) = default; // NOLINT
    ~CppTemplate() = default;

    void method();
};

} // namespace CppTemplate
