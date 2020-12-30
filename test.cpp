#include "utf8.h"
#include <cassert>

// A UTF-8 character can be of size in the range 1 to 4 bytes.

// If more than one bytes are required to interpret this character,
// then the first byte will contain n high order bits set to 1, where
// n is the total number of bytes for this sequence. The next bit will be
// 0 and rest of them is dedicated to represent the number. Following octets
// start with the bit pattern '10' leaving out 6 bits per octet to represent
// the character number. So even if we jump in the middle of some utf8 encoded
// string, if the current byte begins with '10', then we are in the middle of
// a character representation. Based on our needs, we can move forward or backward
// to get to the starting point of a valid character.
//
// If only one byte is required to represent this number then the first bit
// of the only octet is necessarily 0.

// Format of the different ranges of character code representation is given below.

// Char. number range    |        UTF-8 octet sequence
//      (hexadecimal)    |              (binary)
//   --------------------+---------------------------------------------
//   0000 0000-0000 007F | 0xxxxxxx
//   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
//   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
//   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

// WE DETERMINE THE NUMBER OF OCTETS COVERED FOR A GIVEN NUMBER (CHARACTER) BY USING THE TABLE
// ABOVE.  NOTE THAT ALTHOUGH SOMETIMES THE ACTUAL CHARACTER REPRESENTING THE LETTER CAN FIT IN
// LESS NUMBER OF BYTES THAN THE TABLE ABOVE SUGGESTS, BUT WE ALWAYS NEED TO ACCOUNT FOR THE FIRST
// OCTET WHICH NECESSARILY IS WHERE THE CHARACTER SEQUENCE HAS TO START. LOOK AT THE THIRD ROW IN
// THE TABLE ABOVE FOR EXAMPLE. 0XFFFF CAN COMFORTABLY FIT IN TWO BYTES BUT SINCE WE ALSO NEED TO
// INCLUDE, SORT OF, THE META DATA OF THIS CHARACTER, WE WILL REQUIRE 3 BYTES.

// The encoding process proceeds as the following:

//  1. Determine the number of octets required to represent this character.
//  2. Prepare the high order bits as per the table above.
//  3. Fill in the bits marked x from the bits of the character number,
//       expressed in binary.  Start by putting the lowest-order bit of
//       the character number in the lowest-order position of the last
//       octet of the sequence, then put the next higher-order bit of the
//       character number in the next higher-order position of that octet,
//       etc.  When the x bits of the last octet are filled in, move on to
//       the next to last octet, then to the preceding one, etc. until all
//       x bits are filled in.

// The decoding procedure is as follows:

//  1. Initialize a binary number with all bits set to zero.
//  2. Determine which bits encode the character number in the sequence.
//  3. Distribute the bits in the sequence to the binary number starting by
//   populating the least significant bit and moving up to the most significant
//   bit in the number. The required bits may go up to 21 characters.

void length_test ()
{
    auto pigeon = Utf8::String::wrap("कबूतर");
    assert(pigeon.length() == 5);
    std::cout << "length_test passed :^)\n";
}

void at_test ()
{
    auto pigeon = Utf8::String::wrap("कबूतर");
    assert(pigeon.length() == 5);
    assert(pigeon.at(0) == 2325);
    assert(pigeon.at(1) == 2348);
    assert(pigeon.at(2) == 2370);
    assert(pigeon.at(3) == 2340);
    assert(pigeon.at(4) == 2352);
    std::cout << "at test passed :^)\n";
}

int main()
{
    length_test();
    at_test();
    return 0;
}
