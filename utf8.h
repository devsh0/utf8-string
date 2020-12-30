#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <vector>

namespace Utf8 {

using u8 = uint8_t;
using u32 = uint32_t;

class String {
private:
    std::vector<u8> m_buffer;
    size_t m_length = 0;

    inline u8 validate_first_byte_and_get_size(u8 firs_byte) const;
    inline u32 codepoint_helper(size_t index, u8 size) const;

    static constexpr u8 tail_mask[] = {0x00, 0x01, 0x03, 0x07, 0x15, 0x1F, 0x3F};

    String() = default;

    void init_length();

public:
    static String wrap(const char*);
    static String wrap(const std::string&);

    size_t length() const;
    u32 at(size_t) const;
};
}