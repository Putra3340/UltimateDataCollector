#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

    // Declaration for the C function in a C file
    void printTree(const char* path, int level, FILE* file);
    void GetCDir();
    void GetDDir();
    void GetEDir();
    
#ifdef __cplusplus
}
#endif
