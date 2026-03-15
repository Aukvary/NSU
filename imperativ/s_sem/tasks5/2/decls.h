typedef struct State 
{ 
    char *regs[256]; 
} State;

void echo_0(State *state); 
void echo_1(State *state, char *arg0); 
void echo_2(State *state, char *arg0, char *arg1); 
void echo_3(State *state, char *arg0, char *arg1, char *arg2); 
void print_1(State *state, char *idx); 
void printregs_0(State *state); 
void store_2(State *state, char *idx, char *what); 
void copy_2(State *state, char *dst, char *src); 
void clear_1(State *state, char *idx); 