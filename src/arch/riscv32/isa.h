#ifndef SRC_ARCH_RISCV32_ISA_H_
#define SRC_ARCH_RISCV32_ISA_H_


typedef struct {
	// Extensions[0-25] (WARL)
	unsigned int atomic_ext:1;            //A
	unsigned int reserved_0:1;            //B
	unsigned int compressed_ext:1;        //C
	unsigned int double_prec_float_ext:1; //D
	unsigned int rv32e_base_isa:1;        //E
	unsigned int single_prec_float_ext:1; //F
	unsigned int additional_ext:1;        //G
	unsigned int reserved_1:1;            //H
	unsigned int base_isa_ext:1;          //I
	unsigned int reserved_2:1;            //J
	unsigned int reserved_3:1;            //K
	unsigned int reserved_4:1;            //L
	unsigned int int_mul_div_ext:1;       //M
	unsigned int user_int_ext:1;          //N
	unsigned int reserved_5:1;            //O
	unsigned int reserved_6:1;            //P
	unsigned int quad_prec_float_ext:1;   //Q
	unsigned int reserved_7:1;            //R
	unsigned int supervisor_mode_ext:1;   //S
	unsigned int reserved_8:1;            //T
	unsigned int user_mode_ext:1;         //U
	unsigned int reserved_9:1;            //V
	unsigned int reserved_A:1;            //W
	unsigned int non_standard_ext:1;      //X
	unsigned int reserved_B:1;            //Y
	unsigned int reserved_C:1;            //Z
	// Ignored Field[26-29] (WIRI)
	unsigned int ignore:4;
	// ISA width[30-31] (WARL)
	unsigned int isa_width:2;
} misa_register_t;

misa_register_t get_machine_isa_register_value() {
	misa_register_t ret_val;
	asm volatile ("csrr t0, misa\n\t"
			  "sw t0, %0"
			  : "=m" (ret_val)
			  :
			  );
	return ret_val;
}

#endif /* SRC_ARCH_RISCV32_ISA_H_ */
