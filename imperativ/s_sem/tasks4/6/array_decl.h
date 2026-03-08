#if defined(TYPE) && defined(NAME)

#define CONCAT(a, b) a##b
#define CONCAT2(a, b) CONCAT(a, b)
#define DEF_FUNC(name) CONCAT2(NAME, _##name)


typedef struct NAME {
    int n;          
    int cap;   
    TYPE *arr;      
} NAME;

void DEF_FUNC(init)(NAME *vec);
void DEF_FUNC(destroy)(NAME *vec);
int DEF_FUNC(push)(NAME *vec, TYPE value);
TYPE DEF_FUNC(pop)(NAME *vec);
void DEF_FUNC(reserve)(NAME *vec, int capacity);
void DEF_FUNC(resize)(NAME *vec, int newCnt, TYPE fill);
void DEF_FUNC(insert)(NAME *vec, int where, const TYPE *arr, int num);
void DEF_FUNC(erase)(NAME *vec, int where, int num);

#undef CONCAT
#undef CONCAT2
#undef DEF_FUNC
#undef TYPE
#undef NAME

#endif