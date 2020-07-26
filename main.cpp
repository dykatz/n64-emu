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

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <climits>
#include <SDL.h>
#include "mem.h"
#include "cpu.h"
#include "rcp.h"

extern Registers reg;
extern Registers rcp;

/*
 * Personal Notes:
 * -COP0 is
 * -COP1 is an internal 64-bit FPU
 * -COP2 is 
 * -COP3 is
 */

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

	return 0;
}

void
tick()
{
    for (long long i = 0; i < 31248125; i++) {
        for (int j = 0; j < 3; j++) {
			execCPU(mem.mem[reg.pc], false);
			reg.pc++;
		}
        for (int k = 0; k < 2; k++) {
			execRCP(mem.mem[rcp.pc], false);
			rcp.pc++;
		}
	}
}
