/*
 * This file is part of TTMath Mathematical Library
 * and is distributed under the (new) BSD licence.
 * Author: Tomasz Sowa <t.sowa@slimaczek.pl>
 */

/* 
 * Copyright (c) 2006-2007, Tomasz Sowa
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



#ifndef headerfilettmathtypes
#define headerfilettmathtypes

/*!
	\file ttmathtypes.h
    \brief A Documented file.
    
    Details.
*/


#include <exception>
#include <string>
#include <iostream>
#include <map>




/*!
	the version of the library
*/
#define TTMATH_MAJOR_VER		0
#define TTMATH_MINOR_VER		6
#define TTMATH_REVISION_VER		2








/*!
	this macro enables further testing during writing your code
	you don't have to define it in a release mode

	if this macro is set then macro MATHTT_ASSERT is set as well
	and MATHTT_ASSERT can throw an exception if a condition is not fulfilled
	(look at the definition of MATHTT_ASSERT)

	if you don't want any further testing put two characters '//' before this macro
	e.g. 
	// #define MATHTT_DEBUG
*/
#define MATHTT_DEBUG


/*!
	32 bit integer value without a sign 
	(the same on 64 bits platform (amd))
*/
typedef unsigned int uint;


/*!
	how many bits there are in the uint type
*/
#define BITS_PER_UINT 32u


/*!
	the mask for the highest bit in the unsigned 32bits word (2^31)
*/
#define uint_the_highest_bit 2147483648u


/*!
	the max value of the unsigned 32bits word (2^32 - 1)
	(all bits equal one)
*/
#define uint_max_value 4294967295u


/*!
	if you define this macro that means the version one of the multiplication algorithm 
	will be used in the UInt class
*/
//#define UINT_MUL_VERSION_1



/*!
	if you define this macro that means the version two of the multiplication algorithm 
	will be used in the UInt class

	this algorithm is much faster than previous

	you can't use both these macros together, you must use either UINT_MUL_VERSION_1
	or UINT_MUL_VERSION_2
*/
#define UINT_MUL_VERSION_2



/*!
	characters which represent the comma operator

	MATHTT_COMMA_CHARACTER_1 is used in reading (parsing) and in writing
	MATHTT_COMMA_CHARACTER_2 can be used in reading as an auxiliary comma character
	that means you can input values for example 1.2345 and 1,2345 as well

	if you don't want it just put 0 there eg.
		#define MATHTT_COMMA_CHARACTER_2 0
	then only MATHTT_COMMA_CHARACTER_1 will be used

	don't put here any special character which is used by the parser
	(for example a semicolon ';' shouldn't be here)
*/
#define MATHTT_COMMA_CHARACTER_1 '.'
#define MATHTT_COMMA_CHARACTER_2 ','
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//// odwrocic nazwy ma byc TTMATH




namespace ttmath
{
	/*!
		error codes
	*/
	enum ErrorCode
	{
		err_ok = 0,
		err_nothing_has_read = 1,
		err_unknown_character = 2,
		err_unexpected_final_bracket = 4,
		err_stack_not_clear = 6,
		err_unknown_variable = 8,
		err_division_by_zero = 9,
		err_interrupt = 10,
		err_overflow = 11,
		err_unknown_function = 12,
		err_unexpected_semicolon_operator = 18,
		err_improper_amount_of_arguments = 19,
		err_improper_argument = 20,
		err_unexpected_end = 21,
		err_internal_error = 100,

		err_incorrect_name,
		err_incorrect_value,
		err_variable_exists,
		err_variable_loop,
		err_functions_loop,
		err_must_be_only_one_value,

		err_object_exists,
		err_unknown_object,


		err_this_cant_be_used = 200
	};



	class StopCalculating
	{
	public:
		virtual bool WasStopSignal() const volatile { return false; }
		virtual ~StopCalculating(){}
	};







// moze tutaj z runtime dziedziczyc?
	//zmienic nazwe na TTMathError
	class MathTTError : public std::exception
	{
	ErrorCode code;

	public:
		MathTTError(ErrorCode c) : code(c) {}
		const char* what() const throw()
		{
			switch( code )
			{
			case err_this_cant_be_used:
				return "You've used 'this' somewhere in your code but you can't use it there";
				// dac tu jakis lepszy komunikat w stylu
				// 'uzyles referencji do samego siebie ale w tym miejscu nie mozesz tego zrobic'
			default:
				return ":)"; // temporary
			}

		return "Unnamed";
		}
	};

	#ifdef MATHTT_DEBUG
		#define MATHTT_ASSERT(expression, c) \
		if( !(expression) ) throw MathTTError(c);
	#else
		#define MATHTT_ASSERT(expression, c)
	#endif

	#define MATHTT_THIS_ASSERT(expression) \
		MATHTT_ASSERT( &expression != this, err_this_cant_be_used)



/*
	template<class ValueType>
	class ValuesHistory
	{
		typedef std::map<ValueType, ValueType> buffer_type;
		buffer_type buffer;

	public:

		void AddValue(const ValueType & key, const ValueType & result)
		{
			buffer.insert( std::make_pair(key, result) );
		}

		bool GetValue(const ValueType & key, ValueType & result) const
		{
			buffer_type::iterator i = buffer.find( key );

			if( i == buffer.end() )
				return false;

			result = *i;

		return true;
		}

		uint Size() const
		{
			return static_cast<uint>( buffer.size() );
		}
	};
*/

} // namespace





#endif
