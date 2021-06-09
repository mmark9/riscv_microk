#ifndef RISCV_MICROK_TERMINAL_H
#define RISCV_MICROK_TERMINAL_H

#include "kprint.h"

#include <stdint.h>


void terminal_BEL();
void terminal_BS();
void terminal_TAB();
void terminal_LF();
void terminal_FF();
void terminal_CR();
// cursor up
void terminal_cuu(uint8_t n);
// cursor down
void terminal_cud(uint8_t n);
// cursor forward
void terminal_cuf(uint8_t n);
// cursor back
void terminal_cub(uint8_t n);
// cursor next line
void terminal_cnl(uint8_t n);
// cursor previous line
void terminal_cpl(uint8_t n);
// cursor horizontal absolute
void terminal_cha(uint8_t n);
// cursor position absolute (row/column)
void terminal_cup(uint8_t r, uint8_t c);
typedef enum {
    CLEAR_FROM_CURSOR_TO_END_OF_SCREEN = 0,
    CLEAR_FROM_CURSOR_TO_BEGINNING_OF_SCREEN = 1,
    CLEAR_ENTIRE_SCREEN = 2,
    CLEAR_ENTIRE_SCREEN_DELETE_BUFFER = 3
} CsiEDOptions;
// erase display
void terminal_ed(CsiEDOptions option);
typedef enum {
    CLEAR_FROM_CURSOR_TO_END_OF_LINE = 0,
    CLEAR_FROM_CURSOR_TO_BEGINNING_OF_LINE = 1,
    CLEAR_ENTIRE_LINE =  2
} CsiELOptions;
// erase line
void terminal_el(CsiELOptions option);
// scroll up
void terminal_su(uint8_t n);
// scroll down
void terminal_sd(uint8_t n);
#define terminal_puts(str) kputs(K_INFO, (str))
#define terminal_printf(fmt, ...) kprintf(K_INFO, (fmt), __VA_ARGS__)
#define terminal_clear() terminal_puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define terminal_putchar(c) kputchar(c)

#endif //RISCV_MICROK_TERMINAL_H
