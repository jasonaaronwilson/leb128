#include "decoder.h"

/// Utility function to encode a SLEB128 value to a buffer. Returns
/// the length in bytes of the encoded value.
unsigned array_notation_encodeSLEB128(int64_t Value, uint8_t *p) {
  int More;
  unsigned pos = 0;
  do {
    uint8_t Byte = Value & 0x7f;
    // NOTE: this assumes that this signed shift is an arithmetic right shift.
    Value >>= 7;
    More = !((((Value == 0) && ((Byte & 0x40) == 0)) ||
              ((Value == -1) && ((Byte & 0x40) != 0))));
    if (More) {
      Byte |= 0x80; // Mark this byte to show that more bytes will follow.
    }
    p[pos++] = Byte;
  } while (More);

  return pos;
}
