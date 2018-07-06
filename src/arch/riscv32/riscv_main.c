#include "isa.h"
#include "csr.h"
#include "print.h"


void riscv_print_architecture_string() {
	printf("Architecture detected: ");
	misa_register_t misa;
	misa.value = 0;
	riscv_read_csr_register(CSR_MISA, &misa);
	int isa_width = -1;
	switch (misa.fields.isa_width) {
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
				misa.fields.isa_width);
	} else {
		//  RV [32, 64, 128] I, M, A, F, D, G, Q, L, C, B, J, T, P, V, N
		if (misa.fields.base_isa_ext) {
			arch_buffer[buf_index++] = 'I';
		}
		if (misa.fields.int_mul_div_ext) {
			arch_buffer[buf_index++] = 'M';
		}
		if (misa.fields.atomic_ext) {
			arch_buffer[buf_index++] = 'A';
		}
		if (misa.fields.single_prec_float_ext) {
			arch_buffer[buf_index++] = 'F';
		}
		if (misa.fields.double_prec_float_ext) {
			arch_buffer[buf_index++] = 'D';
		}
		if (misa.fields.additional_ext) {
			arch_buffer[buf_index++] = 'G';
		}
		if (misa.fields.quad_prec_float_ext) {
			arch_buffer[buf_index++] = 'Q';
		}
		if (misa.fields.compressed_ext) {
			arch_buffer[buf_index++] = 'C';
		}
		if (misa.fields.user_int_ext) {
			arch_buffer[buf_index++] = 'N';
		}
		arch_buffer[buf_index++] = '\0';
		printf("RV%d %s", isa_width, arch_buffer);
	}
}

int sum(int a, int b) {
	return a + b;
}

void riscv_main() {
	riscv_print_architecture_string();
	int a,b;
	int r = sum(a, b);
	riscv_machine_mode_do_setup();
}

