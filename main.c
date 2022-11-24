#include <stdio.h>
#include "decoder.h"

void benchmark_SLEB128() {
  uint8_t buffer[64];
  for (int64_t i = -100000000; i < 100000000; i++) {
    int size = encodeSLEB128(i, buffer);
    signed_decode_result result = decodeSLEB128(buffer, buffer+64);
    if (result.size != size) {
      fprintf(stderr, "Encoder and decoder disagree on the size.");
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value.");
    }
  }
}

int main(int argc, char**argv) {
  benchmark_SLEB128();
  return 0;
}
