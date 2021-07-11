#ifndef instruction_guard
#define instruction_guard

#include <stdlib.h>
#include <stdint.h>

#include "CPU/mmu.h"
#include "CPU/register.h"

#define NUM_INSTRUCTYPE 30


/********************* Create Instruction structure **********************************/

/* 2 create Oeraptor, It just is a function */
typedef enum OP {
    mov_reg_reg, // 0
    mov_reg_mem, // 1
    mov_mem_reg, // 2
    push_reg,    // 3
    pop_reg,     // 4
    call,        // 5
    ret,         // 6
    add_reg_reg  // 7
} op_t;


// 3.1 create OD type
typedef enum OD_TYPE {
    EMPTY,
    IMM,                // 0
    REG,                // 1
    MM_IMM,             // 2
    MM_REG,             // 3
    MM_IMM_REG,         // 4
    MM_REG1_REG2,       // 5 
    MM_IMM_REG1_REG2,   // 6    
    MM_REG2_S,          // 7
    MM_IMM_REG2_S,      // 8
    MM_REG1_REG2_S,     // 9
    MM_IMM_REG1_REG2_S  // 10

} od_type_t;


/* 3 create Operand(Input), It may be a value or location which can be in register or in memory */
typedef struct OD {
    // OD should have type and value
    // Type
    od_type_t type;    

    // Value
    int64_t imm;
    int64_t scal;
    // reg represent the value of register
    // *reg represent the value of memory that register 
    uint64_t *reg1;
    uint64_t *reg2;
} od_t;


/* 1 create Instruction */
typedef struct INSTRUCT_STRUCT {
    op_t op;    // Function: mov, push
    od_t src;   // Input 1
    od_t dst;   // Input 2
    char code[100]; // Input Instruction
} inst_t;

/***************************** End Of Creating Instruction ********************************/

/****************************** Create Instruction Table ********************************/
/* pointer to function */
typedef void (* handler_t) (uint64_t, uint64_t);

handler_t handler_table[NUM_INSTRUCTYPE];

void init_handler_table();

/* 指令周期 */
void instruction_cycle();



/************************** 创建各种指令的执行过程 (执行+写回+update PC) ********************/
/************************** 类似硬件电路的 加法器 乘法器 ********************/
void mov_reg_reg_handler(uint64_t src, uint64_t dst);

void add_reg_reg_handler(uint64_t src, uint64_t dst);


#endif