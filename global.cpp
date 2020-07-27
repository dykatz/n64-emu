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

#include "cpu.h"
#include "mem.h"
#include "rcp.h"

Registers reg;
Registers rcp;
Memory mem;

uint16_t
signExtend(uint8_t in)
{
	if ((in & 0b10000000) >> 8) {
		return 0b1111111100000000 & in;
	} else {
		return 0b0000000000000000 & in;
	}
}

uint32_t
signExtend(uint16_t in)
{
	if ((in & 0b1000000000000000) >> 16) {
		return 0b11111111111111110000000000000000 & in;
	} else {
		return 0b00000000000000000000000000000000 & in;
	}
}

uint64_t
signExtend(uint32_t in)
{
	if ((in & 0b10000000000000000000000000000000) >> 31) {
		return 0b1111111111111111111111111111111100000000000000000000000000000000 &
		       in;
	} else {
		return 0b0000000000000000000000000000000000000000000000000000000000000000 &
		       in;
	}
}
