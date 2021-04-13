#ifndef RISCV_MICROK_SYSTEM_H
#define RISCV_MICROK_SYSTEM_H

#include <stdbool.h>

void shutdown();
void kassert(bool condition);
void panic(const char* reason);

#endif //RISCV_MICROK_SYSTEM_H
