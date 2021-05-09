#ifndef SRC_ARCH_RISCV32_CSR_H_
#define SRC_ARCH_RISCV32_CSR_H_

#include <stdint.h>

#define field_mask(n_bits, pos) ((uint32_t)(((1U << (uint32_t)n_bits) - 1) << (uint32_t)pos))
#define clear_field(x, n_bits, pos) (~field_mask(n_bits, pos) & x)
#define extract_field(x, n_bits, pos) (field_mask(n_bits, pos) & x) >> (uint32_t)pos
#define set_field(x, n_bits, val, pos) (clear_field(x, n_bits, pos) \
            | ((field_mask(n_bits, 0) & val) << (uint32_t)pos))

#define misa_ext(x) extract_field(x, 26, 0)
#define misa_mxl(x) extract_field(x, 2, 29)
#define misa_ext_A(x) extract_field(misa_ext(x), 1, 0)
#define misa_ext_B(x) extract_field(misa_ext(x), 1, 1)
#define misa_ext_C(x) extract_field(misa_ext(x), 1, 2)
#define misa_ext_D(x) extract_field(misa_ext(x), 1, 3)
#define misa_ext_E(x) extract_field(misa_ext(x), 1, 4)
#define misa_ext_F(x) extract_field(misa_ext(x), 1, 5)
#define misa_ext_G(x) extract_field(misa_ext(x), 1, 6)
#define misa_ext_H(x) extract_field(misa_ext(x), 1, 7)
#define misa_ext_I(x) extract_field(misa_ext(x), 1, 8)
#define misa_ext_J(x) extract_field(misa_ext(x), 1, 9)
#define misa_ext_K(x) extract_field(misa_ext(x), 1, 10)
#define misa_ext_L(x) extract_field(misa_ext(x), 1, 11)
#define misa_ext_M(x) extract_field(misa_ext(x), 1, 12)
#define misa_ext_N(x) extract_field(misa_ext(x), 1, 13
#define misa_ext_O(x) extract_field(misa_ext(x), 1, 14)
#define misa_ext_P(x) extract_field(misa_ext(x), 1, 15)
#define misa_ext_Q(x) extract_field(misa_ext(x), 1, 16)
#define misa_ext_R(x) extract_field(misa_ext(x), 1, 17)
#define misa_ext_S(x) extract_field(misa_ext(x), 1, 18)
#define misa_ext_T(x) extract_field(misa_ext(x), 1, 19)
#define misa_ext_U(x) extract_field(misa_ext(x), 1, 20)
#define misa_ext_V(x) extract_field(misa_ext(x), 1, 21)
#define misa_ext_W(x) extract_field(misa_ext(x), 1, 22)
#define misa_ext_X(x) extract_field(misa_ext(x), 1, 23)
#define misa_ext_Y(x) extract_field(misa_ext(x), 1, 24)
#define misa_ext_Z(x) extract_field(misa_ext(x), 1, 25)
uint32_t misa_r_csr(void);
#define mvendorid_offset(x) extract_field(x, 7, 0)
#define mvendorid_bank(x) extract_field(x, 25, 7)
uint32_t mvendorid_r_csr(void);
uint32_t marchid_r_csr(void);
uint32_t mimpid_r_csr(void);
uint32_t mhartid_r_csr(void);
#define mstatus_uie(x) extract_field(x, 1, 0)
#define mstatus_sie(x) extract_field(x, 1, 1)
#define mstatus_mie(x) extract_field(x, 1, 3)
#define mstatus_upie(x) extract_field(x, 1, 4)
#define mstatus_spie(x) extract_field(x, 1, 5)
#define mstatus_mpie(x) extract_field(x, 1, 7)
#define mstatus_spp(x) extract_field(x, 1, 8)
#define mstatus_mpp(x) extract_field(x, 2, 11)
#define mstatus_fs(x) extract_field(x, 2, 13)
#define mstatus_xs(x) extract_field(x, 2, 15)
#define mstatus_mprv(x) extract_field(x, 1, 17)
#define mstatus_sum(x) extract_field(x, 1, 18)
#define mstatus_mxr(x) extract_field(x, 1, 19)
#define mstatus_tvm(x) extract_field(x, 1, 20)
#define mstatus_tw(x) extract_field(x, 1, 21)
#define mstatus_tsr(x) extract_field(x, 1, 22)
#define mstatus_sd(x) extract_field(x, 1, 31)

#define mstatus_set_uie(x, val) set_field(x, 1, val, 0)
#define mstatus_set_sie(x, val) set_field(x, 1, val, 1)
#define mstatus_set_mie(x, val) set_field(x, 1, val, 3)
#define mstatus_set_mprv(x, val) set_field(x, 1, val, 17)
#define mstatus_set_tvm(x, val) set_field(x, 1, val, 20)
uint32_t mstatus_r_csr(void);
void mstatus_w_csr(void);
#define mtvec_mode(x) extract_field(x, 2, 0)
#define mtvec_base(x) extract_field(x, 30, 2)
uint32_t mtvec_r_csr(void);
void mtvec_w_csr(uint32_t val);
#define medeleg_ins_misaligned(x) extract_field(x, 1, 0)
#define medeleg_ins_access_fault(x) extract_field(x, 1, 1)
#define medeleg_illegal_ins(x) extract_field(x, 1, 2)
#define medeleg_breakpoint(x) extract_field(x, 1, 3)
#define medeleg_load_addr_misaligned(x) extract_field(x, 1, 4)
#define medeleg_load_access_fault(x) extract_field(x, 1, 5)
#define medeleg_store_amo_add_misaligned(x) extract_field(x, 1, 6)
#define medeleg_store_amo_access_fault(x) extract_field(x, 1, 7)
#define medeleg_ecall_from_u_mode(x) extract_field(x, 1, 8)
#define medeleg_ecall_from_s_mode(x) extract_field(x, 1, 9)
#define medeleg_e_call_from_m_mode(x) extract_field(x, 1, 11)
#define medeleg_ins_page_fault(x) extract_field(x, 1, 12)
#define medeleg_load_page_fault(x) extract_field(x, 1, 13)
#define medeleg_store_amo_page_fault(x) extract_field(x, 1, 15)

#define medeleg_set_ins_misaligned(x, val) set_field(x, 1, val, 0)
#define medeleg_set_ins_access_fault(x, val) set_field(x, 1, val, 1)
#define medeleg_set_illegal_ins(x, val) set_field(x, 1, val, 2)
#define medeleg_set_breakpoint(x, val) set_field(x, 1, val, 3)
#define medeleg_set_load_addr_misaligned(x, val) set_field(x, 1, val, 4)
#define medeleg_set_load_access_fault(x, val) set_field(x, 1, val, 5)
#define medeleg_set_store_amo_add_misaligned(x, val) set_field(x, 1, val, 6)
#define medeleg_set_store_amo_access_fault(x, val) set_field(x, 1, val, 7)
#define medeleg_set_ecall_from_u_mode(x, val) set_field(x, 1, val, 8)
#define medeleg_set_ecall_from_s_mode(x, val) set_field(x, 1, val, 9)
#define medeleg_set_e_call_from_m_mode(x, val) set_field(x, 1, val, 11)
#define medeleg_set_ins_page_fault(x, val) set_field(x, 1, val, 12)
#define medeleg_set_load_page_fault(x, val) set_field(x, 1, val, 13)
#define medeleg_set_store_amo_page_fault(x, val) set_field(x, 1, val, 14)
uint32_t medeleg_r_csr(void);
void medeleg_w_csr(uint32_t val);
#define mip_usip(x) extract_field(x, 1, 0)
#define mip_ssip(x) extract_field(x, 1, 1)
#define mip_msip(x) extract_field(x, 1, 3)
#define mip_utip(x) extract_field(x, 1, 4)
#define mip_stip(x) extract_field(x, 1, 5)
#define mip_mtip(x) extract_field(x, 1, 7)
#define mip_ueip(x) extract_field(x, 1, 8)
#define mip_seip(x) extract_field(x, 1, 9)
#define mip_meip(x) extract_field(x, 1, 11)

#define mip_set_usip(x, val) set_field(x, 1, val, 0)
#define mip_set_ssip(x, val) set_field(x, 1, val, 1)
#define mip_set_msip(x, val) set_field(x, 1, val, 3)
#define mip_set_utip(x, val) set_field(x, 1, val, 4)
#define mip_set_stip(x, val) set_field(x, 1, val, 5)
#define mip_set_mtip(x, val) set_field(x, 1, val, 7)
#define mip_set_ueip(x, val) set_field(x, 1, val, 8)
#define mip_set_seip(x, val) set_field(x, 1, val, 9)
#define mip_set_meip(x, val) set_field(x, 1, val, 11)
uint32_t mip_r_csr(void);
uint32_t mip_w_csr(void);
#define mideleg_usip(x) mip_usip(x)
#define mideleg_ssip(x) mip_ssip(x)
#define mideleg_msip(x) mip_msip(x)
#define mideleg_utip(x) mip_utip(x)
#define mideleg_stip(x) mip_stip(x)
#define mideleg_mtip(x) mip_mtip(x)
#define mideleg_ueip(x) mip_ueip(x)
#define mideleg_seip(x) mip_seip(x)
#define mideleg_meip(x) mip_meip(x)

#define mideleg_set_usip(x, val) mip_set_usip(x, val)
#define mideleg_set_ssip(x, val) mip_set_ssip(x, val)
#define mideleg_set_msip(x, val) mip_set_msip(x, val)
#define mideleg_set_utip(x, val) mip_set_utip(x, val)
#define mideleg_set_stip(x, val) mip_set_stip(x, val)
#define mideleg_set_mtip(x, val) mip_set_mtip(x, val)
#define mideleg_set_ueip(x, val) mip_set_ueip(x, val)
#define mideleg_set_seip(x, val) mip_set_seip(x, val)
#define mideleg_set_meip(x, val) mip_set_meip(x, val)
uint32_t mideleg_r_csr(void);
void mideleg_w_csr(uint32_t val);
#define mie_usie(x) extract_field(x, 1, 0)
#define mie_ssie(x) extract_field(x, 1, 1)
#define mie_msie(x) extract_field(x, 1, 3)
#define mie_utie(x) extract_field(x, 1, 4)
#define mie_stie(x) extract_field(x, 1, 5)
#define mie_mtie(x) extract_field(x, 1, 7)
#define mie_ueie(x) extract_field(x, 1, 8)
#define mie_seie(x) extract_field(x, 1, 9)
#define mie_meie(x) extract_field(x, 1, 11)

#define mie_set_usie(x, val) set_field(x, 1, val, 0)
#define mie_set_ssie(x, val) set_field(x, 1, val, 1)
#define mie_set_msie(x, val) set_field(x, 1, val, 3)
#define mie_set_utie(x, val) set_field(x, 1, val, 4)
#define mie_set_stie(x, val) set_field(x, 1, val, 5)
#define mie_set_mtie(x, val) set_field(x, 1, val, 7)
#define mie_set_ueie(x, val) set_field(x, 1, val, 8)
#define mie_set_seie(x, val) set_field(x, 1, val, 9)
#define mie_set_meie(x, val) set_field(x, 1, val, 11)
uint32_t mie_r_csr(void);
void mie_w_csr(uint32_t val);
void mtime_w_csr(void);
uint64_t mtime_r_csr(void);
uint64_t mtime_cmp_r_csr(void);
void mtime_cmp_w_csr(uint64_t val);
uint64_t mscratch_r_csr(void);
void mscratch_w_csr(uint32_t val);
uint32_t mepc_r_csr(void);
// TODO: abstraction for mapping exception code to enum
#define mcause_except_code(x) extract_field(x, 31, 0)
#define mcause_interrupt(x) extract_field(x, 1, 31)
uint32_t mcause_r_csr(void);
uint32_t mtval_r_csr(void);
// TODO: Add Hardware performance counter CSRs

// Supervisor CSRs
#define sstatus_uie(x) extract_field(x, 1, 0)
#define sstatus_sie(x) extract_field(x, 1, 1)
#define sstatus_upie(x) extract_field(x, 1, 4)
#define sstatus_spie(x) extract_field(x, 1, 5)
#define sstatus_spp(x) extract_field(x, 1, 8)
#define sstatus_fs(x) extract_field(x, 2, 13)
#define sstatus_xs(x) extract_field(x, 2, 15)
#define sstatus_sum(x) extract_field(x, 1, 18)
#define sstatus_mxr(x) extract_field(x, 1, 19)
#define sstatus_sd(x) extract_field(x, 1, 31)

#define sstatus_set_uie(x, val) set_field(x, 1, val, 0)
#define sstatus_set_sie(x, val) set_field(x, 1, val, 1)
#define sstatus_set_upie(x, val) set_field(x, 1, val, 4)
#define sstatus_set_spie(x, val) set_field(x, 1, val, 5)
#define sstatus_set_spp(x, val) set_field(x, 1, val, 8)
#define sstatus_set_fs(x, val) set_field(x, 2, val, 13)
#define sstatus_set_xs(x, val) set_field(x, 2, val, 15)
#define sstatus_set_sum(x, val) set_field(x, 1, val, 18)
#define sstatus_set_mxr(x, val) set_field(x, 1, val, 19)
#define sstatus_set_sd(x, val) set_field(x, 1, val, 31)

uint32_t sstatus_r_csr(void);
void sstatus_w_csr(uint32_t val);
#define stvec_mode(x) extract_field(x, 2, 0)
#define stvec_base(x) extract_field(x, 30, 2)
uint32_t stvec_r_csr(void);
// TODO: supervisor performance counters
void stvec_w_csr(uint32_t val);
uint32_t sscratch_r_csr(void);
void sscratch_w_csr(uint32_t val);
uint32_t sepc_r_csr(void);
void sepc_w_csr(uint32_t val);

#define scause_except_code(x) extract_field(x, 31, 0)
#define scause_interrupt(x) extract_field(x, 1, 31)
// TODO: map supervisor exception codes to enum
uint32_t scause_r_csr(void);
void scause_w_csr(uint32_t val);

uint32_t stval_r_csr(void);
void stval_w_csr(uint32_t val);

#define satp_ppn(x) extract_field(x, 22, 0)
#define satp_asid(x) extract_field(x, 9, 22)
#define satp_mode(x) extract_field(x, 1, 31)

#define satp_set_ppn(x, val) set_field(x, 22, val, 0)
#define satp_set_asid(x, val) set_field(x, 9, val, 22)
#define satp_set_mode(x, val) set_field(x, 1, val, 31)
uint32_t satp_r_csr(void);
void satp_w_csr(uint32_t val);
#define sie_usie(x) extract_field(x, 1, 0)
#define sie_ssie(x) extract_field(x, 1, 1)
#define sie_utie(x) extract_field(x, 1, 4)
#define sie_stie(x) extract_field(x, 1, 5)
#define sie_ueie(x) extract_field(x, 1, 8)
#define sie_seie(x) extract_field(x, 1, 9)

#define sie_set_usie(x, val) set_field(x, 1, val, 0)
#define sie_set_ssie(x, val) set_field(x, 1, val, 1)
#define sie_set_utie(x, val) set_field(x, 1, val, 4)
#define sie_set_stie(x, val) set_field(x, 1, val, 5)
#define sie_set_ueie(x, val) set_field(x, 1, val, 8)
#define sie_set_seie(x, val) set_field(x, 1, val, 9)

uint32_t sie_r_csr(void);
void sie_w_csr(uint32_t val);
void sie_s_csr(uint32_t val);
void sie_c_csr(uint32_t val);

uint64_t time_r_csr(void);
uint64_t cycle_r_csr(void);

#endif /* SRC_ARCH_RISCV32_CSR_H_ */
