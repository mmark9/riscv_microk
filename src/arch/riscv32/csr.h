#ifndef SRC_ARCH_RISCV32_CSR_H_
#define SRC_ARCH_RISCV32_CSR_H_

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

void read_csr_register(unsigned short csr_id, void* reg_out) {
	switch (csr_id) {
	case CSR_USTATUS:
		asm volatile ("csrr t0, ustatus\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UIE:
		asm volatile ("csrr t0, uie\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UTVEC:
		asm volatile ("csrr t0, utvec\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_USCRATCH:
		asm volatile ("csrr t0, uscratch\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UEPC:
		asm volatile ("csrr t0, uepc\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UCAUSE:
		asm volatile ("csrr t0, ucause\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UTVAL:
		asm volatile ("csrr t0, utval\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_UIP:
		asm volatile ("csrr t0, uip\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_FFLAGS:
		asm volatile ("csrr t0, fflags\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_FRM:
		asm volatile ("csrr t0, frm\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_FCSR:
		asm volatile ("csrr t0, fcsr\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_CYCLE:
		asm volatile ("csrr t0, cycle\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TIME:
		asm volatile ("csrr t0, time\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_INSTRET:
		asm volatile ("csrr t0, instret\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER3:
		asm volatile ("csrr t0, hpmcounter3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER4:
		asm volatile ("csrr t0, hpmcounter4\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER5:
		asm volatile ("csrr t0, hpmcounter5\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER6:
		asm volatile ("csrr t0, hpmcounter6\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER7:
		asm volatile ("csrr t0, hpmcounter7\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER8:
		asm volatile ("csrr t0, hpmcounter8\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER9:
		asm volatile ("csrr t0, hpmcounter9\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER10:
		asm volatile ("csrr t0, hpmcounter10\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER11:
		asm volatile ("csrr t0, hpmcounter11\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER12:
		asm volatile ("csrr t0, hpmcounter12\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER13:
		asm volatile ("csrr t0, hpmcounter13\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER14:
		asm volatile ("csrr t0, hpmcounter14\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER15:
		asm volatile ("csrr t0, hpmcounter15\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER16:
		asm volatile ("csrr t0, hpmcounter16\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER17:
		asm volatile ("csrr t0, hpmcounter17\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER18:
		asm volatile ("csrr t0, hpmcounter18\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER19:
		asm volatile ("csrr t0, hpmcounter19\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER20:
		asm volatile ("csrr t0, hpmcounter20\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER21:
		asm volatile ("csrr t0, hpmcounter21\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER22:
		asm volatile ("csrr t0, hpmcounter22\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER23:
		asm volatile ("csrr t0, hpmcounter23\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER24:
		asm volatile ("csrr t0, hpmcounter24\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER25:
		asm volatile ("csrr t0, hpmcounter25\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER26:
		asm volatile ("csrr t0, hpmcounter26\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER27:
		asm volatile ("csrr t0, hpmcounter27\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER28:
		asm volatile ("csrr t0, hpmcounter28\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER29:
		asm volatile ("csrr t0, hpmcounter29\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER30:
		asm volatile ("csrr t0, hpmcounter30\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER31:
		asm volatile ("csrr t0, hpmcounter31\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_CYCLEH:
		asm volatile ("csrr t0, cycleh\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TIMEH:
		asm volatile ("csrr t0, timeh\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_INSTRETH:
		asm volatile ("csrr t0, instreth\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER3H:
		asm volatile ("csrr t0, hpmcounter3h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER4H:
		asm volatile ("csrr t0, hpmcounter4h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER5H:
		asm volatile ("csrr t0, hpmcounter5h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER6H:
		asm volatile ("csrr t0, hpmcounter6h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER7H:
		asm volatile ("csrr t0, hpmcounter7h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER8H:
		asm volatile ("csrr t0, hpmcounter8h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER9H:
		asm volatile ("csrr t0, hpmcounter9h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER10H:
		asm volatile ("csrr t0, hpmcounter10h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER11H:
		asm volatile ("csrr t0, hpmcounter11h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER12H:
		asm volatile ("csrr t0, hpmcounter12h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER13H:
		asm volatile ("csrr t0, hpmcounter13h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER14H:
		asm volatile ("csrr t0, hpmcounter14h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER15H:
		asm volatile ("csrr t0, hpmcounter15h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER16H:
		asm volatile ("csrr t0, hpmcounter16h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER17H:
		asm volatile ("csrr t0, hpmcounter17h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER18H:
		asm volatile ("csrr t0, hpmcounter18h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER19H:
		asm volatile ("csrr t0, hpmcounter19h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER20H:
		asm volatile ("csrr t0, hpmcounter20h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER21H:
		asm volatile ("csrr t0, hpmcounter21h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER22H:
		asm volatile ("csrr t0, hpmcounter22h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER23H:
		asm volatile ("csrr t0, hpmcounter23h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER24H:
		asm volatile ("csrr t0, hpmcounter24h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER25H:
		asm volatile ("csrr t0, hpmcounter25h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER26H:
		asm volatile ("csrr t0, hpmcounter26h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER27H:
		asm volatile ("csrr t0, hpmcounter27h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER28H:
		asm volatile ("csrr t0, hpmcounter28h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER29H:
		asm volatile ("csrr t0, hpmcounter29h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER30H:
		asm volatile ("csrr t0, hpmcounter30h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_HPMCOUNTER31H:
		asm volatile ("csrr t0, hpmcounter31h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SSTATUS:
		asm volatile ("csrr t0, sstatus\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SEDELEG:
		asm volatile ("csrr t0, sedeleg\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SIDELEG:
		asm volatile ("csrr t0, sideleg\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SIE:
		asm volatile ("csrr t0, sie\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_STVEC:
		asm volatile ("csrr t0, stvec\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SCOUNTEREN:
		asm volatile ("csrr t0, scounteren\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SSCRATCH:
		asm volatile ("csrr t0, sscratch\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SEPC:
		asm volatile ("csrr t0, sepc\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SCAUSE:
		asm volatile ("csrr t0, scause\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_STVAL:
		// TODO: figure out why it doesn't like this
		// asm volatile ("csrr t0, stval\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SIP:
		asm volatile ("csrr t0, sip\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_SATP:
		asm volatile ("csrr t0, satp\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MVENDORID:
		asm volatile ("csrr t0, mvendorid\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MARCHID:
		asm volatile ("csrr t0, marchid\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MIMPID:
		asm volatile ("csrr t0, mimpid\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHARTID:
		asm volatile ("csrr t0, mhartid\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MSTATUS:
		asm volatile ("csrr t0, mstatus\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MISA:
		asm volatile ("csrr t0, misa\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MEDELEG:
		asm volatile ("csrr t0, medeleg\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MIDELEG:
		asm volatile ("csrr t0, mideleg\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MIE:
		asm volatile ("csrr t0, mie\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MTVEC:
		asm volatile ("csrr t0, mtvec\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MCOUNTEREN:
		asm volatile ("csrr t0, mcounteren\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MSCRATCH:
		asm volatile ("csrr t0, mscratch\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MEPC:
		asm volatile ("csrr t0, mepc\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MCAUSE:
		asm volatile ("csrr t0, mcause\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MTVAL:
		// TODO: figure out why it doesn't like this
		//asm volatile ("csrr t0, mtval\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MIP:
		asm volatile ("csrr t0, mip\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPCFG0:
		asm volatile ("csrr t0, pmpcfg0\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPCFG1:
		asm volatile ("csrr t0, pmpcfg1\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPCFG2:
		asm volatile ("csrr t0, pmpcfg2\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPCFG3:
		asm volatile ("csrr t0, pmpcfg3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR0:
		asm volatile ("csrr t0, pmpaddr0\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR1:
		asm volatile ("csrr t0, pmpaddr1\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR2:
		asm volatile ("csrr t0, pmpaddr2\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR3:
		asm volatile ("csrr t0, pmpaddr3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR4:
		asm volatile ("csrr t0, pmpaddr4\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR5:
		asm volatile ("csrr t0, pmpaddr5\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR6:
		asm volatile ("csrr t0, pmpaddr6\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR7:
		asm volatile ("csrr t0, pmpaddr7\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR8:
		asm volatile ("csrr t0, pmpaddr8\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR9:
		asm volatile ("csrr t0, pmpaddr9\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR10:
		asm volatile ("csrr t0, pmpaddr10\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR11:
		asm volatile ("csrr t0, pmpaddr11\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR12:
		asm volatile ("csrr t0, pmpaddr12\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR13:
		asm volatile ("csrr t0, pmpaddr13\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR14:
		asm volatile ("csrr t0, pmpaddr14\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_PMPADDR15:
		asm volatile ("csrr t0, pmpaddr15\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MCYCLE:
		asm volatile ("csrr t0, mcycle\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MINSTRET:
		asm volatile ("csrr t0, minstret\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER3:
		asm volatile ("csrr t0, mhpmcounter3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER4:
		asm volatile ("csrr t0, mhpmcounter4\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER5:
		asm volatile ("csrr t0, mhpmcounter5\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER6:
		asm volatile ("csrr t0, mhpmcounter6\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER7:
		asm volatile ("csrr t0, mhpmcounter7\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER8:
		asm volatile ("csrr t0, mhpmcounter8\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER9:
		asm volatile ("csrr t0, mhpmcounter9\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER10:
		asm volatile ("csrr t0, mhpmcounter10\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER11:
		asm volatile ("csrr t0, mhpmcounter11\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER12:
		asm volatile ("csrr t0, mhpmcounter12\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER13:
		asm volatile ("csrr t0, mhpmcounter13\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER14:
		asm volatile ("csrr t0, mhpmcounter14\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER15:
		asm volatile ("csrr t0, mhpmcounter15\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER16:
		asm volatile ("csrr t0, mhpmcounter16\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER17:
		asm volatile ("csrr t0, mhpmcounter17\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER18:
		asm volatile ("csrr t0, mhpmcounter18\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER19:
		asm volatile ("csrr t0, mhpmcounter19\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER20:
		asm volatile ("csrr t0, mhpmcounter20\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER21:
		asm volatile ("csrr t0, mhpmcounter21\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER22:
		asm volatile ("csrr t0, mhpmcounter22\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER23:
		asm volatile ("csrr t0, mhpmcounter23\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER24:
		asm volatile ("csrr t0, mhpmcounter24\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER25:
		asm volatile ("csrr t0, mhpmcounter25\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER26:
		asm volatile ("csrr t0, mhpmcounter26\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER27:
		asm volatile ("csrr t0, mhpmcounter27\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER28:
		asm volatile ("csrr t0, mhpmcounter28\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER29:
		asm volatile ("csrr t0, mhpmcounter29\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER30:
		asm volatile ("csrr t0, mhpmcounter30\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER31:
		asm volatile ("csrr t0, mhpmcounter31\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MCYCLEH:
		asm volatile ("csrr t0, mcycleh\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MINSTRETH:
		asm volatile ("csrr t0, minstreth\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER3H:
		asm volatile ("csrr t0, mhpmcounter3h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER4H:
		asm volatile ("csrr t0, mhpmcounter4h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER5H:
		asm volatile ("csrr t0, mhpmcounter5h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER6H:
		asm volatile ("csrr t0, mhpmcounter6h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER7H:
		asm volatile ("csrr t0, mhpmcounter7h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER8H:
		asm volatile ("csrr t0, mhpmcounter8h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER9H:
		asm volatile ("csrr t0, mhpmcounter9h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER10H:
		asm volatile ("csrr t0, mhpmcounter10h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER11H:
		asm volatile ("csrr t0, mhpmcounter11h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER12H:
		asm volatile ("csrr t0, mhpmcounter12h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER13H:
		asm volatile ("csrr t0, mhpmcounter13h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER14H:
		asm volatile ("csrr t0, mhpmcounter14h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER15H:
		asm volatile ("csrr t0, mhpmcounter15h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER16H:
		asm volatile ("csrr t0, mhpmcounter16h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER17H:
		asm volatile ("csrr t0, mhpmcounter17h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER18H:
		asm volatile ("csrr t0, mhpmcounter18h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER19H:
		asm volatile ("csrr t0, mhpmcounter19h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER20H:
		asm volatile ("csrr t0, mhpmcounter20h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER21H:
		asm volatile ("csrr t0, mhpmcounter21h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER22H:
		asm volatile ("csrr t0, mhpmcounter22h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER23H:
		asm volatile ("csrr t0, mhpmcounter23h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER24H:
		asm volatile ("csrr t0, mhpmcounter24h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER25H:
		asm volatile ("csrr t0, mhpmcounter25h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER26H:
		asm volatile ("csrr t0, mhpmcounter26h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER27H:
		asm volatile ("csrr t0, mhpmcounter27h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER28H:
		asm volatile ("csrr t0, mhpmcounter28h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER29H:
		asm volatile ("csrr t0, mhpmcounter29h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER30H:
		asm volatile ("csrr t0, mhpmcounter30h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMCOUNTER31H:
		asm volatile ("csrr t0, mhpmcounter31h\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT3:
		asm volatile ("csrr t0, mhpmevent3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT4:
		asm volatile ("csrr t0, mhpmevent4\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT5:
		asm volatile ("csrr t0, mhpmevent5\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT6:
		asm volatile ("csrr t0, mhpmevent6\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT7:
		asm volatile ("csrr t0, mhpmevent7\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT8:
		asm volatile ("csrr t0, mhpmevent8\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT9:
		asm volatile ("csrr t0, mhpmevent9\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT10:
		asm volatile ("csrr t0, mhpmevent10\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT11:
		asm volatile ("csrr t0, mhpmevent11\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT12:
		asm volatile ("csrr t0, mhpmevent12\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT13:
		asm volatile ("csrr t0, mhpmevent13\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT14:
		asm volatile ("csrr t0, mhpmevent14\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT15:
		asm volatile ("csrr t0, mhpmevent15\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT16:
		asm volatile ("csrr t0, mhpmevent16\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT17:
		asm volatile ("csrr t0, mhpmevent17\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT18:
		asm volatile ("csrr t0, mhpmevent18\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT19:
		asm volatile ("csrr t0, mhpmevent19\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT20:
		asm volatile ("csrr t0, mhpmevent20\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT21:
		asm volatile ("csrr t0, mhpmevent21\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT22:
		asm volatile ("csrr t0, mhpmevent22\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT23:
		asm volatile ("csrr t0, mhpmevent23\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT24:
		asm volatile ("csrr t0, mhpmevent24\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT25:
		asm volatile ("csrr t0, mhpmevent25\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT26:
		asm volatile ("csrr t0, mhpmevent26\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT27:
		asm volatile ("csrr t0, mhpmevent27\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT28:
		asm volatile ("csrr t0, mhpmevent28\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT29:
		asm volatile ("csrr t0, mhpmevent29\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT30:
		asm volatile ("csrr t0, mhpmevent30\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_MHPMEVENT31:
		asm volatile ("csrr t0, mhpmevent31\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TSELECT:
		asm volatile ("csrr t0, tselect\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TDATA1:
		asm volatile ("csrr t0, tdata1\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TDATA2:
		asm volatile ("csrr t0, tdata2\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_TDATA3:
		asm volatile ("csrr t0, tdata3\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_DCSR:
		asm volatile ("csrr t0, dcsr\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_DPC:
		asm volatile ("csrr t0, dpc\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	case CSR_DSCRATCH:
		asm volatile ("csrr t0, dscratch\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
		break;
	}
}

#endif /* SRC_ARCH_RISCV32_CSR_H_ */
