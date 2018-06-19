#include "isa.h"
#include "print.h"

void print_architecture_string() {
	printf("Architecture detected: ");
	misa_register_t misa;
	read_csr_register(CSR_MISA, &misa);
	int isa_width = -1;
	switch (misa.isa_width) {
	case 1:
		isa_width = 32;
		break;
	case 2:
		isa_width = 64;
		break;
	case 3:
		isa_width = 128;
		break;
	}
	char arch_buffer[27];
	int buf_index = 0;
	if (isa_width == -1) {
		printf("\nUnknown RISCV architecture! misa MXL reports %d",
				misa.isa_width);
	} else {
		//  RV [32, 64, 128] I, M, A, F, D, G, Q, L, C, B, J, T, P, V, N
		if (misa.base_isa_ext) {
			arch_buffer[buf_index++] = 'I';
		}
		if (misa.int_mul_div_ext) {
			arch_buffer[buf_index++] = 'M';
		}
		if (misa.atomic_ext) {
			arch_buffer[buf_index++] = 'A';
		}
		if (misa.single_prec_float_ext) {
			arch_buffer[buf_index++] = 'F';
		}
		if (misa.double_prec_float_ext) {
			arch_buffer[buf_index++] = 'D';
		}
		if (misa.additional_ext) {
			arch_buffer[buf_index++] = 'G';
		}
		if (misa.quad_prec_float_ext) {
			arch_buffer[buf_index++] = 'Q';
		}
		if (misa.compressed_ext) {
			arch_buffer[buf_index++] = 'C';
		}
		if (misa.user_int_ext) {
			arch_buffer[buf_index++] = 'N';
		}
		arch_buffer[buf_index++] = '\0';
		printf("RV%d %s", isa_width, arch_buffer);
	}
}

void hello_main() {
	print_architecture_string();
}

