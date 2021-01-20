#ifndef SPHINX_SBI_RELAY_H
#define SPHINX_SBI_RELAY_H

#include <stdint.h>

typedef enum {
    SBI_SUCCESS = 0,
    SBI_ERR_FAILED,
    SBI_ERR_NOT_SUPPORTED,
    SBI_INVALID_PARAM,
    SBI_ERR_DENIED,
    SBI_ERR_INVALID_ADDRESS,
    SBI_ERR_ALREADY_AVAILABLE
} sbi_err_t;

typedef enum {
    SBI_SHUTDOWN = 0,
    SBI_COLD_REBOOT,
    SBI_WARM_REBOOT
} sbi_reset_type_t;

typedef enum {
    SBI_RESET_NO_REASON = 0,
    SBI_RESET_SYSTEM_FAILURE
} sbi_reset_reason_t;

typedef enum {
    SBI_HART_STARTED = 0,
    SBI_HART_STOPPED,
    SBI_START_PENDING,
    SBI_STOP_PENDING
} sbi_hart_status_t;

typedef enum {
    SBI_BERKLEY_BOOT_LOADER = 0,
    SBI_OPEN_SBI,
    SBI_XVISOR,
    SBI_KVM,
    SBI_RUSTSBI,
    SBI_DIOSIX
} sbi_impl_ids_t;

struct sbiret sbi_relay_get_spec_version(void);
struct sbiret sbi_relay_get_impl_id(void);
struct sbiret sbi_relay_get_impl_version(void);
struct sbiret sbi_relay_probe_extension(long extension_id);
struct sbiret sbi_relay_get_mvendorid(void);
struct sbiret sbi_relay_get_marchid(void);
struct sbiret sbi_relay_get_mimpid(void);
int sbi_relay_console_getchar(void);
void sbi_relay_console_putchar(int ch);
struct sbiret sbi_relay_set_timer(uint64_t stime_value);
struct sbiret sbi_relay_send_ipi(uint32_t hart_mask,
                           uint32_t hart_mask_base);
struct sbiret sbi_relay_remote_fence_i(uint32_t hart_mask,
                                 uint32_t hart_mask_base);
struct sbiret sbi_relay_remote_sfence_vma(uint32_t hart_mask,
                                    uint32_t hart_mask_base,
                                    uint32_t start_addr,
                                    uint32_t size);
struct sbiret sbi_relay_remote_sfence_vma_asid(uint32_t hart_mask,
                                         uint32_t hart_mask_base,
                                         uint32_t start_addr,
                                         uint32_t size,
                                         uint32_t asid);
struct sbiret sbi_relay_remote_hfence_gvma_vmid(uint32_t hart_mask,
                                          uint32_t hart_mask_base,
                                          uint32_t start_addr,
                                          uint32_t size,
                                          uint32_t vmid);
struct sbiret sbi_relay_remote_hfence_gvma(uint32_t hart_mask,
                                     uint32_t hart_mask_base,
                                     uint32_t start_addr,
                                     uint32_t size);
struct sbiret sbi_relay_remote_hfence_vvma_asid(uint32_t hart_mask,
                                          uint32_t hart_mask_base,
                                          uint32_t start_addr,
                                          uint32_t size,
                                          uint32_t asid);
struct sbiret sbi_relay_remote_hfence_vvma(uint32_t hart_mask,
                                     uint32_t hart_mask_base,
                                     uint32_t start_addr,
                                     uint32_t size);
struct sbiret sbi_relay_hart_start(uint32_t hartid,
                             uint32_t start_addr,
                             uint32_t opaque);
struct sbiret sbi_relay_hart_stop(void);
struct sbiret sbi_relay_hart_get_status(uint32_t hartid);
struct sbiret sbi_relay_system_reset(uint32_t reset_type,
                               uint32_t reset_reason);

#endif //SPHINX_SBI_RELAY_H
