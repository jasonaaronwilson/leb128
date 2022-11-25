#include "decoder.h"

// Don't use this code since it is not faster than the simpler smaller
// implementations and hasn't been fully tested either.

// The entire reason to use LEB is because smaller numbers are much
// more common than large ones and this optimized for large
// numbers. The original benchmark showed that it was almost twice as
// slow as the simpler code though reorder the branch statements to
// test for smaller valus first made it only a little slower than
// similar routines (actually I'm comparing signed and unsigned cases
// assuming they have similar speed when we know the unsigned case is
// probably faster).

/// Utility function to encode a SLEB128 value to a buffer. Returns
/// the length in bytes of the encoded value.

// This is just an experiment so we'll only handle the first 8 bytes
// of output to see how the code works.
unsigned parallel_encodeULEB128(int64_t Value, uint8_t *p) {
  uint64_t A = (Value << 0) & (0x7full << 0);
  uint64_t B = (Value << 1) & (0x7full << 8);
  uint64_t C = (Value << 2) & (0x7full << 16);
  uint64_t D = (Value << 3) & (0x7full << 24);
  uint64_t E = (Value << 4) & (0x7full << 32);
  uint64_t F = (Value << 5) & (0x7full << 40);
  uint64_t G = (Value << 6) & (0x7full << 48);
  uint64_t H = (Value << 7) & (0x7full << 56);

  unsigned n_bytes;

  // This mostly looks like the intended result except the
  // continuation bits in the last bit of each byte.
  uint64_t result = A | B | C | D | E | F | G | H;

  // TODO(jawilson): reorder the last few ones or turn into a binary
  // search.
  if (Value < ((1ull << 7) -1)) {
    n_bytes = 1;
  } else if (Value < ((1ull << 14) -1)) {
    n_bytes = 2;
    result |= (1ull << 7);
  } else if (Value < ((1ull << 21) - 1)) {
    n_bytes = 3;
    result |= (1ull << 15) | (1ull << 7);
  } else if (Value < ((1ull << 28) - 1)) {
    n_bytes = 4;
    result |= (1ull << 23) | (1ull << 15) | (1ull << 7);
  } else if (Value < ((1ull << 35) - 1)) {
    n_bytes = 5;
    result |= (1ull << 31) | (1ull << 23) | (1ull << 15) | (1ull << 7);
  } else if (Value >= ((1ull << 49) - 1)) {
    n_bytes = 8;
    result |= (1ull << 57) | (1ull << 47) | (1ull << 39) | (1ull << 31) | (1ull << 23) | (1ull << 15) | (1ull << 7);
  } else if (Value >= ((1ull << 42) - 1)) {
    n_bytes = 7;
    result |= (1ull << 47) | (1ull << 39) | (1ull << 31) | (1ull << 23) | (1ull << 15) | (1ull << 7);
  } else if (Value >= ((1ull << 35) - 1)) {
    n_bytes = 6;
    result |= (1ull << 39) | (1ull << 31) | (1ull << 23) | (1ull << 15) | (1ull << 7);
  } 

  *((uint64_t*)p) = result;

  return n_bytes;
}
