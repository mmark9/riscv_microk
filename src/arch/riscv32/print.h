#ifndef SRC_ARCH_RISCV32_PRINT_H_
#define SRC_ARCH_RISCV32_PRINT_H_

#include <stdarg.h>

#define EOF (-1)


int chtoi(char c);
int printf(const char* const, ...);
int puts(const char* const);
int putchar(int);


#endif /* SRC_ARCH_RISCV32_PRINT_H_ */
