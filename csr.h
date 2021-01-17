#ifndef SRC_ARCH_RISCV32_CSR_H_
#define SRC_ARCH_RISCV32_CSR_H_

#include <stdint.h>

/** User Trap Setup **/
// URW - User status register.
#define CSR_USTATUS 0x000
// URW - User interrupt-enable register.
#define CSR_UIE 0x004
// URW - User trap handler base address.
#define CSR_UTVEC 0x005
/** User Trap Handling **/
// URW - Scratch register for user trap handlers.
#define CSR_USCRATCH 0x040
// URW - User exception program counter.
#define CSR_UEPC 0x041
// URW - User trap cause.
#define CSR_UCAUSE 0x042
// URW - User bad address or instruction.
#define CSR_UTVAL 0x043
// URW - User interrupt pending.
#define CSR_UIP 0x044
/** User Floating-Point CSRs **/
// URW - Floating-Point Accrued Exceptions.
#define CSR_FFLAGS 0x001
// URW - Floating-Point Dynamic Rounding Mode.
#define CSR_FRM 0x002
// URW - Floating-Point Control and Status Register (frm + fflags).
#define CSR_FCSR 0x003
/** User Counter/Timers **/
// URO - Cycle counter for RDCYCLE instruction.
#define CSR_CYCLE 0xC00
// URO - Timer for RDTIME instruction.
#define CSR_TIME 0xC01
// URO - Instructions-retired counter for RDINSTRET instruction.
#define CSR_INSTRET 0xC02
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER3 0xC03
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER4 0xC04
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER5 0xC05
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER6 0xC06
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER7 0xC07
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER8 0xC08
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER9 0xC09
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER10 0xC0A
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER11 0xC0B
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER12 0xC0C
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER13 0xC0D
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER14 0xC0E
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER15 0xC0F
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER16 0xC10
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER17 0xC11
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER18 0xC12
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER19 0xC13
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER20 0xC14
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER21 0xC15
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER22 0xC16
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER23 0xC17
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER24 0xC18
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER25 0xC19
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER26 0xC1A
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER27 0xC1B
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER28 0xC1C
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER29 0xC1D
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER30 0xC1E
// URO - Performance-monitoring counter.
#define CSR_HPMCOUNTER31 0xC1F
// URO - Upper 32 bits of cycle, RV32I only.
#define CSR_CYCLEH 0xC80
// URO - Upper 32 bits of time, RV32I only.
#define CSR_TIMEH 0xC81
// URO - Upper 32 bits of instret, RV32I only.
#define CSR_INSTRETH 0xC82
// URO - Upper 32 bits of hpmcounter3, RV32I only.
#define CSR_HPMCOUNTER3H 0xC83
// URO - Upper 32 bits of hpmcounter4, RV32I only.
#define CSR_HPMCOUNTER4H 0xC84
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER5H 0xC85
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER6H 0xC86
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER7H 0xC87
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER8H 0xC88
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER9H 0xC89
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER10H 0xC8A
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER11H 0xC8B
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER12H 0xC8C
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER13H 0xC8D
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER14H 0xC8E
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER15H 0xC8F
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER16H 0xC90
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER17H 0xC91
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER18H 0xC92
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER19H 0xC93
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER20H 0xC94
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER21H 0xC95
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER22H 0xC96
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER23H 0xC97
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER24H 0xC98
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER25H 0xC99
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER26H 0xC9A
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER27H 0xC9B
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER28H 0xC9C
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER29H 0xC9D
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER30H 0xC9E
// URO - upper 32 bits of hpmcounter31, RV32I only.
#define CSR_HPMCOUNTER31H 0xC9F
/** Supervisor Trap Setup **/
// SRW - Supervisor status register.
#define CSR_SSTATUS 0x100
// SRW - Supervisor exception delegation register.
#define CSR_SEDELEG 0x102
// SRW - Supervisor interrupt delegation register.
#define CSR_SIDELEG 0x103
// SRW - Supervisor interrupt-enable register.
#define CSR_SIE 0x104
// SRW - Supervisor trap handler base address.
#define CSR_STVEC 0x105
// SRW - Supervisor counter enable.
#define CSR_SCOUNTEREN 0x106
/** Supervisor Trap Handling **/
// SRW - Scratch register for supervisor trap handlers.
#define CSR_SSCRATCH 0x140
// SRW - Supervisor exception program counter.
#define CSR_SEPC 0x141
// SRW - Supervisor trap cause.
#define CSR_SCAUSE 0x142
// SRW - Supervisor bad address or instruction.
#define CSR_STVAL 0x143
// SRW - Supervisor interrupt pending.
#define CSR_SIP 0x144
/** Supervisor Protection and Translation **/
// SRW - Supervisor address translation and protection.
#define CSR_SATP 0x180
/** Machine Information Registers **/
// MRO - Vendor ID.
#define CSR_MVENDORID 0xF11
// MRO - Architecture ID.
#define CSR_MARCHID 0xF12
// MRO - Implementation ID.
#define CSR_MIMPID 0xF13
// MRO - Hardware thread ID.
#define CSR_MHARTID 0xF14
/** Machine Trap Setup **/
// MRW - Machine status register.
#define CSR_MSTATUS 0x300
// MRW - ISA and extensions
#define CSR_MISA 0x301
// MRW - Machine exception delegation register.
#define CSR_MEDELEG 0x302
// MRW - Machine interrupt delegation register.
#define CSR_MIDELEG 0x303
// MRW - Machine interrupt-enable register.
#define CSR_MIE 0x304
// MRW - Machine trap-handler base address.
#define CSR_MTVEC 0x305
// MRW - Machine counter enable.
#define CSR_MCOUNTEREN 0x306
/** Machine Trap Handling **/
// MRW - Scratch register for machine trap handlers.
#define CSR_MSCRATCH 0x340
// MRW - Machine exception program counter.
#define CSR_MEPC 0x341
// MRW - Machine trap cause.
#define CSR_MCAUSE 0x342
// MRW - Machine bad address or instruction.
#define CSR_MTVAL 0x343
// MRW - Machine interrupt pending.
#define CSR_MIP 0x344
/** Machine Protection and Translation **/
// MRW - Physical memory protection configuration.
#define CSR_PMPCFG0 0x3A0
// MRW - Physical memory protection configuration, RV32 only.
#define CSR_PMPCFG1 0x3A1
// MRW - Physical memory protection configuration.
#define CSR_PMPCFG2 0x3A2
// MRW - Physical memory protection configuration, RV32 only.
#define CSR_PMPCFG3 0x3A3
// MRW - Physical memory protection address register.
#define CSR_PMPADDR0 0x3B0
// MRW - Physical memory protection address register.
#define CSR_PMPADDR1 0x3B1
// MRW - Physical memory protection address register.
#define CSR_PMPADDR2 0x3B2
// MRW - Physical memory protection address register.
#define CSR_PMPADDR3 0x3B3
// MRW - Physical memory protection address register.
#define CSR_PMPADDR4 0x3B4
// MRW - Physical memory protection address register.
#define CSR_PMPADDR5 0x3B5
// MRW - Physical memory protection address register.
#define CSR_PMPADDR6 0x3B6
// MRW - Physical memory protection address register.
#define CSR_PMPADDR7 0x3B7
// MRW - Physical memory protection address register.
#define CSR_PMPADDR8 0x3B8
// MRW - Physical memory protection address register.
#define CSR_PMPADDR9 0x3B9
// MRW - Physical memory protection address register.
#define CSR_PMPADDR10 0x3BA
// MRW - Physical memory protection address register.
#define CSR_PMPADDR11 0x3BB
// MRW - Physical memory protection address register.
#define CSR_PMPADDR12 0x3BC
// MRW - Physical memory protection address register.
#define CSR_PMPADDR13 0x3BD
// MRW - Physical memory protection address register.
#define CSR_PMPADDR14 0x3BE
// MRW - Physical memory protection address register.
#define CSR_PMPADDR15 0x3BF
/** Machine Counter/Timers **/
// MRW - Machine cycle counter.
#define CSR_MCYCLE 0xB00
// MRW - Machine instructions-retired counter.
#define CSR_MINSTRET 0xB02
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER3 0xB03
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER4 0xB04
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER5 0xB05
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER6 0xB06
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER7 0xB07
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER8 0xB08
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER9 0xB09
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER10 0xB0A
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER11 0xB0B
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER12 0xB0C
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER13 0xB0D
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER14 0xB0E
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER15 0xB0F
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER16 0xB10
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER17 0xB11
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER18 0xB12
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER19 0xB13
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER20 0xB14
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER21 0xB15
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER22 0xB16
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER23 0xB17
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER24 0xB18
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER25 0xB19
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER26 0xB1A
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER27 0xB1B
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER28 0xB1C
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER29 0xB1D
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER30 0xB1E
// MRW - Machine performance-monitoring counter.
#define CSR_MHPMCOUNTER31 0xB1F
// MRW - Upper 32 bits of mcycle, RV32I only.
#define CSR_MCYCLEH 0xB80
// MRW - Upper 32 bits of minstret, RV32I only.
#define CSR_MINSTRETH 0xB82
// MRW - Upper 32 bits of mhpmcounter3, RV32I only.
#define CSR_MHPMCOUNTER3H 0xB83
// MRW - Upper 32 bits of mhpmcounter4, RV32I only.
#define CSR_MHPMCOUNTER4H 0xB84
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER5H 0xB85
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER6H 0xB86
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER7H 0xB87
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER8H 0xB88
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER9H 0xB89
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER10H 0xB8A
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER11H 0xB8B
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER12H 0xB8C
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER13H 0xB8D
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER14H 0xB8E
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER15H 0xB8F
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER16H 0xB90
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER17H 0xB91
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER18H 0xB92
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER19H 0xB93
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER20H 0xB94
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER21H 0xB95
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER22H 0xB96
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER23H 0xB97
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER24H 0xB98
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER25H 0xB99
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER26H 0xB9A
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER27H 0xB9B
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER28H 0xB9C
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER29H 0xB9D
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER30H 0xB9E
// MRW - Upper 32 bits of mhpmcounter31, RV32I only.
#define CSR_MHPMCOUNTER31H 0xB9F
/** Machine Counter Setup **/
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT3 0x323
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT4 0x324
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT5 0x325
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT6 0x326
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT7 0x327
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT8 0x328
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT9 0x329
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT10 0x32A
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT11 0x32B
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT12 0x32C
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT13 0x32D
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT14 0x32E
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT15 0x32F
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT16 0x330
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT17 0x331
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT18 0x332
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT19 0x333
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT20 0x334
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT21 0x335
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT22 0x336
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT23 0x337
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT24 0x338
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT25 0x339
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT26 0x33A
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT27 0x33B
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT28 0x33C
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT29 0x33D
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT30 0x33E
// MRW - Machine performance-monitoring event selector.
#define CSR_MHPMEVENT31 0x33F
/** Debug/Trace Registers (shared with Debug Mode) **/
// MRW - Debug/Trace trigger register select.
#define CSR_TSELECT 0x7A0
// MRW - First Debug/Trace trigger data register.
#define CSR_TDATA1 0x7A1
// MRW - Second Debug/Trace trigger data register.
#define CSR_TDATA2 0x7A2
// MRW - Third Debug/Trace trigger data register.
#define CSR_TDATA3 0x7A3
/** Debug Mode Registers **/
// DRW - Debug control and status register.
#define CSR_DCSR 0x7B0
// DRW - Debug PC.
#define CSR_DPC 0x7B1
// DRW - Debug scratch register.
#define CSR_DSCRATCH 0x7B2

// Machine ISA Register
typedef union {
	uint32_t value;
	struct {
		// Extensions[0-25] (WARL)
		uint32_t atomic_ext:1;            //A
		uint32_t reserved_0:1;            //B
		uint32_t compressed_ext:1;        //C
		uint32_t double_prec_float_ext:1; //D
		uint32_t rv32e_base_isa:1;        //E
		uint32_t single_prec_float_ext:1; //F
		uint32_t additional_ext:1;        //G
		uint32_t reserved_1:1;            //H
		uint32_t base_isa_ext:1;          //I
		uint32_t reserved_2:1;            //J
		uint32_t reserved_3:1;            //K
		uint32_t reserved_4:1;            //L
		uint32_t int_mul_div_ext:1;       //M
		uint32_t user_int_ext:1;          //N
		uint32_t reserved_5:1;            //O
		uint32_t reserved_6:1;            //P
		uint32_t quad_prec_float_ext:1;   //Q
		uint32_t reserved_7:1;            //R
		uint32_t supervisor_mode_ext:1;   //S
		uint32_t reserved_8:1;            //T
		uint32_t user_mode_ext:1;         //U
		uint32_t reserved_9:1;            //V
		uint32_t reserved_A:1;            //W
		uint32_t non_standard_ext:1;      //X
		uint32_t reserved_B:1;            //Y
		uint32_t reserved_C:1;            //Z
		// Ignored Field[26-29] (WIRI)
		uint32_t ignore:4;
		// ISA width[30-31] (WARL)
		uint32_t isa_width:2;
	} fields;
} misa_csr_t;

// Machine Vendor ID Register


typedef union {
	uint32_t value;
	struct {
		uint32_t offset:7;
		uint32_t blank:25;
	} fields;
} mvendorid_csr_t;;

// Machine Architecture ID Register
typedef struct {
	uint32_t architecture_id:32;
} marchid_csr_t;

// Machine Implementation ID Register
typedef struct {
	uint32_t implementation_id:32;
} mimpid_csr_t;

// Hart ID Register - core/hardware thread ID
typedef struct {
	uint32_t hart_id:32;
} mhartid_csr_t;

// Machine Status Register
typedef union {
	uint32_t value;
	struct {
		// Global Interrupt Flags per privilege mode (per Hart)
		uint32_t user_interrupts_enabled:1;
		uint32_t supervisor_interrupts_enabled:1;
		uint32_t reserved_1:1;
		uint32_t machine_interrupts_enabled:1;
		// Prior to trap Interrupt Flags per privilege mode (per Hart)
		uint32_t user_interrupts_enabled_before_trap:1;
		uint32_t supervisor_interrupts_enabled_before_trap:1;
		uint32_t reserved_2:1;
		uint32_t machine_interrupts_enabled_before_trap:1;
		uint32_t supervisor_privilege_mode_before_trap:1;
		uint32_t reserved_3:2;
		uint32_t machine_privilege_mode_before_trap:2;
		// Extension Context Status
		uint32_t fpu_status:2;
		uint32_t additional_user_mode_ext_status:2;
		// Memory Privilege
		uint32_t modify_privilege_enabled:1;
		uint32_t supervisor_user_memory_access_enabled:1;
		uint32_t make_excutable_readable_enabled:1;
		// Virtualization Support
		uint32_t trap_virtual_memory_enabled:1;
		uint32_t interrutpt_time_enabled:1;
		uint32_t trap_sret_enabled:1;
		// Ignored
		uint32_t reserved_4:8;
		unsigned sd:1;
	} fields;
} mstatus_csr_t;

// Machine Exception Delegation Register
typedef union {
	uint32_t value;
	struct {
		uint32_t instruction_address_missaligned_delegated:1;
		uint32_t instruction_access_fault_delegated:1;
		uint32_t illegal_instruction_delegated:1;
		uint32_t break_point_delegated:1;
		uint32_t load_address_misaligned_delegated:1;
		uint32_t load_access_fault_delegated:1;
		uint32_t store_amo_address_misaligned_delegated:1;
		uint32_t store_amo_access_fault_delegated:1;
		uint32_t enviornment_call_from_user_mode_delegated:1;
		uint32_t enviornment_call_from_supervisor_mode_delegated:1;
		uint32_t reserved_1:1;
		// ECALLS from machine mode cannot be delegated
		uint32_t enviornment_call_from_machine_mode_delegated:1;
		uint32_t instruction_page_fault_delegated:1;
		uint32_t load_page_fault_delegated:1;
		uint32_t reserved_2:1;
		uint32_t store_amo_page_fault_delegated:1;
		uint32_t reserved_3:16;
	} fields;
} medeleg_csr_t;

// Machine Interrupt Delegation register
typedef union {
	uint32_t value;
	struct {
		uint32_t user_software_interrupts_delegated:1;
		uint32_t supervisor_software_interrupts_delegated:1;
		uint32_t reserved_1:1;
		uint32_t machine_software_interrupts_delegated:1;
		uint32_t user_timer_interrupts_delegated:1;
		uint32_t supervisor_timer_interrupts_delegated:1;
		uint32_t reserved_2:1;
		uint32_t machine_timer_interrupts_delegated:1;
		uint32_t user_external_interrupts_delegated:1;
		uint32_t supervisor_external_interrupts_delegated:1;
		uint32_t reserved_3:1;
		uint32_t machine_external_interrupts_delegated:1;
		uint32_t reserved_4:20;
	} fields;
} mideleg_csr_t;

// Machine interrupt-pending register
typedef union {
	uint32_t value;
	struct {
		uint32_t user_software_interrupts_pending:1;
		uint32_t supervisor_software_interrupts_pending:1;
		uint32_t reserved_1:1;
		uint32_t machine_software_interrupts_pending:1;
		uint32_t user_timer_interrupts_pending:1;
		uint32_t supervisor_timer_interrupts_pending:1;
		uint32_t reserved_2:1;
		uint32_t machine_timer_interrupts_pending:1;
		uint32_t user_external_interrupts_pending:1;
		uint32_t supervisor_external_interrupts_pending:1;
		uint32_t reserved_3:1;
		uint32_t machine_external_interrupts_pending:1;
		uint32_t reserved_4:20;
	} fields;
} mip_csr_t;

// Machine interrupt-enable registers
typedef union {
	uint32_t value;
	struct {
		uint32_t user_software_interrupts_enabled:1;
		uint32_t supervisor_software_interrupts_enabled:1;
		uint32_t reserved_1:1;
		uint32_t machine_software_interrupts_enabled:1;
		uint32_t user_timer_interrupts_enabled:1;
		uint32_t supervisor_timer_interrupts_enabled:1;
		uint32_t reserved_2:1;
		uint32_t machine_timer_interrupts_enabled:1;
		uint32_t user_external_interrupts_enabled:1;
		uint32_t supervisor_external_interrupts_enabledd:1;
		uint32_t reserved_3:1;
		uint32_t machine_external_interrupts_enabled:1;
		uint32_t reserved_4:20;
	} fields;
} mie_csr_t;

// Machine timer register
// Note two reads are needed for this
typedef struct {
	unsigned long long machine_time:64;
} mtime_csr_t;

// Machine time compare register
typedef struct {
	unsigned long long machine_time_compare_register:64;
} mtimecmp_csr_t;

// Hardware performance monitor counter registers
// Note since these are just 64 bit counters, we can just define one struct
typedef struct {
	unsigned long long value:64;
} hpmc_csr_t;

// Hardware performance monitor event register
// Note since these are just 64 bit counters, we can just define one struct
typedef struct {
	uint32_t value:32;
} hpme_csr_t;

// Counter-enable registers (mcounteren and scounteren)
// m = machine | s = supervisor
// setting a counter bit in a higher privilege mode
// register enables access in a lower privilege mode
typedef union {
	uint32_t value;
	struct {
		uint32_t cycle_enabled:1;
		uint32_t time_enableld:1;
		uint32_t instret_enabled:1;
		uint32_t hpm3_enabled:1;
		uint32_t hpm4_enabled:1;
		uint32_t hpm5_enabled:1;
		uint32_t hpm6_enabled:1;
		uint32_t hpm7_enabled:1;
		uint32_t hpm8_enabled:1;
		uint32_t hpm9_enabled:1;
		uint32_t hpm10_enabled:1;
		uint32_t hpm11_enabled:1;
		uint32_t hpm12_enabled:1;
		uint32_t hpm13_enabled:1;
		uint32_t hpm14_enabled:1;
		uint32_t hpm15_enabled:1;
		uint32_t hpm16_enabled:1;
		uint32_t hpm17_enabled:1;
		uint32_t hpm18_enabled:1;
		uint32_t hpm19_enabled:1;
		uint32_t hpm20_enabled:1;
		uint32_t hpm21_enabled:1;
		uint32_t hpm22_enabled:1;
		uint32_t hpm23_enabled:1;
		uint32_t hpm24_enabled:1;
		uint32_t hpm25_enabled:1;
		uint32_t hpm26_enabled:1;
		uint32_t hpm27_enabled:1;
		uint32_t hpm28_enabled:1;
		uint32_t hpm29_enabled:1;
		uint32_t hpm30_enabled:1;
		uint32_t hpm31_enabled:1;
	} fields;
} counteren_csr_t;

/**  Generic CSRs  **/

// Trap-Vector Base-Address Register
typedef union {
	uint32_t value;
	struct fields {
		// 0 = Direct = All exceptions set pc to Base
		// 1 = Vectored = Asynchronous interrupts set pc to BASE+4xcause
		uint32_t mode:2;
		// Note: base address must be aligned on 4-byte boundary
		uint32_t base:30;
	} fields;
} tvec_csr_t;

// Scratch Register - Generic
typedef struct {
	uint32_t value:32;
} scratch_csr_t;

// Exception Register - Generic
typedef struct {
	uint32_t address:32;
} epc_csr_t;

// Trap Cause Register - Generic


typedef union {
	uint32_t value;
	struct {
		uint32_t exception_code:31;
		uint32_t was_caused_by_interrupt:1;
	} fields;
} tcause_csr_t;


// Trap Value Register - Generic
typedef struct {
	uint32_t value:32;
} ttval_csr_t;


/**  Supervisor CSR specific **/
typedef union {
	uint32_t value;
	struct {
		uint32_t user_interrupts_enabled:1;
		uint32_t supervisor_interrupts_enabled:1;
		uint32_t reserved_1:2;
		uint32_t user_interrupts_enabled_before_trap:1;
		uint32_t supervisor_interrupts_enabled_before_trap:1;
		uint32_t reserved_2:2;
		uint32_t privilege_mode_before_interrupt:1;  // 0 = user 1 = super
		uint32_t reserved_3:4;
		// Extension Context Status
		uint32_t fpu_status:2;
		uint32_t additional_user_mode_ext_status:2;
		// Memory Privilege
		uint32_t reserved_4:1;
		uint32_t supervisor_user_memory_access_enabled:1;
		uint32_t make_excutable_readable_enabled:1;
		// Ignored
		uint32_t reserved_5:11;
		unsigned sd:1;
	} fields;
} sstatus_csr_t;


// Supervisor interrupt-pending register
typedef union {
	uint32_t value;
	struct {
		uint32_t user_software_interrupts_pending:1;
		uint32_t supervisor_software_interrupts_pending:1;
		uint32_t reserved_1:2;
		uint32_t user_timer_interrupts_pending:1;
		uint32_t supervisor_timer_interrupts_pending:1;
		uint32_t reserved_2:2;
		uint32_t user_external_interrupts_pending:1;
		uint32_t supervisor_external_interrupts_pending:1;
		uint32_t reserved_4:22;
	} fields;
} sip_csr_t;

// Supervisor interrupt-enable registers
typedef union {
	uint32_t value;
	struct {
		uint32_t user_software_interrupts_enabled:1;
		uint32_t supervisor_software_interrupts_enabled:1;
		uint32_t reserved_1:2;
		uint32_t user_timer_interrupts_enabled:1;
		uint32_t supervisor_timer_interrupts_enabled:1;
		uint32_t reserved_2:2;
		uint32_t user_external_interrupts_enabled:1;
		uint32_t supervisor_external_interrupts_enabled:1;
		uint32_t reserved_4:22;
	} fields;
} sie_csr_t;

typedef union {
	uint32_t value;
	struct {
		uint32_t physical_page_number:22;
		uint32_t address_space_identifier:9;
		uint32_t mode:1;
	} fields;
} stvec_csr_t;

void riscv_set_csr_bits(uint16_t csr_id, uint32_t value);
void riscv_clear_csr_bits(uint16_t csr_id, uint32_t value);
void riscv_write_csr(uint16_t csr_id, uint32_t value);
void riscv_read_csr_register(uint16_t csr_id, void* reg_out);

#endif /* SRC_ARCH_RISCV32_CSR_H_ */
