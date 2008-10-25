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


#include "uinttest.h"



void UIntTest::set_file_name(const std::string & f)
{
	file_name = f;
}


uuint UIntTest::read_uint()
{
uuint result = 0;
	
	skip_white_characters();

	for( ; *pline>='0' && *pline<='9' ; ++pline )
		result = result * 10 + (*pline - '0');

return result;
}



bool UIntTest::check_minmax_bits(int type_size)
{
	int min_bits = read_uint();
	int max_bits = read_uint();

	if( min_bits != 0 && type_size * TTMATH_BITS_PER_UINT < (unsigned int)min_bits )
		return false;

	if( max_bits != 0 && type_size * TTMATH_BITS_PER_UINT > (unsigned int)max_bits )
		return false;

return true;
}


bool UIntTest::check_minmax_bits_bitperint(int type_size)
{
	if( !check_minmax_bits(type_size) )
		return false;

	int bits = read_uint();

	if( TTMATH_BITS_PER_UINT != bits )
		return false;

return true;
}



bool UIntTest::check_end()
{
	skip_white_characters();

	if( *pline!='#' && *pline!= 0 )
	{
		std::cerr << "syntax error" << std::endl;
		return false;
	}

return true;
}


template<uuint type_size>
bool UIntTest::check_result_carry(const ttmath::UInt<type_size> & result, const ttmath::UInt<type_size> & new_result,
						int carry, int new_carry)
{
bool ok = true;

	if( new_carry != carry )
	{
		std::cerr << "Incorrect carry: " << new_carry << " (expected: " << carry << ")" << std::endl;
		ok = false;
	}

	if( new_result != result )
	{
		std::cerr << "Incorrect result: " << new_result << " (expected: " << result << ")" << std::endl;
		ok = false;
	}

return ok;
}






template<uuint type_size>
void UIntTest::test_add()
{
	UInt<type_size> a,b,result, new_result;

	if( !check_minmax_bits(type_size) )
		return;

	a.FromString(pline, 10, &pline);
	b.FromString(pline, 10, &pline);
	result.FromString(pline, 10, &pline);
	int carry = read_uint();

	std::cerr << '[' << row << "] Add<" << type_size << ">: ";

	if( !check_end() )
		return;

	new_result = a;
	int new_carry = new_result.Add(b);

	if( check_result_carry(result, new_result, carry, new_carry) )
		std::cerr << "ok" << std::endl;
}


template<uuint type_size>
void UIntTest::test_addint()
{
	UInt<type_size> a, result, new_result;

	if( !check_minmax_bits_bitperint(type_size) )
		return;

	a.FromString(pline, 10, &pline);
	uuint b = read_uint();
	uuint index = read_uint();
	result.FromString(pline, 10, &pline);
	int carry = read_uint();

	std::cerr << '[' << row << "] AddInt<" << type_size << ">: ";

	if( !check_end() )
		return;

	new_result = a;
	int new_carry = new_result.AddInt(b, index);

	if( check_result_carry(result, new_result, carry, new_carry) )
		std::cerr << "ok" << std::endl;
}


int UIntTest::upper_char(int c)
{
	if( c>='a' && c<='z' )
		return c - 'a' + 'A';

return c;
}


bool UIntTest::is_white(int c)
{
	if( c==' ' || c=='\t' || c==13 )
		return true;

return false;
}


void UIntTest::skip_white_characters()
{
	while( is_white(*pline) )
		++pline;
}



bool UIntTest::read_method()
{
	skip_white_characters();
	
	if( *pline == '#' )
		return false;
	
	method.clear();

	for(int c = upper_char(*pline) ; c>='A'&& c<='Z' ; c = upper_char(*pline) )
	{
		method += c;
		++pline;
	}

	if( method.empty() )
	{
		skip_white_characters();
		if( *pline == 0 )
			return false;
		else
		{	
			std::cerr << '[' << row << "] ";
			std::cerr << "syntax error" << std::endl;
			return false;
		}
	}


return true;
}


void UIntTest::test_method()
{
const char * p = pline;

	if( method == "ADD" )
	{
		pline = p; test_add<1>();
		pline = p; test_add<2>();
		pline = p; test_add<3>();
		pline = p; test_add<4>();
		pline = p; test_add<5>();
		pline = p; test_add<6>();
		pline = p; test_add<7>();
		pline = p; test_add<8>();
		pline = p; test_add<9>();
	}
	else
	if( method == "ADDINT" )
	{
		pline = p; test_addint<1>();
		pline = p; test_addint<2>();
		pline = p; test_addint<3>();
		pline = p; test_addint<4>();
		pline = p; test_addint<5>();
		pline = p; test_addint<6>();
		pline = p; test_addint<7>();
		pline = p; test_addint<8>();
		pline = p; test_addint<9>();
	}
	else
	{
		std::cerr << '[' << row << "] ";
		std::cerr << "method " << method << " is not supported" << std::endl;
	}
}


bool UIntTest::check_line()
{
	std::getline(file, line);
	
	pline = line.c_str();
	
	if( read_method() )
		test_method();


	if( file.eof() )
		return false;


return true;
}




void UIntTest::go()
{
	file.open(file_name.c_str());


	if( !file )
	{
		std::cerr << "I can't open the input file" << std::endl;
		return;
	}

	row = 1;

	while( check_line() )
		++row;

}




