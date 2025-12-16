#include "disassembler.h"

#include "common.h"

static const char* GetOpcodeString(const ClownZ80_Opcode opcode)
{
	switch (opcode)
	{
		case CLOWNZ80_OPCODE_NOP:
			return "nop";
		case CLOWNZ80_OPCODE_EX_AF_AF:
			return "ex";
		case CLOWNZ80_OPCODE_DJNZ:
			return "djnz";
		case CLOWNZ80_OPCODE_JR_UNCONDITIONAL:
			return "jr";
		case CLOWNZ80_OPCODE_JR_CONDITIONAL:
			return "jr";
		case CLOWNZ80_OPCODE_LD_16BIT:
			return "ld";
		case CLOWNZ80_OPCODE_ADD_HL:
			return "add";
		case CLOWNZ80_OPCODE_LD_8BIT:
			return "ld";
		case CLOWNZ80_OPCODE_INC_16BIT:
			return "inc";
		case CLOWNZ80_OPCODE_DEC_16BIT:
			return "dec";
		case CLOWNZ80_OPCODE_INC_8BIT:
			return "inc";
		case CLOWNZ80_OPCODE_DEC_8BIT:
			return "dec";
		case CLOWNZ80_OPCODE_RLCA:
			return "rlca";
		case CLOWNZ80_OPCODE_RRCA:
			return "rrca";
		case CLOWNZ80_OPCODE_RLA:
			return "rla";
		case CLOWNZ80_OPCODE_RRA:
			return "rra";
		case CLOWNZ80_OPCODE_DAA:
			return "daa";
		case CLOWNZ80_OPCODE_CPL:
			return "cpl";
		case CLOWNZ80_OPCODE_SCF:
			return "scf";
		case CLOWNZ80_OPCODE_CCF:
			return "ccf";
		case CLOWNZ80_OPCODE_HALT:
			return "halt";
		case CLOWNZ80_OPCODE_ADD_A:
			return "add";
		case CLOWNZ80_OPCODE_ADC_A:
			return "adc";
		case CLOWNZ80_OPCODE_SUB:
			return "sub";
		case CLOWNZ80_OPCODE_SBC_A:
			return "sbc";
		case CLOWNZ80_OPCODE_AND:
			return "and";
		case CLOWNZ80_OPCODE_XOR:
			return "xor";
		case CLOWNZ80_OPCODE_OR:
			return "or";
		case CLOWNZ80_OPCODE_CP:
			return "cp";
		case CLOWNZ80_OPCODE_RET_CONDITIONAL:
			return "ret";
		case CLOWNZ80_OPCODE_POP:
			return "pop";
		case CLOWNZ80_OPCODE_RET_UNCONDITIONAL:
			return "ret";
		case CLOWNZ80_OPCODE_EXX:
			return "exx";
		case CLOWNZ80_OPCODE_JP_HL:
			return "jp";
		case CLOWNZ80_OPCODE_LD_SP_HL:
			return "ld";
		case CLOWNZ80_OPCODE_JP_CONDITIONAL:
			return "jp";
		case CLOWNZ80_OPCODE_JP_UNCONDITIONAL:
			return "jp";
		case CLOWNZ80_OPCODE_CB_PREFIX:
			return "[CB PREFIX]";
		case CLOWNZ80_OPCODE_OUT:
			return "out";
		case CLOWNZ80_OPCODE_IN:
			return "in";
		case CLOWNZ80_OPCODE_EX_SP_HL:
			return "ex";
		case CLOWNZ80_OPCODE_EX_DE_HL:
			return "ex";
		case CLOWNZ80_OPCODE_DI:
			return "di";
		case CLOWNZ80_OPCODE_EI:
			return "ei";
		case CLOWNZ80_OPCODE_CALL_CONDITIONAL:
			return "call";
		case CLOWNZ80_OPCODE_PUSH:
			return "push";
		case CLOWNZ80_OPCODE_CALL_UNCONDITIONAL:
			return "call";
		case CLOWNZ80_OPCODE_DD_PREFIX:
			return "[DD PREFIX]";
		case CLOWNZ80_OPCODE_ED_PREFIX:
			return "[ED PREFIX]";
		case CLOWNZ80_OPCODE_FD_PREFIX:
			return "[FD PREFIX]";
		case CLOWNZ80_OPCODE_RST:
			return "rst";
		case CLOWNZ80_OPCODE_RLC:
			return "rlc";
		case CLOWNZ80_OPCODE_RRC:
			return "rrc";
		case CLOWNZ80_OPCODE_RL:
			return "rl";
		case CLOWNZ80_OPCODE_RR:
			return "rr";
		case CLOWNZ80_OPCODE_SLA:
			return "sla";
		case CLOWNZ80_OPCODE_SRA:
			return "sra";
		case CLOWNZ80_OPCODE_SLL:
			return "sll";
		case CLOWNZ80_OPCODE_SRL:
			return "srl";
		case CLOWNZ80_OPCODE_BIT:
			return "bit";
		case CLOWNZ80_OPCODE_RES:
			return "res";
		case CLOWNZ80_OPCODE_SET:
			return "set";
		case CLOWNZ80_OPCODE_IN_REGISTER:
			return "in";
		case CLOWNZ80_OPCODE_IN_NO_REGISTER:
			return "in";
		case CLOWNZ80_OPCODE_OUT_REGISTER:
			return "out";
		case CLOWNZ80_OPCODE_OUT_NO_REGISTER:
			return "out";
		case CLOWNZ80_OPCODE_SBC_HL:
			return "sbc";
		case CLOWNZ80_OPCODE_ADC_HL:
			return "adc";
		case CLOWNZ80_OPCODE_NEG:
			return "neg";
		case CLOWNZ80_OPCODE_RETN:
			return "retn";
		case CLOWNZ80_OPCODE_RETI:
			return "reti";
		case CLOWNZ80_OPCODE_IM:
			return "im";
		case CLOWNZ80_OPCODE_LD_I_A:
			return "ld";
		case CLOWNZ80_OPCODE_LD_R_A:
			return "ld";
		case CLOWNZ80_OPCODE_LD_A_I:
			return "ld";
		case CLOWNZ80_OPCODE_LD_A_R:
			return "ld";
		case CLOWNZ80_OPCODE_RRD:
			return "rrd";
		case CLOWNZ80_OPCODE_RLD:
			return "rld";
		case CLOWNZ80_OPCODE_LDI:
			return "ldi";
		case CLOWNZ80_OPCODE_LDD:
			return "ldd";
		case CLOWNZ80_OPCODE_LDIR:
			return "ldir";
		case CLOWNZ80_OPCODE_LDDR:
			return "lddr";
		case CLOWNZ80_OPCODE_CPI:
			return "cpi";
		case CLOWNZ80_OPCODE_CPD:
			return "cpd";
		case CLOWNZ80_OPCODE_CPIR:
			return "cpir";
		case CLOWNZ80_OPCODE_CPDR:
			return "cpdr";
		case CLOWNZ80_OPCODE_INI:
			return "ini";
		case CLOWNZ80_OPCODE_IND:
			return "ind";
		case CLOWNZ80_OPCODE_INIR:
			return "inir";
		case CLOWNZ80_OPCODE_INDR:
			return "indr";
		case CLOWNZ80_OPCODE_OUTI:
			return "outi";
		case CLOWNZ80_OPCODE_OUTD:
			return "outd";
		case CLOWNZ80_OPCODE_OTIR:
			return "otir";
		case CLOWNZ80_OPCODE_OTDR:
			return "otdr";
	}

	return "[INVALID]";
}

static const char* GetOperandString(const ClownZ80_Operand operand)
{
	switch (operand)
	{
		case CLOWNZ80_OPERAND_NONE:
			return "[NONE]";
		case CLOWNZ80_OPERAND_A:
			return "a";
		case CLOWNZ80_OPERAND_B:
			return "b";
		case CLOWNZ80_OPERAND_C:
			return "c";
		case CLOWNZ80_OPERAND_D:
			return "d";
		case CLOWNZ80_OPERAND_E:
			return "e";
		case CLOWNZ80_OPERAND_H:
			return "h";
		case CLOWNZ80_OPERAND_L:
			return "l";
		case CLOWNZ80_OPERAND_IXH:
			return "ixh";
		case CLOWNZ80_OPERAND_IXL:
			return "ixl";
		case CLOWNZ80_OPERAND_IYH:
			return "iyh";
		case CLOWNZ80_OPERAND_IYL:
			return "iyl";
		case CLOWNZ80_OPERAND_AF:
			return "af";
		case CLOWNZ80_OPERAND_BC:
			return "bc";
		case CLOWNZ80_OPERAND_DE:
			return "de";
		case CLOWNZ80_OPERAND_HL:
			return "hl";
		case CLOWNZ80_OPERAND_IX:
			return "ix";
		case CLOWNZ80_OPERAND_IY:
			return "iy";
		case CLOWNZ80_OPERAND_PC:
			return "pc";
		case CLOWNZ80_OPERAND_SP:
			return "sp";
		case CLOWNZ80_OPERAND_BC_INDIRECT:
			return "(bc)";
		case CLOWNZ80_OPERAND_DE_INDIRECT:
			return "(de)";
		case CLOWNZ80_OPERAND_HL_INDIRECT:
			return "(hl)";
		case CLOWNZ80_OPERAND_IX_INDIRECT:
			return "(ix+X)";
		case CLOWNZ80_OPERAND_IY_INDIRECT:
			return "(iy+X)";
		case CLOWNZ80_OPERAND_ADDRESS:
			return "[ADDRESS]";
		case CLOWNZ80_OPERAND_LITERAL_8BIT:
			return "[LITERAL]";
		case CLOWNZ80_OPERAND_LITERAL_16BIT:
			return "[LITERAL]";
	}

	return "[INVALID]";
}

static const char* GetConditionString(const ClownZ80_Condition condition)
{
	switch (condition)
	{
		case CLOWNZ80_CONDITION_NOT_ZERO:
			return "nz";
		case CLOWNZ80_CONDITION_ZERO:
			return "z";
		case CLOWNZ80_CONDITION_NOT_CARRY:
			return "nc";
		case CLOWNZ80_CONDITION_CARRY:
			return "c";
		case CLOWNZ80_CONDITION_PARITY_OVERFLOW:
			return "po";
		case CLOWNZ80_CONDITION_PARITY_EQUALITY:
			return "pe";
		case CLOWNZ80_CONDITION_PLUS:
			return "p";
		case CLOWNZ80_CONDITION_MINUS:
			return "m";
	}

	return "[INVALID]";
}

static cc_bool IsTerminatingInstruction(const ClownZ80_Opcode opcode)
{
	switch (opcode)
	{
		case CLOWNZ80_OPCODE_JR_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_RET_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_JP_HL:
		case CLOWNZ80_OPCODE_JP_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_RETN:
		case CLOWNZ80_OPCODE_RETI:
			return cc_true;

		case CLOWNZ80_OPCODE_NOP:
		case CLOWNZ80_OPCODE_EX_AF_AF:
		case CLOWNZ80_OPCODE_DJNZ:
		case CLOWNZ80_OPCODE_JR_CONDITIONAL:
		case CLOWNZ80_OPCODE_LD_16BIT:
		case CLOWNZ80_OPCODE_ADD_HL:
		case CLOWNZ80_OPCODE_LD_8BIT:
		case CLOWNZ80_OPCODE_INC_16BIT:
		case CLOWNZ80_OPCODE_DEC_16BIT:
		case CLOWNZ80_OPCODE_INC_8BIT:
		case CLOWNZ80_OPCODE_DEC_8BIT:
		case CLOWNZ80_OPCODE_RLCA:
		case CLOWNZ80_OPCODE_RRCA:
		case CLOWNZ80_OPCODE_RLA:
		case CLOWNZ80_OPCODE_RRA:
		case CLOWNZ80_OPCODE_DAA:
		case CLOWNZ80_OPCODE_CPL:
		case CLOWNZ80_OPCODE_SCF:
		case CLOWNZ80_OPCODE_CCF:
		case CLOWNZ80_OPCODE_HALT:
		case CLOWNZ80_OPCODE_ADD_A:
		case CLOWNZ80_OPCODE_ADC_A:
		case CLOWNZ80_OPCODE_SUB:
		case CLOWNZ80_OPCODE_SBC_A:
		case CLOWNZ80_OPCODE_AND:
		case CLOWNZ80_OPCODE_XOR:
		case CLOWNZ80_OPCODE_OR:
		case CLOWNZ80_OPCODE_CP:
		case CLOWNZ80_OPCODE_RET_CONDITIONAL:
		case CLOWNZ80_OPCODE_POP:
		case CLOWNZ80_OPCODE_EXX:
		case CLOWNZ80_OPCODE_LD_SP_HL:
		case CLOWNZ80_OPCODE_JP_CONDITIONAL:
		case CLOWNZ80_OPCODE_CB_PREFIX:
		case CLOWNZ80_OPCODE_OUT:
		case CLOWNZ80_OPCODE_IN:
		case CLOWNZ80_OPCODE_EX_SP_HL:
		case CLOWNZ80_OPCODE_EX_DE_HL:
		case CLOWNZ80_OPCODE_DI:
		case CLOWNZ80_OPCODE_EI:
		case CLOWNZ80_OPCODE_CALL_CONDITIONAL:
		case CLOWNZ80_OPCODE_PUSH:
		case CLOWNZ80_OPCODE_CALL_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_DD_PREFIX:
		case CLOWNZ80_OPCODE_ED_PREFIX:
		case CLOWNZ80_OPCODE_FD_PREFIX:
		case CLOWNZ80_OPCODE_RST:
		case CLOWNZ80_OPCODE_RLC:
		case CLOWNZ80_OPCODE_RRC:
		case CLOWNZ80_OPCODE_RL:
		case CLOWNZ80_OPCODE_RR:
		case CLOWNZ80_OPCODE_SLA:
		case CLOWNZ80_OPCODE_SRA:
		case CLOWNZ80_OPCODE_SLL:
		case CLOWNZ80_OPCODE_SRL:
		case CLOWNZ80_OPCODE_BIT:
		case CLOWNZ80_OPCODE_RES:
		case CLOWNZ80_OPCODE_SET:
		case CLOWNZ80_OPCODE_IN_REGISTER:
		case CLOWNZ80_OPCODE_IN_NO_REGISTER:
		case CLOWNZ80_OPCODE_OUT_REGISTER:
		case CLOWNZ80_OPCODE_OUT_NO_REGISTER:
		case CLOWNZ80_OPCODE_SBC_HL:
		case CLOWNZ80_OPCODE_ADC_HL:
		case CLOWNZ80_OPCODE_NEG:
		case CLOWNZ80_OPCODE_IM:
		case CLOWNZ80_OPCODE_LD_I_A:
		case CLOWNZ80_OPCODE_LD_R_A:
		case CLOWNZ80_OPCODE_LD_A_I:
		case CLOWNZ80_OPCODE_LD_A_R:
		case CLOWNZ80_OPCODE_RRD:
		case CLOWNZ80_OPCODE_RLD:
		case CLOWNZ80_OPCODE_LDI:
		case CLOWNZ80_OPCODE_LDD:
		case CLOWNZ80_OPCODE_LDIR:
		case CLOWNZ80_OPCODE_LDDR:
		case CLOWNZ80_OPCODE_CPI:
		case CLOWNZ80_OPCODE_CPD:
		case CLOWNZ80_OPCODE_CPIR:
		case CLOWNZ80_OPCODE_CPDR:
		case CLOWNZ80_OPCODE_INI:
		case CLOWNZ80_OPCODE_IND:
		case CLOWNZ80_OPCODE_INIR:
		case CLOWNZ80_OPCODE_INDR:
		case CLOWNZ80_OPCODE_OUTI:
		case CLOWNZ80_OPCODE_OUTD:
		case CLOWNZ80_OPCODE_OTIR:
		case CLOWNZ80_OPCODE_OTDR:
			return cc_false;
	}

	return cc_false;
}

static void PrintSpecialOperands(const ClownZ80_InstructionMetadata* const metadata, CC_ATTRIBUTE_PRINTF(2, 3) const ClownZ80_PrintCallback print_callback, const void* const user_data)
{
	switch ((ClownZ80_Opcode)metadata->opcode)
	{
		case CLOWNZ80_OPCODE_EX_AF_AF:
			print_callback((void*)user_data, "af,af'");
			break;

		case CLOWNZ80_OPCODE_RET_CONDITIONAL:
			print_callback((void*)user_data, "%s", GetConditionString(metadata->condition));
			break;

		case CLOWNZ80_OPCODE_JR_CONDITIONAL:
		case CLOWNZ80_OPCODE_JP_CONDITIONAL:
		case CLOWNZ80_OPCODE_CALL_CONDITIONAL:
			print_callback((void*)user_data, "%s,", GetConditionString(metadata->condition));
			break;

		case CLOWNZ80_OPCODE_EX_SP_HL:
			print_callback((void*)user_data, "(sp),");
			break;

		case CLOWNZ80_OPCODE_EX_DE_HL:
			print_callback((void*)user_data, "de,hl");
			break;

		case CLOWNZ80_OPCODE_RST:
		case CLOWNZ80_OPCODE_IM:
			print_callback((void*)user_data, "%d", metadata->embedded_literal);
			break;

		case CLOWNZ80_OPCODE_BIT:
		case CLOWNZ80_OPCODE_RES:
		case CLOWNZ80_OPCODE_SET:
			print_callback((void*)user_data, "%d,", metadata->embedded_literal);
			break;

		case CLOWNZ80_OPCODE_LD_I_A:
			print_callback((void*)user_data, "i,a");
			break;

		case CLOWNZ80_OPCODE_LD_R_A:
			print_callback((void*)user_data, "r,a");
			break;

		case CLOWNZ80_OPCODE_LD_A_I:
			print_callback((void*)user_data, "a,i");
			break;

		case CLOWNZ80_OPCODE_LD_A_R:
			print_callback((void*)user_data, "a,r");
			break;

		case CLOWNZ80_OPCODE_NOP:
		case CLOWNZ80_OPCODE_DJNZ:
		case CLOWNZ80_OPCODE_JR_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_LD_16BIT:
		case CLOWNZ80_OPCODE_ADD_HL:
		case CLOWNZ80_OPCODE_LD_8BIT:
		case CLOWNZ80_OPCODE_INC_16BIT:
		case CLOWNZ80_OPCODE_DEC_16BIT:
		case CLOWNZ80_OPCODE_INC_8BIT:
		case CLOWNZ80_OPCODE_DEC_8BIT:
		case CLOWNZ80_OPCODE_RLCA:
		case CLOWNZ80_OPCODE_RRCA:
		case CLOWNZ80_OPCODE_RLA:
		case CLOWNZ80_OPCODE_RRA:
		case CLOWNZ80_OPCODE_DAA:
		case CLOWNZ80_OPCODE_CPL:
		case CLOWNZ80_OPCODE_SCF:
		case CLOWNZ80_OPCODE_CCF:
		case CLOWNZ80_OPCODE_HALT:
		case CLOWNZ80_OPCODE_ADD_A:
		case CLOWNZ80_OPCODE_ADC_A:
		case CLOWNZ80_OPCODE_SUB:
		case CLOWNZ80_OPCODE_SBC_A:
		case CLOWNZ80_OPCODE_AND:
		case CLOWNZ80_OPCODE_XOR:
		case CLOWNZ80_OPCODE_OR:
		case CLOWNZ80_OPCODE_CP:
		case CLOWNZ80_OPCODE_POP:
		case CLOWNZ80_OPCODE_RET_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_EXX:
		case CLOWNZ80_OPCODE_JP_HL:
		case CLOWNZ80_OPCODE_LD_SP_HL:
		case CLOWNZ80_OPCODE_JP_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_CB_PREFIX:
		case CLOWNZ80_OPCODE_OUT:
		case CLOWNZ80_OPCODE_IN:
		case CLOWNZ80_OPCODE_DI:
		case CLOWNZ80_OPCODE_EI:
		case CLOWNZ80_OPCODE_PUSH:
		case CLOWNZ80_OPCODE_CALL_UNCONDITIONAL:
		case CLOWNZ80_OPCODE_DD_PREFIX:
		case CLOWNZ80_OPCODE_ED_PREFIX:
		case CLOWNZ80_OPCODE_FD_PREFIX:
		case CLOWNZ80_OPCODE_RLC:
		case CLOWNZ80_OPCODE_RRC:
		case CLOWNZ80_OPCODE_RL:
		case CLOWNZ80_OPCODE_RR:
		case CLOWNZ80_OPCODE_SLA:
		case CLOWNZ80_OPCODE_SRA:
		case CLOWNZ80_OPCODE_SLL:
		case CLOWNZ80_OPCODE_SRL:
		case CLOWNZ80_OPCODE_IN_REGISTER:
		case CLOWNZ80_OPCODE_IN_NO_REGISTER:
		case CLOWNZ80_OPCODE_OUT_REGISTER:
		case CLOWNZ80_OPCODE_OUT_NO_REGISTER:
		case CLOWNZ80_OPCODE_SBC_HL:
		case CLOWNZ80_OPCODE_ADC_HL:
		case CLOWNZ80_OPCODE_NEG:
		case CLOWNZ80_OPCODE_RETN:
		case CLOWNZ80_OPCODE_RETI:
		case CLOWNZ80_OPCODE_RRD:
		case CLOWNZ80_OPCODE_RLD:
		case CLOWNZ80_OPCODE_LDI:
		case CLOWNZ80_OPCODE_LDD:
		case CLOWNZ80_OPCODE_LDIR:
		case CLOWNZ80_OPCODE_LDDR:
		case CLOWNZ80_OPCODE_CPI:
		case CLOWNZ80_OPCODE_CPD:
		case CLOWNZ80_OPCODE_CPIR:
		case CLOWNZ80_OPCODE_CPDR:
		case CLOWNZ80_OPCODE_INI:
		case CLOWNZ80_OPCODE_IND:
		case CLOWNZ80_OPCODE_INIR:
		case CLOWNZ80_OPCODE_INDR:
		case CLOWNZ80_OPCODE_OUTI:
		case CLOWNZ80_OPCODE_OUTD:
		case CLOWNZ80_OPCODE_OTIR:
		case CLOWNZ80_OPCODE_OTDR:
			break;
	}
}

cc_bool ClownZ80_Disassemble(const unsigned char* const machine_code, size_t* const bytes_read, CC_ATTRIBUTE_PRINTF(2, 3) const ClownZ80_PrintCallback print_callback, const void* const user_data)
{
	ClownZ80_InstructionMode instruction_mode = CLOWNZ80_INSTRUCTION_MODE_NORMAL;
	ClownZ80_RegisterMode register_mode = CLOWNZ80_REGISTER_MODE_HL;
	ClownZ80_InstructionMetadata metadata;

	*bytes_read = 0;

	for (;;)
	{
		ClownZ80_DecodeInstructionMetadata(&metadata, instruction_mode, register_mode, machine_code[*bytes_read]);
		++*bytes_read;

		switch (metadata.opcode)
		{
			case CLOWNZ80_OPCODE_CB_PREFIX:
				instruction_mode = CLOWNZ80_INSTRUCTION_MODE_BITS;
				continue;
			case CLOWNZ80_OPCODE_DD_PREFIX:
				register_mode = CLOWNZ80_REGISTER_MODE_IX;
				continue;
			case CLOWNZ80_OPCODE_ED_PREFIX:
				instruction_mode = CLOWNZ80_INSTRUCTION_MODE_MISC;
				continue;
			case CLOWNZ80_OPCODE_FD_PREFIX:
				register_mode = CLOWNZ80_REGISTER_MODE_IY;
				continue;
		}

		break;
	}

	print_callback((void*)user_data, "%-5s", GetOpcodeString(metadata.opcode));
	PrintSpecialOperands(&metadata, print_callback, user_data);

	if (metadata.operands[0] != CLOWNZ80_OPERAND_NONE && metadata.operands[1] != CLOWNZ80_OPERAND_NONE)
		print_callback((void*)user_data, "%s,%s", GetOperandString(metadata.operands[1]), GetOperandString(metadata.operands[0]));
	else if (metadata.operands[0] != CLOWNZ80_OPERAND_NONE)
		print_callback((void*)user_data, "%s", GetOperandString(metadata.operands[0]));
	else if (metadata.operands[1] != CLOWNZ80_OPERAND_NONE)
		print_callback((void*)user_data, "%s", GetOperandString(metadata.operands[1]));

	print_callback((void*)user_data, "\n");

	return !IsTerminatingInstruction(metadata.opcode);
}
