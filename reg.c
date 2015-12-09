#include "reg.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_REG R15_REG

struct reg_status r_table[MAX_REG];

const char *register_name(int r){
    switch (r){
        case RAX_REG:
            return "%rax";
            break;
        case RBX_REG:
            return "%rbx";
            break;
        case RCX_REG:
            return "%rcx";
            break;
        case RDX_REG:
            return "%rdx";
            break;
        case RSI_REG:
            return "%rsi";
            break;
        case RDI_REG:
            return "%rdi";
            break;
        case RBP_REG:
            return "%rbp";
            break;
        case RSP_REG:
            return "%rsp";
            break;
        case R8_REG:
            return "%r8";
            break;
        case R9_REG:
            return "%r9";
            break;
        case R10_REG:
            return "%r10";
            break;
        case R11_REG:
            return "%r11";
            break;
        case R12_REG:
            return "%r12";
            break;
        case R13_REG:
            return "%r13";
            break;
        case R14_REG:
            return "%r14";
            break;
        case R15_REG:
            return "%r15";
            break;
        default:
            return 0;
            break;
    }
}

void init_registers(void){
    int i;
    for (i=0;i<=MAX_REG;i++){
        r_table[i].reg_name = i;
        r_table[i].reg_used = 0;
        if ((i==1)||(i>=10)){
            r_table[i].scratch = 1;
        } else {
            r_table[i].scratch = 0;
        }
    }
}

int register_alloc(void){
    int i,done;
    done = 0;
    for (i=0;i<=MAX_REG;i++){
        if (r_table[i].scratch){ // only check scratch registers
            if (!r_table[i].reg_used){
                r_table[i].reg_used = 1;
                done = 1;
                break;
            }
        }
    }
    if (!done){
        fprintf(stderr,"Ran out of registers\n");
        return -1;
    } else {
        return i;
    }
}

void register_free(my_registers_t reg){
    // free register
}
