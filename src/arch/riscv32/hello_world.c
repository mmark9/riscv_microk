volatile unsigned int* const UART0_ADDR = (unsigned int*)0x10000000;

void print_to_uart(const char* str) {
	for (int i = 0; *str != '\0'; str++, i++) {
		*UART0_ADDR = (unsigned int)(*str);
	}
}

void hello_main() {
	print_to_uart("Hello world!");
}
