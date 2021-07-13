#include <stdio.h>
#include "Memory/dram.h" 
#define SRAM_CACHE_SETTING 0

// flighting

uint64_t read64bits_dram(uint64_t address) {
    // uint64_t result = 0x0;
    if (SRAM_CACHE_SETTING == 1) {
        return 0x0;
    }
    uint64_t result = 0;
    result += (((uint64_t)mm[address + 0]) << 0);
    result += (((uint64_t)mm[address + 1]) << 8) ;
    result += (((uint64_t)mm[address + 2]) << 16);
    result += (((uint64_t)mm[address + 3]) << 24);
    result += (((uint64_t)mm[address + 4]) << 32);
    result += (((uint64_t)mm[address + 5]) << 40);
    result += (((uint64_t)mm[address + 6]) << 48);
    result += (((uint64_t)mm[address + 7]) << 56);
    return result;
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


void print_register() {
    printf("rax = %16lx\trbx = %16lx\trcx = %16lx\trdx = %16lx\n", reg.rax, reg.rbx, reg.rcx, reg.rdx);
    printf("rsi = %16lx\trdi = %16lx\trbp = %16lx\trsp = %16lx\n", reg.rsi, reg.rdi, reg.rbp, reg.rsp);
    printf("rip = %16lx\n",reg.rip);
}

void print_stack() {
    int n = 10;
    uint64_t *high = (uint64_t *)&mm[va2pa(reg.rsp)]; // rsp 物理地址
    high = &high[n];  // &high[n] = high + 10

    uint64_t rsp_start = reg.rsp + n * 8;
     
    for (int i = 0; i < 2 * n; ++i) {
        uint64_t *ptr = (uint64_t *)(high -i);
        printf("0x%16lx :  %16lx", rsp_start, (uint64_t) *ptr);

        if (i == n) {
            printf(" <== rsp");
        }

        rsp_start -= 8;
        
        printf("\n");
    }
}
