/*
 * This file is a part of TTMath Mathematical Library
 * and is distributed under the (new) BSD licence.
 * Author: Tomasz Sowa <t.sowa@slimaczek.pl>
 */

/* 
 * Copyright (c) 2006-2009, Tomasz Sowa
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



const char uint_tests_file[] = "tests.uint32";



void test_uint()
{
	UIntTest test;

	test.set_file_name(uint_tests_file);
	test.go();
}



int main()
{
using namespace ttmath;


/*
Int<300> uu, oo;

	uu = -2;
	oo = 5;

	uint ccc = uu.Pow(oo);

	if( ccc )
		std::cout << "carry: " << ccc << std::endl;
	else
		std::cout << uu << std::endl;
return 0;	
*/


/*
	UInt<2> w = 100;
	w.GetBit(64);
	std::cout << w << std::endl;	

return 0;
*/

/*
	uint q = 100;
	uint last = UInt<3>::SetBitInWord(q, 3);
	std::cout << "nowa wartosc: " << q << ", wczesniejszy bit: " << last << std::endl;
return 0;

*/

/*
	Big<1, 3> a = -26;
	Int<3> b = -8;

	uint c = a.Pow(b);

	if ( c )
		std::cout << "carry: " << c << std::endl;
	else
		std::cout << a << std::endl;
return 0;
*/

	test_uint();


return 0;
}
