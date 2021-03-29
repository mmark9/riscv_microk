#include "bit_utils.h"

uint32_t little2big_l(uint32_t little) {
    uint32_t ret = 0;
    ret |= ((little & 0x000000FFU) >> 0U) << 24U;
    ret |= ((little & 0x0000FF00U) >> 8U) << 16U;
    ret |= ((little & 0x00FF0000U) >> 16U) << 8U;
    ret |= ((little & 0xFF000000U) >> 24U) << 0U;
    return ret;
}

uint32_t big2little_l(uint32_t big) {
    uint32_t ret = 0;
    ret |= ((big & 0xFF000000U) >> 24U) << 0U;
    ret |= ((big & 0x00FF0000U) >> 16U) << 8U;
    ret |= ((big & 0x0000FF00U) >> 8U) << 16U;
    ret |= ((big & 0x000000FFU) >> 0U) << 24U;
    return ret;
}

uint32_t big2little_dl(uint64_t big) {
    uint64_t ret = 0;
    ret |= ((big & 0xFF00000000000000U) >> 56U) << 0U;
    ret |= ((big & 0x00FF000000000000U) >> 48U) << 8U;
    ret |= ((big & 0x0000FF0000000000U) >> 40U) << 16U;
    ret |= ((big & 0x000000FF00000000U) >> 32U) << 24U;
    ret |= ((big & 0x00000000FF000000U) >> 24U) << 32U;
    ret |= ((big & 0x0000000000FF0000U) >> 16U) << 40U;
    ret |= ((big & 0x000000000000FF00U) >> 8U) << 48U;
    ret |= ((big & 0x00000000000000FFU) >> 0U) << 56U;
    return ret;
}