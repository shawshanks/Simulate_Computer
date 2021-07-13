#ifndef main_guard
#define main_guard


#include <stdio.h>

#include "cpu/register.h"
#include "cpu/mmu.h"

#include "Memory/instruction.h"
#include "Memory/dram.h"

#include "Disk/elf.h"




int main() {
    init_handler_table();

    // init
    reg.rax = 0x12340000;
    reg.rbx  = 0x0;
    reg.rcx = 0x8000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee598;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee4b0;
    reg.rsp = 0x7ffffffee490;

    reg.rip = (uint64_t)&program[10];

    write64bits_dram(va2pa(0x7ffffffee4b0), 0x08000660); // %rbp
    write64bits_dram(va2pa(0x7ffffffee4a0), 0xabcd);
    write64bits_dram(va2pa(0x7ffffffee4a8), 0x0);
    write64bits_dram(va2pa(0x7ffffffee498), 0x12340000);
    write64bits_dram(va2pa(0x7ffffffee490), 0x08000660); // %rsp

    print_register();
    print_stack();

    // run
    for (int i = 0; i < 3; ++i) {
        instruction_cycle();
        print_register();
        print_stack();
    };

    // verify
    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x8000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee4b0);
    match = match && (reg.rsp == 0x7ffffffee490);

    if (match == 1) {
        printf("Register match\n");
    }
    else {
        printf("Regist not match\n");
    }

    match = 1;
    match = match && (read64bits_dram(va2pa(0x7ffffffee4a8)) == 0x1234abcd);  
    match = match && (read64bits_dram(va2pa(0x7ffffffee4b0)) == 0x08000660);  // %rbp
    match = match && (read64bits_dram(va2pa(0x7ffffffee4a0)) == 0x0000abcd);  
    match = match && (read64bits_dram(va2pa(0x7ffffffee498)) == 0x12340000);  
    match = match && (read64bits_dram(va2pa(0x7ffffffee490)) == 0x08000660);  // %rsp    
    
    if (match == 1) {
        printf("Memory match\n");
    }
    else {
        printf("Memory not match\n");
    }

    return 0;
}

test


#endif

