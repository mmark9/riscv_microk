#include "kprint.h"
#include "terminal.h"

#include <stdint.h>

#define ESC 0x1B

void terminal_BEL() {
    kputchar(0x7);
}
void terminal_BS() {
    kputchar(0x8);
}
void terminal_TAB() {
    kputchar(0x9);
}
void terminal_LF() {
    kputchar(0xa);
}
void terminal_FF() {
    kputchar(0xc);
}
void terminal_CR() {
    kputchar(0xd);
}
// cursor up
void terminal_cuu(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('A');
}
// cursor down
void terminal_cud(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('B');
}
// cursor forward
void terminal_cuf(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('C');
}
// cursor back
void terminal_cub(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('D');
}
// cursor next line
void terminal_cnl(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('E');
}
// cursor previous line
void terminal_cpl(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('F');
}
// cursor horizontal absolute
void terminal_cha(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('G');
}
// cursor position absolute (row/column)
void terminal_cup(uint8_t r, uint8_t c) {
    // 1 based column
    kputchar(ESC);
    kputchar('[');
    kputchar(r);
    kputchar(';');
    kputchar(c);
    kputchar('H');
}
// erase display
void terminal_ed(CsiEDOptions option) {
    kputchar(ESC);
    kputchar('[');
    kputchar(option);
    kputchar('J');
}
// erase line
void terminal_el(CsiELOptions option) {
    kputchar(ESC);
    kputchar('[');
    kputchar(option);
    kputchar('K');
}
// scroll up
void terminal_su(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('S');
}
// scroll down
void terminal_sd(uint8_t n) {
    kputchar(ESC);
    kputchar('[');
    kputchar(n);
    kputchar('T');
}