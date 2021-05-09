#include "system.h"
#include "devtree.h"
#include "bit_utils.h"
#include "kprint.h"

#include <stdint.h>
#include <stdbool.h>

#define FDT_BEGIN_NODE 0x01
#define FDT_END_NODE 0x02
#define FDT_PROP 0x03
#define FDT_NOP 0x04
#define FDT_END 0x09
#define FDT_HEADER_MAGIC 0xD00DFEED

int32_t strlen_(const char *str) {
    if (str == 0)
        return -1;
    int32_t count = 0;
    while (*str++ != 0)
        count += 1;
    return count;
}

int devtree_load_header(const char *blob, DeviceTreeHdr *header) {
    sys_kassert(header != 0);
    sys_kassert(blob != 0);
    const uint32_t *word_ptr = (uint32_t *) blob;
    header->magic = big2little_l(*word_ptr++);
    header->total_size = big2little_l(*word_ptr++);
    header->off_dt_struct = big2little_l(*word_ptr++);
    header->off_dt_strings = big2little_l(*word_ptr++);
    header->off_mem_rsvmap = big2little_l(*word_ptr++);
    header->version = big2little_l(*word_ptr++);
    header->last_comp_version = big2little_l(*word_ptr++);
    header->boot_cpuid_phys = big2little_l(*word_ptr++);
    header->size_dt_strings = big2little_l(*word_ptr++);
    header->size_dt_struct = big2little_l(*word_ptr++);
    return 0;
}

#define FDT_RESERVE_EMPTY(x) (x->address == 0 && x->size == 0)

bool streq(const char *a, const char *b) {
    while (true) {
        if (*a == 0 && *b == 0)
            return true;
        if (!(*a != 0 && *b != 0))
            return false;
        if (*a != *b)
            return false;
        a++;
        b++;
    }
}

bool streq_node(const char *a, const char *b) {
    // this ignores the address part of the node name
    while (true) {
        if (*a == 0 && *b == 0)
            return true;
        if (*a == '@' || *b == '@')
            return true;
        if (!(*a != 0 && *b != 0))
            return false;
        if (*a != *b)
            return false;
        a++;
        b++;
    }
}

// public interface
uint32_t devtree_print_string(const void *blob_ptr) {
    uint32_t len = 0;
    const char *str_ptr = (const char *) (blob_ptr);
    while (*str_ptr != 0) {
        kprintf("%c", *str_ptr++);
        len++;
    }
    return len;
}

void devtree_print_chars(const void *blob_ptr, int32_t num_chars) {
    if (num_chars == 0)
        return;
    const char *str_ptr = (const char *) (blob_ptr);
    for (uint32_t i = 0; i < num_chars - 1; i++) {
        if (*str_ptr == 0) {
            kprintf(", ");
            str_ptr++;
            continue;
        }
        kprintf("%c", *str_ptr++);
    }
}

void print_indent(int32_t level, uint32_t spaces) {
    uint32_t num_spaces = level * spaces;
    for (uint32_t i = 0; i < num_spaces; i++)
        kprintf(" ");
}

void devtree_load_prop_hdr(DeviceTreePropHdr *hdr_out, const void *blob_ptr) {
    uint32_t *tmp_ptr = (uint32_t *) blob_ptr;
    hdr_out->len = big2little_l(*tmp_ptr++);
    hdr_out->name_off = big2little_l(*tmp_ptr);
}

void devtree_print_prop_value(const char *name, uint32_t prop_len, const void *blob_ptr) {
    if (prop_len == 0)
        return;
    if (streq(name, "compatible")
        || streq(name, "model")
        || streq(name, "status")
        || streq(name, "name")
        || streq(name, "device_type")
        || streq(name, "bootargs")
        || streq(name, "stdout-path")
        || streq(name, "stdin-path")
        || streq(name, "power-isa-version")
        || streq(name, "mmu-type")) {
        devtree_print_chars(blob_ptr, prop_len);
    } else {
        uint32_t num_words = prop_len / 4;
        uint32_t *word_ptr = (uint32_t *) blob_ptr;
        kprintf("<");
        for (uint32_t i = 0; i < num_words; i++) {
            kprintf("0x%08x", big2little_l(*word_ptr++));
            if (i + 1 < num_words)
                kprintf(" ");
        }
        kprintf(">");
    }
}

int devtree_property(const char *name, DeviceTreeProp *out,
                     const DeviceTreeContext *ctx) {
    sys_kassert(ctx != 0);
    uint32_t token = 0;
    const int8_t* ptr = (const int8_t*)ctx->node;
    DeviceTreePropHdr prop_hdr;
    const char* prop_name = 0;
    while (true) {
        token = big2little_l(*((uint32_t *) ptr));
        if (token == FDT_PROP) {
            ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, ptr);
            prop_name = (const char *) ctx->tree_root
                        + ctx->header.off_dt_strings + prop_hdr.name_off;
            ptr += sizeof(DeviceTreePropHdr);
            if (streq(prop_name, name)) {
                out->name = prop_name;
                out->value = ptr;
                out->len = prop_hdr.len;
                out->valid = true;
                return 0;
            }
            ptr += prop_hdr.len;
        } else if (token == FDT_END
                   || token == FDT_END_NODE
                   || token == FDT_BEGIN_NODE) {
            break;
        } else {
            ptr++;
        }
    }
    out->valid = false;
    return -1;
}

void devtree_print_all(const void *blob) {
    sys_kassert(blob != 0);
    DeviceTreeHdr header;
    devtree_load_header(blob, &header);
    sys_kassert(header.magic == FDT_HEADER_MAGIC);
    // load memory reservation block
    DeviceTreeMemReserve *resv_ptr = (DeviceTreeMemReserve *) (blob + header.off_mem_rsvmap);
    while (!FDT_RESERVE_EMPTY(resv_ptr)) {
        resv_ptr++;
    }
    // load structure block
    int32_t level = -1;
    uint32_t str_len = 0;
    uint32_t token = 0;
    DeviceTreePropHdr prop_hdr;
    uint32_t cur_num_address_cells = 0;
    uint32_t cur_num_size_cells = 0;
    const int8_t *fdt_struct_ptr = blob + header.off_dt_struct;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            print_indent(level, 8);
            str_len = devtree_print_string(fdt_struct_ptr + sizeof(uint32_t));
            if (str_len == 0 && level == 0) {
                kprintf("/");
                fdt_struct_ptr++;
            } else
                fdt_struct_ptr += str_len;
            kprintf(" {\n");
        } else if (token == FDT_END_NODE) {
            print_indent(level, 8);
            kprintf("};\n");
            fdt_struct_ptr += sizeof(uint32_t);
            level -= 1;
        } else if (token == FDT_PROP) {
            fdt_struct_ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, fdt_struct_ptr);
            print_indent(level + 1, 8);
            const char *prop_name = (const char *) blob + header.off_dt_strings + prop_hdr.name_off;
            //devtree_print_string(blob + header.off_dt_strings + prop_hdr.name_off);
            kprintf("%s = ", prop_name);
            fdt_struct_ptr += sizeof(DeviceTreePropHdr);
            //devtree_print_chars(fdt_struct_ptr, prop_hdr.len);
            if (streq(prop_name, "#address-cells")) {
                cur_num_address_cells = big2little_l(*(uint32_t *) fdt_struct_ptr);
            } else if (streq(prop_name, "#size-cells")) {
                cur_num_size_cells = big2little_l(*(uint32_t *) fdt_struct_ptr);
            }
            devtree_print_prop_value(prop_name, prop_hdr.len, fdt_struct_ptr);
            kprintf(";\n");
            fdt_struct_ptr += prop_hdr.len;
        } else if (token == FDT_NOP) {
            fdt_struct_ptr += sizeof(uint32_t);
        } else if (token == FDT_END) {
            break;
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
        // advance pointer
    }
}

int devtree_load_context(const void* blob, DeviceTreeContext* ctx) {
    sys_kassert(blob != 0);
    ctx->tree_root = blob;
    ctx->level = 0;
    devtree_load_header(blob, &ctx->header);
    sys_kassert(ctx->header.magic == FDT_HEADER_MAGIC);
    // load structure block
    int32_t level = -1;
    uint32_t str_len = 0;
    uint32_t token = 0;
    const char* node_name = 0;
    const int8_t *fdt_struct_ptr = blob + ctx->header.off_dt_struct;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            fdt_struct_ptr += sizeof(uint32_t);
            node_name = (const char*) fdt_struct_ptr;
            str_len = strlen_(node_name);
            if (str_len == 0 && level == 0) {
                fdt_struct_ptr++;
                ctx->root = fdt_struct_ptr;
                ctx->node = fdt_struct_ptr;
                ctx->node_name = "root";
                break;
            } else {
                return -1;
            }
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
        // advance pointer
    }
    DeviceTreeProp address_cells_prop;
    DeviceTreeProp size_cells_prop;
    int addr_cells_res = devtree_property("#address-cells", &address_cells_prop, ctx);
    int size_cells_res = devtree_property("#size-cells", &size_cells_prop, ctx);
    ctx->root_address_cells = addr_cells_res == 0 ? big2little_l(*(uint32_t*)address_cells_prop.value) : 2;
    ctx->root_size_cells = size_cells_res == 0 ? big2little_l(*(uint32_t*)size_cells_prop.value) : 1;
    ctx->address_cells = ctx->root_address_cells;
    ctx->size_cells = ctx->root_size_cells;
    return 0;
}

int devtree_move_to_child(uint32_t index, DeviceTreeContext *ctx) {
    int32_t level = ctx->level;
    uint32_t str_len = 0;
    uint32_t token = 0;
    DeviceTreePropHdr prop_hdr;
    uint32_t address_cells = 2;
    uint32_t size_cells = 1;
    int32_t node_count = 0;
    const char *prop_name = 0;
    const char *node_name = 0;
    const int8_t *fdt_struct_ptr = (const int8_t *) ctx->node;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            fdt_struct_ptr += sizeof(uint32_t);
            node_name = (const char *) fdt_struct_ptr;
            str_len = strlen_(node_name);
            if (str_len == 0 && level == 0) {
                fdt_struct_ptr++;
            } else
                fdt_struct_ptr += str_len;
            if (node_count == index) {
                ctx->node = fdt_struct_ptr;
                ctx->size_cells = size_cells;
                ctx->address_cells = address_cells;
                ctx->level = level;
                ctx->node_name = node_name;
                return 0;
            }
            if (level-1 == ctx->level)
                node_count++;
        } else if (token == FDT_END_NODE) {
            fdt_struct_ptr += sizeof(uint32_t);
            level -= 1;
        } else if (token == FDT_PROP) {
            fdt_struct_ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, fdt_struct_ptr);
            fdt_struct_ptr += sizeof(DeviceTreePropHdr);
            prop_name = (const char *) ctx->tree_root
                        + ctx->header.off_dt_strings + prop_hdr.name_off;
            if (streq(prop_name, "#address-cells")) {
                address_cells = big2little_l(*(uint32_t *) fdt_struct_ptr);
            } else if (streq(prop_name, "#size-cells")) {
                size_cells = big2little_l(*(uint32_t *) fdt_struct_ptr);
            }
            fdt_struct_ptr += prop_hdr.len;
        } else if (token == FDT_NOP) {
            fdt_struct_ptr += sizeof(uint32_t);
        } else if (token == FDT_END) {
            break;
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
    }
    return -1;
}

uint32_t devtree_child_node_count(DeviceTreeContext *ctx) {
    int32_t level = ctx->level;
    uint32_t str_len = 0;
    uint32_t token = 0;
    DeviceTreePropHdr prop_hdr;
    uint32_t address_cells = 2;
    uint32_t size_cells = 1;
    uint32_t node_count = 0;
    const char *prop_name = 0;
    const char *node_name = 0;
    const int8_t *fdt_struct_ptr = (const int8_t *) ctx->node;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            fdt_struct_ptr += sizeof(uint32_t);
            node_name = (const char *) fdt_struct_ptr;
            str_len = strlen_(node_name);
            if (str_len == 0 && level == 0) {
                fdt_struct_ptr++;
            } else
                fdt_struct_ptr += str_len;
            if (level-1 == ctx->level)
                node_count += 1;
        } else if (token == FDT_END_NODE) {
            fdt_struct_ptr += sizeof(uint32_t);
            level -= 1;
        } else if (token == FDT_PROP) {
            fdt_struct_ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, fdt_struct_ptr);
            fdt_struct_ptr += sizeof(DeviceTreePropHdr);
            fdt_struct_ptr += prop_hdr.len;
        } else if (token == FDT_NOP) {
            fdt_struct_ptr += sizeof(uint32_t);
        } else if (token == FDT_END) {
            break;
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
    }
    return node_count;
}

const char *devtree_child_name(uint32_t index, DeviceTreeContext *ctx) {
    int32_t level = ctx->level;
    uint32_t str_len = 0;
    uint32_t token = 0;
    DeviceTreePropHdr prop_hdr;
    uint32_t address_cells = 2;
    uint32_t size_cells = 1;
    uint32_t node_count = 0;
    const char *node_name = 0;
    const int8_t *fdt_struct_ptr = (const int8_t *) ctx->node;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            fdt_struct_ptr += sizeof(uint32_t);
            str_len = strlen_((const char *) fdt_struct_ptr);
            node_name = (const char *) fdt_struct_ptr;
            if (str_len == 0 && level == 0) {
                fdt_struct_ptr++;
            } else
                fdt_struct_ptr += str_len;
            if (node_count == index && level-1 == ctx->level)
                return node_name;
            if (level-1 == ctx->level)
                node_count += 1;
        } else if (token == FDT_END_NODE) {
            fdt_struct_ptr += sizeof(uint32_t);
            level -= 1;
        } else if (token == FDT_PROP) {
            fdt_struct_ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, fdt_struct_ptr);
            fdt_struct_ptr += sizeof(DeviceTreePropHdr);
            fdt_struct_ptr += prop_hdr.len;
        } else if (token == FDT_NOP) {
            fdt_struct_ptr += sizeof(uint32_t);
        } else if (token == FDT_END) {
            break;
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
    }
    return 0;
}

int devtree_move_to_root(DeviceTreeContext *ctx) {
    if (ctx == 0)
        return -1;
    ctx->node = ctx->root;
    ctx->size_cells = ctx->root_size_cells;
    ctx->address_cells = ctx->root_address_cells;
    ctx->level = 0;
    return 0;
}

const char *devtree_node_name(const DeviceTreeContext *ctx) {
    sys_kassert(ctx != 0);
    return ctx->node_name;
}

bool devtree_property_exists(const char *name, const DeviceTreeContext *ctx) {
    DeviceTreeProp tmp;
    int result = devtree_property(name, &tmp, ctx);
    return result == 0;
}

/*int devtree_load_from_file(const char* file_path, DeviceTreeContext* ctx) {
    struct stat file_stat;
    int stat_res = stat(file_path, &file_stat);
    kassert(stat_res == 0);
    char *buffer = (char *) calloc(file_stat.st_size, sizeof(char));
    FILE *in_fh = fopen(file_path, "rb");
    kassert(in_fh != 0);
    uint32_t read_count = fread(buffer, sizeof(char), file_stat.st_size, in_fh);
    sys_kassert(read_count == file_stat.st_size);
    devtree_print_all(buffer);
    int res = devtree_load_context(buffer, ctx);
    return res;
}*/

int32_t devtree_word_at_index(uint32_t index,
                              const DeviceTreeProp* prop,
                              uint32_t* word_out,
                              const DeviceTreeContext* ctx) {
    if (index >= prop->len)
        return -1;
    uint32_t* word_ptr = (uint32_t*)prop->value;
    *word_out = big2little_l(word_ptr[index]);
    return 0;
}

uint32_t devtree_memory_reservation_count(const DeviceTreeContext* ctx) {
    uint32_t count = 0;
    const DeviceTreeMemReserve* res_ptr = ctx->tree_root + ctx->header.off_mem_rsvmap;
    while (res_ptr->size != 0 && res_ptr->address != 0) {
        count++;
        res_ptr++;
    }
    return count;
}

int devtree_memory_reservation(uint32_t index, DeviceTreeMemReserve* out,
                               const DeviceTreeContext* ctx) {
    uint32_t count = 0;
    const DeviceTreeMemReserve* res_ptr = ctx->tree_root + ctx->header.off_mem_rsvmap;
    while (res_ptr->size != 0 && res_ptr->address != 0) {
        if (count == index) {
            out->address = big2little_dl(res_ptr->address);
            out->size = big2little_dl(res_ptr->size);
            return 0;
        }
        count++;
        res_ptr++;
    }
    return -1;
}

bool devtree_child_node_exists(const char* target_name, DeviceTreeContext* ctx) {
    int32_t level = -1;
    uint32_t str_len = 0;
    uint32_t token = 0;
    DeviceTreePropHdr prop_hdr;
    uint32_t address_cells = 2;
    uint32_t size_cells = 1;
    uint32_t node_count = 0;
    const char *prop_name = 0;
    const char *node_name = 0;
    const int8_t *fdt_struct_ptr = (const int8_t *) ctx->node;
    while (true) {
        token = big2little_l(*((uint32_t *) fdt_struct_ptr));
        if (token == FDT_BEGIN_NODE) {
            level += 1;
            fdt_struct_ptr += sizeof(uint32_t);
            node_name = (const char *) fdt_struct_ptr;
            str_len = strlen_(node_name);
            if (str_len == 0 && level == 0) {
                fdt_struct_ptr++;
            } else
                fdt_struct_ptr += str_len;
            if (ctx->level == level && streq(node_name, target_name)) {
                return true;
            }
        } else if (token == FDT_END_NODE) {
            fdt_struct_ptr += sizeof(uint32_t);
            level -= 1;
        } else if (token == FDT_PROP) {
            fdt_struct_ptr += sizeof(uint32_t);
            devtree_load_prop_hdr(&prop_hdr, fdt_struct_ptr);
            fdt_struct_ptr += sizeof(DeviceTreePropHdr);
            fdt_struct_ptr += prop_hdr.len;
        } else if (token == FDT_NOP) {
            fdt_struct_ptr += sizeof(uint32_t);
        } else if (token == FDT_END) {
            break;
        } else {
            // assume free space
            fdt_struct_ptr++;
        }
    }
    return false;
}