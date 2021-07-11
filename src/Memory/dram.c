#include "Memory/dram.h"
#define SRAM_CACHE_SETTING 0

// flighting

uint64_t read64bits_dram(uint64_t address) {
    // uint64_t result = 0x0;
    if (SRAM_CACHE_SETTING == 1) {
        return 0x0;
    }
    // result = mm[address + 0] | result;
    // result = ((uint64_t)mm[address + 1]) << 8) | result;
    // result = ((uint64_t)mm[address + 2]) << 16) | result;
    // result = ((uint64_t)mm[address + 3]) << 24) | result;
    // result = ((uint64_t)mm[address + 4]) << 32) | result;
    // result = ((uint64_t)mm[address + 5]) << 40) | result;
    // result = ((uint64_t)mm[address + 6]) << 48) | result;
    // result = ((uint64_t)mm[address + 7]) << 56) | result;
    // return result;
    return 0x0;
}

void write64bits_dram(uint64_t address, uint64_t data) {
    if (SRAM_CACHE_SETTING == 1) {
        return ;
    } 
    else {
        mm[address + 0] = (data >> 0 ) & 0xff;
        mm[address + 1] = (data >> 8 ) & 0xff;
        mm[address + 2] = (data >> 16 ) & 0xff;
        mm[address + 3] = (data >> 24 ) & 0xff;
        mm[address + 4] = (data >> 32 ) & 0xff;
        mm[address + 5] = (data >> 40 ) & 0xff;
        mm[address + 6] = (data >> 48 ) & 0xff;
        mm[address + 7] = (data >> 56 ) & 0xff;

    }


}
