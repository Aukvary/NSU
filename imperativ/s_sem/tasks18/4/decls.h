#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

typedef struct State 
{ 
    char *regs[256]; 
} State;

EXPORT
void echo_0(State *state); 

EXPORT
void echo_1(State *state, char *arg0); 

EXPORT
void echo_2(State *state, char *arg0, char *arg1); 

EXPORT
void echo_3(State *state, char *arg0, char *arg1, char *arg2); 

EXPORT
void print_1(State *state, char *idx); 

EXPORT
void printregs_0(State *state); 

EXPORT
void store_2(State *state, char *idx, char *what); 

EXPORT
void copy_2(State *state, char *dst, char *src); 

EXPORT
void clear_1(State *state, char *idx); 