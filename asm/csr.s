.section .text
### CSR READS

.globl ustatus_r_csr
ustatus_r_csr:
    csrr a0, ustatus
    ret

.globl uie_r_csr
uie_r_csr:
    csrr a0, uie
    ret

.globl utvec_r_csr
utvec_r_csr:
    csrr a0, utvec
    ret

.globl uscratch_r_csr
uscratch_r_csr:
    csrr a0, uscratch
    ret

.globl uepc_r_csr
uepc_r_csr:
    csrr a0, uepc
    ret

.globl ucause_r_csr
ucause_r_csr:
    csrr a0, ucause
    ret

.globl utval_r_csr
utval_r_csr:
    csrr a0, utval
    ret

.globl uip_r_csr
uip_r_csr:
    csrr a0, uip
    ret

.globl fflags_r_csr
fflags_r_csr:
    csrr a0, fflags
    ret

.globl frm_r_csr
frm_r_csr:
    csrr a0, frm
    ret

.globl fcsr_r_csr
fcsr_r_csr:
    csrr a0, fcsr
    ret

.globl cycle_r_csr
cycle_r_csr:
    csrr a0, cycle
    ret

.globl time_r_csr
time_r_csr:
    csrr a0, time
    ret

.globl instret_r_csr
instret_r_csr:
    csrr a0, instret
    ret

.globl hpmcounter3_r_csr
hpmcounter3_r_csr:
    csrr a0, hpmcounter3
    ret

.globl hpmcounter4_r_csr
hpmcounter4_r_csr:
    csrr a0, hpmcounter4
    ret

.globl hpmcounter5_r_csr
hpmcounter5_r_csr:
    csrr a0, hpmcounter5
    ret

.globl hpmcounter6_r_csr
hpmcounter6_r_csr:
    csrr a0, hpmcounter6
    ret

.globl hpmcounter7_r_csr
hpmcounter7_r_csr:
    csrr a0, hpmcounter7
    ret

.globl hpmcounter8_r_csr
hpmcounter8_r_csr:
    csrr a0, hpmcounter8
    ret

.globl hpmcounter9_r_csr
hpmcounter9_r_csr:
    csrr a0, hpmcounter9
    ret

.globl hpmcounter10_r_csr
hpmcounter10_r_csr:
    csrr a0, hpmcounter10
    ret

.globl hpmcounter11_r_csr
hpmcounter11_r_csr:
    csrr a0, hpmcounter11
    ret

.globl hpmcounter12_r_csr
hpmcounter12_r_csr:
    csrr a0, hpmcounter12
    ret

.globl hpmcounter13_r_csr
hpmcounter13_r_csr:
    csrr a0, hpmcounter13
    ret

.globl hpmcounter14_r_csr
hpmcounter14_r_csr:
    csrr a0, hpmcounter14
    ret

.globl hpmcounter15_r_csr
hpmcounter15_r_csr:
    csrr a0, hpmcounter15
    ret

.globl hpmcounter16_r_csr
hpmcounter16_r_csr:
    csrr a0, hpmcounter16
    ret

.globl hpmcounter17_r_csr
hpmcounter17_r_csr:
    csrr a0, hpmcounter17
    ret

.globl hpmcounter18_r_csr
hpmcounter18_r_csr:
    csrr a0, hpmcounter18
    ret

.globl hpmcounter19_r_csr
hpmcounter19_r_csr:
    csrr a0, hpmcounter19
    ret

.globl hpmcounter20_r_csr
hpmcounter20_r_csr:
    csrr a0, hpmcounter20
    ret

.globl hpmcounter21_r_csr
hpmcounter21_r_csr:
    csrr a0, hpmcounter21
    ret

.globl hpmcounter22_r_csr
hpmcounter22_r_csr:
    csrr a0, hpmcounter22
    ret

.globl hpmcounter23_r_csr
hpmcounter23_r_csr:
    csrr a0, hpmcounter23
    ret

.globl hpmcounter24_r_csr
hpmcounter24_r_csr:
    csrr a0, hpmcounter24
    ret

.globl hpmcounter25_r_csr
hpmcounter25_r_csr:
    csrr a0, hpmcounter25
    ret

.globl hpmcounter26_r_csr
hpmcounter26_r_csr:
    csrr a0, hpmcounter26
    ret

.globl hpmcounter27_r_csr
hpmcounter27_r_csr:
    csrr a0, hpmcounter27
    ret

.globl hpmcounter28_r_csr
hpmcounter28_r_csr:
    csrr a0, hpmcounter28
    ret

.globl hpmcounter29_r_csr
hpmcounter29_r_csr:
    csrr a0, hpmcounter29
    ret

.globl hpmcounter30_r_csr
hpmcounter30_r_csr:
    csrr a0, hpmcounter30
    ret

.globl hpmcounter31_r_csr
hpmcounter31_r_csr:
    csrr a0, hpmcounter31
    ret

.globl cycleh_r_csr
cycleh_r_csr:
    csrr a0, cycleh
    ret

.globl timeh_r_csr
timeh_r_csr:
    csrr a0, timeh
    ret

.globl instreth_r_csr
instreth_r_csr:
    csrr a0, instreth
    ret

.globl hpmcounter3h_r_csr
hpmcounter3h_r_csr:
    csrr a0, hpmcounter3h
    ret

.globl hpmcounter4h_r_csr
hpmcounter4h_r_csr:
    csrr a0, hpmcounter4h
    ret

.globl hpmcounter5h_r_csr
hpmcounter5h_r_csr:
    csrr a0, hpmcounter5h
    ret

.globl hpmcounter6h_r_csr
hpmcounter6h_r_csr:
    csrr a0, hpmcounter6h
    ret

.globl hpmcounter7h_r_csr
hpmcounter7h_r_csr:
    csrr a0, hpmcounter7h
    ret

.globl hpmcounter8h_r_csr
hpmcounter8h_r_csr:
    csrr a0, hpmcounter8h
    ret

.globl hpmcounter9h_r_csr
hpmcounter9h_r_csr:
    csrr a0, hpmcounter9h
    ret

.globl hpmcounter10h_r_csr
hpmcounter10h_r_csr:
    csrr a0, hpmcounter10h
    ret

.globl hpmcounter11h_r_csr
hpmcounter11h_r_csr:
    csrr a0, hpmcounter11h
    ret

.globl hpmcounter12h_r_csr
hpmcounter12h_r_csr:
    csrr a0, hpmcounter12h
    ret

.globl hpmcounter13h_r_csr
hpmcounter13h_r_csr:
    csrr a0, hpmcounter13h
    ret

.globl hpmcounter14h_r_csr
hpmcounter14h_r_csr:
    csrr a0, hpmcounter14h
    ret

.globl hpmcounter15h_r_csr
hpmcounter15h_r_csr:
    csrr a0, hpmcounter15h
    ret

.globl hpmcounter16h_r_csr
hpmcounter16h_r_csr:
    csrr a0, hpmcounter16h
    ret

.globl hpmcounter17h_r_csr
hpmcounter17h_r_csr:
    csrr a0, hpmcounter17h
    ret

.globl hpmcounter18h_r_csr
hpmcounter18h_r_csr:
    csrr a0, hpmcounter18h
    ret

.globl hpmcounter19h_r_csr
hpmcounter19h_r_csr:
    csrr a0, hpmcounter19h
    ret

.globl hpmcounter20h_r_csr
hpmcounter20h_r_csr:
    csrr a0, hpmcounter20h
    ret

.globl hpmcounter21h_r_csr
hpmcounter21h_r_csr:
    csrr a0, hpmcounter21h
    ret

.globl hpmcounter22h_r_csr
hpmcounter22h_r_csr:
    csrr a0, hpmcounter22h
    ret

.globl hpmcounter23h_r_csr
hpmcounter23h_r_csr:
    csrr a0, hpmcounter23h
    ret

.globl hpmcounter24h_r_csr
hpmcounter24h_r_csr:
    csrr a0, hpmcounter24h
    ret

.globl hpmcounter25h_r_csr
hpmcounter25h_r_csr:
    csrr a0, hpmcounter25h
    ret

.globl hpmcounter26h_r_csr
hpmcounter26h_r_csr:
    csrr a0, hpmcounter26h
    ret

.globl hpmcounter27h_r_csr
hpmcounter27h_r_csr:
    csrr a0, hpmcounter27h
    ret

.globl hpmcounter28h_r_csr
hpmcounter28h_r_csr:
    csrr a0, hpmcounter28h
    ret

.globl hpmcounter29h_r_csr
hpmcounter29h_r_csr:
    csrr a0, hpmcounter29h
    ret

.globl hpmcounter30h_r_csr
hpmcounter30h_r_csr:
    csrr a0, hpmcounter30h
    ret

.globl hpmcounter31h_r_csr
hpmcounter31h_r_csr:
    csrr a0, hpmcounter31h
    ret

.globl sstatus_r_csr
sstatus_r_csr:
    csrr a0, sstatus
    ret

.globl sedeleg_r_csr
sedeleg_r_csr:
    csrr a0, sedeleg
    ret

.globl sideleg_r_csr
sideleg_r_csr:
    csrr a0, sideleg
    ret

.globl sie_r_csr
sie_r_csr:
    csrr a0, sie
    ret

.globl stvec_r_csr
stvec_r_csr:
    csrr a0, stvec
    ret

.globl scounteren_r_csr
scounteren_r_csr:
    csrr a0, scounteren
    ret

.globl sscratch_r_csr
sscratch_r_csr:
    csrr a0, sscratch
    ret

.globl sepc_r_csr
sepc_r_csr:
    csrr a0, sepc
    ret

.globl scause_r_csr
scause_r_csr:
    csrr a0, scause
    ret

.globl sbadaddr_r_csr
sbadaddr_r_csr:
    csrr a0, sbadaddr
    ret

.globl sip_r_csr
sip_r_csr:
    csrr a0, sip
    ret

.globl satp_r_csr
satp_r_csr:
    csrr a0, satp
    ret

.globl mvendorid_r_csr
mvendorid_r_csr:
    csrr a0, mvendorid
    ret

.globl marchid_r_csr
marchid_r_csr:
    csrr a0, marchid
    ret

.globl mimpid_r_csr
mimpid_r_csr:
    csrr a0, mimpid
    ret

.globl mhartid_r_csr
mhartid_r_csr:
    csrr a0, mhartid
    ret

.globl mstatus_r_csr
mstatus_r_csr:
    csrr a0, mstatus
    ret

.globl misa_r_csr
misa_r_csr:
    csrr a0, misa
    ret

.globl medeleg_r_csr
medeleg_r_csr:
    csrr a0, medeleg
    ret

.globl mideleg_r_csr
mideleg_r_csr:
    csrr a0, mideleg
    ret

.globl mie_r_csr
mie_r_csr:
    csrr a0, mie
    ret

.globl mtvec_r_csr
mtvec_r_csr:
    csrr a0, mtvec
    ret

.globl mcounteren_r_csr
mcounteren_r_csr:
    csrr a0, mcounteren
    ret

.globl mscratch_r_csr
mscratch_r_csr:
    csrr a0, mscratch
    ret

.globl mepc_r_csr
mepc_r_csr:
    csrr a0, mepc
    ret

.globl mcause_r_csr
mcause_r_csr:
    csrr a0, mcause
    ret

.globl mbadaddr_r_csr
mbadaddr_r_csr:
    csrr a0, mbadaddr
    ret

.globl mip_r_csr
mip_r_csr:
    csrr a0, mip
    ret

.globl pmpcfg0_r_csr
pmpcfg0_r_csr:
    csrr a0, pmpcfg0
    ret

.globl pmpcfg1_r_csr
pmpcfg1_r_csr:
    csrr a0, pmpcfg1
    ret

.globl pmpcfg2_r_csr
pmpcfg2_r_csr:
    csrr a0, pmpcfg2
    ret

.globl pmpcfg3_r_csr
pmpcfg3_r_csr:
    csrr a0, pmpcfg3
    ret

.globl pmpaddr0_r_csr
pmpaddr0_r_csr:
    csrr a0, pmpaddr0
    ret

.globl pmpaddr1_r_csr
pmpaddr1_r_csr:
    csrr a0, pmpaddr1
    ret

.globl pmpaddr2_r_csr
pmpaddr2_r_csr:
    csrr a0, pmpaddr2
    ret

.globl pmpaddr3_r_csr
pmpaddr3_r_csr:
    csrr a0, pmpaddr3
    ret

.globl pmpaddr4_r_csr
pmpaddr4_r_csr:
    csrr a0, pmpaddr4
    ret

.globl pmpaddr5_r_csr
pmpaddr5_r_csr:
    csrr a0, pmpaddr5
    ret

.globl pmpaddr6_r_csr
pmpaddr6_r_csr:
    csrr a0, pmpaddr6
    ret

.globl pmpaddr7_r_csr
pmpaddr7_r_csr:
    csrr a0, pmpaddr7
    ret

.globl pmpaddr8_r_csr
pmpaddr8_r_csr:
    csrr a0, pmpaddr8
    ret

.globl pmpaddr9_r_csr
pmpaddr9_r_csr:
    csrr a0, pmpaddr9
    ret

.globl pmpaddr10_r_csr
pmpaddr10_r_csr:
    csrr a0, pmpaddr10
    ret

.globl pmpaddr11_r_csr
pmpaddr11_r_csr:
    csrr a0, pmpaddr11
    ret

.globl pmpaddr12_r_csr
pmpaddr12_r_csr:
    csrr a0, pmpaddr12
    ret

.globl pmpaddr13_r_csr
pmpaddr13_r_csr:
    csrr a0, pmpaddr13
    ret

.globl pmpaddr14_r_csr
pmpaddr14_r_csr:
    csrr a0, pmpaddr14
    ret

.globl pmpaddr15_r_csr
pmpaddr15_r_csr:
    csrr a0, pmpaddr15
    ret

.globl mcycle_r_csr
mcycle_r_csr:
    csrr a0, mcycle
    ret

.globl minstret_r_csr
minstret_r_csr:
    csrr a0, minstret
    ret

.globl mhpmcounter3_r_csr
mhpmcounter3_r_csr:
    csrr a0, mhpmcounter3
    ret

.globl mhpmcounter4_r_csr
mhpmcounter4_r_csr:
    csrr a0, mhpmcounter4
    ret

.globl mhpmcounter5_r_csr
mhpmcounter5_r_csr:
    csrr a0, mhpmcounter5
    ret

.globl mhpmcounter6_r_csr
mhpmcounter6_r_csr:
    csrr a0, mhpmcounter6
    ret

.globl mhpmcounter7_r_csr
mhpmcounter7_r_csr:
    csrr a0, mhpmcounter7
    ret

.globl mhpmcounter8_r_csr
mhpmcounter8_r_csr:
    csrr a0, mhpmcounter8
    ret

.globl mhpmcounter9_r_csr
mhpmcounter9_r_csr:
    csrr a0, mhpmcounter9
    ret

.globl mhpmcounter10_r_csr
mhpmcounter10_r_csr:
    csrr a0, mhpmcounter10
    ret

.globl mhpmcounter11_r_csr
mhpmcounter11_r_csr:
    csrr a0, mhpmcounter11
    ret

.globl mhpmcounter12_r_csr
mhpmcounter12_r_csr:
    csrr a0, mhpmcounter12
    ret

.globl mhpmcounter13_r_csr
mhpmcounter13_r_csr:
    csrr a0, mhpmcounter13
    ret

.globl mhpmcounter14_r_csr
mhpmcounter14_r_csr:
    csrr a0, mhpmcounter14
    ret

.globl mhpmcounter15_r_csr
mhpmcounter15_r_csr:
    csrr a0, mhpmcounter15
    ret

.globl mhpmcounter16_r_csr
mhpmcounter16_r_csr:
    csrr a0, mhpmcounter16
    ret

.globl mhpmcounter17_r_csr
mhpmcounter17_r_csr:
    csrr a0, mhpmcounter17
    ret

.globl mhpmcounter18_r_csr
mhpmcounter18_r_csr:
    csrr a0, mhpmcounter18
    ret

.globl mhpmcounter19_r_csr
mhpmcounter19_r_csr:
    csrr a0, mhpmcounter19
    ret

.globl mhpmcounter20_r_csr
mhpmcounter20_r_csr:
    csrr a0, mhpmcounter20
    ret

.globl mhpmcounter21_r_csr
mhpmcounter21_r_csr:
    csrr a0, mhpmcounter21
    ret

.globl mhpmcounter22_r_csr
mhpmcounter22_r_csr:
    csrr a0, mhpmcounter22
    ret

.globl mhpmcounter23_r_csr
mhpmcounter23_r_csr:
    csrr a0, mhpmcounter23
    ret

.globl mhpmcounter24_r_csr
mhpmcounter24_r_csr:
    csrr a0, mhpmcounter24
    ret

.globl mhpmcounter25_r_csr
mhpmcounter25_r_csr:
    csrr a0, mhpmcounter25
    ret

.globl mhpmcounter26_r_csr
mhpmcounter26_r_csr:
    csrr a0, mhpmcounter26
    ret

.globl mhpmcounter27_r_csr
mhpmcounter27_r_csr:
    csrr a0, mhpmcounter27
    ret

.globl mhpmcounter28_r_csr
mhpmcounter28_r_csr:
    csrr a0, mhpmcounter28
    ret

.globl mhpmcounter29_r_csr
mhpmcounter29_r_csr:
    csrr a0, mhpmcounter29
    ret

.globl mhpmcounter30_r_csr
mhpmcounter30_r_csr:
    csrr a0, mhpmcounter30
    ret

.globl mhpmcounter31_r_csr
mhpmcounter31_r_csr:
    csrr a0, mhpmcounter31
    ret

.globl mcycleh_r_csr
mcycleh_r_csr:
    csrr a0, mcycleh
    ret

.globl minstreth_r_csr
minstreth_r_csr:
    csrr a0, minstreth
    ret

.globl mhpmcounter3h_r_csr
mhpmcounter3h_r_csr:
    csrr a0, mhpmcounter3h
    ret

.globl mhpmcounter4h_r_csr
mhpmcounter4h_r_csr:
    csrr a0, mhpmcounter4h
    ret

.globl mhpmcounter5h_r_csr
mhpmcounter5h_r_csr:
    csrr a0, mhpmcounter5h
    ret

.globl mhpmcounter6h_r_csr
mhpmcounter6h_r_csr:
    csrr a0, mhpmcounter6h
    ret

.globl mhpmcounter7h_r_csr
mhpmcounter7h_r_csr:
    csrr a0, mhpmcounter7h
    ret

.globl mhpmcounter8h_r_csr
mhpmcounter8h_r_csr:
    csrr a0, mhpmcounter8h
    ret

.globl mhpmcounter9h_r_csr
mhpmcounter9h_r_csr:
    csrr a0, mhpmcounter9h
    ret

.globl mhpmcounter10h_r_csr
mhpmcounter10h_r_csr:
    csrr a0, mhpmcounter10h
    ret

.globl mhpmcounter11h_r_csr
mhpmcounter11h_r_csr:
    csrr a0, mhpmcounter11h
    ret

.globl mhpmcounter12h_r_csr
mhpmcounter12h_r_csr:
    csrr a0, mhpmcounter12h
    ret

.globl mhpmcounter13h_r_csr
mhpmcounter13h_r_csr:
    csrr a0, mhpmcounter13h
    ret

.globl mhpmcounter14h_r_csr
mhpmcounter14h_r_csr:
    csrr a0, mhpmcounter14h
    ret

.globl mhpmcounter15h_r_csr
mhpmcounter15h_r_csr:
    csrr a0, mhpmcounter15h
    ret

.globl mhpmcounter16h_r_csr
mhpmcounter16h_r_csr:
    csrr a0, mhpmcounter16h
    ret

.globl mhpmcounter17h_r_csr
mhpmcounter17h_r_csr:
    csrr a0, mhpmcounter17h
    ret

.globl mhpmcounter18h_r_csr
mhpmcounter18h_r_csr:
    csrr a0, mhpmcounter18h
    ret

.globl mhpmcounter19h_r_csr
mhpmcounter19h_r_csr:
    csrr a0, mhpmcounter19h
    ret

.globl mhpmcounter20h_r_csr
mhpmcounter20h_r_csr:
    csrr a0, mhpmcounter20h
    ret

.globl mhpmcounter21h_r_csr
mhpmcounter21h_r_csr:
    csrr a0, mhpmcounter21h
    ret

.globl mhpmcounter22h_r_csr
mhpmcounter22h_r_csr:
    csrr a0, mhpmcounter22h
    ret

.globl mhpmcounter23h_r_csr
mhpmcounter23h_r_csr:
    csrr a0, mhpmcounter23h
    ret

.globl mhpmcounter24h_r_csr
mhpmcounter24h_r_csr:
    csrr a0, mhpmcounter24h
    ret

.globl mhpmcounter25h_r_csr
mhpmcounter25h_r_csr:
    csrr a0, mhpmcounter25h
    ret

.globl mhpmcounter26h_r_csr
mhpmcounter26h_r_csr:
    csrr a0, mhpmcounter26h
    ret

.globl mhpmcounter27h_r_csr
mhpmcounter27h_r_csr:
    csrr a0, mhpmcounter27h
    ret

.globl mhpmcounter28h_r_csr
mhpmcounter28h_r_csr:
    csrr a0, mhpmcounter28h
    ret

.globl mhpmcounter29h_r_csr
mhpmcounter29h_r_csr:
    csrr a0, mhpmcounter29h
    ret

.globl mhpmcounter30h_r_csr
mhpmcounter30h_r_csr:
    csrr a0, mhpmcounter30h
    ret

.globl mhpmcounter31h_r_csr
mhpmcounter31h_r_csr:
    csrr a0, mhpmcounter31h
    ret

.globl mhpmevent3_r_csr
mhpmevent3_r_csr:
    csrr a0, mhpmevent3
    ret

.globl mhpmevent4_r_csr
mhpmevent4_r_csr:
    csrr a0, mhpmevent4
    ret

.globl mhpmevent5_r_csr
mhpmevent5_r_csr:
    csrr a0, mhpmevent5
    ret

.globl mhpmevent6_r_csr
mhpmevent6_r_csr:
    csrr a0, mhpmevent6
    ret

.globl mhpmevent7_r_csr
mhpmevent7_r_csr:
    csrr a0, mhpmevent7
    ret

.globl mhpmevent8_r_csr
mhpmevent8_r_csr:
    csrr a0, mhpmevent8
    ret

.globl mhpmevent9_r_csr
mhpmevent9_r_csr:
    csrr a0, mhpmevent9
    ret

.globl mhpmevent10_r_csr
mhpmevent10_r_csr:
    csrr a0, mhpmevent10
    ret

.globl mhpmevent11_r_csr
mhpmevent11_r_csr:
    csrr a0, mhpmevent11
    ret

.globl mhpmevent12_r_csr
mhpmevent12_r_csr:
    csrr a0, mhpmevent12
    ret

.globl mhpmevent13_r_csr
mhpmevent13_r_csr:
    csrr a0, mhpmevent13
    ret

.globl mhpmevent14_r_csr
mhpmevent14_r_csr:
    csrr a0, mhpmevent14
    ret

.globl mhpmevent15_r_csr
mhpmevent15_r_csr:
    csrr a0, mhpmevent15
    ret

.globl mhpmevent16_r_csr
mhpmevent16_r_csr:
    csrr a0, mhpmevent16
    ret

.globl mhpmevent17_r_csr
mhpmevent17_r_csr:
    csrr a0, mhpmevent17
    ret

.globl mhpmevent18_r_csr
mhpmevent18_r_csr:
    csrr a0, mhpmevent18
    ret

.globl mhpmevent19_r_csr
mhpmevent19_r_csr:
    csrr a0, mhpmevent19
    ret

.globl mhpmevent20_r_csr
mhpmevent20_r_csr:
    csrr a0, mhpmevent20
    ret

.globl mhpmevent21_r_csr
mhpmevent21_r_csr:
    csrr a0, mhpmevent21
    ret

.globl mhpmevent22_r_csr
mhpmevent22_r_csr:
    csrr a0, mhpmevent22
    ret

.globl mhpmevent23_r_csr
mhpmevent23_r_csr:
    csrr a0, mhpmevent23
    ret

.globl mhpmevent24_r_csr
mhpmevent24_r_csr:
    csrr a0, mhpmevent24
    ret

.globl mhpmevent25_r_csr
mhpmevent25_r_csr:
    csrr a0, mhpmevent25
    ret

.globl mhpmevent26_r_csr
mhpmevent26_r_csr:
    csrr a0, mhpmevent26
    ret

.globl mhpmevent27_r_csr
mhpmevent27_r_csr:
    csrr a0, mhpmevent27
    ret

.globl mhpmevent28_r_csr
mhpmevent28_r_csr:
    csrr a0, mhpmevent28
    ret

.globl mhpmevent29_r_csr
mhpmevent29_r_csr:
    csrr a0, mhpmevent29
    ret

.globl mhpmevent30_r_csr
mhpmevent30_r_csr:
    csrr a0, mhpmevent30
    ret

.globl mhpmevent31_r_csr
mhpmevent31_r_csr:
    csrr a0, mhpmevent31
    ret

.globl tselect_r_csr
tselect_r_csr:
    csrr a0, tselect
    ret

.globl tdata1_r_csr
tdata1_r_csr:
    csrr a0, tdata1
    ret

.globl tdata2_r_csr
tdata2_r_csr:
    csrr a0, tdata2
    ret

.globl tdata3_r_csr
tdata3_r_csr:
    csrr a0, tdata3
    ret

.globl dcsr_r_csr
dcsr_r_csr:
    csrr a0, dcsr
    ret

.globl dpc_r_csr
dpc_r_csr:
    csrr a0, dpc
    ret

.globl dscratch_r_csr
dscratch_r_csr:
    csrr a0, dscratch
    ret
### CSR WRITES

.globl ustatus_w_csr
ustatus_w_csr:
    csrw ustatus, a0
    ret

.globl uie_w_csr
uie_w_csr:
    csrw uie, a0
    ret

.globl utvec_w_csr
utvec_w_csr:
    csrw utvec, a0
    ret

.globl uscratch_w_csr
uscratch_w_csr:
    csrw uscratch, a0
    ret

.globl uepc_w_csr
uepc_w_csr:
    csrw uepc, a0
    ret

.globl ucause_w_csr
ucause_w_csr:
    csrw ucause, a0
    ret

.globl utval_w_csr
utval_w_csr:
    csrw utval, a0
    ret

.globl uip_w_csr
uip_w_csr:
    csrw uip, a0
    ret

.globl fflags_w_csr
fflags_w_csr:
    csrw fflags, a0
    ret

.globl frm_w_csr
frm_w_csr:
    csrw frm, a0
    ret

.globl fcsr_w_csr
fcsr_w_csr:
    csrw fcsr, a0
    ret

.globl cycle_w_csr
cycle_w_csr:
    csrw cycle, a0
    ret

.globl time_w_csr
time_w_csr:
    csrw time, a0
    ret

.globl instret_w_csr
instret_w_csr:
    csrw instret, a0
    ret

.globl hpmcounter3_w_csr
hpmcounter3_w_csr:
    csrw hpmcounter3, a0
    ret

.globl hpmcounter4_w_csr
hpmcounter4_w_csr:
    csrw hpmcounter4, a0
    ret

.globl hpmcounter5_w_csr
hpmcounter5_w_csr:
    csrw hpmcounter5, a0
    ret

.globl hpmcounter6_w_csr
hpmcounter6_w_csr:
    csrw hpmcounter6, a0
    ret

.globl hpmcounter7_w_csr
hpmcounter7_w_csr:
    csrw hpmcounter7, a0
    ret

.globl hpmcounter8_w_csr
hpmcounter8_w_csr:
    csrw hpmcounter8, a0
    ret

.globl hpmcounter9_w_csr
hpmcounter9_w_csr:
    csrw hpmcounter9, a0
    ret

.globl hpmcounter10_w_csr
hpmcounter10_w_csr:
    csrw hpmcounter10, a0
    ret

.globl hpmcounter11_w_csr
hpmcounter11_w_csr:
    csrw hpmcounter11, a0
    ret

.globl hpmcounter12_w_csr
hpmcounter12_w_csr:
    csrw hpmcounter12, a0
    ret

.globl hpmcounter13_w_csr
hpmcounter13_w_csr:
    csrw hpmcounter13, a0
    ret

.globl hpmcounter14_w_csr
hpmcounter14_w_csr:
    csrw hpmcounter14, a0
    ret

.globl hpmcounter15_w_csr
hpmcounter15_w_csr:
    csrw hpmcounter15, a0
    ret

.globl hpmcounter16_w_csr
hpmcounter16_w_csr:
    csrw hpmcounter16, a0
    ret

.globl hpmcounter17_w_csr
hpmcounter17_w_csr:
    csrw hpmcounter17, a0
    ret

.globl hpmcounter18_w_csr
hpmcounter18_w_csr:
    csrw hpmcounter18, a0
    ret

.globl hpmcounter19_w_csr
hpmcounter19_w_csr:
    csrw hpmcounter19, a0
    ret

.globl hpmcounter20_w_csr
hpmcounter20_w_csr:
    csrw hpmcounter20, a0
    ret

.globl hpmcounter21_w_csr
hpmcounter21_w_csr:
    csrw hpmcounter21, a0
    ret

.globl hpmcounter22_w_csr
hpmcounter22_w_csr:
    csrw hpmcounter22, a0
    ret

.globl hpmcounter23_w_csr
hpmcounter23_w_csr:
    csrw hpmcounter23, a0
    ret

.globl hpmcounter24_w_csr
hpmcounter24_w_csr:
    csrw hpmcounter24, a0
    ret

.globl hpmcounter25_w_csr
hpmcounter25_w_csr:
    csrw hpmcounter25, a0
    ret

.globl hpmcounter26_w_csr
hpmcounter26_w_csr:
    csrw hpmcounter26, a0
    ret

.globl hpmcounter27_w_csr
hpmcounter27_w_csr:
    csrw hpmcounter27, a0
    ret

.globl hpmcounter28_w_csr
hpmcounter28_w_csr:
    csrw hpmcounter28, a0
    ret

.globl hpmcounter29_w_csr
hpmcounter29_w_csr:
    csrw hpmcounter29, a0
    ret

.globl hpmcounter30_w_csr
hpmcounter30_w_csr:
    csrw hpmcounter30, a0
    ret

.globl hpmcounter31_w_csr
hpmcounter31_w_csr:
    csrw hpmcounter31, a0
    ret

.globl cycleh_w_csr
cycleh_w_csr:
    csrw cycleh, a0
    ret

.globl timeh_w_csr
timeh_w_csr:
    csrw timeh, a0
    ret

.globl instreth_w_csr
instreth_w_csr:
    csrw instreth, a0
    ret

.globl hpmcounter3h_w_csr
hpmcounter3h_w_csr:
    csrw hpmcounter3h, a0
    ret

.globl hpmcounter4h_w_csr
hpmcounter4h_w_csr:
    csrw hpmcounter4h, a0
    ret

.globl hpmcounter5h_w_csr
hpmcounter5h_w_csr:
    csrw hpmcounter5h, a0
    ret

.globl hpmcounter6h_w_csr
hpmcounter6h_w_csr:
    csrw hpmcounter6h, a0
    ret

.globl hpmcounter7h_w_csr
hpmcounter7h_w_csr:
    csrw hpmcounter7h, a0
    ret

.globl hpmcounter8h_w_csr
hpmcounter8h_w_csr:
    csrw hpmcounter8h, a0
    ret

.globl hpmcounter9h_w_csr
hpmcounter9h_w_csr:
    csrw hpmcounter9h, a0
    ret

.globl hpmcounter10h_w_csr
hpmcounter10h_w_csr:
    csrw hpmcounter10h, a0
    ret

.globl hpmcounter11h_w_csr
hpmcounter11h_w_csr:
    csrw hpmcounter11h, a0
    ret

.globl hpmcounter12h_w_csr
hpmcounter12h_w_csr:
    csrw hpmcounter12h, a0
    ret

.globl hpmcounter13h_w_csr
hpmcounter13h_w_csr:
    csrw hpmcounter13h, a0
    ret

.globl hpmcounter14h_w_csr
hpmcounter14h_w_csr:
    csrw hpmcounter14h, a0
    ret

.globl hpmcounter15h_w_csr
hpmcounter15h_w_csr:
    csrw hpmcounter15h, a0
    ret

.globl hpmcounter16h_w_csr
hpmcounter16h_w_csr:
    csrw hpmcounter16h, a0
    ret

.globl hpmcounter17h_w_csr
hpmcounter17h_w_csr:
    csrw hpmcounter17h, a0
    ret

.globl hpmcounter18h_w_csr
hpmcounter18h_w_csr:
    csrw hpmcounter18h, a0
    ret

.globl hpmcounter19h_w_csr
hpmcounter19h_w_csr:
    csrw hpmcounter19h, a0
    ret

.globl hpmcounter20h_w_csr
hpmcounter20h_w_csr:
    csrw hpmcounter20h, a0
    ret

.globl hpmcounter21h_w_csr
hpmcounter21h_w_csr:
    csrw hpmcounter21h, a0
    ret

.globl hpmcounter22h_w_csr
hpmcounter22h_w_csr:
    csrw hpmcounter22h, a0
    ret

.globl hpmcounter23h_w_csr
hpmcounter23h_w_csr:
    csrw hpmcounter23h, a0
    ret

.globl hpmcounter24h_w_csr
hpmcounter24h_w_csr:
    csrw hpmcounter24h, a0
    ret

.globl hpmcounter25h_w_csr
hpmcounter25h_w_csr:
    csrw hpmcounter25h, a0
    ret

.globl hpmcounter26h_w_csr
hpmcounter26h_w_csr:
    csrw hpmcounter26h, a0
    ret

.globl hpmcounter27h_w_csr
hpmcounter27h_w_csr:
    csrw hpmcounter27h, a0
    ret

.globl hpmcounter28h_w_csr
hpmcounter28h_w_csr:
    csrw hpmcounter28h, a0
    ret

.globl hpmcounter29h_w_csr
hpmcounter29h_w_csr:
    csrw hpmcounter29h, a0
    ret

.globl hpmcounter30h_w_csr
hpmcounter30h_w_csr:
    csrw hpmcounter30h, a0
    ret

.globl hpmcounter31h_w_csr
hpmcounter31h_w_csr:
    csrw hpmcounter31h, a0
    ret

.globl sstatus_w_csr
sstatus_w_csr:
    csrw sstatus, a0
    ret

.globl sedeleg_w_csr
sedeleg_w_csr:
    csrw sedeleg, a0
    ret

.globl sideleg_w_csr
sideleg_w_csr:
    csrw sideleg, a0
    ret

.globl sie_w_csr
sie_w_csr:
    csrw sie, a0
    ret

.globl stvec_w_csr
stvec_w_csr:
    csrw stvec, a0
    ret

.globl scounteren_w_csr
scounteren_w_csr:
    csrw scounteren, a0
    ret

.globl sscratch_w_csr
sscratch_w_csr:
    csrw sscratch, a0
    ret

.globl sepc_w_csr
sepc_w_csr:
    csrw sepc, a0
    ret

.globl scause_w_csr
scause_w_csr:
    csrw scause, a0
    ret

.globl sbadaddr_w_csr
sbadaddr_w_csr:
    csrw sbadaddr, a0
    ret

.globl sip_w_csr
sip_w_csr:
    csrw sip, a0
    ret

.globl satp_w_csr
satp_w_csr:
    csrw satp, a0
    ret

.globl mvendorid_w_csr
mvendorid_w_csr:
    csrw mvendorid, a0
    ret

.globl marchid_w_csr
marchid_w_csr:
    csrw marchid, a0
    ret

.globl mimpid_w_csr
mimpid_w_csr:
    csrw mimpid, a0
    ret

.globl mhartid_w_csr
mhartid_w_csr:
    csrw mhartid, a0
    ret

.globl mstatus_w_csr
mstatus_w_csr:
    csrw mstatus, a0
    ret

.globl misa_w_csr
misa_w_csr:
    csrw misa, a0
    ret

.globl medeleg_w_csr
medeleg_w_csr:
    csrw medeleg, a0
    ret

.globl mideleg_w_csr
mideleg_w_csr:
    csrw mideleg, a0
    ret

.globl mie_w_csr
mie_w_csr:
    csrw mie, a0
    ret

.globl mtvec_w_csr
mtvec_w_csr:
    csrw mtvec, a0
    ret

.globl mcounteren_w_csr
mcounteren_w_csr:
    csrw mcounteren, a0
    ret

.globl mscratch_w_csr
mscratch_w_csr:
    csrw mscratch, a0
    ret

.globl mepc_w_csr
mepc_w_csr:
    csrw mepc, a0
    ret

.globl mcause_w_csr
mcause_w_csr:
    csrw mcause, a0
    ret

.globl mbadaddr_w_csr
mbadaddr_w_csr:
    csrw mbadaddr, a0
    ret

.globl mip_w_csr
mip_w_csr:
    csrw mip, a0
    ret

.globl pmpcfg0_w_csr
pmpcfg0_w_csr:
    csrw pmpcfg0, a0
    ret

.globl pmpcfg1_w_csr
pmpcfg1_w_csr:
    csrw pmpcfg1, a0
    ret

.globl pmpcfg2_w_csr
pmpcfg2_w_csr:
    csrw pmpcfg2, a0
    ret

.globl pmpcfg3_w_csr
pmpcfg3_w_csr:
    csrw pmpcfg3, a0
    ret

.globl pmpaddr0_w_csr
pmpaddr0_w_csr:
    csrw pmpaddr0, a0
    ret

.globl pmpaddr1_w_csr
pmpaddr1_w_csr:
    csrw pmpaddr1, a0
    ret

.globl pmpaddr2_w_csr
pmpaddr2_w_csr:
    csrw pmpaddr2, a0
    ret

.globl pmpaddr3_w_csr
pmpaddr3_w_csr:
    csrw pmpaddr3, a0
    ret

.globl pmpaddr4_w_csr
pmpaddr4_w_csr:
    csrw pmpaddr4, a0
    ret

.globl pmpaddr5_w_csr
pmpaddr5_w_csr:
    csrw pmpaddr5, a0
    ret

.globl pmpaddr6_w_csr
pmpaddr6_w_csr:
    csrw pmpaddr6, a0
    ret

.globl pmpaddr7_w_csr
pmpaddr7_w_csr:
    csrw pmpaddr7, a0
    ret

.globl pmpaddr8_w_csr
pmpaddr8_w_csr:
    csrw pmpaddr8, a0
    ret

.globl pmpaddr9_w_csr
pmpaddr9_w_csr:
    csrw pmpaddr9, a0
    ret

.globl pmpaddr10_w_csr
pmpaddr10_w_csr:
    csrw pmpaddr10, a0
    ret

.globl pmpaddr11_w_csr
pmpaddr11_w_csr:
    csrw pmpaddr11, a0
    ret

.globl pmpaddr12_w_csr
pmpaddr12_w_csr:
    csrw pmpaddr12, a0
    ret

.globl pmpaddr13_w_csr
pmpaddr13_w_csr:
    csrw pmpaddr13, a0
    ret

.globl pmpaddr14_w_csr
pmpaddr14_w_csr:
    csrw pmpaddr14, a0
    ret

.globl pmpaddr15_w_csr
pmpaddr15_w_csr:
    csrw pmpaddr15, a0
    ret

.globl mcycle_w_csr
mcycle_w_csr:
    csrw mcycle, a0
    ret

.globl minstret_w_csr
minstret_w_csr:
    csrw minstret, a0
    ret

.globl mhpmcounter3_w_csr
mhpmcounter3_w_csr:
    csrw mhpmcounter3, a0
    ret

.globl mhpmcounter4_w_csr
mhpmcounter4_w_csr:
    csrw mhpmcounter4, a0
    ret

.globl mhpmcounter5_w_csr
mhpmcounter5_w_csr:
    csrw mhpmcounter5, a0
    ret

.globl mhpmcounter6_w_csr
mhpmcounter6_w_csr:
    csrw mhpmcounter6, a0
    ret

.globl mhpmcounter7_w_csr
mhpmcounter7_w_csr:
    csrw mhpmcounter7, a0
    ret

.globl mhpmcounter8_w_csr
mhpmcounter8_w_csr:
    csrw mhpmcounter8, a0
    ret

.globl mhpmcounter9_w_csr
mhpmcounter9_w_csr:
    csrw mhpmcounter9, a0
    ret

.globl mhpmcounter10_w_csr
mhpmcounter10_w_csr:
    csrw mhpmcounter10, a0
    ret

.globl mhpmcounter11_w_csr
mhpmcounter11_w_csr:
    csrw mhpmcounter11, a0
    ret

.globl mhpmcounter12_w_csr
mhpmcounter12_w_csr:
    csrw mhpmcounter12, a0
    ret

.globl mhpmcounter13_w_csr
mhpmcounter13_w_csr:
    csrw mhpmcounter13, a0
    ret

.globl mhpmcounter14_w_csr
mhpmcounter14_w_csr:
    csrw mhpmcounter14, a0
    ret

.globl mhpmcounter15_w_csr
mhpmcounter15_w_csr:
    csrw mhpmcounter15, a0
    ret

.globl mhpmcounter16_w_csr
mhpmcounter16_w_csr:
    csrw mhpmcounter16, a0
    ret

.globl mhpmcounter17_w_csr
mhpmcounter17_w_csr:
    csrw mhpmcounter17, a0
    ret

.globl mhpmcounter18_w_csr
mhpmcounter18_w_csr:
    csrw mhpmcounter18, a0
    ret

.globl mhpmcounter19_w_csr
mhpmcounter19_w_csr:
    csrw mhpmcounter19, a0
    ret

.globl mhpmcounter20_w_csr
mhpmcounter20_w_csr:
    csrw mhpmcounter20, a0
    ret

.globl mhpmcounter21_w_csr
mhpmcounter21_w_csr:
    csrw mhpmcounter21, a0
    ret

.globl mhpmcounter22_w_csr
mhpmcounter22_w_csr:
    csrw mhpmcounter22, a0
    ret

.globl mhpmcounter23_w_csr
mhpmcounter23_w_csr:
    csrw mhpmcounter23, a0
    ret

.globl mhpmcounter24_w_csr
mhpmcounter24_w_csr:
    csrw mhpmcounter24, a0
    ret

.globl mhpmcounter25_w_csr
mhpmcounter25_w_csr:
    csrw mhpmcounter25, a0
    ret

.globl mhpmcounter26_w_csr
mhpmcounter26_w_csr:
    csrw mhpmcounter26, a0
    ret

.globl mhpmcounter27_w_csr
mhpmcounter27_w_csr:
    csrw mhpmcounter27, a0
    ret

.globl mhpmcounter28_w_csr
mhpmcounter28_w_csr:
    csrw mhpmcounter28, a0
    ret

.globl mhpmcounter29_w_csr
mhpmcounter29_w_csr:
    csrw mhpmcounter29, a0
    ret

.globl mhpmcounter30_w_csr
mhpmcounter30_w_csr:
    csrw mhpmcounter30, a0
    ret

.globl mhpmcounter31_w_csr
mhpmcounter31_w_csr:
    csrw mhpmcounter31, a0
    ret

.globl mcycleh_w_csr
mcycleh_w_csr:
    csrw mcycleh, a0
    ret

.globl minstreth_w_csr
minstreth_w_csr:
    csrw minstreth, a0
    ret

.globl mhpmcounter3h_w_csr
mhpmcounter3h_w_csr:
    csrw mhpmcounter3h, a0
    ret

.globl mhpmcounter4h_w_csr
mhpmcounter4h_w_csr:
    csrw mhpmcounter4h, a0
    ret

.globl mhpmcounter5h_w_csr
mhpmcounter5h_w_csr:
    csrw mhpmcounter5h, a0
    ret

.globl mhpmcounter6h_w_csr
mhpmcounter6h_w_csr:
    csrw mhpmcounter6h, a0
    ret

.globl mhpmcounter7h_w_csr
mhpmcounter7h_w_csr:
    csrw mhpmcounter7h, a0
    ret

.globl mhpmcounter8h_w_csr
mhpmcounter8h_w_csr:
    csrw mhpmcounter8h, a0
    ret

.globl mhpmcounter9h_w_csr
mhpmcounter9h_w_csr:
    csrw mhpmcounter9h, a0
    ret

.globl mhpmcounter10h_w_csr
mhpmcounter10h_w_csr:
    csrw mhpmcounter10h, a0
    ret

.globl mhpmcounter11h_w_csr
mhpmcounter11h_w_csr:
    csrw mhpmcounter11h, a0
    ret

.globl mhpmcounter12h_w_csr
mhpmcounter12h_w_csr:
    csrw mhpmcounter12h, a0
    ret

.globl mhpmcounter13h_w_csr
mhpmcounter13h_w_csr:
    csrw mhpmcounter13h, a0
    ret

.globl mhpmcounter14h_w_csr
mhpmcounter14h_w_csr:
    csrw mhpmcounter14h, a0
    ret

.globl mhpmcounter15h_w_csr
mhpmcounter15h_w_csr:
    csrw mhpmcounter15h, a0
    ret

.globl mhpmcounter16h_w_csr
mhpmcounter16h_w_csr:
    csrw mhpmcounter16h, a0
    ret

.globl mhpmcounter17h_w_csr
mhpmcounter17h_w_csr:
    csrw mhpmcounter17h, a0
    ret

.globl mhpmcounter18h_w_csr
mhpmcounter18h_w_csr:
    csrw mhpmcounter18h, a0
    ret

.globl mhpmcounter19h_w_csr
mhpmcounter19h_w_csr:
    csrw mhpmcounter19h, a0
    ret

.globl mhpmcounter20h_w_csr
mhpmcounter20h_w_csr:
    csrw mhpmcounter20h, a0
    ret

.globl mhpmcounter21h_w_csr
mhpmcounter21h_w_csr:
    csrw mhpmcounter21h, a0
    ret

.globl mhpmcounter22h_w_csr
mhpmcounter22h_w_csr:
    csrw mhpmcounter22h, a0
    ret

.globl mhpmcounter23h_w_csr
mhpmcounter23h_w_csr:
    csrw mhpmcounter23h, a0
    ret

.globl mhpmcounter24h_w_csr
mhpmcounter24h_w_csr:
    csrw mhpmcounter24h, a0
    ret

.globl mhpmcounter25h_w_csr
mhpmcounter25h_w_csr:
    csrw mhpmcounter25h, a0
    ret

.globl mhpmcounter26h_w_csr
mhpmcounter26h_w_csr:
    csrw mhpmcounter26h, a0
    ret

.globl mhpmcounter27h_w_csr
mhpmcounter27h_w_csr:
    csrw mhpmcounter27h, a0
    ret

.globl mhpmcounter28h_w_csr
mhpmcounter28h_w_csr:
    csrw mhpmcounter28h, a0
    ret

.globl mhpmcounter29h_w_csr
mhpmcounter29h_w_csr:
    csrw mhpmcounter29h, a0
    ret

.globl mhpmcounter30h_w_csr
mhpmcounter30h_w_csr:
    csrw mhpmcounter30h, a0
    ret

.globl mhpmcounter31h_w_csr
mhpmcounter31h_w_csr:
    csrw mhpmcounter31h, a0
    ret

.globl mhpmevent3_w_csr
mhpmevent3_w_csr:
    csrw mhpmevent3, a0
    ret

.globl mhpmevent4_w_csr
mhpmevent4_w_csr:
    csrw mhpmevent4, a0
    ret

.globl mhpmevent5_w_csr
mhpmevent5_w_csr:
    csrw mhpmevent5, a0
    ret

.globl mhpmevent6_w_csr
mhpmevent6_w_csr:
    csrw mhpmevent6, a0
    ret

.globl mhpmevent7_w_csr
mhpmevent7_w_csr:
    csrw mhpmevent7, a0
    ret

.globl mhpmevent8_w_csr
mhpmevent8_w_csr:
    csrw mhpmevent8, a0
    ret

.globl mhpmevent9_w_csr
mhpmevent9_w_csr:
    csrw mhpmevent9, a0
    ret

.globl mhpmevent10_w_csr
mhpmevent10_w_csr:
    csrw mhpmevent10, a0
    ret

.globl mhpmevent11_w_csr
mhpmevent11_w_csr:
    csrw mhpmevent11, a0
    ret

.globl mhpmevent12_w_csr
mhpmevent12_w_csr:
    csrw mhpmevent12, a0
    ret

.globl mhpmevent13_w_csr
mhpmevent13_w_csr:
    csrw mhpmevent13, a0
    ret

.globl mhpmevent14_w_csr
mhpmevent14_w_csr:
    csrw mhpmevent14, a0
    ret

.globl mhpmevent15_w_csr
mhpmevent15_w_csr:
    csrw mhpmevent15, a0
    ret

.globl mhpmevent16_w_csr
mhpmevent16_w_csr:
    csrw mhpmevent16, a0
    ret

.globl mhpmevent17_w_csr
mhpmevent17_w_csr:
    csrw mhpmevent17, a0
    ret

.globl mhpmevent18_w_csr
mhpmevent18_w_csr:
    csrw mhpmevent18, a0
    ret

.globl mhpmevent19_w_csr
mhpmevent19_w_csr:
    csrw mhpmevent19, a0
    ret

.globl mhpmevent20_w_csr
mhpmevent20_w_csr:
    csrw mhpmevent20, a0
    ret

.globl mhpmevent21_w_csr
mhpmevent21_w_csr:
    csrw mhpmevent21, a0
    ret

.globl mhpmevent22_w_csr
mhpmevent22_w_csr:
    csrw mhpmevent22, a0
    ret

.globl mhpmevent23_w_csr
mhpmevent23_w_csr:
    csrw mhpmevent23, a0
    ret

.globl mhpmevent24_w_csr
mhpmevent24_w_csr:
    csrw mhpmevent24, a0
    ret

.globl mhpmevent25_w_csr
mhpmevent25_w_csr:
    csrw mhpmevent25, a0
    ret

.globl mhpmevent26_w_csr
mhpmevent26_w_csr:
    csrw mhpmevent26, a0
    ret

.globl mhpmevent27_w_csr
mhpmevent27_w_csr:
    csrw mhpmevent27, a0
    ret

.globl mhpmevent28_w_csr
mhpmevent28_w_csr:
    csrw mhpmevent28, a0
    ret

.globl mhpmevent29_w_csr
mhpmevent29_w_csr:
    csrw mhpmevent29, a0
    ret

.globl mhpmevent30_w_csr
mhpmevent30_w_csr:
    csrw mhpmevent30, a0
    ret

.globl mhpmevent31_w_csr
mhpmevent31_w_csr:
    csrw mhpmevent31, a0
    ret

.globl tselect_w_csr
tselect_w_csr:
    csrw tselect, a0
    ret

.globl tdata1_w_csr
tdata1_w_csr:
    csrw tdata1, a0
    ret

.globl tdata2_w_csr
tdata2_w_csr:
    csrw tdata2, a0
    ret

.globl tdata3_w_csr
tdata3_w_csr:
    csrw tdata3, a0
    ret

.globl dcsr_w_csr
dcsr_w_csr:
    csrw dcsr, a0
    ret

.globl dpc_w_csr
dpc_w_csr:
    csrw dpc, a0
    ret

.globl dscratch_w_csr
dscratch_w_csr:
    csrw dscratch, a0
    ret
### CSR SETS

.globl ustatus_s_csr
ustatus_s_csr:
    csrs ustatus, a0
    ret

.globl uie_s_csr
uie_s_csr:
    csrs uie, a0
    ret

.globl utvec_s_csr
utvec_s_csr:
    csrs utvec, a0
    ret

.globl uscratch_s_csr
uscratch_s_csr:
    csrs uscratch, a0
    ret

.globl uepc_s_csr
uepc_s_csr:
    csrs uepc, a0
    ret

.globl ucause_s_csr
ucause_s_csr:
    csrs ucause, a0
    ret

.globl utval_s_csr
utval_s_csr:
    csrs utval, a0
    ret

.globl uip_s_csr
uip_s_csr:
    csrs uip, a0
    ret

.globl fflags_s_csr
fflags_s_csr:
    csrs fflags, a0
    ret

.globl frm_s_csr
frm_s_csr:
    csrs frm, a0
    ret

.globl fcsr_s_csr
fcsr_s_csr:
    csrs fcsr, a0
    ret

.globl cycle_s_csr
cycle_s_csr:
    csrs cycle, a0
    ret

.globl time_s_csr
time_s_csr:
    csrs time, a0
    ret

.globl instret_s_csr
instret_s_csr:
    csrs instret, a0
    ret

.globl hpmcounter3_s_csr
hpmcounter3_s_csr:
    csrs hpmcounter3, a0
    ret

.globl hpmcounter4_s_csr
hpmcounter4_s_csr:
    csrs hpmcounter4, a0
    ret

.globl hpmcounter5_s_csr
hpmcounter5_s_csr:
    csrs hpmcounter5, a0
    ret

.globl hpmcounter6_s_csr
hpmcounter6_s_csr:
    csrs hpmcounter6, a0
    ret

.globl hpmcounter7_s_csr
hpmcounter7_s_csr:
    csrs hpmcounter7, a0
    ret

.globl hpmcounter8_s_csr
hpmcounter8_s_csr:
    csrs hpmcounter8, a0
    ret

.globl hpmcounter9_s_csr
hpmcounter9_s_csr:
    csrs hpmcounter9, a0
    ret

.globl hpmcounter10_s_csr
hpmcounter10_s_csr:
    csrs hpmcounter10, a0
    ret

.globl hpmcounter11_s_csr
hpmcounter11_s_csr:
    csrs hpmcounter11, a0
    ret

.globl hpmcounter12_s_csr
hpmcounter12_s_csr:
    csrs hpmcounter12, a0
    ret

.globl hpmcounter13_s_csr
hpmcounter13_s_csr:
    csrs hpmcounter13, a0
    ret

.globl hpmcounter14_s_csr
hpmcounter14_s_csr:
    csrs hpmcounter14, a0
    ret

.globl hpmcounter15_s_csr
hpmcounter15_s_csr:
    csrs hpmcounter15, a0
    ret

.globl hpmcounter16_s_csr
hpmcounter16_s_csr:
    csrs hpmcounter16, a0
    ret

.globl hpmcounter17_s_csr
hpmcounter17_s_csr:
    csrs hpmcounter17, a0
    ret

.globl hpmcounter18_s_csr
hpmcounter18_s_csr:
    csrs hpmcounter18, a0
    ret

.globl hpmcounter19_s_csr
hpmcounter19_s_csr:
    csrs hpmcounter19, a0
    ret

.globl hpmcounter20_s_csr
hpmcounter20_s_csr:
    csrs hpmcounter20, a0
    ret

.globl hpmcounter21_s_csr
hpmcounter21_s_csr:
    csrs hpmcounter21, a0
    ret

.globl hpmcounter22_s_csr
hpmcounter22_s_csr:
    csrs hpmcounter22, a0
    ret

.globl hpmcounter23_s_csr
hpmcounter23_s_csr:
    csrs hpmcounter23, a0
    ret

.globl hpmcounter24_s_csr
hpmcounter24_s_csr:
    csrs hpmcounter24, a0
    ret

.globl hpmcounter25_s_csr
hpmcounter25_s_csr:
    csrs hpmcounter25, a0
    ret

.globl hpmcounter26_s_csr
hpmcounter26_s_csr:
    csrs hpmcounter26, a0
    ret

.globl hpmcounter27_s_csr
hpmcounter27_s_csr:
    csrs hpmcounter27, a0
    ret

.globl hpmcounter28_s_csr
hpmcounter28_s_csr:
    csrs hpmcounter28, a0
    ret

.globl hpmcounter29_s_csr
hpmcounter29_s_csr:
    csrs hpmcounter29, a0
    ret

.globl hpmcounter30_s_csr
hpmcounter30_s_csr:
    csrs hpmcounter30, a0
    ret

.globl hpmcounter31_s_csr
hpmcounter31_s_csr:
    csrs hpmcounter31, a0
    ret

.globl cycleh_s_csr
cycleh_s_csr:
    csrs cycleh, a0
    ret

.globl timeh_s_csr
timeh_s_csr:
    csrs timeh, a0
    ret

.globl instreth_s_csr
instreth_s_csr:
    csrs instreth, a0
    ret

.globl hpmcounter3h_s_csr
hpmcounter3h_s_csr:
    csrs hpmcounter3h, a0
    ret

.globl hpmcounter4h_s_csr
hpmcounter4h_s_csr:
    csrs hpmcounter4h, a0
    ret

.globl hpmcounter5h_s_csr
hpmcounter5h_s_csr:
    csrs hpmcounter5h, a0
    ret

.globl hpmcounter6h_s_csr
hpmcounter6h_s_csr:
    csrs hpmcounter6h, a0
    ret

.globl hpmcounter7h_s_csr
hpmcounter7h_s_csr:
    csrs hpmcounter7h, a0
    ret

.globl hpmcounter8h_s_csr
hpmcounter8h_s_csr:
    csrs hpmcounter8h, a0
    ret

.globl hpmcounter9h_s_csr
hpmcounter9h_s_csr:
    csrs hpmcounter9h, a0
    ret

.globl hpmcounter10h_s_csr
hpmcounter10h_s_csr:
    csrs hpmcounter10h, a0
    ret

.globl hpmcounter11h_s_csr
hpmcounter11h_s_csr:
    csrs hpmcounter11h, a0
    ret

.globl hpmcounter12h_s_csr
hpmcounter12h_s_csr:
    csrs hpmcounter12h, a0
    ret

.globl hpmcounter13h_s_csr
hpmcounter13h_s_csr:
    csrs hpmcounter13h, a0
    ret

.globl hpmcounter14h_s_csr
hpmcounter14h_s_csr:
    csrs hpmcounter14h, a0
    ret

.globl hpmcounter15h_s_csr
hpmcounter15h_s_csr:
    csrs hpmcounter15h, a0
    ret

.globl hpmcounter16h_s_csr
hpmcounter16h_s_csr:
    csrs hpmcounter16h, a0
    ret

.globl hpmcounter17h_s_csr
hpmcounter17h_s_csr:
    csrs hpmcounter17h, a0
    ret

.globl hpmcounter18h_s_csr
hpmcounter18h_s_csr:
    csrs hpmcounter18h, a0
    ret

.globl hpmcounter19h_s_csr
hpmcounter19h_s_csr:
    csrs hpmcounter19h, a0
    ret

.globl hpmcounter20h_s_csr
hpmcounter20h_s_csr:
    csrs hpmcounter20h, a0
    ret

.globl hpmcounter21h_s_csr
hpmcounter21h_s_csr:
    csrs hpmcounter21h, a0
    ret

.globl hpmcounter22h_s_csr
hpmcounter22h_s_csr:
    csrs hpmcounter22h, a0
    ret

.globl hpmcounter23h_s_csr
hpmcounter23h_s_csr:
    csrs hpmcounter23h, a0
    ret

.globl hpmcounter24h_s_csr
hpmcounter24h_s_csr:
    csrs hpmcounter24h, a0
    ret

.globl hpmcounter25h_s_csr
hpmcounter25h_s_csr:
    csrs hpmcounter25h, a0
    ret

.globl hpmcounter26h_s_csr
hpmcounter26h_s_csr:
    csrs hpmcounter26h, a0
    ret

.globl hpmcounter27h_s_csr
hpmcounter27h_s_csr:
    csrs hpmcounter27h, a0
    ret

.globl hpmcounter28h_s_csr
hpmcounter28h_s_csr:
    csrs hpmcounter28h, a0
    ret

.globl hpmcounter29h_s_csr
hpmcounter29h_s_csr:
    csrs hpmcounter29h, a0
    ret

.globl hpmcounter30h_s_csr
hpmcounter30h_s_csr:
    csrs hpmcounter30h, a0
    ret

.globl hpmcounter31h_s_csr
hpmcounter31h_s_csr:
    csrs hpmcounter31h, a0
    ret

.globl sstatus_s_csr
sstatus_s_csr:
    csrs sstatus, a0
    ret

.globl sedeleg_s_csr
sedeleg_s_csr:
    csrs sedeleg, a0
    ret

.globl sideleg_s_csr
sideleg_s_csr:
    csrs sideleg, a0
    ret

.globl sie_s_csr
sie_s_csr:
    csrs sie, a0
    ret

.globl stvec_s_csr
stvec_s_csr:
    csrs stvec, a0
    ret

.globl scounteren_s_csr
scounteren_s_csr:
    csrs scounteren, a0
    ret

.globl sscratch_s_csr
sscratch_s_csr:
    csrs sscratch, a0
    ret

.globl sepc_s_csr
sepc_s_csr:
    csrs sepc, a0
    ret

.globl scause_s_csr
scause_s_csr:
    csrs scause, a0
    ret

.globl sbadaddr_s_csr
sbadaddr_s_csr:
    csrs sbadaddr, a0
    ret

.globl sip_s_csr
sip_s_csr:
    csrs sip, a0
    ret

.globl satp_s_csr
satp_s_csr:
    csrs satp, a0
    ret

.globl mvendorid_s_csr
mvendorid_s_csr:
    csrs mvendorid, a0
    ret

.globl marchid_s_csr
marchid_s_csr:
    csrs marchid, a0
    ret

.globl mimpid_s_csr
mimpid_s_csr:
    csrs mimpid, a0
    ret

.globl mhartid_s_csr
mhartid_s_csr:
    csrs mhartid, a0
    ret

.globl mstatus_s_csr
mstatus_s_csr:
    csrs mstatus, a0
    ret

.globl misa_s_csr
misa_s_csr:
    csrs misa, a0
    ret

.globl medeleg_s_csr
medeleg_s_csr:
    csrs medeleg, a0
    ret

.globl mideleg_s_csr
mideleg_s_csr:
    csrs mideleg, a0
    ret

.globl mie_s_csr
mie_s_csr:
    csrs mie, a0
    ret

.globl mtvec_s_csr
mtvec_s_csr:
    csrs mtvec, a0
    ret

.globl mcounteren_s_csr
mcounteren_s_csr:
    csrs mcounteren, a0
    ret

.globl mscratch_s_csr
mscratch_s_csr:
    csrs mscratch, a0
    ret

.globl mepc_s_csr
mepc_s_csr:
    csrs mepc, a0
    ret

.globl mcause_s_csr
mcause_s_csr:
    csrs mcause, a0
    ret

.globl mbadaddr_s_csr
mbadaddr_s_csr:
    csrs mbadaddr, a0
    ret

.globl mip_s_csr
mip_s_csr:
    csrs mip, a0
    ret

.globl pmpcfg0_s_csr
pmpcfg0_s_csr:
    csrs pmpcfg0, a0
    ret

.globl pmpcfg1_s_csr
pmpcfg1_s_csr:
    csrs pmpcfg1, a0
    ret

.globl pmpcfg2_s_csr
pmpcfg2_s_csr:
    csrs pmpcfg2, a0
    ret

.globl pmpcfg3_s_csr
pmpcfg3_s_csr:
    csrs pmpcfg3, a0
    ret

.globl pmpaddr0_s_csr
pmpaddr0_s_csr:
    csrs pmpaddr0, a0
    ret

.globl pmpaddr1_s_csr
pmpaddr1_s_csr:
    csrs pmpaddr1, a0
    ret

.globl pmpaddr2_s_csr
pmpaddr2_s_csr:
    csrs pmpaddr2, a0
    ret

.globl pmpaddr3_s_csr
pmpaddr3_s_csr:
    csrs pmpaddr3, a0
    ret

.globl pmpaddr4_s_csr
pmpaddr4_s_csr:
    csrs pmpaddr4, a0
    ret

.globl pmpaddr5_s_csr
pmpaddr5_s_csr:
    csrs pmpaddr5, a0
    ret

.globl pmpaddr6_s_csr
pmpaddr6_s_csr:
    csrs pmpaddr6, a0
    ret

.globl pmpaddr7_s_csr
pmpaddr7_s_csr:
    csrs pmpaddr7, a0
    ret

.globl pmpaddr8_s_csr
pmpaddr8_s_csr:
    csrs pmpaddr8, a0
    ret

.globl pmpaddr9_s_csr
pmpaddr9_s_csr:
    csrs pmpaddr9, a0
    ret

.globl pmpaddr10_s_csr
pmpaddr10_s_csr:
    csrs pmpaddr10, a0
    ret

.globl pmpaddr11_s_csr
pmpaddr11_s_csr:
    csrs pmpaddr11, a0
    ret

.globl pmpaddr12_s_csr
pmpaddr12_s_csr:
    csrs pmpaddr12, a0
    ret

.globl pmpaddr13_s_csr
pmpaddr13_s_csr:
    csrs pmpaddr13, a0
    ret

.globl pmpaddr14_s_csr
pmpaddr14_s_csr:
    csrs pmpaddr14, a0
    ret

.globl pmpaddr15_s_csr
pmpaddr15_s_csr:
    csrs pmpaddr15, a0
    ret

.globl mcycle_s_csr
mcycle_s_csr:
    csrs mcycle, a0
    ret

.globl minstret_s_csr
minstret_s_csr:
    csrs minstret, a0
    ret

.globl mhpmcounter3_s_csr
mhpmcounter3_s_csr:
    csrs mhpmcounter3, a0
    ret

.globl mhpmcounter4_s_csr
mhpmcounter4_s_csr:
    csrs mhpmcounter4, a0
    ret

.globl mhpmcounter5_s_csr
mhpmcounter5_s_csr:
    csrs mhpmcounter5, a0
    ret

.globl mhpmcounter6_s_csr
mhpmcounter6_s_csr:
    csrs mhpmcounter6, a0
    ret

.globl mhpmcounter7_s_csr
mhpmcounter7_s_csr:
    csrs mhpmcounter7, a0
    ret

.globl mhpmcounter8_s_csr
mhpmcounter8_s_csr:
    csrs mhpmcounter8, a0
    ret

.globl mhpmcounter9_s_csr
mhpmcounter9_s_csr:
    csrs mhpmcounter9, a0
    ret

.globl mhpmcounter10_s_csr
mhpmcounter10_s_csr:
    csrs mhpmcounter10, a0
    ret

.globl mhpmcounter11_s_csr
mhpmcounter11_s_csr:
    csrs mhpmcounter11, a0
    ret

.globl mhpmcounter12_s_csr
mhpmcounter12_s_csr:
    csrs mhpmcounter12, a0
    ret

.globl mhpmcounter13_s_csr
mhpmcounter13_s_csr:
    csrs mhpmcounter13, a0
    ret

.globl mhpmcounter14_s_csr
mhpmcounter14_s_csr:
    csrs mhpmcounter14, a0
    ret

.globl mhpmcounter15_s_csr
mhpmcounter15_s_csr:
    csrs mhpmcounter15, a0
    ret

.globl mhpmcounter16_s_csr
mhpmcounter16_s_csr:
    csrs mhpmcounter16, a0
    ret

.globl mhpmcounter17_s_csr
mhpmcounter17_s_csr:
    csrs mhpmcounter17, a0
    ret

.globl mhpmcounter18_s_csr
mhpmcounter18_s_csr:
    csrs mhpmcounter18, a0
    ret

.globl mhpmcounter19_s_csr
mhpmcounter19_s_csr:
    csrs mhpmcounter19, a0
    ret

.globl mhpmcounter20_s_csr
mhpmcounter20_s_csr:
    csrs mhpmcounter20, a0
    ret

.globl mhpmcounter21_s_csr
mhpmcounter21_s_csr:
    csrs mhpmcounter21, a0
    ret

.globl mhpmcounter22_s_csr
mhpmcounter22_s_csr:
    csrs mhpmcounter22, a0
    ret

.globl mhpmcounter23_s_csr
mhpmcounter23_s_csr:
    csrs mhpmcounter23, a0
    ret

.globl mhpmcounter24_s_csr
mhpmcounter24_s_csr:
    csrs mhpmcounter24, a0
    ret

.globl mhpmcounter25_s_csr
mhpmcounter25_s_csr:
    csrs mhpmcounter25, a0
    ret

.globl mhpmcounter26_s_csr
mhpmcounter26_s_csr:
    csrs mhpmcounter26, a0
    ret

.globl mhpmcounter27_s_csr
mhpmcounter27_s_csr:
    csrs mhpmcounter27, a0
    ret

.globl mhpmcounter28_s_csr
mhpmcounter28_s_csr:
    csrs mhpmcounter28, a0
    ret

.globl mhpmcounter29_s_csr
mhpmcounter29_s_csr:
    csrs mhpmcounter29, a0
    ret

.globl mhpmcounter30_s_csr
mhpmcounter30_s_csr:
    csrs mhpmcounter30, a0
    ret

.globl mhpmcounter31_s_csr
mhpmcounter31_s_csr:
    csrs mhpmcounter31, a0
    ret

.globl mcycleh_s_csr
mcycleh_s_csr:
    csrs mcycleh, a0
    ret

.globl minstreth_s_csr
minstreth_s_csr:
    csrs minstreth, a0
    ret

.globl mhpmcounter3h_s_csr
mhpmcounter3h_s_csr:
    csrs mhpmcounter3h, a0
    ret

.globl mhpmcounter4h_s_csr
mhpmcounter4h_s_csr:
    csrs mhpmcounter4h, a0
    ret

.globl mhpmcounter5h_s_csr
mhpmcounter5h_s_csr:
    csrs mhpmcounter5h, a0
    ret

.globl mhpmcounter6h_s_csr
mhpmcounter6h_s_csr:
    csrs mhpmcounter6h, a0
    ret

.globl mhpmcounter7h_s_csr
mhpmcounter7h_s_csr:
    csrs mhpmcounter7h, a0
    ret

.globl mhpmcounter8h_s_csr
mhpmcounter8h_s_csr:
    csrs mhpmcounter8h, a0
    ret

.globl mhpmcounter9h_s_csr
mhpmcounter9h_s_csr:
    csrs mhpmcounter9h, a0
    ret

.globl mhpmcounter10h_s_csr
mhpmcounter10h_s_csr:
    csrs mhpmcounter10h, a0
    ret

.globl mhpmcounter11h_s_csr
mhpmcounter11h_s_csr:
    csrs mhpmcounter11h, a0
    ret

.globl mhpmcounter12h_s_csr
mhpmcounter12h_s_csr:
    csrs mhpmcounter12h, a0
    ret

.globl mhpmcounter13h_s_csr
mhpmcounter13h_s_csr:
    csrs mhpmcounter13h, a0
    ret

.globl mhpmcounter14h_s_csr
mhpmcounter14h_s_csr:
    csrs mhpmcounter14h, a0
    ret

.globl mhpmcounter15h_s_csr
mhpmcounter15h_s_csr:
    csrs mhpmcounter15h, a0
    ret

.globl mhpmcounter16h_s_csr
mhpmcounter16h_s_csr:
    csrs mhpmcounter16h, a0
    ret

.globl mhpmcounter17h_s_csr
mhpmcounter17h_s_csr:
    csrs mhpmcounter17h, a0
    ret

.globl mhpmcounter18h_s_csr
mhpmcounter18h_s_csr:
    csrs mhpmcounter18h, a0
    ret

.globl mhpmcounter19h_s_csr
mhpmcounter19h_s_csr:
    csrs mhpmcounter19h, a0
    ret

.globl mhpmcounter20h_s_csr
mhpmcounter20h_s_csr:
    csrs mhpmcounter20h, a0
    ret

.globl mhpmcounter21h_s_csr
mhpmcounter21h_s_csr:
    csrs mhpmcounter21h, a0
    ret

.globl mhpmcounter22h_s_csr
mhpmcounter22h_s_csr:
    csrs mhpmcounter22h, a0
    ret

.globl mhpmcounter23h_s_csr
mhpmcounter23h_s_csr:
    csrs mhpmcounter23h, a0
    ret

.globl mhpmcounter24h_s_csr
mhpmcounter24h_s_csr:
    csrs mhpmcounter24h, a0
    ret

.globl mhpmcounter25h_s_csr
mhpmcounter25h_s_csr:
    csrs mhpmcounter25h, a0
    ret

.globl mhpmcounter26h_s_csr
mhpmcounter26h_s_csr:
    csrs mhpmcounter26h, a0
    ret

.globl mhpmcounter27h_s_csr
mhpmcounter27h_s_csr:
    csrs mhpmcounter27h, a0
    ret

.globl mhpmcounter28h_s_csr
mhpmcounter28h_s_csr:
    csrs mhpmcounter28h, a0
    ret

.globl mhpmcounter29h_s_csr
mhpmcounter29h_s_csr:
    csrs mhpmcounter29h, a0
    ret

.globl mhpmcounter30h_s_csr
mhpmcounter30h_s_csr:
    csrs mhpmcounter30h, a0
    ret

.globl mhpmcounter31h_s_csr
mhpmcounter31h_s_csr:
    csrs mhpmcounter31h, a0
    ret

.globl mhpmevent3_s_csr
mhpmevent3_s_csr:
    csrs mhpmevent3, a0
    ret

.globl mhpmevent4_s_csr
mhpmevent4_s_csr:
    csrs mhpmevent4, a0
    ret

.globl mhpmevent5_s_csr
mhpmevent5_s_csr:
    csrs mhpmevent5, a0
    ret

.globl mhpmevent6_s_csr
mhpmevent6_s_csr:
    csrs mhpmevent6, a0
    ret

.globl mhpmevent7_s_csr
mhpmevent7_s_csr:
    csrs mhpmevent7, a0
    ret

.globl mhpmevent8_s_csr
mhpmevent8_s_csr:
    csrs mhpmevent8, a0
    ret

.globl mhpmevent9_s_csr
mhpmevent9_s_csr:
    csrs mhpmevent9, a0
    ret

.globl mhpmevent10_s_csr
mhpmevent10_s_csr:
    csrs mhpmevent10, a0
    ret

.globl mhpmevent11_s_csr
mhpmevent11_s_csr:
    csrs mhpmevent11, a0
    ret

.globl mhpmevent12_s_csr
mhpmevent12_s_csr:
    csrs mhpmevent12, a0
    ret

.globl mhpmevent13_s_csr
mhpmevent13_s_csr:
    csrs mhpmevent13, a0
    ret

.globl mhpmevent14_s_csr
mhpmevent14_s_csr:
    csrs mhpmevent14, a0
    ret

.globl mhpmevent15_s_csr
mhpmevent15_s_csr:
    csrs mhpmevent15, a0
    ret

.globl mhpmevent16_s_csr
mhpmevent16_s_csr:
    csrs mhpmevent16, a0
    ret

.globl mhpmevent17_s_csr
mhpmevent17_s_csr:
    csrs mhpmevent17, a0
    ret

.globl mhpmevent18_s_csr
mhpmevent18_s_csr:
    csrs mhpmevent18, a0
    ret

.globl mhpmevent19_s_csr
mhpmevent19_s_csr:
    csrs mhpmevent19, a0
    ret

.globl mhpmevent20_s_csr
mhpmevent20_s_csr:
    csrs mhpmevent20, a0
    ret

.globl mhpmevent21_s_csr
mhpmevent21_s_csr:
    csrs mhpmevent21, a0
    ret

.globl mhpmevent22_s_csr
mhpmevent22_s_csr:
    csrs mhpmevent22, a0
    ret

.globl mhpmevent23_s_csr
mhpmevent23_s_csr:
    csrs mhpmevent23, a0
    ret

.globl mhpmevent24_s_csr
mhpmevent24_s_csr:
    csrs mhpmevent24, a0
    ret

.globl mhpmevent25_s_csr
mhpmevent25_s_csr:
    csrs mhpmevent25, a0
    ret

.globl mhpmevent26_s_csr
mhpmevent26_s_csr:
    csrs mhpmevent26, a0
    ret

.globl mhpmevent27_s_csr
mhpmevent27_s_csr:
    csrs mhpmevent27, a0
    ret

.globl mhpmevent28_s_csr
mhpmevent28_s_csr:
    csrs mhpmevent28, a0
    ret

.globl mhpmevent29_s_csr
mhpmevent29_s_csr:
    csrs mhpmevent29, a0
    ret

.globl mhpmevent30_s_csr
mhpmevent30_s_csr:
    csrs mhpmevent30, a0
    ret

.globl mhpmevent31_s_csr
mhpmevent31_s_csr:
    csrs mhpmevent31, a0
    ret

.globl tselect_s_csr
tselect_s_csr:
    csrs tselect, a0
    ret

.globl tdata1_s_csr
tdata1_s_csr:
    csrs tdata1, a0
    ret

.globl tdata2_s_csr
tdata2_s_csr:
    csrs tdata2, a0
    ret

.globl tdata3_s_csr
tdata3_s_csr:
    csrs tdata3, a0
    ret

.globl dcsr_s_csr
dcsr_s_csr:
    csrs dcsr, a0
    ret

.globl dpc_s_csr
dpc_s_csr:
    csrs dpc, a0
    ret

.globl dscratch_s_csr
dscratch_s_csr:
    csrs dscratch, a0
    ret
### CSR CLEARS

.globl ustatus_c_csr
ustatus_c_csr:
    csrc ustatus, a0
    ret

.globl uie_c_csr
uie_c_csr:
    csrc uie, a0
    ret

.globl utvec_c_csr
utvec_c_csr:
    csrc utvec, a0
    ret

.globl uscratch_c_csr
uscratch_c_csr:
    csrc uscratch, a0
    ret

.globl uepc_c_csr
uepc_c_csr:
    csrc uepc, a0
    ret

.globl ucause_c_csr
ucause_c_csr:
    csrc ucause, a0
    ret

.globl utval_c_csr
utval_c_csr:
    csrc utval, a0
    ret

.globl uip_c_csr
uip_c_csr:
    csrc uip, a0
    ret

.globl fflags_c_csr
fflags_c_csr:
    csrc fflags, a0
    ret

.globl frm_c_csr
frm_c_csr:
    csrc frm, a0
    ret

.globl fcsr_c_csr
fcsr_c_csr:
    csrc fcsr, a0
    ret

.globl cycle_c_csr
cycle_c_csr:
    csrc cycle, a0
    ret

.globl time_c_csr
time_c_csr:
    csrc time, a0
    ret

.globl instret_c_csr
instret_c_csr:
    csrc instret, a0
    ret

.globl hpmcounter3_c_csr
hpmcounter3_c_csr:
    csrc hpmcounter3, a0
    ret

.globl hpmcounter4_c_csr
hpmcounter4_c_csr:
    csrc hpmcounter4, a0
    ret

.globl hpmcounter5_c_csr
hpmcounter5_c_csr:
    csrc hpmcounter5, a0
    ret

.globl hpmcounter6_c_csr
hpmcounter6_c_csr:
    csrc hpmcounter6, a0
    ret

.globl hpmcounter7_c_csr
hpmcounter7_c_csr:
    csrc hpmcounter7, a0
    ret

.globl hpmcounter8_c_csr
hpmcounter8_c_csr:
    csrc hpmcounter8, a0
    ret

.globl hpmcounter9_c_csr
hpmcounter9_c_csr:
    csrc hpmcounter9, a0
    ret

.globl hpmcounter10_c_csr
hpmcounter10_c_csr:
    csrc hpmcounter10, a0
    ret

.globl hpmcounter11_c_csr
hpmcounter11_c_csr:
    csrc hpmcounter11, a0
    ret

.globl hpmcounter12_c_csr
hpmcounter12_c_csr:
    csrc hpmcounter12, a0
    ret

.globl hpmcounter13_c_csr
hpmcounter13_c_csr:
    csrc hpmcounter13, a0
    ret

.globl hpmcounter14_c_csr
hpmcounter14_c_csr:
    csrc hpmcounter14, a0
    ret

.globl hpmcounter15_c_csr
hpmcounter15_c_csr:
    csrc hpmcounter15, a0
    ret

.globl hpmcounter16_c_csr
hpmcounter16_c_csr:
    csrc hpmcounter16, a0
    ret

.globl hpmcounter17_c_csr
hpmcounter17_c_csr:
    csrc hpmcounter17, a0
    ret

.globl hpmcounter18_c_csr
hpmcounter18_c_csr:
    csrc hpmcounter18, a0
    ret

.globl hpmcounter19_c_csr
hpmcounter19_c_csr:
    csrc hpmcounter19, a0
    ret

.globl hpmcounter20_c_csr
hpmcounter20_c_csr:
    csrc hpmcounter20, a0
    ret

.globl hpmcounter21_c_csr
hpmcounter21_c_csr:
    csrc hpmcounter21, a0
    ret

.globl hpmcounter22_c_csr
hpmcounter22_c_csr:
    csrc hpmcounter22, a0
    ret

.globl hpmcounter23_c_csr
hpmcounter23_c_csr:
    csrc hpmcounter23, a0
    ret

.globl hpmcounter24_c_csr
hpmcounter24_c_csr:
    csrc hpmcounter24, a0
    ret

.globl hpmcounter25_c_csr
hpmcounter25_c_csr:
    csrc hpmcounter25, a0
    ret

.globl hpmcounter26_c_csr
hpmcounter26_c_csr:
    csrc hpmcounter26, a0
    ret

.globl hpmcounter27_c_csr
hpmcounter27_c_csr:
    csrc hpmcounter27, a0
    ret

.globl hpmcounter28_c_csr
hpmcounter28_c_csr:
    csrc hpmcounter28, a0
    ret

.globl hpmcounter29_c_csr
hpmcounter29_c_csr:
    csrc hpmcounter29, a0
    ret

.globl hpmcounter30_c_csr
hpmcounter30_c_csr:
    csrc hpmcounter30, a0
    ret

.globl hpmcounter31_c_csr
hpmcounter31_c_csr:
    csrc hpmcounter31, a0
    ret

.globl cycleh_c_csr
cycleh_c_csr:
    csrc cycleh, a0
    ret

.globl timeh_c_csr
timeh_c_csr:
    csrc timeh, a0
    ret

.globl instreth_c_csr
instreth_c_csr:
    csrc instreth, a0
    ret

.globl hpmcounter3h_c_csr
hpmcounter3h_c_csr:
    csrc hpmcounter3h, a0
    ret

.globl hpmcounter4h_c_csr
hpmcounter4h_c_csr:
    csrc hpmcounter4h, a0
    ret

.globl hpmcounter5h_c_csr
hpmcounter5h_c_csr:
    csrc hpmcounter5h, a0
    ret

.globl hpmcounter6h_c_csr
hpmcounter6h_c_csr:
    csrc hpmcounter6h, a0
    ret

.globl hpmcounter7h_c_csr
hpmcounter7h_c_csr:
    csrc hpmcounter7h, a0
    ret

.globl hpmcounter8h_c_csr
hpmcounter8h_c_csr:
    csrc hpmcounter8h, a0
    ret

.globl hpmcounter9h_c_csr
hpmcounter9h_c_csr:
    csrc hpmcounter9h, a0
    ret

.globl hpmcounter10h_c_csr
hpmcounter10h_c_csr:
    csrc hpmcounter10h, a0
    ret

.globl hpmcounter11h_c_csr
hpmcounter11h_c_csr:
    csrc hpmcounter11h, a0
    ret

.globl hpmcounter12h_c_csr
hpmcounter12h_c_csr:
    csrc hpmcounter12h, a0
    ret

.globl hpmcounter13h_c_csr
hpmcounter13h_c_csr:
    csrc hpmcounter13h, a0
    ret

.globl hpmcounter14h_c_csr
hpmcounter14h_c_csr:
    csrc hpmcounter14h, a0
    ret

.globl hpmcounter15h_c_csr
hpmcounter15h_c_csr:
    csrc hpmcounter15h, a0
    ret

.globl hpmcounter16h_c_csr
hpmcounter16h_c_csr:
    csrc hpmcounter16h, a0
    ret

.globl hpmcounter17h_c_csr
hpmcounter17h_c_csr:
    csrc hpmcounter17h, a0
    ret

.globl hpmcounter18h_c_csr
hpmcounter18h_c_csr:
    csrc hpmcounter18h, a0
    ret

.globl hpmcounter19h_c_csr
hpmcounter19h_c_csr:
    csrc hpmcounter19h, a0
    ret

.globl hpmcounter20h_c_csr
hpmcounter20h_c_csr:
    csrc hpmcounter20h, a0
    ret

.globl hpmcounter21h_c_csr
hpmcounter21h_c_csr:
    csrc hpmcounter21h, a0
    ret

.globl hpmcounter22h_c_csr
hpmcounter22h_c_csr:
    csrc hpmcounter22h, a0
    ret

.globl hpmcounter23h_c_csr
hpmcounter23h_c_csr:
    csrc hpmcounter23h, a0
    ret

.globl hpmcounter24h_c_csr
hpmcounter24h_c_csr:
    csrc hpmcounter24h, a0
    ret

.globl hpmcounter25h_c_csr
hpmcounter25h_c_csr:
    csrc hpmcounter25h, a0
    ret

.globl hpmcounter26h_c_csr
hpmcounter26h_c_csr:
    csrc hpmcounter26h, a0
    ret

.globl hpmcounter27h_c_csr
hpmcounter27h_c_csr:
    csrc hpmcounter27h, a0
    ret

.globl hpmcounter28h_c_csr
hpmcounter28h_c_csr:
    csrc hpmcounter28h, a0
    ret

.globl hpmcounter29h_c_csr
hpmcounter29h_c_csr:
    csrc hpmcounter29h, a0
    ret

.globl hpmcounter30h_c_csr
hpmcounter30h_c_csr:
    csrc hpmcounter30h, a0
    ret

.globl hpmcounter31h_c_csr
hpmcounter31h_c_csr:
    csrc hpmcounter31h, a0
    ret

.globl sstatus_c_csr
sstatus_c_csr:
    csrc sstatus, a0
    ret

.globl sedeleg_c_csr
sedeleg_c_csr:
    csrc sedeleg, a0
    ret

.globl sideleg_c_csr
sideleg_c_csr:
    csrc sideleg, a0
    ret

.globl sie_c_csr
sie_c_csr:
    csrc sie, a0
    ret

.globl stvec_c_csr
stvec_c_csr:
    csrc stvec, a0
    ret

.globl scounteren_c_csr
scounteren_c_csr:
    csrc scounteren, a0
    ret

.globl sscratch_c_csr
sscratch_c_csr:
    csrc sscratch, a0
    ret

.globl sepc_c_csr
sepc_c_csr:
    csrc sepc, a0
    ret

.globl scause_c_csr
scause_c_csr:
    csrc scause, a0
    ret

.globl sbadaddr_c_csr
sbadaddr_c_csr:
    csrc sbadaddr, a0
    ret

.globl sip_c_csr
sip_c_csr:
    csrc sip, a0
    ret

.globl satp_c_csr
satp_c_csr:
    csrc satp, a0
    ret

.globl mvendorid_c_csr
mvendorid_c_csr:
    csrc mvendorid, a0
    ret

.globl marchid_c_csr
marchid_c_csr:
    csrc marchid, a0
    ret

.globl mimpid_c_csr
mimpid_c_csr:
    csrc mimpid, a0
    ret

.globl mhartid_c_csr
mhartid_c_csr:
    csrc mhartid, a0
    ret

.globl mstatus_c_csr
mstatus_c_csr:
    csrc mstatus, a0
    ret

.globl misa_c_csr
misa_c_csr:
    csrc misa, a0
    ret

.globl medeleg_c_csr
medeleg_c_csr:
    csrc medeleg, a0
    ret

.globl mideleg_c_csr
mideleg_c_csr:
    csrc mideleg, a0
    ret

.globl mie_c_csr
mie_c_csr:
    csrc mie, a0
    ret

.globl mtvec_c_csr
mtvec_c_csr:
    csrc mtvec, a0
    ret

.globl mcounteren_c_csr
mcounteren_c_csr:
    csrc mcounteren, a0
    ret

.globl mscratch_c_csr
mscratch_c_csr:
    csrc mscratch, a0
    ret

.globl mepc_c_csr
mepc_c_csr:
    csrc mepc, a0
    ret

.globl mcause_c_csr
mcause_c_csr:
    csrc mcause, a0
    ret

.globl mbadaddr_c_csr
mbadaddr_c_csr:
    csrc mbadaddr, a0
    ret

.globl mip_c_csr
mip_c_csr:
    csrc mip, a0
    ret

.globl pmpcfg0_c_csr
pmpcfg0_c_csr:
    csrc pmpcfg0, a0
    ret

.globl pmpcfg1_c_csr
pmpcfg1_c_csr:
    csrc pmpcfg1, a0
    ret

.globl pmpcfg2_c_csr
pmpcfg2_c_csr:
    csrc pmpcfg2, a0
    ret

.globl pmpcfg3_c_csr
pmpcfg3_c_csr:
    csrc pmpcfg3, a0
    ret

.globl pmpaddr0_c_csr
pmpaddr0_c_csr:
    csrc pmpaddr0, a0
    ret

.globl pmpaddr1_c_csr
pmpaddr1_c_csr:
    csrc pmpaddr1, a0
    ret

.globl pmpaddr2_c_csr
pmpaddr2_c_csr:
    csrc pmpaddr2, a0
    ret

.globl pmpaddr3_c_csr
pmpaddr3_c_csr:
    csrc pmpaddr3, a0
    ret

.globl pmpaddr4_c_csr
pmpaddr4_c_csr:
    csrc pmpaddr4, a0
    ret

.globl pmpaddr5_c_csr
pmpaddr5_c_csr:
    csrc pmpaddr5, a0
    ret

.globl pmpaddr6_c_csr
pmpaddr6_c_csr:
    csrc pmpaddr6, a0
    ret

.globl pmpaddr7_c_csr
pmpaddr7_c_csr:
    csrc pmpaddr7, a0
    ret

.globl pmpaddr8_c_csr
pmpaddr8_c_csr:
    csrc pmpaddr8, a0
    ret

.globl pmpaddr9_c_csr
pmpaddr9_c_csr:
    csrc pmpaddr9, a0
    ret

.globl pmpaddr10_c_csr
pmpaddr10_c_csr:
    csrc pmpaddr10, a0
    ret

.globl pmpaddr11_c_csr
pmpaddr11_c_csr:
    csrc pmpaddr11, a0
    ret

.globl pmpaddr12_c_csr
pmpaddr12_c_csr:
    csrc pmpaddr12, a0
    ret

.globl pmpaddr13_c_csr
pmpaddr13_c_csr:
    csrc pmpaddr13, a0
    ret

.globl pmpaddr14_c_csr
pmpaddr14_c_csr:
    csrc pmpaddr14, a0
    ret

.globl pmpaddr15_c_csr
pmpaddr15_c_csr:
    csrc pmpaddr15, a0
    ret

.globl mcycle_c_csr
mcycle_c_csr:
    csrc mcycle, a0
    ret

.globl minstret_c_csr
minstret_c_csr:
    csrc minstret, a0
    ret

.globl mhpmcounter3_c_csr
mhpmcounter3_c_csr:
    csrc mhpmcounter3, a0
    ret

.globl mhpmcounter4_c_csr
mhpmcounter4_c_csr:
    csrc mhpmcounter4, a0
    ret

.globl mhpmcounter5_c_csr
mhpmcounter5_c_csr:
    csrc mhpmcounter5, a0
    ret

.globl mhpmcounter6_c_csr
mhpmcounter6_c_csr:
    csrc mhpmcounter6, a0
    ret

.globl mhpmcounter7_c_csr
mhpmcounter7_c_csr:
    csrc mhpmcounter7, a0
    ret

.globl mhpmcounter8_c_csr
mhpmcounter8_c_csr:
    csrc mhpmcounter8, a0
    ret

.globl mhpmcounter9_c_csr
mhpmcounter9_c_csr:
    csrc mhpmcounter9, a0
    ret

.globl mhpmcounter10_c_csr
mhpmcounter10_c_csr:
    csrc mhpmcounter10, a0
    ret

.globl mhpmcounter11_c_csr
mhpmcounter11_c_csr:
    csrc mhpmcounter11, a0
    ret

.globl mhpmcounter12_c_csr
mhpmcounter12_c_csr:
    csrc mhpmcounter12, a0
    ret

.globl mhpmcounter13_c_csr
mhpmcounter13_c_csr:
    csrc mhpmcounter13, a0
    ret

.globl mhpmcounter14_c_csr
mhpmcounter14_c_csr:
    csrc mhpmcounter14, a0
    ret

.globl mhpmcounter15_c_csr
mhpmcounter15_c_csr:
    csrc mhpmcounter15, a0
    ret

.globl mhpmcounter16_c_csr
mhpmcounter16_c_csr:
    csrc mhpmcounter16, a0
    ret

.globl mhpmcounter17_c_csr
mhpmcounter17_c_csr:
    csrc mhpmcounter17, a0
    ret

.globl mhpmcounter18_c_csr
mhpmcounter18_c_csr:
    csrc mhpmcounter18, a0
    ret

.globl mhpmcounter19_c_csr
mhpmcounter19_c_csr:
    csrc mhpmcounter19, a0
    ret

.globl mhpmcounter20_c_csr
mhpmcounter20_c_csr:
    csrc mhpmcounter20, a0
    ret

.globl mhpmcounter21_c_csr
mhpmcounter21_c_csr:
    csrc mhpmcounter21, a0
    ret

.globl mhpmcounter22_c_csr
mhpmcounter22_c_csr:
    csrc mhpmcounter22, a0
    ret

.globl mhpmcounter23_c_csr
mhpmcounter23_c_csr:
    csrc mhpmcounter23, a0
    ret

.globl mhpmcounter24_c_csr
mhpmcounter24_c_csr:
    csrc mhpmcounter24, a0
    ret

.globl mhpmcounter25_c_csr
mhpmcounter25_c_csr:
    csrc mhpmcounter25, a0
    ret

.globl mhpmcounter26_c_csr
mhpmcounter26_c_csr:
    csrc mhpmcounter26, a0
    ret

.globl mhpmcounter27_c_csr
mhpmcounter27_c_csr:
    csrc mhpmcounter27, a0
    ret

.globl mhpmcounter28_c_csr
mhpmcounter28_c_csr:
    csrc mhpmcounter28, a0
    ret

.globl mhpmcounter29_c_csr
mhpmcounter29_c_csr:
    csrc mhpmcounter29, a0
    ret

.globl mhpmcounter30_c_csr
mhpmcounter30_c_csr:
    csrc mhpmcounter30, a0
    ret

.globl mhpmcounter31_c_csr
mhpmcounter31_c_csr:
    csrc mhpmcounter31, a0
    ret

.globl mcycleh_c_csr
mcycleh_c_csr:
    csrc mcycleh, a0
    ret

.globl minstreth_c_csr
minstreth_c_csr:
    csrc minstreth, a0
    ret

.globl mhpmcounter3h_c_csr
mhpmcounter3h_c_csr:
    csrc mhpmcounter3h, a0
    ret

.globl mhpmcounter4h_c_csr
mhpmcounter4h_c_csr:
    csrc mhpmcounter4h, a0
    ret

.globl mhpmcounter5h_c_csr
mhpmcounter5h_c_csr:
    csrc mhpmcounter5h, a0
    ret

.globl mhpmcounter6h_c_csr
mhpmcounter6h_c_csr:
    csrc mhpmcounter6h, a0
    ret

.globl mhpmcounter7h_c_csr
mhpmcounter7h_c_csr:
    csrc mhpmcounter7h, a0
    ret

.globl mhpmcounter8h_c_csr
mhpmcounter8h_c_csr:
    csrc mhpmcounter8h, a0
    ret

.globl mhpmcounter9h_c_csr
mhpmcounter9h_c_csr:
    csrc mhpmcounter9h, a0
    ret

.globl mhpmcounter10h_c_csr
mhpmcounter10h_c_csr:
    csrc mhpmcounter10h, a0
    ret

.globl mhpmcounter11h_c_csr
mhpmcounter11h_c_csr:
    csrc mhpmcounter11h, a0
    ret

.globl mhpmcounter12h_c_csr
mhpmcounter12h_c_csr:
    csrc mhpmcounter12h, a0
    ret

.globl mhpmcounter13h_c_csr
mhpmcounter13h_c_csr:
    csrc mhpmcounter13h, a0
    ret

.globl mhpmcounter14h_c_csr
mhpmcounter14h_c_csr:
    csrc mhpmcounter14h, a0
    ret

.globl mhpmcounter15h_c_csr
mhpmcounter15h_c_csr:
    csrc mhpmcounter15h, a0
    ret

.globl mhpmcounter16h_c_csr
mhpmcounter16h_c_csr:
    csrc mhpmcounter16h, a0
    ret

.globl mhpmcounter17h_c_csr
mhpmcounter17h_c_csr:
    csrc mhpmcounter17h, a0
    ret

.globl mhpmcounter18h_c_csr
mhpmcounter18h_c_csr:
    csrc mhpmcounter18h, a0
    ret

.globl mhpmcounter19h_c_csr
mhpmcounter19h_c_csr:
    csrc mhpmcounter19h, a0
    ret

.globl mhpmcounter20h_c_csr
mhpmcounter20h_c_csr:
    csrc mhpmcounter20h, a0
    ret

.globl mhpmcounter21h_c_csr
mhpmcounter21h_c_csr:
    csrc mhpmcounter21h, a0
    ret

.globl mhpmcounter22h_c_csr
mhpmcounter22h_c_csr:
    csrc mhpmcounter22h, a0
    ret

.globl mhpmcounter23h_c_csr
mhpmcounter23h_c_csr:
    csrc mhpmcounter23h, a0
    ret

.globl mhpmcounter24h_c_csr
mhpmcounter24h_c_csr:
    csrc mhpmcounter24h, a0
    ret

.globl mhpmcounter25h_c_csr
mhpmcounter25h_c_csr:
    csrc mhpmcounter25h, a0
    ret

.globl mhpmcounter26h_c_csr
mhpmcounter26h_c_csr:
    csrc mhpmcounter26h, a0
    ret

.globl mhpmcounter27h_c_csr
mhpmcounter27h_c_csr:
    csrc mhpmcounter27h, a0
    ret

.globl mhpmcounter28h_c_csr
mhpmcounter28h_c_csr:
    csrc mhpmcounter28h, a0
    ret

.globl mhpmcounter29h_c_csr
mhpmcounter29h_c_csr:
    csrc mhpmcounter29h, a0
    ret

.globl mhpmcounter30h_c_csr
mhpmcounter30h_c_csr:
    csrc mhpmcounter30h, a0
    ret

.globl mhpmcounter31h_c_csr
mhpmcounter31h_c_csr:
    csrc mhpmcounter31h, a0
    ret

.globl mhpmevent3_c_csr
mhpmevent3_c_csr:
    csrc mhpmevent3, a0
    ret

.globl mhpmevent4_c_csr
mhpmevent4_c_csr:
    csrc mhpmevent4, a0
    ret

.globl mhpmevent5_c_csr
mhpmevent5_c_csr:
    csrc mhpmevent5, a0
    ret

.globl mhpmevent6_c_csr
mhpmevent6_c_csr:
    csrc mhpmevent6, a0
    ret

.globl mhpmevent7_c_csr
mhpmevent7_c_csr:
    csrc mhpmevent7, a0
    ret

.globl mhpmevent8_c_csr
mhpmevent8_c_csr:
    csrc mhpmevent8, a0
    ret

.globl mhpmevent9_c_csr
mhpmevent9_c_csr:
    csrc mhpmevent9, a0
    ret

.globl mhpmevent10_c_csr
mhpmevent10_c_csr:
    csrc mhpmevent10, a0
    ret

.globl mhpmevent11_c_csr
mhpmevent11_c_csr:
    csrc mhpmevent11, a0
    ret

.globl mhpmevent12_c_csr
mhpmevent12_c_csr:
    csrc mhpmevent12, a0
    ret

.globl mhpmevent13_c_csr
mhpmevent13_c_csr:
    csrc mhpmevent13, a0
    ret

.globl mhpmevent14_c_csr
mhpmevent14_c_csr:
    csrc mhpmevent14, a0
    ret

.globl mhpmevent15_c_csr
mhpmevent15_c_csr:
    csrc mhpmevent15, a0
    ret

.globl mhpmevent16_c_csr
mhpmevent16_c_csr:
    csrc mhpmevent16, a0
    ret

.globl mhpmevent17_c_csr
mhpmevent17_c_csr:
    csrc mhpmevent17, a0
    ret

.globl mhpmevent18_c_csr
mhpmevent18_c_csr:
    csrc mhpmevent18, a0
    ret

.globl mhpmevent19_c_csr
mhpmevent19_c_csr:
    csrc mhpmevent19, a0
    ret

.globl mhpmevent20_c_csr
mhpmevent20_c_csr:
    csrc mhpmevent20, a0
    ret

.globl mhpmevent21_c_csr
mhpmevent21_c_csr:
    csrc mhpmevent21, a0
    ret

.globl mhpmevent22_c_csr
mhpmevent22_c_csr:
    csrc mhpmevent22, a0
    ret

.globl mhpmevent23_c_csr
mhpmevent23_c_csr:
    csrc mhpmevent23, a0
    ret

.globl mhpmevent24_c_csr
mhpmevent24_c_csr:
    csrc mhpmevent24, a0
    ret

.globl mhpmevent25_c_csr
mhpmevent25_c_csr:
    csrc mhpmevent25, a0
    ret

.globl mhpmevent26_c_csr
mhpmevent26_c_csr:
    csrc mhpmevent26, a0
    ret

.globl mhpmevent27_c_csr
mhpmevent27_c_csr:
    csrc mhpmevent27, a0
    ret

.globl mhpmevent28_c_csr
mhpmevent28_c_csr:
    csrc mhpmevent28, a0
    ret

.globl mhpmevent29_c_csr
mhpmevent29_c_csr:
    csrc mhpmevent29, a0
    ret

.globl mhpmevent30_c_csr
mhpmevent30_c_csr:
    csrc mhpmevent30, a0
    ret

.globl mhpmevent31_c_csr
mhpmevent31_c_csr:
    csrc mhpmevent31, a0
    ret

.globl tselect_c_csr
tselect_c_csr:
    csrc tselect, a0
    ret

.globl tdata1_c_csr
tdata1_c_csr:
    csrc tdata1, a0
    ret

.globl tdata2_c_csr
tdata2_c_csr:
    csrc tdata2, a0
    ret

.globl tdata3_c_csr
tdata3_c_csr:
    csrc tdata3, a0
    ret

.globl dcsr_c_csr
dcsr_c_csr:
    csrc dcsr, a0
    ret

.globl dpc_c_csr
dpc_c_csr:
    csrc dpc, a0
    ret

.globl dscratch_c_csr
dscratch_c_csr:
    csrc dscratch, a0
    ret
