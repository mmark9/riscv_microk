.section .text

.globl sbi_relay_get_spec_version
sbi_relay_get_spec_version:
    li a7,0x10
    li a6,0x0
    ecall
    ret

.globl sbi_relay_get_impl_id
sbi_relay_get_impl_id:
    li a7,0x10
    li a6,0x1
    ecall
    ret

.globl sbi_relay_get_impl_version
sbi_relay_get_impl_version:
    li a7,0x10
    li a6,0x2
    ecall
    ret

.globl sbi_relay_probe_extension
sbi_relay_probe_extension:
    li a7,0x10
    li a6,0x3
    ecall
    ret

.globl sbi_relay_get_mvendorid
sbi_relay_get_mvendorid:
    li a7,0x10
    li a6,0x4
    ecall
    ret

.globl sbi_relay_get_marchid
sbi_relay_get_marchid:
    li a7,0x10
    li a6,0x5
    ecall
    ret

.globl sbi_relay_get_mimpid
sbi_relay_get_mipid:
    li a7,0x10
    li a6,0x6
    ecall
    ret

# legacy SBI extension (should be probed)
# no replacement yet
# a0 = ch
.globl sbi_relay_console_putchar
sbi_relay_console_putchar:
    li a7,0x01
    li a6,0x0
    ecall
    ret

# legacy SBI extension (should be probed)
# no replacement yet
.globl sbi_relay_console_getchar
sbi_relay_console_getchar:
    li a7,0x02
    li a6,0x0
    ecall
    ret

.globl sbi_relay_set_timer
sbi_relay_set_timer:
    li a7,0x54494D45
    li a6,0x0
    ecall
    ret

.globl sbi_relay_send_ipi
sbi_relay_send_ipi:
    li a7,0x735049
    li a6,0x0
    ecall
    ret

.globl sbi_relay_remote_fence_i
sbi_relay_remote_fence_i:
    li a7,0x52464E43
    li a6,0x0
    ecall
    ret

.globl sbi_relay_remote_fence_vma
sbi_relay_remote_fence_vma:
    li a7,0x52464E43
    li a6,0x1
    ecall
    ret

.globl sbi_relay_remote_fence_vma_asid
sbi_relay_remote_fence_vma_asid:
    li a7,0x52464E43
    li a6,0x2
    ecall
    ret

.globl sbi_relay_remote_hfence_gvma_vmid
sbi_relay_remote_hfence_gvma_vmid:
    li a7,0x52464E43
    li a6,0x3
    ecall
    ret

.globl sbi_relay_remote_hfence_vma_asid
sbi_relay_remote_hfence_vma_asid:
    li a7,0x52464E43
    li a6,0x5
    ecall
    ret

.globl sbi_relay_remote_hfence_vma
sbi_relay_remote_hfence_vma:
    li a7,0x52464E43
    li a6,0x6
    ecall
    ret

.globl sbi_relay_hart_start
sbi_relay_hart_start:
    li a7,0x48534D
    li a6,0x0
    ecall
    ret

.globl sbi_relay_hart_stop
sbi_relay_hart_stop:
    li a7,0x48534D
    li a6,0x1
    ecall
    ret

.globl sbi_relay_hart_get_status
sbi_relay_hart_get_status:
    li a7,0x48534D
    li a6,0x2
    ecall
    ret

.globl sbi_relay_system_reset
sbi_relay_system_reset:
    li a7,0x53525354
    li a6,0x0
    ecall
    ret
