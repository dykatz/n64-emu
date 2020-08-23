/*
 * Copyright (c) 2020 Justin Warner
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#include "cpu.h"
#include "mem.h"

static int branchNext = -1;

void
execCPU(uint32_t opcode, int context, bool parseOnly)
{
	uint8_t op = (opcode & 0b11111100000000000000000000000000) >> 26;
	/* I-Type (Immediate) variables */
	uint16_t immediate = opcode & 0b00000000000000001111111111111111;
	/* J-Type (Jump) variables */
	uint32_t target = opcode & 0b00000011111111111111111111111111;
	/* R-Type (Register) variables (rs, rt used in I Type as well) */
	uint8_t rs = opcode & 0b00000011111000000000000000000000 >> 21;
	uint8_t rt = opcode & 0b00000000000111110000000000000000 >> 16;
	uint8_t rd = opcode & 0b00000000000000001111100000000000 >> 11;
	uint8_t sa = opcode & 0b00000000000000000000011111000000 >> 6;
	uint8_t funct = opcode & 0b00000000000000000000000000111111;
	if (!parseOnly) {
		switch (op) {
		case 0b00000000:
			if (sa == 0b00000000) {
				switch (funct) {
				case 0b00100000: /* ADD */
					if (reg.gpr[rs] <
					    INT_MAX - reg.gpr[rt]) {
						/* Add integer overflow code! */
					}
					reg.gpr[rd] = ((signed)reg.gpr[rs] +
						       (signed)reg.gpr[rt]);
					break;
				case 0b00100001: /* ADDU */
					reg.gpr[rd] =
						(reg.gpr[rs] + reg.gpr[rt]);
					break;
				case 0b00100100: /* AND */
					reg.gpr[rd] =
						(reg.gpr[rs] & reg.gpr[rt]);
					break;
				case 0b00101100: /* DADD */
					/*
					 * Note: Should only run in 64
					 * bit mode or 32 bit kernel
					 * mode. Otherwise throw
					 * reserved instruction
					 * exception.
					 */
					if (reg.gpr[rs] <
					    INT_MAX - reg.gpr[rt]) {
						/* Add integer overflow code! */
					} else {
						reg.gpr[rd] = ((signed)reg.gpr[rs] +
							       (signed)reg.gpr[rt]);
					}
					break;
				case 0b00101101: /* DADDU */
					/*
					 * Note: Should only run in 64
					 * bit mode or 32 bit kernel
					 * mode. Otherwise throw
					 * reserved instruction
					 * exception.
					 */
					reg.gpr[rd] = ((signed)reg.gpr[rs] +
						       (signed)reg.gpr[rt]);
					break;
				}
			} else {
				switch (funct) {
				case 0b00001101: /* BREAK */
					/* TODO */
					break;
				}
			}
		case 0b00001000: /* ADDI */
			if (reg.gpr[rs] <
			    INT_MAX - reg.gpr[signExtend(immediate)]) {
				/* Add integer overflow code! */
			}
			reg.gpr[rt] = ((signed)reg.gpr[rs] +
				       (signed)signExtend(immediate));
			break;
		case 0b00001001: /* ADDIU */
			reg.gpr[rt] = (reg.gpr[rs] + signExtend(immediate));
			break;
		case 0b00001100: /* ANDI */
			reg.gpr[rt] = (reg.gpr[rs] & immediate);
			break;
		case 0b00010000:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC0 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC0F */
						/* TODO */
						break;
					case 0b00000010: /* BC0FL */
						/* TODO */
						break;
					case 0b00000001: /* BC0T */
						/* TODO */
						break;
					case 0b00000011: /* BC0TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP0 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC0 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010001:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC1 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC1F */
						/* TODO */
						break;
					case 0b00000010: /* BC1FL */
						/* TODO */
						break;
					case 0b00000001: /* BC1T */
						/* TODO */
						break;
					case 0b00000011: /* BC1TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP1 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC1 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010010:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC2 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC2F */
						/* TODO */
						break;
					case 0b00000010: /* BC2FL */
						/* TODO */
						break;
					case 0b00000001: /* BC2T */
						/* TODO */
						break;
					case 0b00000011: /* BC2TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP2 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC2 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010011:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC3 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC3F */
						/* TODO */
						break;
					case 0b00000010: /* BC3FL */
						/* TODO */
						break;
					case 0b00000001: /* BC3T */
						/* TODO */
						break;
					case 0b00000011: /* BC3TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP3 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC3 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00000100: /* BEQ */
			if (reg.gpr[rs] == reg.gpr[rt]) {
				branchNext = mem.mem[reg.pc + 1] +
					     (signExtend(immediate) << 2);
			}
			break;
		case 0b00010100: /* BEQL */
			if (reg.gpr[rs] == reg.gpr[rt]) {
				branchNext = mem.mem[reg.pc + 1] +
					     (signExtend(immediate) << 2);
			} else {
				reg.pc++;
			}
			break;
		case 0b00000001:
			switch (rt) {
			case 0b00000001: /* BGEZ */
				if (reg.gpr[rs] >= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			case 0b00010001: /* BGEZAL */
				reg.gpr[31] = mem.mem[reg.pc + 1];
				if (reg.gpr[rs] >= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			case 0b00010011: /* BGEZALL */
				reg.gpr[31] = mem.mem[reg.pc + 1];
				if (reg.gpr[rs] >= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			case 0b00000011: /* BGEZL */
				if (reg.gpr[rs] >= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			case 0b00000000: /* BLTZ */
				if (reg.gpr[rs] < 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			case 0b00010000: /* BLTZAL */
				reg.gpr[31] = mem.mem[reg.pc + 1];
				if (reg.gpr[rs] < 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			case 0b00010010: /* BLTZALL */
				reg.gpr[31] = mem.mem[reg.pc + 1];
				if (reg.gpr[rs] < 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			case 0b00000010: /* BLTZL */
				if (reg.gpr[rs] < 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			}
			break;
		case 0b00000111:
			switch (rt) {
			case 0b00000000: /* BGTZ */
				if (reg.gpr[rs] > 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			}
			break;
		case 0b00010111:
			switch (rt) {
			case 0b00000000: /* BGTZL */
				if (reg.gpr[rs] > 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			}
			break;
		case 0b00000110:
			switch (rt) {
			case 0b00000000: /* BLEZ */
				if (reg.gpr[rs] <= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				}
				break;
			}
			break;
		case 0b00010110:
			switch (rt) {
			case 0b00000000: /* BLEZL */
				if (reg.gpr[rs] <= 0) {
					branchNext =
						mem.mem[reg.pc + 1] +
						(signExtend(immediate) << 2);
				} else {
					reg.pc++;
				}
				break;
			}
			break;
		case 0b00000101: /* BNE */
			if (reg.gpr[rs] != reg.gpr[rt]) {
				branchNext = mem.mem[reg.pc + 1] +
					     (signExtend(immediate) << 2);
			}
			break;
		case 0b00010101: /* BNEL */
			if (reg.gpr[rs] != reg.gpr[rt]) {
				branchNext = mem.mem[reg.pc + 1] +
					     (signExtend(immediate) << 2);
			} else {
				reg.pc++;
			}
			break;
		case 0b00101111: /* CACHE */
			/* TODO */
			break;
		case 0b00011000: /* DADDI */
			/*
			 * Note: Should only run in 64
			 * bit mode or 32 bit kernel
			 * mode. Otherwise throw
			 * reserved instruction
			 * exception.
			 */
			if (reg.gpr[rs] <
			    INT_MAX - reg.gpr[rt]) {
				/* Add integer overflow code! */
			} else {
				reg.gpr[rt] = (signExtend(immediate) +
					       (signed)reg.gpr[rs]);
			}
		break;
		case 0b00011001: /* DADDIU */
			/*
			 * Note: Should only run in 64
			 * bit mode or 32 bit kernel
			 * mode. Otherwise throw
			 * reserved instruction
			 * exception.
			 */
			reg.gpr[rt] = (signExtend(immediate) +
				       (signed)reg.gpr[rs]);
		default:
			/* Add unknown opcode! */
			break;
			if (branchNext >= 0) {
				reg.pc = branchNext;
				branchNext = -1;
			}
		}
		/* Interpreter ends HERE, parser follows */
	} else {
		switch (op) {
		case 0b00000000: /* ADD */
			std::cout << "ADD";
			break;
		case 0b00001000: /* ADDI */
			std::cout << "ADDI";
			break;
		case 0b00001001: /* ADDIU */
			std::cout << "ADDIU";
			break;
		case 0b00101111: /* CACHE */
			/* TODO */
			break;
		case 0b00010000:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC0 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC0F */
						/* TODO */
						break;
					case 0b00000010: /* BC0FL */
						/* TODO */
						break;
					case 0b00000001: /* BC0T */
						/* TODO */
						break;
					case 0b00000011: /* BC0TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP0 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC0 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010001:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC1 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC1F */
						/* TODO */
						break;
					case 0b00000010: /* BC1FL */
						/* TODO */
						break;
					case 0b00000001: /* BC1T */
						/* TODO */
						break;
					case 0b00000011: /* BC1TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP1 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC1 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010010:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC2 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC2F */
						/* TODO */
						break;
					case 0b00000010: /* BC2FL */
						/* TODO */
						break;
					case 0b00000001: /* BC2T */
						/* TODO */
						break;
					case 0b00000011: /* BC2TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP2 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC2 */
						/* TODO */
					}
					break;
				}
			}
			break;
		case 0b00010011:
			if ((sa == 0) && (funct == 0)) {
				switch (rs) {
				case 0b00000010: /* CFC3 */
					/* TODO */
					break;
				}
			} else {
				switch (rs) {
				case 0b00001000:
					switch (rt) {
					case 0b00000000: /* BC3F */
						/* TODO */
						break;
					case 0b00000010: /* BC3FL */
						/* TODO */
						break;
					case 0b00000001: /* BC3T */
						/* TODO */
						break;
					case 0b00000011: /* BC3TL */
						/* TODO */
						break;
					}
					break;
				case 0b00010000: /* COP3 */
					/* TODO */
					break;
				case 0b0000110:
					if (opcode &
					    0b00000000000000000000011111111111) { /* CTC3 */
						/* TODO */
					}
					break;
				}
			}
			break;
		default:
			/* Add unknown opcode! */
			break;
		}
	}
}
