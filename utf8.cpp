#include "utf8.h"
#include <bitset>
#include <iostream>

namespace Utf8 {

void String::init_length()
{
    for (size_t i = 0; i < m_buffer.size();) {
        m_length++;
        auto code_size = validate_first_byte_and_get_size(m_buffer.at(i));
        i += code_size;
    }
}

inline u8 String::validate_first_byte_and_get_size(u8 firs_byte) const
{
    bool first_bit_set = firs_byte & 0x80;
    bool second_bit_set = firs_byte & (0x80 >> 1);
    bool third_bit_set = firs_byte & (0x80 >> 2);
    bool fourth_bit_set = firs_byte & (0x80 >> 3);

    if (!first_bit_set)
        return 1;

    if (!second_bit_set)
        throw std::invalid_argument("Invalid codepoint!");

    return 2 + third_bit_set + fourth_bit_set;
}

inline u32 String::codepoint_helper(size_t index, u8 size) const
{
    if (size < 1 || size > 4) {
        auto str_size = std::to_string(size);
        throw std::invalid_argument("Invalid size!");
    }

    if (size == 1)
        return m_buffer.at(index);

    // +1 for the zero that comes after series of 1s.
    u8 first_mask_index = 8 - (size + 1);
    u32 value = m_buffer.at(index) & tail_mask[first_mask_index];
    for (int i = 1; i < size; i++) {
        u8 current_byte = m_buffer.at(index + i) & tail_mask[6];
        value <<= 6;
        value |= current_byte;
    }

    return value;
}

String String::wrap(const char* seed)
{
    String utf_string;
    size_t size = strlen(seed);
    utf_string.m_buffer.reserve(size);
    for (; *seed; ++seed)
        utf_string.m_buffer.push_back(*seed);
    utf_string.init_length();
    return utf_string;
}

String String::wrap(const std::string& seed)
{
    return wrap(seed.data());
}

size_t String::length() const
{
    return m_length;
}

uint32_t String::at(size_t position) const
{
    size_t start_index = 0;
    unsigned codepoint_size = 0;
    for (size_t i = 0; i <= position; i++) {
        start_index += codepoint_size;
        codepoint_size = validate_first_byte_and_get_size(m_buffer.at(start_index));
    }
    return codepoint_helper(start_index, codepoint_size);
}
}
