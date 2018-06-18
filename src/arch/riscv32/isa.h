#ifndef SRC_ARCH_RISCV32_ISA_H_
#define SRC_ARCH_RISCV32_ISA_H_

typedef struct {
	// Extensions[0-25] (WARL)
	unsigned int atomic_ext:1;            //A
	unsigned int reserved_0:1;            //B
	unsigned int compressed_ext:1;        //C
	unsigned int double_prec_float_ext:1; //D
	unsigned int rv32e_base_isa:1;        //E
	unsigned int single_prec_float_ext:1; //F
	unsigned int additional_ext:1;        //G
	unsigned int reserved_1:1;            //H
	unsigned int base_isa_ext:1;          //I
	unsigned int reserved_2:1;            //J
	unsigned int reserved_3:1;            //K
	unsigned int reserved_4:1;            //L
	unsigned int int_mul_div_ext:1;       //M
	unsigned int user_int_ext:1;          //N
	unsigned int reserved_5:1;            //O
	unsigned int reserved_6:1;            //P
	unsigned int quad_prec_float_ext:1;   //Q
	unsigned int reserved_7:1;            //R
	unsigned int supervisor_mode_ext:1;   //S
	unsigned int reserved_8:1;            //T
	unsigned int user_mode_ext:1;         //U
	unsigned int reserved_9:1;            //V
	unsigned int reserved_A:1;            //W
	unsigned int non_standard_ext:1;      //X
	unsigned int reserved_B:1;            //Y
	unsigned int reserved_C:1;            //Z
	// Ignored Field[26-29] (WIRI)
	unsigned int ignore:4;
	// ISA width[30-31] (WARL)
	unsigned int isa_width:2;
} misa_register_t;

typedef struct {
	unsigned int offset:7;
	unsigned int blank:25;
} mvendorid_register_t;

typedef struct {
	unsigned int architecture_id:32;
} marchid_register_t;

typedef struct {
	unsigned int implementation_id:32;
} mimpid_register_t;

typedef struct {
	unsigned int hart_id:32;
} mhartid_register_t;

typedef struct {
	// Global Interrupt Flags per privilege mode (per Hart)
	unsigned int user_interrupt_enabled:1;
	unsigned int supervisor_interrupt_enabled:1;
	unsigned int not_used_1:1;
	unsigned int machine_interrupt_enabled:1;
	// Prior to trap Interrupt Flags per privilege mode (per Hart)
	unsigned int user_before_trap_interrupt_enabled:1;
	unsigned int supervisor_before_trap_interrupt_enabled:1;
	unsigned int not_used_2:1;
	unsigned int machine_before_trap_interrupt_enabled:1;
	unsigned int supervisor_prev_privilege_mode:1;
	unsigned int not_used_3:2;
	unsigned int machine_prev_privilege_mode:2;
	// Extension Context Status
	unsigned int fpu_status:2;
	unsigned int additional_usr_mode_ext_status:2;
	// Memory Privilege
	unsigned int modify_privilege_enabled:1;
	unsigned int supervisor_user_memory_access_enabled:1;
	unsigned int make_excutable_readable_enabled:1;
	// Virtualization Support
	unsigned int trap_virtual_memory_enabled:1;
	unsigned int interrutpt_time_enabled:1;
	unsigned int trap_sret_enabled:1;
	// Ignored
	unsigned int not_used_4:8;
} mstatus_register_t;

typedef struct {
	// 0 = Direct = All exceptions set pc to Base
	// 1 = Vectored = Asynchronous interrupts set pc to BASE+4xcause
	unsigned int mode:2;
	// Note: base address must be aligned on 4-byte boundary
	unsigned int base:30;
} mtvec_register_t;

typedef struct {
	unsigned int user_software_interrupt_delegated:1;
	unsigned int supervisor_software_interrupt_delegated:1;
	unsigned int reserved_1:1;
	unsigned int machine_software_interrupt_delegated:1;
	unsigned int user_timer_interrupt_delegated:1;
	unsigned int supervisor_timer_interrupt_delegated:1;
	unsigned int reserved_2:1;
	unsigned int machine_timer_interrupt_delegated:1;
} mideleg_register_t;

typedef struct {
	unsigned int instruction_address_missaligned_delegated:1;
	unsigned int instruction_fault_delegated:1;
	unsigned int illegal_instruction_delegated:1;
	unsigned int break_point_delegated:1;
	unsigned int load_address_misaligned_delegated:1;
	unsigned int load_access_fault_delegated:1;
	unsigned int store_amo_address_misaligned_delegated:1;
	unsigned int store_amo_access_fault_delegated:1;
	unsigned int enviornment_call_from_u_mode_delegated:1;
	unsigned int enviornment_call_from_s_mode_delegated:1;
	unsigned int reserved_1:1;
	unsigned int enviornment_call_from_m_mode_delegated:1;
	unsigned int instruction_page_fault_delegated:1;
	unsigned int load_page_fault_delegated:1;
	unsigned int reserved_2:1;
	unsigned int store_amo_page_fault:1;
} medeleg_register_t;

// TODO: continue defining register layouts
typedef struct {

};

// TODO: use python script to generate pseudo enum
// Pseudo enum
struct {
	unsigned short misa;
	unsigned short mvendorid;
} CSR_ID = {
		.misa = 0x300,
		.mvendorid = 0x301
};

// TODO: use python script to generate read calls
void read_csr_register(unsigned int csr_id, void* reg_out) {
	switch(csr_id) {
	case 0:
		asm volatile ("csrr t0, misa\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case 1:
		asm volatile ("csrr t0, mvendorid\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	}
}

int get_core_vendor_id() {
	mvendorid_register_t reg;
	read_csr_register(1, &reg);
	return reg.offset ^ 0x80;
}

#endif /* SRC_ARCH_RISCV32_ISA_H_ */
