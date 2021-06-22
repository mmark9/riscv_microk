#ifndef SRC_ARCH_RISCV32_CSR_H_
#define SRC_ARCH_RISCV32_CSR_H_

#include "arch.h"
#include <stdint.h>

#ifdef RV64
#define field_mask(n_bits, pos) ((rvu_word)(((1ULL << (rvu_word)(n_bits)) - 1) << (rvu_word)(pos)))
#else
#define field_mask(n_bits, pos) ((rvu_word)(((1U << (rvu_word)(n_bits)) - 1) << (uint32_t)(pos)))
#endif
#define clear_field(x, n_bits, pos) (~field_mask((n_bits), (pos)) & (x))
#define extract_field(x, n_bits, pos) ((field_mask((n_bits), (pos)) & (x)) >> (rvu_word)(pos))
#define set_field(x, n_bits, val, pos) (clear_field((x), (n_bits), (pos)) \
            | (field_mask((n_bits), 0) & (val)) << (rvu_word)(pos))

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
#ifdef RV64
#define sstatus_uxl(x) extract_field(x, 2, 32)
#endif
#define sstatus_sd(x) extract_field(x, 1, XLEN-1)


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

rvu_word sstatus_r_csr(void);
void sstatus_w_csr(rvu_word val);
#define stvec_mode(x) extract_field(x, 2, 0)
#define stvec_base(x) extract_field(x, XLEN-2, 2)
rvu_word stvec_r_csr(void);
// TODO: supervisor performance counters
void stvec_w_csr(rvu_word val);
rvu_word sscratch_r_csr(void);
void sscratch_w_csr(rvu_word val);
rvu_word sepc_r_csr(void);
void sepc_w_csr(rvu_word val);

#define scause_except_code(x) extract_field(x, XLEN-1, 0)
#define scause_interrupt(x) extract_field(x, 1, XLEN-1)
// TODO: map supervisor exception codes to enum
rvu_word scause_r_csr(void);
void scause_w_csr(rvu_word val);

rvu_word stval_r_csr(void);
void stval_w_csr(rvu_word val);
rvu_word sbadaddr_r_csr(void);

#ifdef RV64
#define satp_ppn(x) extract_field(x, 44, 0)
#define satp_asid(x) extract_field(x, 16, 44)
#define satp_mode(x) extract_field(x, 4, XLEN-4)
#define satp_set_ppn(x, val) set_field(x, 44, val, 0)
#define satp_set_asid(x, val) set_field(x, 9, val, 44)
#define satp_set_mode(x, val) set_field(x, 4, val, XLEN-4)
#else
#define satp_ppn(x) extract_field(x, 22, 0)
#define satp_asid(x) extract_field(x, 9, 22)
#define satp_mode(x) extract_field(x, 1, 31)
#define satp_set_ppn(x, val) set_field(x, 22, val, 0)
#define satp_set_asid(x, val) set_field(x, 9, val, 22)
#define satp_set_mode(x, val) set_field(x, 1, val, XLEN-1)
#endif

void satp_w_csr(rvu_word val);
rvu_word satp_r_csr(void);

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

rvu_word sie_r_csr(void);
void sie_w_csr(rvu_word val);
void sie_s_csr(rvu_word val);
void sie_c_csr(rvu_word val);

#ifdef RV64
uint64_t time_r_csr64(void);
uint64_t cycle_r_csr64(void);
#define cycle_r_csr() cycle_r_csr64()
#define time_r_csr() time_r_csr64()
#else
uint64_t time_r_csr32(void);
uint64_t cycle_r_csr32(void);
#define cycle_r_csr() cycle_r_csr64()
#define time_r_csr() time_r_csr64()
#endif

#endif /* SRC_ARCH_RISCV32_CSR_H_ */
