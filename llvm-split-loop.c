/* 
 * This is a simple optimization of llvm.c
 */

#include "decoder.h"

/// Utility function to encode a SLEB128 value to a buffer. Returns
/// the length in bytes of the encoded value.
unsigned split_loop_encodeSLEB128(int64_t Value, uint8_t *p) {
  uint8_t *orig_p = p;
  unsigned Count = 0;
  if (Value >= 0) {
    int More;
    do {
      uint8_t Byte = Value & 0x7f;
      // NOTE: this assumes that this signed shift is an arithmetic right shift.
      Value >>= 7;
      Count++;
      More = !((((Value == 0 ) && ((Byte & 0x40) == 0)) ||
                ((Value == -1) && ((Byte & 0x40) != 0))));
      if (More)
        Byte |= 0x80; // Mark this byte to show that more bytes will follow.
      *p++ = Byte;
    } while (More);
  } else {
    int More;
    do {
      uint8_t Byte = Value & 0x7f;
      // NOTE: this assumes that this signed shift is an arithmetic right shift.
      Value >>= 7;
      Count++;
      More = !((((Value == 0 ) && ((Byte & 0x40) == 0)) ||
                ((Value == -1) && ((Byte & 0x40) != 0))));
      if (More)
        Byte |= 0x80; // Mark this byte to show that more bytes will follow.
      *p++ = Byte;
    } while (More);
  }
    
   return (unsigned)(p - orig_p);
}
