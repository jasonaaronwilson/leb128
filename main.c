#include <stdio.h>
#include <string.h>
#include "decoder.h"

void benchmark_SLEB128() {
  uint8_t buffer[64];
  for (int64_t i = -100000000; i < 100000000; i++) {
    int size = encodeSLEB128(i, buffer);
    signed_decode_result result = decodeSLEB128(buffer, buffer+size);
    if (result.size != size) {
      fprintf(stderr, "Encoder and decoder disagree on the size.\n");
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value.\n");
    }
    buffer[0] ^= 254;
    buffer[1] ^= 254;
  }
}

void benchmark_split_loop_encodeSLEB128() {
  uint8_t buffer[64];
  for (int64_t i = -100000000; i < 100000000; i++) {
    int size = split_loop_encodeSLEB128(i, buffer);
    signed_decode_result result = decodeSLEB128(buffer, buffer+size);
    if (result.size != size) {
      fprintf(stderr, "Encoder and deoder disagree on the size.\n");
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value.\n");
    }
    buffer[0] ^= 254;
    buffer[1] ^= 254;
  }
}

int main(int argc, char**argv) {
  if (strcmp(argv[1], "split") == 0) {
    fprintf(stderr, "split loop test\n");
    benchmark_split_loop_encodeSLEB128();
  } else {
    fprintf(stderr, "llvm implementation test\n");
    benchmark_SLEB128();
  }
  return 0;
}
