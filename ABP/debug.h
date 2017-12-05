#include <stdio.h>

#ifdef DEBUG
#define dprintf(fmt, ...) \
        do {\
             printf(fmt, ##__VA_ARGS__);\
        } while (0)
#else
#define dprintf(...)
#endif
