#ifndef SRC_ARCH_RISCV32_PRINT_H_
#define SRC_ARCH_RISCV32_PRINT_H_

#include <stdarg.h>

#define EOF (-1)

typedef enum {
    K_DEBUG = 0,
    K_INFO,
    K_WARN,
    K_ERROR,
} KLogLevel;

int kchtoi(char c);
int kprintf(KLogLevel level, const char* const, ...);
int kputs(KLogLevel level, const char* const);
int kputchar(int);


#endif /* SRC_ARCH_RISCV32_PRINT_H_ */
