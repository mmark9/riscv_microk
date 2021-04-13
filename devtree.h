#ifndef RISCV_MICROK_DEVTREE_H
#define RISCV_MICROK_DEVTREE_H

#ifndef KERNEL_MODULES_DEVTREE_H
#define KERNEL_MODULES_DEVTREE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const void *value;
    const char *name;
    uint32_t len;
    bool valid;
} DeviceTreeProp;
typedef struct {
    uint32_t magic;
    uint32_t total_size;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
} DeviceTreeHdr;
typedef struct {
    uint64_t address;
    uint64_t size;
} DeviceTreeMemReserve;
typedef struct {
    uint32_t len;
    uint32_t name_off;
} DeviceTreePropHdr;
typedef struct {
    //const void* parent_node;
    const void *root;
    const void *node;
    const void *prop;
    const void* tree_root;
    const char* node_name;
    DeviceTreeHdr header;
    uint32_t root_address_cells;
    uint32_t root_size_cells;
    uint32_t address_cells;
    uint32_t size_cells;
    int32_t level;
} DeviceTreeContext;
uint32_t devtree_print_string(const void *blob_ptr);
void devtree_print_chars(const void *blob_ptr, int32_t num_chars);
void print_indent(int32_t level, uint32_t spaces);
void devtree_load_prop_hdr(DeviceTreePropHdr *hdr_out, const void *blob_ptr);
void devtree_print_prop_value(const char *name, uint32_t prop_len, const void *blob_ptr);
int devtree_property(const char *name, DeviceTreeProp *out,
                     const DeviceTreeContext *ctx);
void devtree_print_all(const void *blob);
int devtree_load_context(const void* blob, DeviceTreeContext* ctx);
int devtree_move_to_child(uint32_t index, DeviceTreeContext *ctx);
uint32_t devtree_child_node_count(DeviceTreeContext *ctx);
const char *devtree_child_name(uint32_t index, DeviceTreeContext *ctx);
int devtree_move_to_root(DeviceTreeContext *ctx);
const char *devtree_node_name(const DeviceTreeContext *ctx);
bool devtree_property_exists(const char *name, const DeviceTreeContext *ctx);
int devtree_load_from_file(const char* file_path, DeviceTreeContext* ctx);
int32_t devtree_word_at_index(uint32_t index,
                              const DeviceTreeProp* prop,
                              uint32_t* word_out,
                              const DeviceTreeContext* ctx);
uint32_t devtree_memory_reservation_count(const DeviceTreeContext* ctx);
int devtree_memory_reservation(uint32_t index, DeviceTreeMemReserve* out,
                               const DeviceTreeContext* ctx);
bool streq_node(const char *a, const char *b);

#endif //KERNEL_MODULES_DEVTREE_H


#endif //RISCV_MICROK_DEVTREE_H
