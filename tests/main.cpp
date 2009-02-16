/*
 * This file is a part of TTMath Mathematical Library
 * and is distributed under the (new) BSD licence.
 * Author: Tomasz Sowa <t.sowa@slimaczek.pl>
 */

/* 
 * Copyright (c) 2006-2008, Tomasz Sowa
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *    
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *    
 *  * Neither the name Tomasz Sowa nor the names of contributors to this
 *    project may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <iostream>
#include <ttmath/ttmath.h>
#include "uinttest.h"

//#include <windows.h>

const char uint_tests_file[] = "tests.uint32";




bool test_lahf()
{
#ifdef TTMATH_PLATFORM64


	#ifndef __GNUC__
			#error "another compiler than GCC is currently not supported in 64bit mode"
	#endif


	std::cout << "Processor 64bit: checking LAHF and SAHF instructions....";

	unsigned long int is_lahf;


	__asm__ __volatile__ (
		
		"push %%rax               \n"
		"push %%rcx               \n"
		"push %%rdx               \n"

		"mov $0x80000001, %%rax   \n"
		"CPUID                    \n"
		"test $1, %%rcx           \n"
		"setnz %%al               \n"
		"movzx %%al, %%rbx        \n"

		"pop %%rdx                \n"
		"pop %%rcx                \n"
		"pop %%rax                \n"

		: "=b" (is_lahf)
		:
	    : "cc"
		);

	if( is_lahf )
	{
		std::cout << "ok" << std::endl;
		return true;
	}

	std::cout << "fail" << std::endl;


	return false;

#endif


	// 32bit platform
return true;
}


void test_uint()
{
	UIntTest test;

	test.set_file_name(uint_tests_file);
	test.go();
}



int main()
{
using namespace ttmath;
	
	if( !test_lahf() )
		return 1;

	test_uint();


return 0;
}
