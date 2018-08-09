#include "isa.h"
#include "csr.h"


void riscv_halt() { for(;;) {} }

void riscv_ecall() { asm volatile ("ecall" : : : ); }

// does not return
void riscv_machine_mode_do_setup() {
	tvec_register_t tv;
	mstatus_register_t mstatus;
	mie_register_t mie;
	mip_register_t mip;
	medeleg_register_t medeleg;
	mideleg_register_t mideleg;

	tv.value = 0;
	mstatus.value = 0;
	mie.value = 0;
	mip.value = 0;
	medeleg.value = 0;
	mideleg.value = 0;

	// set machine trap vector
	tv.fields.base = (unsigned int)(asm_machine_trap) >> 2;
	tv.fields.mode = 0;
	riscv_write_csr(CSR_MTVEC, tv.value);

	// enable machine/supervisor software interrupts
	mie.fields.machine_software_interrupts_enabled = 1;
	mie.fields.supervisor_software_interrupts_enabled = 1;
	riscv_set_csr_bits(CSR_MIE, mie.value);

	// interrupt delegation
	mideleg.fields.supervisor_external_interrupts_delegated = 1;
	mideleg.fields.supervisor_software_interrupts_delegated = 1;
	mideleg.fields.supervisor_timer_interrupts_delegated = 1;
	mideleg.fields.user_external_interrupts_delegated = 1;
	mideleg.fields.user_software_interrupts_delegated = 1;
	mideleg.fields.user_timer_interrupts_delegated = 1;
	riscv_set_csr_bits(CSR_MIDELEG, mideleg.value);

	// exception delegation
	medeleg.fields.instruction_address_missaligned_delegated = 1;
	medeleg.fields.instruction_access_fault_delegated = 1;
	medeleg.fields.illegal_instruction_delegated = 1;
	medeleg.fields.break_point_delegated = 1;
	medeleg.fields.load_address_misaligned_delegated = 1;
	medeleg.fields.load_access_fault_delegated = 1;
	medeleg.fields.store_amo_address_misaligned_delegated = 1;
	medeleg.fields.store_amo_access_fault_delegated = 1;
	medeleg.fields.enviornment_call_from_supervisor_mode_delegated = 1;
	medeleg.fields.enviornment_call_from_user_mode_delegated = 1;
	medeleg.fields.instruction_page_fault_delegated = 1;
	medeleg.fields.load_page_fault_delegated = 1;
	medeleg.fields.store_amo_page_fault_delegated = 1;
	riscv_set_csr_bits(CSR_MEDELEG, medeleg.value);

	// enable machine interrupts in machine mode
	mstatus.fields.machine_interrupts_enabled = 1;
	riscv_set_csr_bits(CSR_MSTATUS, mstatus.value);

	riscv_ecall();
}

void riscv_supervisor_mode_do_setup() {
	tvec_register_t tv;
	sstatus_register_t sstatus;
	mstatus_register_t mstatus;
	sip_register_t sip;
	sie_register_t sie;
	tv.fields.base = (unsigned int)(asm_supervisor_trap) >> 2;
	tv.fields.mode = 0;
	riscv_write_csr(CSR_STVEC, tv.value);
	sstatus.value = 0;
	riscv_read_csr_register(CSR_SSTATUS, &sstatus);

	sie.value = 0;
	sip.value = 0;
	riscv_read_csr_register(CSR_SIE, &sie);
	riscv_read_csr_register(CSR_SIP, &sip);
	sie.fields.supervisor_software_interrupts_enabled = 1;
	riscv_set_csr_bits(CSR_SIE, sie.value);
	sstatus.fields.supervisor_interrupts_enabled = 1;
	riscv_set_csr_bits(CSR_SSTATUS, sstatus.value);
	riscv_read_csr_register(CSR_MSTATUS, &mstatus);
	int i = 0;
	riscv_halt();
}


void riscv_handle_machine_interrupt() {
	tcause_register_t trap_cause;
	epc_register_t trap_instr;
	mstatus_register_t machine_status;
	ttval_register_t trap_arg;
	mip_register_t pending_interrupts;
	pending_interrupts.value = 0;
	riscv_read_csr_register(CSR_MCAUSE, &trap_cause);
	riscv_read_csr_register(CSR_MEPC, &trap_instr);
	riscv_read_csr_register(CSR_MSTATUS, &machine_status);
	riscv_read_csr_register(CSR_MTVAL, &trap_arg);
	riscv_read_csr_register(CSR_MIP, &pending_interrupts);
}

void riscv_handle_supervisor_interrupt() {
	tcause_register_t trap_cause;
	epc_register_t trap_instr;
	sstatus_register_t supervisor_status;
	ttval_register_t trap_arg;
	sip_register_t sip;
	sip.value = 0;
	riscv_read_csr_register(CSR_SIP, &sip);
	riscv_read_csr_register(CSR_SCAUSE, &trap_cause);
	riscv_read_csr_register(CSR_SEPC, &trap_instr);
	riscv_read_csr_register(CSR_SSTATUS, &supervisor_status);
	riscv_read_csr_register(CSR_STVAL, &trap_arg);
}

void riscv_handle_user_interrupt() {
	int x = 0;
}

int riscv_get_core_vendor_id() {
	mvendorid_register_t reg;
	riscv_read_csr_register(CSR_MVENDORID, &reg);
	return reg.fields.offset ^ 0x80;
}
