#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define DT_LIB_HANDLE HMODULE
#define DT_LIB_LOAD(name) LoadLibrary(name)
#define DT_LIB_GET(handle, name) GetProcAddress(handle, name)
#define DT_LIB_EXTENTION ".dll"
#else
#include <dlfcn.h>
#define DT_LIB_HANDLE void*
#define DT_LIB_LOAD(name) dlopen(name, RTLD_LAZY)
#define DT_LIB_GET(handle, name) dlsym(handle, name)
#define DT_LIB_EXTENTION ".so"
#endif

typedef struct State {
    char *regs[256];
} State;

int main() {
    State state;
    memset(&state, 0, sizeof(State));
    char line[1001];

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == '\0') continue;

        char *words[4];
        int n = 0;
        char *token = strtok(line, " ");
        while (token && n < 4) {
            words[n++] = token;
            token = strtok(NULL, " ");
        }

        if (n == 0) continue;

        char plugin_name[31] = "core";
        char func_name[31] = "";
        char *colon = strchr(words[0], ':');
        
        if (colon) {
            *colon = '\0';
            strncpy(plugin_name, words[0], 30);
            strncpy(func_name, colon + 1, 30);
        } else {
            strncpy(func_name, words[0], 30);
        }

        char lib_path[64];
        sprintf(lib_path, "./%s%s", plugin_name, DT_LIB_EXTENTION);
        
        DT_LIB_HANDLE handle = DT_LIB_LOAD(lib_path);
        if (!handle) {
            printf("Missing plugin %s\n", plugin_name);
            continue;
        }

        char full_func[64];
        sprintf(full_func, "%s_%d", func_name, n - 1);
        
        void *func = (void *)DT_LIB_GET(handle, full_func);

        if (!func) {
            printf("Missing function %s in plugin %s\n", full_func, plugin_name);
        } else {
            if (n == 1) ((void (*)(State*))func)(&state);
            else if (n == 2) ((void (*)(State*, char*))func)(&state, words[1]);
            else if (n == 3) ((void (*)(State*, char*, char*))func)(&state, words[1], words[2]);
            else if (n == 4) ((void (*)(State*, char*, char*, char*))func)(&state, words[1], words[2], words[3]);
        }
    }
    return 0;
}