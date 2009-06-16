/*
 * This file is a part of TTMath Bignum Library
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


#ifndef headerfilettmathtypes
#define headerfilettmathtypes

/*!
	\file ttmathtypes.h
    \brief constants used in the library
    
    As our library is written in header files (templates) we cannot use
	constants like 'const int' etc. because we should have some source files
	*.cpp to define this variables. Only what we can have are constants
	defined by #define preprocessor macros.

	All macros are preceded by TTMATH_ prefix
*/


#include <stdexcept>
#include <sstream>


/*!
	the version of the library

	TTMATH_PRERELEASE_VER is either zero or one
	if zero that means this is the release version of the library
*/
#define TTMATH_MAJOR_VER		0
#define TTMATH_MINOR_VER		8
#define TTMATH_REVISION_VER		5
#define TTMATH_PRERELEASE_VER	0


/*!
	TTMATH_DEBUG
	this macro enables further testing during writing your code
	you don't have to define it in a release mode

	if this macro is set then macros TTMATH_ASSERT and TTMATH_REFERENCE_ASSERT
	are set as well	and these macros can throw an exception if a condition in it
	is not fulfilled (look at the definition of TTMATH_ASSERT and TTMATH_REFERENCE_ASSERT)

	TTMATH_RELEASE
	if you are confident that your code is perfect you can define TTMATH_RELEASE
	macro for example by using -D option in gcc
	 gcc -DTTMATH_RELEASE -o myprogram myprogram.cpp 
	or by defining this macro in your code before using any header files of this library

	if TTMATH_RELEASE is not set then TTMATH_DEBUG is set automatically
*/
#ifndef TTMATH_RELEASE
	#define TTMATH_DEBUG
#endif



namespace ttmath
{

#if !defined _M_X64 && !defined __x86_64__

	/*!
		we're using a 32bit platform
	*/
	#define TTMATH_PLATFORM32

#else

	/*!
		we're using a 64bit platform
	*/
	#define TTMATH_PLATFORM64

#endif



#ifdef TTMATH_PLATFORM32

	/*!
		on 32bit platforms one word (uint, sint) will be equal 32bits
	*/
	typedef unsigned int uint;
	typedef signed   int sint;

	/*!
		this type is twice bigger than uint
		(64bit on a 32bit platforms)

		although C++ Standard - ANSI ISO IEC 14882:2003 doesn't define such a type (long long) 
		but it is defined in C99 and in upcoming C++0x /3.9.1 (2)/ and many compilers support it

		this type is used in UInt::MulTwoWords and UInt::DivTwoWords when macro TTMATH_NOASM is defined
		but only on a 32bit platform
	*/
	#ifdef TTMATH_NOASM
		typedef unsigned long long int ulint;
	#endif

	/*!
		how many bits there are in the uint type
	*/
	#define TTMATH_BITS_PER_UINT 32u

	/*!
		the mask for the highest bit in the unsigned 32bit word (2^31)
	*/
	#define TTMATH_UINT_HIGHEST_BIT 2147483648u

	/*!
		the max value of the unsigned 32bit word (2^32 - 1)
		(all bits equal one)
	*/
	#define TTMATH_UINT_MAX_VALUE 4294967295u

	/*!
		the number of words (32bit words on 32bit platform)
		which are kept in built-in variables for a Big<> type
		(these variables are defined in ttmathbig.h)
	*/
	#define TTMATH_BUILTIN_VARIABLES_SIZE 256u

#else

	/*!
		on 64bit platforms one word (uint, sint) will be equal 64bits
	*/
	typedef unsigned long uint;
	typedef signed   long sint;

	/*!
		on 64bit platform we do not define ulint
		sizeof(long long) is 8 (64bit) but we need 128bit

		on 64 bit platform (when there is defined TTMATH_NOASM macro)
		methods UInt::MulTwoWords and UInt::DivTwoWords are using other algorithms than those on 32 bit
	*/
	//typedef unsigned long long int ulint;

	/*!
		how many bits there are in the uint type
	*/
	#define TTMATH_BITS_PER_UINT 64ul

	/*!
		the mask for the highest bit in the unsigned 64bit word (2^63)
	*/
	#define TTMATH_UINT_HIGHEST_BIT 9223372036854775808ul

	/*!
		the max value of the unsigned 64bit word (2^64 - 1)
		(all bits equal one)
	*/
	#define TTMATH_UINT_MAX_VALUE 18446744073709551615ul

	/*!
		the number of words (64bit words on 64bit platforms)
		which are kept in built-in variables for a Big<> type
		(these variables are defined in ttmathbig.h)
	*/
	#define TTMATH_BUILTIN_VARIABLES_SIZE 128ul

#endif
}



/*!
	characters which represent the comma operator

	TTMATH_COMMA_CHARACTER_1 is used in reading (parsing) and in writing (default, can be overwritten in ToString() function)
	TTMATH_COMMA_CHARACTER_2 can be used in reading as an auxiliary comma character
	that means you can input values for example 1.2345 and 1,2345 as well

	if you don't want it just put 0 there e.g.
		#define TTMATH_COMMA_CHARACTER_2 0
	then only TTMATH_COMMA_CHARACTER_1 will be used

	don't put there any special character which is used by the parser
	(for example a semicolon ';' shouldn't be there)
*/
#define TTMATH_COMMA_CHARACTER_1 '.'
#define TTMATH_COMMA_CHARACTER_2 ','



/*!
	this variable defines how many iterations are performed
	during some kind of calculating when we're making any long formulas
	(for example Taylor series)

	it's used in ExpSurrounding0(...), LnSurrounding1(...), Sin0pi05(...), etc.

	note! there'll not be so many iterations, iterations are stopped when
	there is no sense to continue calculating (for example when the result
	still remains unchanged after adding next series and we know that the next
	series are smaller than previous ones)
*/
#define TTMATH_ARITHMETIC_MAX_LOOP 10000



/*!
	this is a limit when calculating Karatsuba multiplication
	if the size of a vector is smaller than TTMATH_USE_KARATSUBA_MULTIPLICATION_FROM_SIZE
	the Karatsuba algorithm will use standard schoolbook multiplication
*/
#ifdef __GNUC__
#define TTMATH_USE_KARATSUBA_MULTIPLICATION_FROM_SIZE 3
#else
#define TTMATH_USE_KARATSUBA_MULTIPLICATION_FROM_SIZE 5
#endif


namespace ttmath
{

	/*!
		error codes
	*/
	enum ErrorCode
	{
		err_ok = 0,
		err_nothing_has_read,
		err_unknown_character,
		err_unexpected_final_bracket,
		err_stack_not_clear,
		err_unknown_variable,
		err_division_by_zero,
		err_interrupt,
		err_overflow,
		err_unknown_function,
		err_unknown_operator,
		err_unexpected_semicolon_operator,
		err_improper_amount_of_arguments,
		err_improper_argument,
		err_unexpected_end,
		err_internal_error,
		err_incorrect_name,
		err_incorrect_value,
		err_variable_exists,
		err_variable_loop,
		err_functions_loop,
		err_must_be_only_one_value,
		err_object_exists,
		err_unknown_object,
		err_still_calculating,
		err_too_big_factorial,
		err_in_short_form_used_function
	};


	/*!
		this simple class can be used in multithreading model
		(you can write your own class derived from this one)

		for example: in some functions like Factorial() 
		/at the moment only Factorial/ you can give a pointer to 
		the 'stop object', if the method WasStopSignal() of this 
		object returns true that means we should break the calculating
		and return
	*/
	class StopCalculating
	{
	public:
		virtual bool WasStopSignal() const volatile { return false; }
		virtual ~StopCalculating(){}
	};


	/*!
		a small class which is useful when compiling with gcc

		object of this type holds the name and the line of a file
		in which the macro TTMATH_ASSERT or TTMATH_REFERENCE_ASSERT was used
	*/
	class ExceptionInfo
	{
	const char * file;
	int line;

	public:
		ExceptionInfo() : file(0), line(0) {}
		ExceptionInfo(const char * f, int l) : file(f), line(l) {}

		std::string Where() const
		{
			if( !file )
				return "unknown";

			std::ostringstream result;
			result << file << ":" << line;

		return result.str();
		}
	};


	/*!
		A small class used for reporting 'reference' errors

		In the library is used macro TTMATH_REFERENCE_ASSERT which
		can throw an exception of this type

		If you compile with gcc you can get a small benefit 
		from using method Where() (it returns std::string with
		the name and the line of a file where the macro TTMATH_REFERENCE_ASSERT
		was used)

		What is the 'reference' error?
		Some kind of methods use a reference as their argument to another object,
		and the another object not always can be the same which is calling, e.g.
			Big<1,2> foo(10);
			foo.Mul(foo); // this is incorrect
		above method Mul is making something more with 'this' object and 
		'this' cannot be passed as the argument because the result will be undefined

		macro TTMATH_REFERENCE_ASSERT helps us to solve the above problem

		note! some methods can use 'this' object as the argument
		for example this code is correct:
			UInt<2> foo(10);
			foo.Add(foo);
		but there are only few methods which can do that
	*/
	class ReferenceError : public std::logic_error, public ExceptionInfo
	{
	public:

		ReferenceError() : std::logic_error ("reference error")
		{
		}

		ReferenceError(const char * f, int l) :
							std::logic_error ("reference error"), ExceptionInfo(f,l)
		{
		}

		std::string Where() const
		{
			return ExceptionInfo::Where();
		}
	};


	/*!
		a small class used for reporting errors

		in the library is used macro TTMATH_ASSERT which
		(if the condition in it is false) throw an exception
		of this type

		if you compile with gcc you can get a small benefit 
		from using method Where() (it returns std::string with
		the name and the line of a file where the macro TTMATH_ASSERT
		was used)
	*/
	class RuntimeError : public std::runtime_error, public ExceptionInfo
	{
	public:

		RuntimeError() : std::runtime_error ("internal error")
		{
		}

		RuntimeError(const char * f, int l) :
						std::runtime_error ("internal error"), ExceptionInfo(f,l)
		{
		}

		std::string Where() const
		{
			return ExceptionInfo::Where();
		}
	};



	/*!
		look at the description of macros TTMATH_RELEASE and TTMATH_DEBUG
	*/
	#ifdef TTMATH_DEBUG

		#if defined(__FILE__) && defined(__LINE__)

			#define TTMATH_REFERENCE_ASSERT(expression) \
				if( &(expression) == this ) throw ttmath::ReferenceError(__FILE__, __LINE__);

			#define TTMATH_ASSERT(expression) \
				if( !(expression) ) throw ttmath::RuntimeError(__FILE__, __LINE__);

		#else

			#define TTMATH_REFERENCE_ASSERT(expression) \
				if( &(expression) == this ) throw ReferenceError();

			#define TTMATH_ASSERT(expression) \
				if( !(expression) ) throw RuntimeError();
		#endif

	#else
		#define TTMATH_REFERENCE_ASSERT(expression)
		#define TTMATH_ASSERT(expression)
	#endif



	#ifdef TTMATH_DEBUG_LOG

		#define TTMATH_LOG(msg) \
			PrintLog(msg, std::cout);		

	#else

		#define TTMATH_LOG(msg)

	#endif


} // namespace


#endif
