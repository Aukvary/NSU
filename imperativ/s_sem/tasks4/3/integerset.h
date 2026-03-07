#ifndef INTEGER_SET_H
#define INTEGER_SET_H

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT
#endif

typedef struct {
    int count;
    int nums[];
} IntegerSet;

EXPORT
IntegerSet* CreateSet(int* nums, int count);
EXPORT
int IsInSet(IntegerSet* set, int num);

#endif /*INTEGER_SET_H*/