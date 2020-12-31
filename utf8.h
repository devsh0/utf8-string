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
    static constexpr u8 tail_mask[] = { 0x00, 0x01, 0x03, 0x07, 0x15, 0x1F, 0x3F };

    std::vector<u8> m_buffer;
    size_t m_length = 0;

    String() = default;
    void init_length();
    inline u8 validate_first_byte_and_get_size(u8 firs_byte) const;

    // Returns the starting index and size of utf-8 character at `position` in the internal buffer.
    // Example: Suppose the utf-8 string has two characters, each 3 bytes in length. We want to get
    // the location of the 2nd char, which will be located at index 3 in the internal buffer. So we
    // call this function with argument `position=1` and it will return {3, 3}.
    inline std::pair<size_t, u8> get_index_and_size_of_char_at(size_t position) const;

    inline u32 codepoint_helper(size_t index, u8 size) const;
    std::vector<u8> utf8_bytes_helper(size_t index, u8 size) const;

public:
    static String wrap(const char*);
    static String wrap(const std::string&);

    size_t length() const;

    // Returns the codepoint of the UTF-8 char at `position`.
    u32 codepoint_at(size_t position) const;

    // Returns the octets representing the UTF-8 char at `position` wrapped in a vector.
    std::vector<u8> bytes_of_char_at(size_t position) const;
};
}