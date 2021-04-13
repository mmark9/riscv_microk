#ifndef SRC_ARCH_RISCV32_PRINT_H_
#define SRC_ARCH_RISCV32_PRINT_H_

#include <stdarg.h>

#define EOF (-1)


int kchtoi(char c);
int kprintf(const char* const, ...);
int kputs(const char* const);
int kputchar(int);


#endif /* SRC_ARCH_RISCV32_PRINT_H_ */
