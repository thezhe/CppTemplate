#pragma once

class CppTemplate
{
public:
    CppTemplate() = default;
    CppTemplate(CppTemplate&&) = default;
    CppTemplate(const CppTemplate&) = default;
    CppTemplate& operator=(CppTemplate&&) = default;
    CppTemplate& operator=(const CppTemplate&) = default;
    ~CppTemplate() = default;
};
