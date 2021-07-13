#include <stdio.h>
#include "Memory/instruction.h"



// 实现有问题
// 1 立即数 和 立即数寻址没有分开
// 2 使用了寄存器寻址代替内存寻址
// update: 
// 1 memory 寻址, 返回的是地址 vaddr. 所以 立即数和立即数寻址是分开的
// 2 同理, 寄存器寻址和内存寻址也是分开的

static uint64_t decode_od(od_t od) { 
    if (od.type == IMM) {
        // 先输出位模式, 使用时再用int解释, 这样可以不损失信息
        //同时保证输出是 uint64_t
        return *(uint64_t *)&od.imm;  
    } 
    else if (od.type == REG) {
        return (uint64_t) od.reg1;
    }
    else {
        //mm
        uint64_t vaddr = 0;

        if (od.type == MM_IMM) { // 2
            vaddr = od.imm;
        }
        else if (od.type == MM_REG) { //3
            vaddr = *(od.reg1);
        }
        else if (od.type == MM_IMM_REG) { // 4
            vaddr = od.imm + *(od.reg1);
        }
        else if (od.type == MM_REG1_REG2) {  // 5
            /* 指针和寄存器不一样, 寄存器可以直接相加, 但是指针
               不能直接相加, 所以 分开相加. 因为是模拟器, 只要
               能一一map就行了 */
            vaddr = *(od.reg1) + *(od.reg2);
        }        
        else if (od.type == MM_IMM_REG1_REG2) { // 6
            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_REG2_S) {  // 7
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG2_S) { // 8
            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_REG1_REG2_S) { //9
            vaddr = *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG1_REG2_S) { // 10
            vaddr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scal;
        }

        return va2pa(vaddr);
    }
}

void instruction_cycle() {
    // 1 Fetch code
    inst_t *instr = (inst_t *)reg.rip; 
    
    // 2 decode
    // Function: decode + VA->PA
    // map(Input, Output)
    // imm : imm
    // reg: value
    // mm: phy addrr 
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    // 3 Execute and write back
    // add rax rbx
    // op = add_reg_reg = 3
    // handler_table[add_reg_reg] == handler_table[3] == add_reg_reg_handler

    handler_t handler = handler_table[instr->op];
    handler(src, dst);

    printf("-----------------New instruction is executed!----------------\n");
    printf("----------------$%s $--------------\n", instr->code);
} 

void init_handler_table() {
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
    handler_table[call] = &call_handler;
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst) {
    // src: reg
    // det: reg
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip += sizeof(inst_t);
}


void add_reg_reg_handler(uint64_t src, uint64_t dst) {
    // src: reg
    // det: reg
    *(uint64_t *)dst += *(uint64_t *)src;
    reg.rip += sizeof(inst_t);
}


void call_handler(uint64_t src, uint64_t dst) {
    // src: imm address of called function
    // 1 push return_address
    // 1.1 decrease rsp
    reg.rsp -= 8;
    // 1.2 write return address to rsp memory
    write64bits_dram(va2pa(reg.rsp), reg.rip + sizeof(inst_t));
    
    // 2 set pc -> the called function address
    reg.rip = src;
    
}