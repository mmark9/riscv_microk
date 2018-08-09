#ifndef SRC_ARCH_RISCV32_ISA_H_
#define SRC_ARCH_RISCV32_ISA_H_

typedef enum {
	RISCV_PRIV_MACHINE,
	RISCV_PRIV_SUPERVISOR,
	RISCV_PRIV_USER
} riscv_privilege_t;


void asm_machine_trap();

void asm_supervisor_trap();

void riscv_setup_interrupts();

int riscv_get_core_vendor_id();

#endif /* SRC_ARCH_RISCV32_ISA_H_ */
