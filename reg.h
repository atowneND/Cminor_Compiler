#ifndef REG_H
#define REG_H
typedef enum{
    RAX_REG,
    RBX_REG,
    RCX_REG,
    RDX_REG,
    RSI_REG,
    RDI_REG,
    RBP_REG,
    RSP_REG,
    R8_REG,
    R9_REG,
    R10_REG,
    R11_REG,
    R12_REG,
    R13_REG,
    R14_REG,
    R15_REG
} my_registers_t;

struct reg_status {
    my_registers_t reg_name;
    int reg_free;
};

void register_free(struct reg_status *expr_reg);

#endif
