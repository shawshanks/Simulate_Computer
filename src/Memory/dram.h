#ifndef dram_guard
#define dram_guard

#include <stdlib.h>
#include <stdint.h>


#define MM_LEN 1000


uint8_t mm[MM_LEN]; // physical memroy

uint64_t read64bits_dram(uint64_t address);

void write64bits_dram(uint64_t address, uint64_t data);

#endif