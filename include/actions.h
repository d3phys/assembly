ACTION(PSH | VAL_T,
{
        push_stack(stack, *(arg_t *)ip);       
        ip += sizeof(arg_t);
})

ACTION(PSH | REG_T, 
{
        push_stack(stack, reg[*(arg_t *)ip]);       
        ip += sizeof(arg_t);
})

ACTION(PSH | MEM_T | REG_T, 
{
        push_stack(stack, mem[(arg_t)(*(val_t *)&reg[*(arg_t *)ip])]);       
        ip += sizeof(arg_t);
})

ACTION(PSH | MEM_T | VAL_T, 
{
        push_stack(stack, mem[(arg_t)(*(val_t *)ip])]);       
        ip += sizeof(arg_t);
})

ACTION(POP, 
{
        pop_stack(stack);       
})

ACTION(POP | REG_T, 
{
        reg[*(arg_t *)ip] = pop_stack(stack);       
        ip += sizeof(arg_t);
})

ACTION(POP | MEM_T | VAL_T, 
{
        mem[(arg_t)*(val_t *)ip] = pop_stack(stack);       
        ip += sizeof(arg_t);
})
