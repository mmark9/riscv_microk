#include "csr.h"

// FIXME: attempts to read or modify xtval, xcause registers causes compiler to complain:
// Error: Instruction csxx requires absolute expression
void riscv_set_csr_bits(unsigned short csr_id, unsigned int value) {
	switch(csr_id) {
	case CSR_USTATUS:
		asm volatile ("csrs ustatus, %0" : : "r" (value) : );
		break;
	case CSR_UIE:
		asm volatile ("csrs uie, %0" : : "r" (value) : );
		break;
	case CSR_UTVEC:
		asm volatile ("csrs utvec, %0" : : "r" (value) : );
		break;
	case CSR_USCRATCH:
		asm volatile ("csrs uscratch, %0" : : "r" (value) : );
		break;
	case CSR_UEPC:
		asm volatile ("csrs uepc, %0" : : "r" (value) : );
		break;
	case CSR_UCAUSE:
		asm volatile ("csrs ucause, %0" : : "r" (value) : );
		break;
	case CSR_UTVAL:
		asm volatile ("csrs utval, %0" : : "r" (value) : );
		break;
	case CSR_UIP:
		asm volatile ("csrs uip, %0" : : "r" (value) : );
		break;
	case CSR_FFLAGS:
		asm volatile ("csrs fflags, %0" : : "r" (value) : );
		break;
	case CSR_FRM:
		asm volatile ("csrs frm, %0" : : "r" (value) : );
		break;
	case CSR_FCSR:
		asm volatile ("csrs fcsr, %0" : : "r" (value) : );
		break;
	case CSR_CYCLE:
		asm volatile ("csrs cycle, %0" : : "r" (value) : );
		break;
	case CSR_TIME:
		asm volatile ("csrs time, %0" : : "r" (value) : );
		break;
	case CSR_INSTRET:
		asm volatile ("csrs instret, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3:
		asm volatile ("csrs hpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4:
		asm volatile ("csrs hpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5:
		asm volatile ("csrs hpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6:
		asm volatile ("csrs hpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7:
		asm volatile ("csrs hpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8:
		asm volatile ("csrs hpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9:
		asm volatile ("csrs hpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10:
		asm volatile ("csrs hpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11:
		asm volatile ("csrs hpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12:
		asm volatile ("csrs hpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13:
		asm volatile ("csrs hpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14:
		asm volatile ("csrs hpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15:
		asm volatile ("csrs hpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16:
		asm volatile ("csrs hpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17:
		asm volatile ("csrs hpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18:
		asm volatile ("csrs hpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19:
		asm volatile ("csrs hpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20:
		asm volatile ("csrs hpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21:
		asm volatile ("csrs hpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22:
		asm volatile ("csrs hpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23:
		asm volatile ("csrs hpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24:
		asm volatile ("csrs hpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25:
		asm volatile ("csrs hpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26:
		asm volatile ("csrs hpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27:
		asm volatile ("csrs hpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28:
		asm volatile ("csrs hpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29:
		asm volatile ("csrs hpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30:
		asm volatile ("csrs hpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31:
		asm volatile ("csrs hpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_CYCLEH:
		asm volatile ("csrs cycleh, %0" : : "r" (value) : );
		break;
	case CSR_TIMEH:
		asm volatile ("csrs timeh, %0" : : "r" (value) : );
		break;
	case CSR_INSTRETH:
		asm volatile ("csrs instreth, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3H:
		asm volatile ("csrs hpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4H:
		asm volatile ("csrs hpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5H:
		asm volatile ("csrs hpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6H:
		asm volatile ("csrs hpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7H:
		asm volatile ("csrs hpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8H:
		asm volatile ("csrs hpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9H:
		asm volatile ("csrs hpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10H:
		asm volatile ("csrs hpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11H:
		asm volatile ("csrs hpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12H:
		asm volatile ("csrs hpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13H:
		asm volatile ("csrs hpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14H:
		asm volatile ("csrs hpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15H:
		asm volatile ("csrs hpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16H:
		asm volatile ("csrs hpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17H:
		asm volatile ("csrs hpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18H:
		asm volatile ("csrs hpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19H:
		asm volatile ("csrs hpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20H:
		asm volatile ("csrs hpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21H:
		asm volatile ("csrs hpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22H:
		asm volatile ("csrs hpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23H:
		asm volatile ("csrs hpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24H:
		asm volatile ("csrs hpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25H:
		asm volatile ("csrs hpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26H:
		asm volatile ("csrs hpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27H:
		asm volatile ("csrs hpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28H:
		asm volatile ("csrs hpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29H:
		asm volatile ("csrs hpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30H:
		asm volatile ("csrs hpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31H:
		asm volatile ("csrs hpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_SSTATUS:
		asm volatile ("csrs sstatus, %0" : : "r" (value) : );
		break;
	case CSR_SEDELEG:
		asm volatile ("csrs sedeleg, %0" : : "r" (value) : );
		break;
	case CSR_SIDELEG:
		asm volatile ("csrs sideleg, %0" : : "r" (value) : );
		break;
	case CSR_SIE:
		asm volatile ("csrs sie, %0" : : "r" (value) : );
		break;
	case CSR_STVEC:
		asm volatile ("csrs stvec, %0" : : "r" (value) : );
		break;
	case CSR_SCOUNTEREN:
		asm volatile ("csrs scounteren, %0" : : "r" (value) : );
		break;
	case CSR_SSCRATCH:
		asm volatile ("csrs sscratch, %0" : : "r" (value) : );
		break;
	case CSR_SEPC:
		asm volatile ("csrs sepc, %0" : : "r" (value) : );
		break;
	case CSR_SCAUSE:
		//asm volatile ("csrs scause, %0" : : "r" (value) : );
		break;
	case CSR_STVAL:
		//asm volatile ("csrs stval, %0" : : "r" (value) : );
		break;
	case CSR_SIP:
		asm volatile ("csrs sip, %0" : : "r" (value) : );
		break;
	case CSR_SATP:
		asm volatile ("csrs satp, %0" : : "r" (value) : );
		break;
	case CSR_MVENDORID:
		asm volatile ("csrs mvendorid, %0" : : "r" (value) : );
		break;
	case CSR_MARCHID:
		asm volatile ("csrs marchid, %0" : : "r" (value) : );
		break;
	case CSR_MIMPID:
		asm volatile ("csrs mimpid, %0" : : "r" (value) : );
		break;
	case CSR_MHARTID:
		asm volatile ("csrs mhartid, %0" : : "r" (value) : );
		break;
	case CSR_MSTATUS:
		asm volatile ("csrs mstatus, %0" : : "r" (value) : );
		break;
	case CSR_MISA:
		asm volatile ("csrs misa, %0" : : "r" (value) : );
		break;
	case CSR_MEDELEG:
		asm volatile ("csrs medeleg, %0" : : "r" (value) : );
		break;
	case CSR_MIDELEG:
		asm volatile ("csrs mideleg, %0" : : "r" (value) : );
		break;
	case CSR_MIE:
		asm volatile ("csrs mie, %0" : : "r" (value) : );
		break;
	case CSR_MTVEC:
		asm volatile ("csrs mtvec, %0" : : "r" (value) : );
		break;
	case CSR_MCOUNTEREN:
		asm volatile ("csrs mcounteren, %0" : : "r" (value) : );
		break;
	case CSR_MSCRATCH:
		asm volatile ("csrs mscratch, %0" : : "r" (value) : );
		break;
	case CSR_MEPC:
		asm volatile ("csrs mepc, %0" : : "r" (value) : );
		break;
	case CSR_MCAUSE:
		//asm volatile ("csrs mcause, t0" : : "r" (value) : );
		break;
	case CSR_MTVAL:
		//asm volatile ("csrs mtval, %0" : : "r" (value) : );
		break;
	case CSR_MIP:
		asm volatile ("csrs mip, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG0:
		asm volatile ("csrs pmpcfg0, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG1:
		asm volatile ("csrs pmpcfg1, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG2:
		asm volatile ("csrs pmpcfg2, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG3:
		asm volatile ("csrs pmpcfg3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR0:
		asm volatile ("csrs pmpaddr0, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR1:
		asm volatile ("csrs pmpaddr1, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR2:
		asm volatile ("csrs pmpaddr2, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR3:
		asm volatile ("csrs pmpaddr3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR4:
		asm volatile ("csrs pmpaddr4, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR5:
		asm volatile ("csrs pmpaddr5, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR6:
		asm volatile ("csrs pmpaddr6, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR7:
		asm volatile ("csrs pmpaddr7, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR8:
		asm volatile ("csrs pmpaddr8, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR9:
		asm volatile ("csrs pmpaddr9, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR10:
		asm volatile ("csrs pmpaddr10, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR11:
		asm volatile ("csrs pmpaddr11, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR12:
		asm volatile ("csrs pmpaddr12, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR13:
		asm volatile ("csrs pmpaddr13, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR14:
		asm volatile ("csrs pmpaddr14, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR15:
		asm volatile ("csrs pmpaddr15, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLE:
		asm volatile ("csrs mcycle, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRET:
		asm volatile ("csrs minstret, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3:
		asm volatile ("csrs mhpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4:
		asm volatile ("csrs mhpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5:
		asm volatile ("csrs mhpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6:
		asm volatile ("csrs mhpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7:
		asm volatile ("csrs mhpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8:
		asm volatile ("csrs mhpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9:
		asm volatile ("csrs mhpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10:
		asm volatile ("csrs mhpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11:
		asm volatile ("csrs mhpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12:
		asm volatile ("csrs mhpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13:
		asm volatile ("csrs mhpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14:
		asm volatile ("csrs mhpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15:
		asm volatile ("csrs mhpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16:
		asm volatile ("csrs mhpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17:
		asm volatile ("csrs mhpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18:
		asm volatile ("csrs mhpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19:
		asm volatile ("csrs mhpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20:
		asm volatile ("csrs mhpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21:
		asm volatile ("csrs mhpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22:
		asm volatile ("csrs mhpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23:
		asm volatile ("csrs mhpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24:
		asm volatile ("csrs mhpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25:
		asm volatile ("csrs mhpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26:
		asm volatile ("csrs mhpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27:
		asm volatile ("csrs mhpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28:
		asm volatile ("csrs mhpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29:
		asm volatile ("csrs mhpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30:
		asm volatile ("csrs mhpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31:
		asm volatile ("csrs mhpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLEH:
		asm volatile ("csrs mcycleh, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRETH:
		asm volatile ("csrs minstreth, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3H:
		asm volatile ("csrs mhpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4H:
		asm volatile ("csrs mhpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5H:
		asm volatile ("csrs mhpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6H:
		asm volatile ("csrs mhpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7H:
		asm volatile ("csrs mhpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8H:
		asm volatile ("csrs mhpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9H:
		asm volatile ("csrs mhpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10H:
		asm volatile ("csrs mhpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11H:
		asm volatile ("csrs mhpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12H:
		asm volatile ("csrs mhpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13H:
		asm volatile ("csrs mhpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14H:
		asm volatile ("csrs mhpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15H:
		asm volatile ("csrs mhpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16H:
		asm volatile ("csrs mhpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17H:
		asm volatile ("csrs mhpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18H:
		asm volatile ("csrs mhpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19H:
		asm volatile ("csrs mhpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20H:
		asm volatile ("csrs mhpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21H:
		asm volatile ("csrs mhpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22H:
		asm volatile ("csrs mhpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23H:
		asm volatile ("csrs mhpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24H:
		asm volatile ("csrs mhpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25H:
		asm volatile ("csrs mhpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26H:
		asm volatile ("csrs mhpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27H:
		asm volatile ("csrs mhpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28H:
		asm volatile ("csrs mhpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29H:
		asm volatile ("csrs mhpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30H:
		asm volatile ("csrs mhpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31H:
		asm volatile ("csrs mhpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT3:
		asm volatile ("csrs mhpmevent3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT4:
		asm volatile ("csrs mhpmevent4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT5:
		asm volatile ("csrs mhpmevent5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT6:
		asm volatile ("csrs mhpmevent6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT7:
		asm volatile ("csrs mhpmevent7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT8:
		asm volatile ("csrs mhpmevent8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT9:
		asm volatile ("csrs mhpmevent9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT10:
		asm volatile ("csrs mhpmevent10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT11:
		asm volatile ("csrs mhpmevent11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT12:
		asm volatile ("csrs mhpmevent12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT13:
		asm volatile ("csrs mhpmevent13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT14:
		asm volatile ("csrs mhpmevent14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT15:
		asm volatile ("csrs mhpmevent15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT16:
		asm volatile ("csrs mhpmevent16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT17:
		asm volatile ("csrs mhpmevent17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT18:
		asm volatile ("csrs mhpmevent18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT19:
		asm volatile ("csrs mhpmevent19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT20:
		asm volatile ("csrs mhpmevent20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT21:
		asm volatile ("csrs mhpmevent21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT22:
		asm volatile ("csrs mhpmevent22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT23:
		asm volatile ("csrs mhpmevent23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT24:
		asm volatile ("csrs mhpmevent24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT25:
		asm volatile ("csrs mhpmevent25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT26:
		asm volatile ("csrs mhpmevent26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT27:
		asm volatile ("csrs mhpmevent27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT28:
		asm volatile ("csrs mhpmevent28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT29:
		asm volatile ("csrs mhpmevent29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT30:
		asm volatile ("csrs mhpmevent30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT31:
		asm volatile ("csrs mhpmevent31, %0" : : "r" (value) : );
		break;
	case CSR_TSELECT:
		asm volatile ("csrs tselect, %0" : : "r" (value) : );
		break;
	case CSR_TDATA1:
		asm volatile ("csrs tdata1, %0" : : "r" (value) : );
		break;
	case CSR_TDATA2:
		asm volatile ("csrs tdata2, %0" : : "r" (value) : );
		break;
	case CSR_TDATA3:
		asm volatile ("csrs tdata3, %0" : : "r" (value) : );
		break;
	case CSR_DCSR:
		asm volatile ("csrs dcsr, %0" : : "r" (value) : );
		break;
	case CSR_DPC:
		asm volatile ("csrs dpc, %0" : : "r" (value) : );
		break;
	case CSR_DSCRATCH:
		asm volatile ("csrs dscratch, %0" : : "r" (value) : );
		break;
	default:
		break;
	}
}

void riscv_clear_csr_bits(unsigned short csr_id, unsigned int value) {
	switch(csr_id) {
	case CSR_USTATUS:
		asm volatile ("csrc ustatus, %0" : : "r" (value) : );
		break;
	case CSR_UIE:
		asm volatile ("csrc uie, %0" : : "r" (value) : );
		break;
	case CSR_UTVEC:
		asm volatile ("csrc utvec, %0" : : "r" (value) : );
		break;
	case CSR_USCRATCH:
		asm volatile ("csrc uscratch, %0" : : "r" (value) : );
		break;
	case CSR_UEPC:
		asm volatile ("csrc uepc, %0" : : "r" (value) : );
		break;
	case CSR_UCAUSE:
		asm volatile ("csrc ucause, %0" : : "r" (value) : );
		break;
	case CSR_UTVAL:
		asm volatile ("csrc utval, %0" : : "r" (value) : );
		break;
	case CSR_UIP:
		asm volatile ("csrc uip, %0" : : "r" (value) : );
		break;
	case CSR_FFLAGS:
		asm volatile ("csrc fflags, %0" : : "r" (value) : );
		break;
	case CSR_FRM:
		asm volatile ("csrc frm, %0" : : "r" (value) : );
		break;
	case CSR_FCSR:
		asm volatile ("csrc fcsr, %0" : : "r" (value) : );
		break;
	case CSR_CYCLE:
		asm volatile ("csrc cycle, %0" : : "r" (value) : );
		break;
	case CSR_TIME:
		asm volatile ("csrc time, %0" : : "r" (value) : );
		break;
	case CSR_INSTRET:
		asm volatile ("csrc instret, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3:
		asm volatile ("csrc hpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4:
		asm volatile ("csrc hpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5:
		asm volatile ("csrc hpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6:
		asm volatile ("csrc hpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7:
		asm volatile ("csrc hpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8:
		asm volatile ("csrc hpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9:
		asm volatile ("csrc hpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10:
		asm volatile ("csrc hpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11:
		asm volatile ("csrc hpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12:
		asm volatile ("csrc hpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13:
		asm volatile ("csrc hpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14:
		asm volatile ("csrc hpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15:
		asm volatile ("csrc hpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16:
		asm volatile ("csrc hpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17:
		asm volatile ("csrc hpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18:
		asm volatile ("csrc hpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19:
		asm volatile ("csrc hpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20:
		asm volatile ("csrc hpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21:
		asm volatile ("csrc hpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22:
		asm volatile ("csrc hpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23:
		asm volatile ("csrc hpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24:
		asm volatile ("csrc hpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25:
		asm volatile ("csrc hpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26:
		asm volatile ("csrc hpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27:
		asm volatile ("csrc hpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28:
		asm volatile ("csrc hpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29:
		asm volatile ("csrc hpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30:
		asm volatile ("csrc hpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31:
		asm volatile ("csrc hpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_CYCLEH:
		asm volatile ("csrc cycleh, %0" : : "r" (value) : );
		break;
	case CSR_TIMEH:
		asm volatile ("csrc timeh, %0" : : "r" (value) : );
		break;
	case CSR_INSTRETH:
		asm volatile ("csrc instreth, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3H:
		asm volatile ("csrc hpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4H:
		asm volatile ("csrc hpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5H:
		asm volatile ("csrc hpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6H:
		asm volatile ("csrc hpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7H:
		asm volatile ("csrc hpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8H:
		asm volatile ("csrc hpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9H:
		asm volatile ("csrc hpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10H:
		asm volatile ("csrc hpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11H:
		asm volatile ("csrc hpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12H:
		asm volatile ("csrc hpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13H:
		asm volatile ("csrc hpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14H:
		asm volatile ("csrc hpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15H:
		asm volatile ("csrc hpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16H:
		asm volatile ("csrc hpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17H:
		asm volatile ("csrc hpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18H:
		asm volatile ("csrc hpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19H:
		asm volatile ("csrc hpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20H:
		asm volatile ("csrc hpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21H:
		asm volatile ("csrc hpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22H:
		asm volatile ("csrc hpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23H:
		asm volatile ("csrc hpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24H:
		asm volatile ("csrc hpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25H:
		asm volatile ("csrc hpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26H:
		asm volatile ("csrc hpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27H:
		asm volatile ("csrc hpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28H:
		asm volatile ("csrc hpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29H:
		asm volatile ("csrc hpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30H:
		asm volatile ("csrc hpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31H:
		asm volatile ("csrc hpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_SSTATUS:
		asm volatile ("csrc sstatus, %0" : : "r" (value) : );
		break;
	case CSR_SEDELEG:
		asm volatile ("csrc sedeleg, %0" : : "r" (value) : );
		break;
	case CSR_SIDELEG:
		asm volatile ("csrc sideleg, %0" : : "r" (value) : );
		break;
	case CSR_SIE:
		asm volatile ("csrc sie, %0" : : "r" (value) : );
		break;
	case CSR_STVEC:
		asm volatile ("csrc stvec, %0" : : "r" (value) : );
		break;
	case CSR_SCOUNTEREN:
		asm volatile ("csrc scounteren, %0" : : "r" (value) : );
		break;
	case CSR_SSCRATCH:
		asm volatile ("csrc sscratch, %0" : : "r" (value) : );
		break;
	case CSR_SEPC:
		asm volatile ("csrc sepc, %0" : : "r" (value) : );
		break;
	case CSR_SCAUSE:
		asm volatile ("csrc scause, %0" : : "r" (value) : );
		break;
	case CSR_STVAL:
		//asm volatile ("csrc stval, %0" : : "r" (value) : );
		break;
	case CSR_SIP:
		asm volatile ("csrc sip, %0" : : "r" (value) : );
		break;
	case CSR_SATP:
		asm volatile ("csrc satp, %0" : : "r" (value) : );
		break;
	case CSR_MVENDORID:
		asm volatile ("csrc mvendorid, %0" : : "r" (value) : );
		break;
	case CSR_MARCHID:
		asm volatile ("csrc marchid, %0" : : "r" (value) : );
		break;
	case CSR_MIMPID:
		asm volatile ("csrc mimpid, %0" : : "r" (value) : );
		break;
	case CSR_MHARTID:
		asm volatile ("csrc mhartid, %0" : : "r" (value) : );
		break;
	case CSR_MSTATUS:
		asm volatile ("csrc mstatus, %0" : : "r" (value) : );
		break;
	case CSR_MISA:
		asm volatile ("csrc misa, %0" : : "r" (value) : );
		break;
	case CSR_MEDELEG:
		asm volatile ("csrc medeleg, %0" : : "r" (value) : );
		break;
	case CSR_MIDELEG:
		asm volatile ("csrc mideleg, %0" : : "r" (value) : );
		break;
	case CSR_MIE:
		asm volatile ("csrc mie, %0" : : "r" (value) : );
		break;
	case CSR_MTVEC:
		asm volatile ("csrc mtvec, %0" : : "r" (value) : );
		break;
	case CSR_MCOUNTEREN:
		asm volatile ("csrc mcounteren, %0" : : "r" (value) : );
		break;
	case CSR_MSCRATCH:
		asm volatile ("csrc mscratch, %0" : : "r" (value) : );
		break;
	case CSR_MEPC:
		asm volatile ("csrc mepc, %0" : : "r" (value) : );
		break;
	case CSR_MCAUSE:
		asm volatile ("csrc mcause, %0" : : "r" (value) : );
		break;
	case CSR_MTVAL:
		//asm volatile ("csrc mtval, %0" : : "r" (value) : );
		break;
	case CSR_MIP:
		asm volatile ("csrc mip, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG0:
		asm volatile ("csrc pmpcfg0, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG1:
		asm volatile ("csrc pmpcfg1, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG2:
		asm volatile ("csrc pmpcfg2, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG3:
		asm volatile ("csrc pmpcfg3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR0:
		asm volatile ("csrc pmpaddr0, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR1:
		asm volatile ("csrc pmpaddr1, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR2:
		asm volatile ("csrc pmpaddr2, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR3:
		asm volatile ("csrc pmpaddr3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR4:
		asm volatile ("csrc pmpaddr4, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR5:
		asm volatile ("csrc pmpaddr5, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR6:
		asm volatile ("csrc pmpaddr6, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR7:
		asm volatile ("csrc pmpaddr7, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR8:
		asm volatile ("csrc pmpaddr8, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR9:
		asm volatile ("csrc pmpaddr9, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR10:
		asm volatile ("csrc pmpaddr10, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR11:
		asm volatile ("csrc pmpaddr11, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR12:
		asm volatile ("csrc pmpaddr12, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR13:
		asm volatile ("csrc pmpaddr13, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR14:
		asm volatile ("csrc pmpaddr14, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR15:
		asm volatile ("csrc pmpaddr15, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLE:
		asm volatile ("csrc mcycle, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRET:
		asm volatile ("csrc minstret, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3:
		asm volatile ("csrc mhpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4:
		asm volatile ("csrc mhpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5:
		asm volatile ("csrc mhpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6:
		asm volatile ("csrc mhpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7:
		asm volatile ("csrc mhpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8:
		asm volatile ("csrc mhpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9:
		asm volatile ("csrc mhpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10:
		asm volatile ("csrc mhpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11:
		asm volatile ("csrc mhpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12:
		asm volatile ("csrc mhpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13:
		asm volatile ("csrc mhpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14:
		asm volatile ("csrc mhpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15:
		asm volatile ("csrc mhpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16:
		asm volatile ("csrc mhpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17:
		asm volatile ("csrc mhpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18:
		asm volatile ("csrc mhpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19:
		asm volatile ("csrc mhpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20:
		asm volatile ("csrc mhpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21:
		asm volatile ("csrc mhpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22:
		asm volatile ("csrc mhpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23:
		asm volatile ("csrc mhpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24:
		asm volatile ("csrc mhpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25:
		asm volatile ("csrc mhpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26:
		asm volatile ("csrc mhpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27:
		asm volatile ("csrc mhpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28:
		asm volatile ("csrc mhpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29:
		asm volatile ("csrc mhpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30:
		asm volatile ("csrc mhpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31:
		asm volatile ("csrc mhpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLEH:
		asm volatile ("csrc mcycleh, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRETH:
		asm volatile ("csrc minstreth, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3H:
		asm volatile ("csrc mhpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4H:
		asm volatile ("csrc mhpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5H:
		asm volatile ("csrc mhpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6H:
		asm volatile ("csrc mhpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7H:
		asm volatile ("csrc mhpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8H:
		asm volatile ("csrc mhpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9H:
		asm volatile ("csrc mhpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10H:
		asm volatile ("csrc mhpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11H:
		asm volatile ("csrc mhpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12H:
		asm volatile ("csrc mhpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13H:
		asm volatile ("csrc mhpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14H:
		asm volatile ("csrc mhpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15H:
		asm volatile ("csrc mhpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16H:
		asm volatile ("csrc mhpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17H:
		asm volatile ("csrc mhpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18H:
		asm volatile ("csrc mhpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19H:
		asm volatile ("csrc mhpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20H:
		asm volatile ("csrc mhpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21H:
		asm volatile ("csrc mhpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22H:
		asm volatile ("csrc mhpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23H:
		asm volatile ("csrc mhpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24H:
		asm volatile ("csrc mhpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25H:
		asm volatile ("csrc mhpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26H:
		asm volatile ("csrc mhpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27H:
		asm volatile ("csrc mhpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28H:
		asm volatile ("csrc mhpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29H:
		asm volatile ("csrc mhpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30H:
		asm volatile ("csrc mhpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31H:
		asm volatile ("csrc mhpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT3:
		asm volatile ("csrc mhpmevent3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT4:
		asm volatile ("csrc mhpmevent4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT5:
		asm volatile ("csrc mhpmevent5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT6:
		asm volatile ("csrc mhpmevent6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT7:
		asm volatile ("csrc mhpmevent7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT8:
		asm volatile ("csrc mhpmevent8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT9:
		asm volatile ("csrc mhpmevent9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT10:
		asm volatile ("csrc mhpmevent10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT11:
		asm volatile ("csrc mhpmevent11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT12:
		asm volatile ("csrc mhpmevent12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT13:
		asm volatile ("csrc mhpmevent13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT14:
		asm volatile ("csrc mhpmevent14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT15:
		asm volatile ("csrc mhpmevent15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT16:
		asm volatile ("csrc mhpmevent16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT17:
		asm volatile ("csrc mhpmevent17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT18:
		asm volatile ("csrc mhpmevent18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT19:
		asm volatile ("csrc mhpmevent19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT20:
		asm volatile ("csrc mhpmevent20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT21:
		asm volatile ("csrc mhpmevent21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT22:
		asm volatile ("csrc mhpmevent22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT23:
		asm volatile ("csrc mhpmevent23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT24:
		asm volatile ("csrc mhpmevent24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT25:
		asm volatile ("csrc mhpmevent25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT26:
		asm volatile ("csrc mhpmevent26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT27:
		asm volatile ("csrc mhpmevent27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT28:
		asm volatile ("csrc mhpmevent28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT29:
		asm volatile ("csrc mhpmevent29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT30:
		asm volatile ("csrc mhpmevent30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT31:
		asm volatile ("csrc mhpmevent31, %0" : : "r" (value) : );
		break;
	case CSR_TSELECT:
		asm volatile ("csrc tselect, %0" : : "r" (value) : );
		break;
	case CSR_TDATA1:
		asm volatile ("csrc tdata1, %0" : : "r" (value) : );
		break;
	case CSR_TDATA2:
		asm volatile ("csrc tdata2, %0" : : "r" (value) : );
		break;
	case CSR_TDATA3:
		asm volatile ("csrc tdata3, %0" : : "r" (value) : );
		break;
	case CSR_DCSR:
		asm volatile ("csrc dcsr, %0" : : "r" (value) : );
		break;
	case CSR_DPC:
		asm volatile ("csrc dpc, %0" : : "r" (value) : );
		break;
	case CSR_DSCRATCH:
		asm volatile ("csrc dscratch, %0" : : "r" (value) : );
		break;
	default:
		break;
	}
}

void riscv_write_csr(unsigned short csr_id, unsigned int value) {
	switch(csr_id) {
	case CSR_USTATUS:
		asm volatile ("csrw ustatus, %0" : : "r" (value) : );
		break;
	case CSR_UIE:
		asm volatile ("csrw uie, %0" : : "r" (value) : );
		break;
	case CSR_UTVEC:
		asm volatile ("csrw utvec, %0" : : "r" (value) : );
		break;
	case CSR_USCRATCH:
		asm volatile ("csrw uscratch, %0" : : "r" (value) : );
		break;
	case CSR_UEPC:
		asm volatile ("csrw uepc, %0" : : "r" (value) : );
		break;
	case CSR_UCAUSE:
		asm volatile ("csrw ucause, %0" : : "r" (value) : );
		break;
	case CSR_UTVAL:
		asm volatile ("csrw utval, %0" : : "r" (value) : );
		break;
	case CSR_UIP:
		asm volatile ("csrw uip, %0" : : "r" (value) : );
		break;
	case CSR_FFLAGS:
		asm volatile ("csrw fflags, %0" : : "r" (value) : );
		break;
	case CSR_FRM:
		asm volatile ("csrw frm, %0" : : "r" (value) : );
		break;
	case CSR_FCSR:
		asm volatile ("csrw fcsr, %0" : : "r" (value) : );
		break;
	case CSR_CYCLE:
		asm volatile ("csrw cycle, %0" : : "r" (value) : );
		break;
	case CSR_TIME:
		asm volatile ("csrw time, %0" : : "r" (value) : );
		break;
	case CSR_INSTRET:
		asm volatile ("csrw instret, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3:
		asm volatile ("csrw hpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4:
		asm volatile ("csrw hpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5:
		asm volatile ("csrw hpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6:
		asm volatile ("csrw hpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7:
		asm volatile ("csrw hpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8:
		asm volatile ("csrw hpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9:
		asm volatile ("csrw hpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10:
		asm volatile ("csrw hpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11:
		asm volatile ("csrw hpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12:
		asm volatile ("csrw hpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13:
		asm volatile ("csrw hpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14:
		asm volatile ("csrw hpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15:
		asm volatile ("csrw hpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16:
		asm volatile ("csrw hpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17:
		asm volatile ("csrw hpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18:
		asm volatile ("csrw hpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19:
		asm volatile ("csrw hpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20:
		asm volatile ("csrw hpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21:
		asm volatile ("csrw hpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22:
		asm volatile ("csrw hpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23:
		asm volatile ("csrw hpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24:
		asm volatile ("csrw hpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25:
		asm volatile ("csrw hpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26:
		asm volatile ("csrw hpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27:
		asm volatile ("csrw hpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28:
		asm volatile ("csrw hpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29:
		asm volatile ("csrw hpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30:
		asm volatile ("csrw hpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31:
		asm volatile ("csrw hpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_CYCLEH:
		asm volatile ("csrw cycleh, %0" : : "r" (value) : );
		break;
	case CSR_TIMEH:
		asm volatile ("csrw timeh, %0" : : "r" (value) : );
		break;
	case CSR_INSTRETH:
		asm volatile ("csrw instreth, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER3H:
		asm volatile ("csrw hpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER4H:
		asm volatile ("csrw hpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER5H:
		asm volatile ("csrw hpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER6H:
		asm volatile ("csrw hpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER7H:
		asm volatile ("csrw hpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER8H:
		asm volatile ("csrw hpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER9H:
		asm volatile ("csrw hpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER10H:
		asm volatile ("csrw hpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER11H:
		asm volatile ("csrw hpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER12H:
		asm volatile ("csrw hpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER13H:
		asm volatile ("csrw hpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER14H:
		asm volatile ("csrw hpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER15H:
		asm volatile ("csrw hpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER16H:
		asm volatile ("csrw hpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER17H:
		asm volatile ("csrw hpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER18H:
		asm volatile ("csrw hpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER19H:
		asm volatile ("csrw hpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER20H:
		asm volatile ("csrw hpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER21H:
		asm volatile ("csrw hpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER22H:
		asm volatile ("csrw hpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER23H:
		asm volatile ("csrw hpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER24H:
		asm volatile ("csrw hpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER25H:
		asm volatile ("csrw hpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER26H:
		asm volatile ("csrw hpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER27H:
		asm volatile ("csrw hpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER28H:
		asm volatile ("csrw hpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER29H:
		asm volatile ("csrw hpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER30H:
		asm volatile ("csrw hpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_HPMCOUNTER31H:
		asm volatile ("csrw hpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_SSTATUS:
		asm volatile ("csrw sstatus, %0" : : "r" (value) : );
		break;
	case CSR_SEDELEG:
		asm volatile ("csrw sedeleg, %0" : : "r" (value) : );
		break;
	case CSR_SIDELEG:
		asm volatile ("csrw sideleg, %0" : : "r" (value) : );
		break;
	case CSR_SIE:
		asm volatile ("csrw sie, %0" : : "r" (value) : );
		break;
	case CSR_STVEC:
		asm volatile ("csrw stvec, %0" : : "r" (value) : );
		break;
	case CSR_SCOUNTEREN:
		asm volatile ("csrw scounteren, %0" : : "r" (value) : );
		break;
	case CSR_SSCRATCH:
		asm volatile ("csrw sscratch, %0" : : "r" (value) : );
		break;
	case CSR_SEPC:
		asm volatile ("csrw sepc, %0" : : "r" (value) : );
		break;
	case CSR_SCAUSE:
		asm volatile ("csrw scause, %0" : : "r" (value) : );
		break;
	case CSR_STVAL:
		//asm volatile ("csrw stval, %0" : : "r" (value) : );
		break;
	case CSR_SIP:
		asm volatile ("csrw sip, %0" : : "r" (value) : );
		break;
	case CSR_SATP:
		asm volatile ("csrw satp, %0" : : "r" (value) : );
		break;
	case CSR_MVENDORID:
		asm volatile ("csrw mvendorid, %0" : : "r" (value) : );
		break;
	case CSR_MARCHID:
		asm volatile ("csrw marchid, %0" : : "r" (value) : );
		break;
	case CSR_MIMPID:
		asm volatile ("csrw mimpid, %0" : : "r" (value) : );
		break;
	case CSR_MHARTID:
		asm volatile ("csrw mhartid, %0" : : "r" (value) : );
		break;
	case CSR_MSTATUS:
		asm volatile ("csrw mstatus, %0" : : "r" (value) : );
		break;
	case CSR_MISA:
		asm volatile ("csrw misa, %0" : : "r" (value) : );
		break;
	case CSR_MEDELEG:
		asm volatile ("csrw medeleg, %0" : : "r" (value) : );
		break;
	case CSR_MIDELEG:
		asm volatile ("csrw mideleg, %0" : : "r" (value) : );
		break;
	case CSR_MIE:
		asm volatile ("csrw mie, %0" : : "r" (value) : );
		break;
	case CSR_MTVEC:
		asm volatile ("csrw mtvec, %0" : : "r" (value) : );
		break;
	case CSR_MCOUNTEREN:
		asm volatile ("csrw mcounteren, %0" : : "r" (value) : );
		break;
	case CSR_MSCRATCH:
		asm volatile ("csrw mscratch, %0" : : "r" (value) : );
		break;
	case CSR_MEPC:
		asm volatile ("csrw mepc, %0" : : "r" (value) : );
		break;
	case CSR_MCAUSE:
		asm volatile ("csrw mcause, %0" : : "r" (value) : );
		break;
	case CSR_MTVAL:
		//asm volatile ("csrw mtval, %0" : : "r" (value) : );
		break;
	case CSR_MIP:
		asm volatile ("csrw mip, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG0:
		asm volatile ("csrw pmpcfg0, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG1:
		asm volatile ("csrw pmpcfg1, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG2:
		asm volatile ("csrw pmpcfg2, %0" : : "r" (value) : );
		break;
	case CSR_PMPCFG3:
		asm volatile ("csrw pmpcfg3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR0:
		asm volatile ("csrw pmpaddr0, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR1:
		asm volatile ("csrw pmpaddr1, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR2:
		asm volatile ("csrw pmpaddr2, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR3:
		asm volatile ("csrw pmpaddr3, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR4:
		asm volatile ("csrw pmpaddr4, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR5:
		asm volatile ("csrw pmpaddr5, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR6:
		asm volatile ("csrw pmpaddr6, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR7:
		asm volatile ("csrw pmpaddr7, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR8:
		asm volatile ("csrw pmpaddr8, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR9:
		asm volatile ("csrw pmpaddr9, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR10:
		asm volatile ("csrw pmpaddr10, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR11:
		asm volatile ("csrw pmpaddr11, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR12:
		asm volatile ("csrw pmpaddr12, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR13:
		asm volatile ("csrw pmpaddr13, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR14:
		asm volatile ("csrw pmpaddr14, %0" : : "r" (value) : );
		break;
	case CSR_PMPADDR15:
		asm volatile ("csrw pmpaddr15, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLE:
		asm volatile ("csrw mcycle, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRET:
		asm volatile ("csrw minstret, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3:
		asm volatile ("csrw mhpmcounter3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4:
		asm volatile ("csrw mhpmcounter4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5:
		asm volatile ("csrw mhpmcounter5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6:
		asm volatile ("csrw mhpmcounter6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7:
		asm volatile ("csrw mhpmcounter7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8:
		asm volatile ("csrw mhpmcounter8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9:
		asm volatile ("csrw mhpmcounter9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10:
		asm volatile ("csrw mhpmcounter10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11:
		asm volatile ("csrw mhpmcounter11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12:
		asm volatile ("csrw mhpmcounter12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13:
		asm volatile ("csrw mhpmcounter13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14:
		asm volatile ("csrw mhpmcounter14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15:
		asm volatile ("csrw mhpmcounter15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16:
		asm volatile ("csrw mhpmcounter16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17:
		asm volatile ("csrw mhpmcounter17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18:
		asm volatile ("csrw mhpmcounter18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19:
		asm volatile ("csrw mhpmcounter19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20:
		asm volatile ("csrw mhpmcounter20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21:
		asm volatile ("csrw mhpmcounter21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22:
		asm volatile ("csrw mhpmcounter22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23:
		asm volatile ("csrw mhpmcounter23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24:
		asm volatile ("csrw mhpmcounter24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25:
		asm volatile ("csrw mhpmcounter25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26:
		asm volatile ("csrw mhpmcounter26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27:
		asm volatile ("csrw mhpmcounter27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28:
		asm volatile ("csrw mhpmcounter28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29:
		asm volatile ("csrw mhpmcounter29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30:
		asm volatile ("csrw mhpmcounter30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31:
		asm volatile ("csrw mhpmcounter31, %0" : : "r" (value) : );
		break;
	case CSR_MCYCLEH:
		asm volatile ("csrw mcycleh, %0" : : "r" (value) : );
		break;
	case CSR_MINSTRETH:
		asm volatile ("csrw minstreth, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER3H:
		asm volatile ("csrw mhpmcounter3h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER4H:
		asm volatile ("csrw mhpmcounter4h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER5H:
		asm volatile ("csrw mhpmcounter5h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER6H:
		asm volatile ("csrw mhpmcounter6h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER7H:
		asm volatile ("csrw mhpmcounter7h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER8H:
		asm volatile ("csrw mhpmcounter8h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER9H:
		asm volatile ("csrw mhpmcounter9h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER10H:
		asm volatile ("csrw mhpmcounter10h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER11H:
		asm volatile ("csrw mhpmcounter11h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER12H:
		asm volatile ("csrw mhpmcounter12h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER13H:
		asm volatile ("csrw mhpmcounter13h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER14H:
		asm volatile ("csrw mhpmcounter14h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER15H:
		asm volatile ("csrw mhpmcounter15h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER16H:
		asm volatile ("csrw mhpmcounter16h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER17H:
		asm volatile ("csrw mhpmcounter17h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER18H:
		asm volatile ("csrw mhpmcounter18h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER19H:
		asm volatile ("csrw mhpmcounter19h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER20H:
		asm volatile ("csrw mhpmcounter20h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER21H:
		asm volatile ("csrw mhpmcounter21h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER22H:
		asm volatile ("csrw mhpmcounter22h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER23H:
		asm volatile ("csrw mhpmcounter23h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER24H:
		asm volatile ("csrw mhpmcounter24h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER25H:
		asm volatile ("csrw mhpmcounter25h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER26H:
		asm volatile ("csrw mhpmcounter26h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER27H:
		asm volatile ("csrw mhpmcounter27h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER28H:
		asm volatile ("csrw mhpmcounter28h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER29H:
		asm volatile ("csrw mhpmcounter29h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER30H:
		asm volatile ("csrw mhpmcounter30h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMCOUNTER31H:
		asm volatile ("csrw mhpmcounter31h, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT3:
		asm volatile ("csrw mhpmevent3, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT4:
		asm volatile ("csrw mhpmevent4, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT5:
		asm volatile ("csrw mhpmevent5, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT6:
		asm volatile ("csrw mhpmevent6, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT7:
		asm volatile ("csrw mhpmevent7, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT8:
		asm volatile ("csrw mhpmevent8, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT9:
		asm volatile ("csrw mhpmevent9, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT10:
		asm volatile ("csrw mhpmevent10, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT11:
		asm volatile ("csrw mhpmevent11, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT12:
		asm volatile ("csrw mhpmevent12, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT13:
		asm volatile ("csrw mhpmevent13, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT14:
		asm volatile ("csrw mhpmevent14, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT15:
		asm volatile ("csrw mhpmevent15, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT16:
		asm volatile ("csrw mhpmevent16, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT17:
		asm volatile ("csrw mhpmevent17, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT18:
		asm volatile ("csrw mhpmevent18, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT19:
		asm volatile ("csrw mhpmevent19, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT20:
		asm volatile ("csrw mhpmevent20, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT21:
		asm volatile ("csrw mhpmevent21, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT22:
		asm volatile ("csrw mhpmevent22, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT23:
		asm volatile ("csrw mhpmevent23, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT24:
		asm volatile ("csrw mhpmevent24, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT25:
		asm volatile ("csrw mhpmevent25, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT26:
		asm volatile ("csrw mhpmevent26, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT27:
		asm volatile ("csrw mhpmevent27, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT28:
		asm volatile ("csrw mhpmevent28, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT29:
		asm volatile ("csrw mhpmevent29, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT30:
		asm volatile ("csrw mhpmevent30, %0" : : "r" (value) : );
		break;
	case CSR_MHPMEVENT31:
		asm volatile ("csrw mhpmevent31, %0" : : "r" (value) : );
		break;
	case CSR_TSELECT:
		asm volatile ("csrw tselect, %0" : : "r" (value) : );
		break;
	case CSR_TDATA1:
		asm volatile ("csrw tdata1, %0" : : "r" (value) : );
		break;
	case CSR_TDATA2:
		asm volatile ("csrw tdata2, %0" : : "r" (value) : );
		break;
	case CSR_TDATA3:
		asm volatile ("csrw tdata3, %0" : : "r" (value) : );
		break;
	case CSR_DCSR:
		asm volatile ("csrw dcsr, %0" : : "r" (value) : );
		break;
	case CSR_DPC:
		asm volatile ("csrw dpc, %0" : : "r" (value) : );
		break;
	case CSR_DSCRATCH:
		asm volatile ("csrw dscratch, %0" : : "r" (value) : );
		break;
	default:
		break;
	}
}

void riscv_read_csr_register(unsigned short csr_id, void* reg_out) {
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
		//asm volatile ("csrr t0, stval\n\tsw t0, %0" : "=m" (*reg_out) : : "memory");
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
	default:
		break;
	}
}
