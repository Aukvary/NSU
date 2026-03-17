#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define LIB_HANDLE HMODULE
#define LIB_LOAD(name) LoadLibraryA(name)
#define LIB_GET(handle, name) GetProcAddress(handle, name)
#define LIB_CLOSE(handle) FreeLibrary(handle)
#define LIB_EXT ".dll"
#else
#include <dlfcn.h>
#define LIB_HANDLE void*
#define LIB_LOAD(name) dlopen(name, RTLD_LAZY)
#define LIB_GET(handle, name) dlsym(handle, name)
#define LIB_CLOSE(handle) dlclose(handle)
#define LIB_EXT ".so"
#endif

typedef struct State {
    char *regs[256];
} State;

int main() {
    State state = {0};
    char line[1024] = {0};
    static const char delims[] = " \t\n\r";

    while (fgets(line, sizeof(line), stdin)) {
        char *words[4] = {0};
        int n = 0;

        char *token = strtok(line, delims);
        while (token && n < 4) {
            words[n++] = token;
            token = strtok(NULL, delims);
        }

        if (n == 0) continue;

        char plugin_name[128] = "core";
        char func_raw[128] = {0};

        char *colon = strchr(words[0], ':');
        if (colon) {
            int name_len = (int)(colon - words[0]);
            if (name_len > 127) name_len = 127;
            memcpy(plugin_name, words[0], name_len);
            plugin_name[name_len] = '\0';
            strcpy(func_raw, colon + 1);
        } else {
            strcpy(plugin_name, "core");
            strcpy(func_raw, words[0]);
        }

        char lib_path[1005];

        #ifdef _WIN32
            sprintf(lib_path, "%s%s", plugin_name, LIB_EXT); 
        #else
            sprintf(lib_path, "./%s%s", plugin_name, LIB_EXT); 
        #endif

        LIB_HANDLE handle = LIB_LOAD(lib_path);
        if (!handle) {
            printf("Missing plugin %s\n", plugin_name);
            fflush(stdout);
            continue;
        }

        char full_func[1005];
        sprintf(full_func, "%s_%d", func_raw, n - 1);

        void *func = (void *)LIB_GET(handle, full_func);

        if (!func) {
            printf("Missing function %s in plugin %s\n", full_func, plugin_name);
            fflush(stdout);
        } else {
            if (n == 1) ((void (*)(State*))func)(&state);
            else if (n == 2) ((void (*)(State*, char*))func)(&state, words[1]);
            else if (n == 3) ((void (*)(State*, char*, char*))func)(&state, words[1], words[2]);
            else if (n == 4) ((void (*)(State*, char*, char*, char*))func)(&state, words[1], words[2], words[3]);
            fflush(stdout);
        }
    }
    return 0;
}