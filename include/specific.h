#ifndef SPECIFIC_H_
#define SPECIFIC_H_

const uint16_t MSB = ~((cmd_t)(~0x00) >> 0x01);

const cmd_t VAL_T = MSB >> 0x00;
const cmd_t MEM_T = MSB >> 0x01;
const cmd_t REG_T = MSB >> 0x02;

const opcode_t PSH = 0xF0;
const opcode_t POP = 0xF1;
const opcode_t SUB = 0xDA;
const opcode_t MUL = 0x1D;
const opcode_t DIV = 0xD1;
const opcode_t ADD = 0xAD;

#define CMD(name, opcode, mnemonic)     \
        const opcode_t name = opcode;   \
        const char MN_##name[]   = mnemonic; \

CMD(0xF0, PSH);
CMD(0xF1, POP);
CMD(0xF0, PSH);
CMD(0xF0, PSH);
CMD(0xF0, PSH);

#define ACT(code, action)             \

ACT(PSH | VAL_T, 
{
        pop;
})

ACT(PSH | REG_T, 
{
        pop;
})



#endif /* SPECIFIC_H_ */
