#pragma once

#include <string_view>
#include <locale>

#include "utility/String.hpp"
#include "ReClass.hpp"

namespace utility::re_string {
    static std::wstring_view get_view(const ::REString& str) {
#ifdef RE8
        if (str.ptr == nullptr || ((uintptr_t)str.ptr & (sizeof(void*) - 1)) != 0 || str.ptr->size == 0) {
            return L"";
        }

        return (wchar_t*)&str.ptr->data;
#else
        auto length = str.length;

        if (length <= 0) {
            return L"";
        }

        std::wstring_view raw_name;

        if (length >= 12) {
            auto name_ptr = *(wchar_t**)&str;

            if (name_ptr == nullptr) {
                return L"";
            }

            raw_name = name_ptr;
        } else {
            if (length <= 0) {
                return L"";
            }

            raw_name = (wchar_t*)&str;
        }

        return raw_name;
#endif
    }

    static std::string get_string(const ::REString& str) {
        return utility::narrow(get_view(str));
    }

    static bool equals(const ::REString& str, std::wstring_view view) {
        return get_view(str) == view;
    }
}