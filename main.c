#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"

void benchmark_SLEB128() {
  uint8_t buffer[64];
  for (int64_t i = -100000000; i < 100000000; i++) {
    int size = encodeSLEB128(i, buffer);
    signed_decode_result result = decodeSLEB128(buffer, buffer+size);
    if (result.size != size) {
      fprintf(stderr, "Encoder and decoder disagree on the size.\n");
      exit(-1);
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value.\n");
      exit(-1);
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
      fprintf(stderr, "Encoder and decoder disagree on the size.\n");
      exit(-1);
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value.\n");
      exit(-1);
    }
    buffer[0] ^= 254;
    buffer[1] ^= 254;
  }
}

void benchmark_array_notation_encodeSLEB128() {
  uint8_t buffer[64];
  for (int64_t i = -100000000; i < 100000000; i++) {
    int size = array_notation_encodeSLEB128(i, buffer);
    signed_decode_result result = decodeSLEB128(buffer, buffer+size);
    if (result.size != size) {
      fprintf(stderr, "Encoder and decoder disagree on the size.\n");
      exit(-1);
    }
    if (result.number != i) {
      fprintf(stderr, "Encoder and decoder disagree on the value %ld %ld\n", i, result.number);
      exit(-1);
    }
    buffer[0] ^= 254;
    buffer[1] ^= 254;
  }
}

void benchmark_parallel_encodeULEB128() {
  uint8_t buffer[64];
  for (uint64_t i = 0; i < 200000000; i++) {
    // int size = parallel_encodeULEB128(i, buffer);
    int size = parallel_encodeULEB128(i, buffer);
    unsigned_decode_result result = decodeULEB128(buffer, buffer+size);
    if (result.size != size) {
      fprintf(stderr, "Encode bytes %x\n", *((uint32_t*)buffer));
      fprintf(stderr, "Encoder and decoder disagree on the size %ld %d %d.\n", i, size, result.size);
      exit(-1);
    }
    if (result.number != i) {
      fprintf(stderr, "Encode bytes %x\n", *((uint32_t*)buffer));
      fprintf(stderr, "Encoder and decoder disagree on the value %ld %ld\n", i, result.number);
      exit(-1);
    }
    buffer[0] ^= 254;
    buffer[1] ^= 254;
    *((uint64_t*)buffer) = 0;
  }
}

int main(int argc, char**argv) {
  if (strcmp(argv[1], "parallel") == 0) {
    fprintf(stderr, "parallel\n");
    benchmark_parallel_encodeULEB128();
  } else if (strcmp(argv[1], "split") == 0) {
    fprintf(stderr, "split loop test\n");
    benchmark_split_loop_encodeSLEB128();
  } else if (strcmp(argv[1], "array") == 0) {
    fprintf(stderr, "array implementation test\n");
    benchmark_array_notation_encodeSLEB128();
  } else {
    fprintf(stderr, "llvm implementation test\n");
    benchmark_SLEB128();
  }
  return 0;
}
