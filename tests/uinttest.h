/*
 * This file is a part of TTMath Bignum Library
 * and is distributed under the 3-Clause BSD Licence.
 * Author: Tomasz Sowa <t.sowa@ttmath.org>
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


#ifndef headerfileuinttest
#define headerfileuinttest

#include <string>
#include <fstream>
#include <iostream>

#include <ttmath/ttmath.h>

using namespace ttmath;
typedef ttmath::uint uuint;


class UIntTest
{

	std::string file_name;

	// current line from the file
	std::string line;
	const char * pline;

	std::ifstream file;


	std::string method;

	int row;

public:

	void set_file_name(const std::string & f);

	void go();

bool read_uint(uuint & result);

template<uuint type_size>
bool read_uint(UInt<type_size> & result);


	template<uuint type_size> void test_add();
	template<uuint type_size> void test_addint();
	template<uuint type_size> void test_addtwoints();

	template<uuint type_size> bool check_result_carry(const ttmath::UInt<type_size> & result, const ttmath::UInt<type_size> & new_result,
						int carry, int new_carry);

	template<uuint type_size> bool check_result_or_carry(const ttmath::UInt<type_size> & result, const ttmath::UInt<type_size> & new_result,
						int carry, int new_carry);

int upper_char(int c);
bool is_white(int c);
void skip_white_characters();
bool read_method();
void test_method();
bool check_line();

bool check_minmax_bits(int type_size);
bool check_minmax_bits_bitperint(int type_size);
bool check_end();


};


#endif
