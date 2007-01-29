/*
 * This file is a part of TTMath Mathematical Library
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

#ifndef headerfilettmathbig
#define headerfilettmathbig

/*!
	\file ttmathbig.h
    \brief A Class for representing big numbers
*/

#include "ttmathint.h"

namespace ttmath
{


/*!
	\brief it implements the big value
*/
template <uint exp,uint man>
class Big
{

/*
	value = mantissa * 2^exponent	

	exponent - integer value with a sign
	mantissa - integer value without a sing

	mantissa must be pushed into the left side that is the highest bit from 
	mantissa must be one (of course if there's another value than zero) -- this job
	(pushing bits into the left side) making Standardizing() method

	for example:
	if we want to store value one (1) into our Big object we must:
		set mantissa to 1
		set exponent to 0
		set info to 0
		and call method Standardizing()
*/


public:

Int<exp>  exponent;
UInt<man> mantissa;
unsigned char info;


/*!
	the number of a bit from 'info' which means that a value is with the sign
	(when the bit is set)
*/
#define TTMATH_BIG_SIGN 128




public:


	/*!
		this method moves all bits from mantissa into its left side
		(suitably changes the exponent) or if the mantissa is zero
		it sets the exponent as zero as well

		it can return a carry
		the carry will be when we don't have enough space in the exponent

		you don't have to use this method if you don't change the mantissa
		and exponent directly
	*/
	uint Standardizing()
	{
		if( mantissa.IsTheHighestBitSet() )
			return 0;

		if( CorrectZero() )
			return 0;

		uint comp = mantissa.CompensationToLeft();

	return exponent.Sub( comp );
	}


private:

	/*!
		if mantissa is equal zero this method sets exponent to zero and
		info without the sign

		it returns true if there was the correction
	*/
	bool CorrectZero()
	{
		if( mantissa.IsZero() )
		{
			Abs();
			exponent.SetZero();

		return true;
		}

	return false;
	}




public:

	/*!
		it sets value zero
	*/
	void SetZero()
	{
		info = 0;
		exponent.SetZero();
		mantissa.SetZero();

		/*
			we don't have to compensate zero
		*/
	}

	
	/*!
		it sets value one
	*/
	void SetOne()
	{
		info = 0;
		mantissa.SetOne();
		exponent.SetZero();
		Standardizing();
	}


	/*!
		it sets value 0.5
	*/
	void SetDotOne()
	{
		SetOne();
		exponent.SubOne();
	}


	/*!
		it sets value pi
	*/
	void SetPi()
	{
	static const uint temp_table[] = {
		0xc90fdaa2, 0x2168c234, 0xc4c6628b, 0x80dc1cd1, 0x29024e08, 0x8a67cc74, 0x020bbea6, 0x3b139b22, 
		0x514a0879, 0x8e3404dd, 0xef9519b3, 0xcd3a431b, 0x302b0a6d, 0xf25f1437, 0x4fe1356d, 0x6d51c245, 
		0xe485b576, 0x625e7ec6, 0xf44c42e9, 0xa637ed6b, 0x0bff5cb6, 0xf406b7ed, 0xee386bfb, 0x5a899fa5, 
		0xae9f2411, 0x7c4b1fe6, 0x49286651, 0xece45b3d, 0xc2007cb8, 0xa163bf05, 0x98da4836, 0x1c55d39a, 
		0x69163fa8, 0xfd24cf5f, 0x83655d23, 0xdca3ad96, 0x1c62f356, 0x208552bb, 0x9ed52907, 0x7096966d, 
		0x670c354e, 0x4abc9804, 0xf1746c08, 0xca18217c, 0x32905e46, 0x2e36ce3b, 0xe39e772c, 0x180e8603, 
		0x9b2783a2, 0xec07a28f, 0xb5c55df0, 0x6f4c52c9, 0xde2bcbf6, 0x95581718, 0x3995497c, 0xea956ae5, 
		0x15d22618, 0x98fa0510, 0x15728e5a, 0x8aaac42d, 0xad33170d, 0x04507a33, 0xa85521ab, 0xdf1cba64, 
		0xecfb8504, 0x58dbef0a, 0x8aea7157, 0x5d060c7d, 0xb3970f85, 0xa6e1e4c7, 0xabf5ae8c, 0xdb0933d7, 
		0x1e8c94e0, 0x4a25619d, 0xcee3d226, 0x1ad2ee6b, 0xf0139f9d, 0x88e637cb
		};
		// 78 unsigned words
		// this is static table which represents the value Pi (mantissa of its)
		// (first is the highest word)
	
		mantissa.SetFromTable(temp_table, sizeof(temp_table) / sizeof(uint));
		exponent = -sint(man)*sint(TTMATH_BITS_PER_UINT) + 2;
		info = 0;
	}


	/*!
		it sets value 0.5 * pi
	*/
	void Set05Pi()
	{
		SetPi();	
		exponent = -sint(man)*sint(TTMATH_BITS_PER_UINT) + 1;
	}


	/*!
		it sets value 2 * pi
	*/
	void Set2Pi()
	{
		SetPi();
		exponent = -sint(man)*sint(TTMATH_BITS_PER_UINT) + 3;
	}


	/*!
		it sets value e
		(the base of natural logarithm)
	*/
	void SetE()
	{
	static const uint temp_table[] = {
		0xadf85458, 0xa2bb4a9a, 0xafdc5620, 0x273d3cf1, 0xd8b9c583, 0xce2d3695, 0xa9e13641, 0x146433fb, 
		0xcc939dce, 0x249b3ef9, 0x7d2fe363, 0x630c75d8, 0xf681b202, 0xaec4617a, 0xd3df1ed5, 0xd5fd6561, 
		0x2433f51f, 0x5f066ed0, 0x85636555, 0x3ded1af3, 0xb557135e, 0x7f57c935, 0x984f0c70, 0xe0e68b77, 
		0xe2a689da, 0xf3efe872, 0x1df158a1, 0x36ade735, 0x30acca4f, 0x483a797a, 0xbc0ab182, 0xb324fb61, 
		0xd108a94b, 0xb2c8e3fb, 0xb96adab7, 0x60d7f468, 0x1d4f42a3, 0xde394df4, 0xae56ede7, 0x6372bb19, 
		0x0b07a7c8, 0xee0a6d70, 0x9e02fce1, 0xcdf7e2ec, 0xc03404cd, 0x28342f61, 0x9172fe9c, 0xe98583ff, 
		0x8e4f1232, 0xeef28183, 0xc3fe3b1b, 0x4c6fad73, 0x3bb5fcbc, 0x2ec22005, 0xc58ef183, 0x7d1683b2, 
		0xc6f34a26, 0xc1b2effa, 0x886b4238, 0x611fcfdc, 0xde355b3b, 0x6519035b, 0xbc34f4de, 0xf99c0238, 
		0x61b46fc9, 0xd6e6c907, 0x7ad91d26, 0x91f7f7ee, 0x598cb0fa, 0xc186d91c, 0xaefe1309, 0x85139270, 
		0xb4130c93, 0xbc437944, 0xf4fd4452, 0xe2d74dd3, 0x645b2194, 0x41468794
		};
	
		mantissa.SetFromTable(temp_table, sizeof(temp_table) / sizeof(uint));
		exponent = -sint(man)*sint(TTMATH_BITS_PER_UINT) + 2;
		info = 0;
	}


	/*!
		it sets value ln(2)
		the natural logarithm from value 2
	*/
	void SetLn2()
	{
	static const uint temp_table[] = {
		0xb17217f7, 0xd1cf79ab, 0xc9e3b398, 0x03f2f6af, 0x40f34326, 0x7298b62d, 0x8a0d175b, 0x8baafa2b, 
		0xe7b87620, 0x6debac98, 0x559552fb, 0x4afa1b10, 0xed2eae35, 0xc1382144, 0x27573b29, 0x1169b825, 
		0x3e96ca16, 0x224ae8c5, 0x1acbda11, 0x317c387e, 0xb9ea9bc3, 0xb136603b, 0x256fa0ec, 0x7657f74b, 
		0x72ce87b1, 0x9d6548ca, 0xf5dfa6bd, 0x38303248, 0x655fa187, 0x2f20e3a2, 0xda2d97c5, 0x0f3fd5c6, 
		0x07f4ca11, 0xfb5bfb90, 0x610d30f8, 0x8fe551a2, 0xee569d6d, 0xfc1efa15, 0x7d2e23de, 0x1400b396, 
		0x17460775, 0xdb8990e5, 0xc943e732, 0xb479cd33, 0xcccc4e65, 0x9393514c, 0x4c1a1e0b, 0xd1d6095d, 
		0x25669b33, 0x3564a337, 0x6a9c7f8a, 0x5e148e82, 0x074db601, 0x5cfe7aa3, 0x0c480a54, 0x17350d2c, 
		0x955d5179, 0xb1e17b9d, 0xae313cdb, 0x6c606cb1, 0x078f735d, 0x1b2db31b, 0x5f50b518, 0x5064c18b, 
		0x4d162db3, 0xb365853d, 0x7598a195, 0x1ae273ee, 0x5570b6c6, 0x8f969834, 0x96d4e6d3, 0x30af889b, 
		0x44a02554, 0x731cdc8e, 0xa17293d1, 0x228a4ef8, 0x6e1adf84, 0x08689fa8
		};	

		mantissa.SetFromTable(temp_table, sizeof(temp_table) / sizeof(uint));
		exponent = -sint(man)*sint(TTMATH_BITS_PER_UINT);
		info = 0;
	}


	/*!
		it sets the maximum value which can be held in this type
	*/
	void SetMax()
	{
		info = 0;
		mantissa.SetMaxValue();
		exponent.SetMaxValue();

		// we don't have to use 'Standardizing()' because the last bit from
		// the mantissa is set
	}


	/*!
		it sets the minimum value which can be held in this type
	*/
	void SetMin()
	{
		info = 0;
		SetSign();

		mantissa.SetMaxValue();
		exponent.SetMaxValue();

		// we don't have to use 'Standardizing()' because the last bit from
		// the mantissa is set
	}


	/*!
		it's testing whether there is a value zero or not
	*/
	bool IsZero() const
	{
		/*
			we only have to test the mantissa
		*/
		return mantissa.IsZero();
	}


	/*!
		it returns true when there's the sign set
	*/
	bool IsSign() const
	{
		return (info & TTMATH_BIG_SIGN) == TTMATH_BIG_SIGN;
	}


	/*!
		it clears the sign
		(there'll be a absolute value)

			e.g.
			-1 -> 1
			2  -> 2
	*/
	void Abs()
	{
		info &= ~TTMATH_BIG_SIGN;
	}


	/*!
		it sets the sign

			e.g.
			-1 -> -1
			2  -> -2
	*/
	void SetSign()
	{
		if( IsZero() )
			return;

		info |=  TTMATH_BIG_SIGN;
	}


	/*!
		it changes the sign

			e.g.
			-1 -> 1
			2  -> -2
	*/
	void ChangeSign()
	{
		if( IsZero() )
			return;

		info = (info & (~TTMATH_BIG_SIGN)) | ((~info) & TTMATH_BIG_SIGN);
	}





	/*!
	*
	*	basic mathematic functions
	*
	*/


	/*!
		Addition this = this + ss2

		it returns carry if the sum is too big
	*/
	uint Add(Big<exp, man> ss2)
	{
	Int<exp> exp_offset( exponent );
	Int<exp> mantissa_size_in_bits( man * TTMATH_BITS_PER_UINT );
	uint c = 0;

		exp_offset.Sub( ss2.exponent );
		exp_offset.Abs();

		// abs(this) will be >= abs(ss2)
		if( SmallerWithoutSignThan(ss2) )
		{
			Big<exp, man> temp(ss2);

			ss2   = *this;
			*this = temp;
		}
		
		if( exp_offset > mantissa_size_in_bits )
		{
			// the second value is too short for taking into consideration in the sum
			return 0;
		}
		else
		if( exp_offset < mantissa_size_in_bits )
		{
			// moving 'exp_offset' times
			ss2.mantissa.Rcr( exp_offset.ToInt(), 0 );
		}
		else
		{
			// exp_offset == mantissa_size_in_bits
			// we're rounding 'this' about one (up or down depending on a ss2 sign)
			ss2.mantissa.SetOne();
		}


		if( IsSign() == ss2.IsSign() )
		{
			// values have the same signs
			if( mantissa.Add(ss2.mantissa) )
			{
				mantissa.Rcr(1);
				c = exponent.AddOne();
			}
		}
		else
		{
			// values have different signs
			if( mantissa.Sub(ss2.mantissa) )
			{
				mantissa.Rcl(1);
				c = exponent.SubOne();
			}
		}

		c += Standardizing();

	return (c==0)? 0 : 1;
	}


	/*!
		Subtraction this = this - ss2

		it returns carry if the result is too big
	*/
	uint Sub(Big<exp, man> ss2)
	{
		ss2.ChangeSign();

	return Add(ss2);
	}
		
	
	/*!
		multiplication this = this * ss2
		this method returns carry
	*/
	uint Mul(const Big<exp, man> & ss2)
	{
	TTMATH_REFERENCE_ASSERT( ss2 )

	UInt<man*2> man_result;
	uint i,c;

		// man_result = mantissa * ss2.mantissa
		mantissa.MulBig(ss2.mantissa, man_result);

		// 'i' will be from 0 to man*TTMATH_BITS_PER_UINT
		// because mantissa and ss2.mantissa are standardized 
		// (the highest bit in man_result is set to 1 or
		// if there is a zero value in man_result the method CompensationToLeft()
		// returns 0 but we'll correct this at the end in Standardizing() method)
		i = man_result.CompensationToLeft();
		
		c  = exponent.Add( man * TTMATH_BITS_PER_UINT - i );
		c += exponent.Add( ss2.exponent );

		for(i=0 ; i<man ; ++i)
			mantissa.table[i] = man_result.table[i+man];

		if( IsSign() == ss2.IsSign() )
		{
			// the signs are the same, the result is positive
			Abs();
		}
		else
		{
			// the signs are different, the result is negative
			SetSign();
		}

		c += Standardizing();

	return (c==0)? 0 : 1;
	}
	

	/*!
		division this = this / ss2
		this method returns carry (in a division carry can be as well)

		(it also returns 0 if ss2 is zero)
	*/
	uint Div(const Big<exp, man> & ss2)
	{
	TTMATH_REFERENCE_ASSERT( ss2 )

	UInt<man*2> man1;
	UInt<man*2> man2;
	uint i,c;
		
		if( ss2.IsZero() )
		{
			// we don't divide by zero
			return 1;
		}

		for(i=0 ; i<man ; ++i)
		{
			man1.table[i+man] = mantissa.table[i];
			man2.table[i]     = ss2.mantissa.table[i];
		}

		for(i=0 ; i<man ; ++i)
		{
			man1.table[i] = 0;
			man2.table[i+man] = 0;
		}

		man1.Div(man2);

		i = man1.CompensationToLeft();

		c  = exponent.Sub(i);
		c += exponent.Sub(ss2.exponent);
		
		for(i=0 ; i<man ; ++i)
			mantissa.table[i] = man1.table[i+man];

		if( IsSign() == ss2.IsSign() )
			Abs();
		else
			SetSign();

		c += Standardizing();

	return (c==0)? 0 : 1;
	}


	/*!
		power this = this ^ pow
		pow without a sign

		binary algorithm (r-to-l)
	*/
	template<uint pow_size>
	uint PowUInt(UInt<pow_size> pow)
	{
		if(pow.IsZero() && IsZero())
			// we don't define zero^zero
			return 1;

		Big<exp, man> start(*this);
		Big<exp, man> result;
		result.SetOne();

		while( !pow.IsZero() )
		{
			if( pow.table[0] & 1 )
				if( result.Mul(start) )
					return 1;

			if( start.Mul(start) )
				return 1;

			pow.Rcr();
		}

		*this = result;

	return 0;
	}


	/*!
		power this = this ^ pow
		p can be with a sign
		p can be negative
	*/
	template<uint pow_size>
	uint PowInt(Int<pow_size> pow)
	{
		if( !pow.IsSign() )
			return PowUInt(pow);


		if( IsZero() )
			// if 'p' is negative then
			// 'this' must be different from zero
			return 1;

		if( pow.ChangeSign() )
			return 1;

		Big<exp, man> t(*this);
		if( t.PowUInt(pow) )
			return 1;

		SetOne();
		if( Div(t) )
			return 1;

	return 0;
	}


	/*!
		this method returns true if 'this' mod 2 is equal one
	*/
	bool Mod2() const
	{
		if( exponent>sint(0) || exponent<=-sint(man*TTMATH_BITS_PER_UINT) )
			return false;

		sint exp_int = exponent.ToInt();
		// 'exp_int' is negative (or zero), we set its as positive
		exp_int = -exp_int;

		// !!! here we'll use a new method (method for testing a bit)
		uint value = mantissa.table[ exp_int / TTMATH_BITS_PER_UINT ];
		value >>= (uint(exp_int) % TTMATH_BITS_PER_UINT);

	return bool(value & 1);
	}


	/*!
		power this = this ^ abs([pow])
		pow without a sign and without a fraction
	*/
	uint PowBUInt(Big<exp, man> pow)
	{
		if( pow.IsZero() && IsZero() )
			return 1;

		if( pow.IsSign() )
			pow.Abs();

		Big<exp, man> start(*this), start_temp;
		Big<exp, man> result;
		Big<exp, man> one;
		Int<exp> e_one;

		e_one.SetOne();
		one.SetOne();
		result.SetOne();

		while( pow >= one )
		{
			if( pow.Mod2() )
				if( result.Mul(start) )
					return 1;

			start_temp = start;
			if( start.Mul(start_temp) )
				return 1;

			pow.exponent.Sub( e_one );
		}

		*this = result;

	return 0;
	}


	/*!
		power this = this ^ [pow]
		pow without a fraction
		pow can be negative
	*/
	uint PowBInt(const Big<exp, man> & pow)
	{
		TTMATH_REFERENCE_ASSERT( pow )
	
		if( !pow.IsSign() )
			return PowBUInt(pow);

		if( IsZero() )
			// if 'pow' is negative then
			// 'this' must be different from zero
			return 1;

		Big<exp, man> temp(*this);
		if( temp.PowBUInt(pow) )
			return 1;

		SetOne();
		if( Div(temp) )
			return 1;

	return 0;
	}
	

	/*!
		power this = this ^ pow
		pow can be negative and with fraction

		return values:
		1 - carry
		2 - incorrect argument ('this' or 'pow')
	*/
	/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		there should be 'sint Pow(const Big<exp, man> & pow)'
		but vc2005express doesn't want to compile it perfect, that means
		when using 'Maximize Speed /O2' the result of compilation doesn't work property
		for example 10^(1/2) is a big value
		i don't know where is the problem, with this source code or in the compilator
		(it is when we're using 'Big<3,10>' or bigger values in parsing)
		/gcc 3.4.2 works perfect (with -O3 optimalization flag)/

		(we also can change 'Div' instead modifying this 'Pow' -- it'll be the same effect,
		this error is only when we're using our mathematic parser)
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __GNUC__
	uint Pow(const Big<exp, man> & pow)
#else
	uint Pow(const Big<exp, man> pow)
#endif
	{
		TTMATH_REFERENCE_ASSERT( pow )

		if( IsZero() )
		{
			// 0^pow will be 0 only for pow>0
			if( pow.IsSign() || pow.IsZero() )
				return 2;

			SetZero();

		return 0;
		}

		Big<exp, man> pow_frac( pow );
		pow_frac.RemainFraction();

		if( pow_frac.IsZero() )
			return PowBInt( pow );

		// pow is with fraction (not integer)
		// result = e^(pow * ln(this) ) where 'this' must be greater than 0

		// IsZero() was tested before
		if( IsSign() )
			return 2;

		Big<exp, man> temp;
		uint c = temp.Ln(*this);
		c += temp.Mul(pow);
		c += Exp(temp);
	
	return (c==0)? 0 : 1;
	}


private:

	/*!
		Exponent this = exp(x) = e^x where x is in (-1,1)

		we're using the formula exp(x) = 1 + (x)/(1!) + (x^2)/(2!) + (x^3)/(3!) + ...
	*/
	void ExpSurrounding0(const Big<exp,man> & x)
	{
		TTMATH_REFERENCE_ASSERT( x )

		Big<exp,man> denominator, denominator_i;
		Big<exp,man> one, old_value, next_part;
		Big<exp,man> numerator = x;
		
		SetOne();
		one.SetOne();
		denominator.SetOne();
		denominator_i.SetOne();

	
		// every 'step_test' times we make a test
		const uint step_test = 5;

		// we begin from 1 in order to not testing at the start
		for(uint i=1 ; i<=TTMATH_ARITHMETIC_MAX_LOOP ; ++i)
		{
			bool testing = ((i % step_test) == 0);

			if( testing )
				old_value = *this;

			next_part = numerator;

			if( next_part.Div( denominator ) )
				// if there is a carry here we only break the loop 
				// however the result we return as good
				// it means there are too many parts of the formula
				break;

			// there shouldn't be a carry here
			Add( next_part );

			if( testing && old_value==*this )
				// we've added a next part of the formula but the result
				// is still the same then we break the loop
				break;

			// we set the denominator and the numerator for a next part of the formula
			if( denominator_i.Add(one) )
				// if there is a carry here the result we return as good
				break;

			if( denominator.Mul(denominator_i) )
				break;

			if( numerator.Mul(x) )
				break;
		}
	}



public:


	/*!
		Exponent this = exp(x) = e^x

		we're using the fact that our value is stored in form of:
			x = mantissa * 2^exponent
		then
			e^x = e^(mantissa* 2^exponent) or
			e^x = (e^mantissa)^(2^exponent)

		'Exp' returns a carry if we can't count the result ('x' is too big)
	*/
	uint Exp(const Big<exp,man> & x)
	{
	uint c = 0;
		
		if( x.IsZero() )
		{
			SetOne();
		return 0;
		}

		// m will be the value of the mantissa in range (-1,1)
		Big<exp,man> m(x);
		m.exponent = -sint(man*TTMATH_BITS_PER_UINT);

		// 'e_' will be the value of '2^exponent'
		//   e_.mantissa.table[man-1] = TTMATH_UINT_HIGHEST_BIT;  and
		//   e_.exponent.Add(1) mean:
		//     e_.mantissa.table[0] = 1;
		//     e_.Standardizing();
		//     e_.exponent.Add(man*TTMATH_BITS_PER_UINT)
		//     (we must add 'man*TTMATH_BITS_PER_UINT' because we've taken it from the mantissa)
		Big<exp,man> e_(x);
		e_.mantissa.SetZero();
		e_.mantissa.table[man-1] = TTMATH_UINT_HIGHEST_BIT;
		c += e_.exponent.Add(1);
		e_.Abs();

		/*
			now we've got:
			m - the value of the mantissa in range (-1,1)
			e_ - 2^exponent

			e_ can be as:
			...2^-2, 2^-1, 2^0, 2^1, 2^2 ...
			...1/4 , 1/2 , 1  , 2  , 4   ...

			above one e_ is integer

			if e_ is greater than 1 we calculate the exponent as:
				e^(m * e_) = ExpSurrounding0(m) ^ e_
			and if e_ is smaller or equal one we calculate the exponent in this way:
				e^(m * e_) = ExpSurrounding0(m* e_)
			because if e_ is smaller or equal 1 then the product of m*e_ is smaller or equal m
		*/

		if( e_ <= 1 )
		{
			m.Mul(e_);
			ExpSurrounding0(m);
		}
		else
		{
			ExpSurrounding0(m);
			c += PowBUInt(e_);
		}
	
	return (c==0)? 0 : 1;
	}




private:

	/*!
		Natural logarithm this = ln(x) where x in range <1,2)

		we're using the formula:
		ln x = 2 * [ (x-1)/(x+1) + (1/3)((x-1)/(x+1))^3 + (1/5)((x-1)/(x+1))^5 + ... ]

		parts - it's used for approximation, it means how many parts of the above formula
		will be caltulated, when equals 0 then it is ommited

	*/
	void LnSurrounding1(const Big<exp,man> & x)
	{
		Big<exp,man> old_value, next_part, denominator, one, two, x1(x), x2(x);

		one.SetOne();

		if( x == one )
		{
			// LnSurrounding1(1) is 0
			SetZero();
			return;
		}

		two = 2;

		x1.Sub(one);
		x2.Add(one);

		x1.Div(x2);
		x2 = x1;
		x2.Mul(x1);

		denominator.SetOne();
		SetZero();
		
		// every 'step_test' times we make a test

		const uint step_test = 5;

		// we begin from 1 in order to not testing at the beginning
		for(uint i=1 ; i<=TTMATH_ARITHMETIC_MAX_LOOP ; ++i)
		{
			bool testing = ((i % step_test) == 0);

			next_part = x1;

			if( next_part.Div(denominator) )
				// if there is a carry here we only break the loop 
				// however the result we return as good
				// it means there are too many parts of the formula
				break;

			if( testing )
				old_value = *this;

			// there shouldn't be a carry here
			Add(next_part);

			if( testing && old_value == *this )
				// we've added next (step_test) parts of the formula but the result
				// is still the same then we break the loop
				break;

			if( x1.Mul(x2) )
				// if there is a carry here the result we return as good
				break;

			if( denominator.Add(two) )
				break;
		}

		// this = this * 2
		// ( there can't be a carry here because we calculate the logarithm between <1,2) )
		exponent.AddOne(); 
	}




public:


	/*!
		Natural logarithm this = ln(x)
		(a logarithm with the base equal 'e')

		we're using the fact that our value is stored in form of:
			x = mantissa * 2^exponent
		then
			ln(x) = ln (mantissa * 2^exponent) = ln (mantissa) + (exponent * ln (2))

		the mantissa we'll show as a value from range <1,2) because the logarithm
		is decreasing too fast when 'x' is going to 0

		return values:
			0 - ok
			1 - overflow
			2 - incorrect argument (x<=0)
	
		parts: look at the LnSurrounding1() method
	*/
	uint Ln(const Big<exp,man> & x)
	{
		TTMATH_REFERENCE_ASSERT( x )

		if( x.IsSign() || x.IsZero() )
			return 2;

		// m will be the value of the mantissa in range <1,2)
		Big<exp,man> m(x);
		m.exponent = -sint(man*TTMATH_BITS_PER_UINT - 1);
	    LnSurrounding1(m);

		Big<exp,man> exponent_temp;
		exponent_temp.FromInt( x.exponent );

		// we must add 'man*TTMATH_BITS_PER_UINT-1' because we've taken it from the mantissa
		uint c = exponent_temp.Add(man*TTMATH_BITS_PER_UINT-1);

		Big<exp,man> ln2;
		ln2.SetLn2();

		c += exponent_temp.Mul(ln2);
		c += Add(exponent_temp);

	return (c==0)? 0 : 1;
	}



	/*!
		Logarithm with a base 'base' -- this = Log(x) with a base 'base'

		we're using the formula:
			Log(x) with 'base' = ln(x) / ln(base)

		return values:
			0 - ok
			1 - overflow
			2 - incorrect argument (x<=0)
			3 - incorrect base (a<=0 lub a=1)


		parts: look at the LnSurrounding1() method
		  we pass this value only into 'ln(x)' method
		  because if we passed 'parts' into 'ln(base)' as well then
		  the error (after dividing) would be too great
	*/
	uint Log(const Big<exp,man> & x, const Big<exp,man> & base)
	{
		TTMATH_REFERENCE_ASSERT( base )
		TTMATH_REFERENCE_ASSERT( x )

		if( x.IsSign() || x.IsZero() )
			return 2;

		Big<exp,man> denominator;;
		denominator.SetOne();

		if( base.IsSign() || base.IsZero() || base==denominator )
			return 3;
		
		if( x == denominator ) // (this is: if x == 1)
		{
			// log(1) is 0
			SetZero();
			return 0;
		}

		// another error values we've tested at the start
		// there can be only a carry
		uint c = Ln(x);

		// we don't pass the 'parts' here (the error after dividing would be to great)
		c += denominator.Ln(base);
		c += Div(denominator);

	return (c==0)? 0 : 1;
	}




	/*!
	*
	*	convertion method
	*
	*/


	/*!
		this method sets 'result' as the one word of type sint

		if the value is too big this method returns a carry (1)
	*/
	uint ToInt(sint & result) const
	{
		result = 0;

		if( IsZero() )
			return 0;
		
		sint maxbit = -sint(man*TTMATH_BITS_PER_UINT);

		if( exponent > maxbit + sint(TTMATH_BITS_PER_UINT) )
			// if exponent > (maxbit + sint(TTMATH_BITS_PER_UINT)) the value can't be passed
			// into the 'sint' type (it's too big)
			return 1;

		if( exponent <= maxbit )
			// our value is from range (-1,1) and we return zero
			return 0;

		UInt<man> mantissa_temp(mantissa);
		// exponent is from a range of (-maxbit,0>
		sint how_many_bits = exponent.ToInt();

		// how_many_bits is negative, we'll make it positive
		how_many_bits = -how_many_bits;
	
		// we're taking into an account only the last word in a mantissa table
		mantissa_temp.Rcr( how_many_bits % TTMATH_BITS_PER_UINT, 0 );
		result = mantissa_temp.table[ man-1 ];

		// the exception for the minimal value
		if( IsSign() && result == TTMATH_UINT_HIGHEST_BIT )
			return 0;

		if( (result & TTMATH_UINT_HIGHEST_BIT) != 0 )
			// the value is too big
			return 1;

		if( IsSign() )
			result = -sint(result);

	return 0;
	}


	/*!
		this method sets the value in 'result'

		if the value is too big this method returns a carry (1)
	*/
	template<uint int_size>
	uint ToInt(Int<int_size> & result) const
	{
		result.SetZero();

		if( IsZero() )
			return 0;
		
		sint maxbit = -sint(man*TTMATH_BITS_PER_UINT);

		if( exponent > maxbit + sint(int_size*TTMATH_BITS_PER_UINT) )
			// if exponent > (maxbit + sint(int_size*TTMATH_BITS_PER_UINT)) the value can't be passed
			// into the 'Int<int_size>' type (it's too big)
			return 1;

		if( exponent <= maxbit )
			// our value is from range (-1,1) and we return zero
			return 0;

		UInt<man> mantissa_temp(mantissa);
		sint how_many_bits = exponent.ToInt();

		if( how_many_bits < 0 )
		{
			how_many_bits = -how_many_bits;
			uint index    = how_many_bits / TTMATH_BITS_PER_UINT;
			mantissa_temp.Rcr( how_many_bits % TTMATH_BITS_PER_UINT, 0 );

			for(uint i=index, a=0 ; i<man ; ++i,++a)
				result.table[a] = mantissa_temp.table[i];
		}
		else
		{
			uint index = how_many_bits / TTMATH_BITS_PER_UINT;

			for(uint i=0 ; i<man ; ++i)
				result.table[index+i] = mantissa_temp.table[i];

			result.Rcl( how_many_bits % TTMATH_BITS_PER_UINT, 0 );
		}

		// the exception for the minimal value
		if( IsSign() )
		{
			Int<int_size> min;
			min.SetMinValue();

			if( result == min )
				return 0;
		}

		if( (result.table[int_size-1] & TTMATH_UINT_HIGHEST_BIT) != 0 )
			// the value is too big
			return 1;

		if( IsSign() )
			result.ChangeSign();

	return 0;
	}


	/*!
		a method for converting 'sint' to this class
	*/
	void FromInt(sint value)
	{
	bool is_sign = false;

		if( value < 0 )
		{
			value  = -value;
			is_sign = true;
		}

		info = 0;
		mantissa = value;
		exponent.SetZero();

		if( is_sign )
			SetSign();

		// there shouldn't be a carry because 'value' has the type 'sint'
		Standardizing();
	}


	/*!
		an operator= for converting 'sint' to this class
	*/
	Big<exp, man> & operator=(sint value)
	{
		FromInt(value);

	return *this;
	}


	/*!
		a constructor for converting 'sint' and 'uint' to this class
	*/
	Big(sint value)
	{
		FromInt(value);
	}

	Big(uint value)
	{
		FromInt( sint(value) );
	}

#if defined _M_X64 || defined __x86_64__
	/*!
		a constructor for converting 'int' to this class
		(on 64bit platforms 'sint' has 64 bits and 'int' has 32 bits
	*/
	Big(int value)
	{
		FromInt( sint(value) );
	}
#endif


	/*!
		a method for converting from 'Int<int_size>' to this class
	*/
	template<uint int_size>
	void FromInt(Int<int_size> value)
	{
		info = 0;

		if( value.IsSign() )
		{
			value.ChangeSign();
			SetSign();
		}

		uint minimum_size = (int_size < man)? int_size : man;
		sint compensation  = (sint)value.CompensationToLeft();
		exponent          = (sint(int_size)-sint(man)) * sint(TTMATH_BITS_PER_UINT) - compensation;
		
		// copying the highest words
		uint i;
		for(i=1 ; i<=minimum_size ; ++i)
			mantissa.table[man-i] = value.table[int_size-i];

		// setting the rest of mantissa.table into zero (if some has left)
		for( ; i<=man ; ++i)
			mantissa.table[man-i] = 0;

	}


	/*!
		an operator= for converting from 'Int<int_size>' to this class
	*/
	template<uint int_size>
	Big<exp,man> & operator=(const Int<int_size> & value)
	{
		FromInt(value);

	return *this;
	}


	/*!
		a constructor for converting from 'Int<int_size>' to this class
	*/
	template<uint int_size>
	Big(const Int<int_size> & value)
	{
		FromInt(value);
	}


	/*!
		a default constructor

		warning: we don't set any of the members to zero etc.
	*/
	Big()
	{
	}


	/*!
		a destructor
	*/
	virtual ~Big()
	{
	}


	/*!
		the default assignment operator
	*/
	Big<exp,man> & operator=(const Big<exp,man> & value)
	{
		info = value.info;
		exponent = value.exponent;
		mantissa = value.mantissa;

	return *this;
	}


	/*!
		a constructor for copying from another object of this class
	*/
	Big(const Big<exp,man> & value)
	{
		operator=(value);
	}


	/*!
		a method for converting the value into the string with a base equal 'base'

		input:
			base - the base on which the value will be showed

			if 'always_scientific' is true the result will be showed in 'scientific' mode

			if 'always_scientific' is false the result will be showed
			either as 'scientific' or 'normal' mode, it depends whether the abs(exponent)
			is greater than 'when_scientific' or not, if it's greater the value
			will be printed as 'scientific'

			if 'max_digit_after_comma' is equal -1 that all digits in the mantissa
			will be printed
			
			if 'max_digit_after_comma' is equal -2 that not mattered digits
			in the mantissa will be cut off
			(zero characters at the end -- after the comma operator)

			if 'max_digit_after_comma' is equal or greater than zero
			that only 'max_digit_after_comma' after the comma operator will be showed
			(if 'max_digit_after_comma' is equal zero there'll be showed only 
			integer value without the comma)
				for example when the value is:
					12.345678 and max_digit_after_comma is 4
				then the result will be 
					12.3457   (the last digit was rounded)

			if there isn't the comma operator (when the value is too big and we're printing
			it not as scientific) 'max_digit_after_comma' will be ignored

		output:
			return value:
			0 - ok and 'result' will be an object of type std::string which holds the value
			1 - if there was a carry 
	*/
	uint ToString(	std::string & result,
					uint base                  = 10,
					bool always_scientific     = false,
					sint  when_scientific       = 15,
					sint  max_digit_after_comma = -2 ) const
	{
		static char error_overflow_msg[] = "overflow";
		result.erase();

		if(base<2 || base>16)
		{
			result = error_overflow_msg;
			return 1;
		}
	
		if( IsZero() )
		{
			result = "0";

		return 0;
		}

		/*
			since 'base' is greater or equal 2 that 'new_exp' of type 'Int<exp>' should
			hold the new value of exponent but we're using 'Int<exp+1>' because
			if the value for example would be 'max()' then we couldn't show it

				max() ->  11111111 * 2 ^ 11111111111  (bin)(the mantissa and exponent have all bits set)
				if we were using 'Int<exp>' we couldn't show it in this format:
				1,1111111 * 2 ^ 11111111111  (bin)
				because we have to add something to the mantissa and because 
				mantissa is full we can't do it and it'll be a carry
				(look at ToString_SetCommaAndExponent(...))

				when the base would be greater than two (for example 10) 
				we could use 'Int<exp>' here
		*/
		Int<exp+1> new_exp;

		if( ToString_CreateNewMantissaAndExponent(result, base, new_exp) )
		{
			result = error_overflow_msg;
			return 1;
		}

		/*
			we're rounding the mantissa only if the base is different from 2,4,8 or 16
			(this formula means that the number of bits in the base is greater than one)
		*/
		if( base!=2 && base!=4 && base!=8 && base!=16 )
			if( ToString_RoundMantissa(result, base, new_exp) )
			{
				result = error_overflow_msg;
				return 1;
			}

		if( ToString_SetCommaAndExponent(	result, base, new_exp, always_scientific,
											when_scientific, max_digit_after_comma ) )
		{
			result = error_overflow_msg;
			return 1;
		}

		if( IsSign() )
			result.insert(result.begin(), '-');

	// converted successfully
	return 0;
	}


private:


	/*!
		in the method 'ToString_CreateNewMantissaAndExponent()' we're using 
		type 'Big<exp+1,man>' and we should have the ability to use some
		necessary methods from that class (methods which are private here)
	*/
	friend class Big<exp-1,man>;


	/*!
		an auxiliary method for converting into the string (private)

		input:
			base - the base in range <2,16>

		output:
			return values:
				0 - ok
				1 - if there was a carry
			new_man - the new mantissa for 'base'
			new_exp - the new exponent for 'base'

		mathematic part:

		the value is stored as:
			value = mantissa * 2^exponent
		we want to show 'value' as:
			value = new_man * base^new_exp

		then 'new_man' we'll print using the standard method from UInt<> type for printing
		and 'new_exp' is the offset of the comma operator in a system of a base 'base'

		value = mantissa * 2^exponent
		value = mantissa * 2^exponent * (base^new_exp / base^new_exp)
		value = mantissa * (2^exponent / base^new_exp) * base^new_exp

		look at the part (2^exponent / base^new_exp), there'll be good if we take
		a 'new_exp' equal that value when the (2^exponent / base^new_exp) will be equal one

		on account of the 'base' is not as power of 2 (can be from 2 to 16),
		this formula will not be true for integer 'new_exp' then in our case we take 
		'base^new_exp' _greater_ than '2^exponent' 

		if 'base^new_exp' were smaller than '2^exponent' the new mantissa could be
		greater than the max value of the container UInt<man>

		value = mantissa * (2^exponent / base^new_exp) * base^new_exp
		  let M = mantissa * (2^exponent / base^new_exp) then
		value = M * base^new_exp

		in our calculation we treat M as floating value showing it as:
			M = mm * 2^ee where ee will be <= 0 

		next we'll move all bits of mm into the right when ee is equal zero
		abs(ee) must not to be too big that only few bits from mm we can leave

		then we'll have:
			M = mmm * 2^0
		'mmm' is the new_man which we're looking for


		new_exp we calculate in this way:
			2^exponent <= base^new_exp
			new_exp >= log base (2^exponent)   <- logarithm with the base 'base' from (2^exponent)
			
			but we need 'new'exp' as integer then we take:
			new_exp = [log base (2^exponent)] + 1  <- where [x] means integer value from x
	*/
	uint ToString_CreateNewMantissaAndExponent(	std::string & new_man, uint base,
												Int<exp+1> & new_exp) const
	{
	uint c = 0;

		if(base<2 || base>16)
			return 1;
	
		// the speciality for base equal 2
		if( base == 2 )
			return ToString_CreateNewMantissaAndExponent_Base2(new_man, new_exp);

		// this = mantissa * 2^exponent

		// temp = +1 * 2^exponent  
		// we're using a bigger type than 'big<exp,man>' (look below)
		Big<exp+1,man> temp;
		temp.info = 0;
		temp.exponent = exponent;
		temp.mantissa.SetOne();
		c += temp.Standardizing();

		// new_exp_ = [log base (2^exponent)] + 1
		Big<exp+1,man> new_exp_;
		c += new_exp_.ToString_Log(temp, base); // this logarithm isn't very complicated
		new_exp_.SkipFraction();
		temp.SetOne();
		c += new_exp_.Add( temp );

		// because 'base^new_exp' is >= '2^exponent' then 
		// because base is >= 2 then we've got:
		// 'new_exp_' must be smaller or equal 'new_exp'
		// and we can pass it into the Int<exp> type
		// (in fact we're using a greater type then it'll be ok)
		c += new_exp_.ToInt(new_exp);

		// base_ = base
		Big<exp+1,man> base_(base);

		// base_ = base_ ^ new_exp_
		c += base_.Pow( new_exp_ );
		// if we hadn't used a bigger type than 'Big<exp,man>' then the result
		// of this formula 'Pow(...)' would have been with an overflow

		// temp = mantissa * 2^exponent / base_^new_exp_
		// the sign don't interest us here
		temp.mantissa = mantissa;
		temp.exponent = exponent;

		c += temp.Div( base_ );

		// moving all bits of the mantissa into the right 
		// (how many times to move depend on the exponent)
		c += temp.ToString_MoveMantissaIntoRight();

		// on account of we take 'new_exp' as small as it's
		// possible ([log base (2^exponent)] + 1) that after the division 
		// (temp.Div( base_ )) the value of exponent should be equal zero or 
		// minimum smaller than zero then we've got the mantissa which has 
		// maximum valid bits

		temp.mantissa.ToString(new_man, base);

		// because we had used a bigger type for calculating I think we 
		// shouldn't have had a carry
		// (in the future this can be changed)

	return (c==0)? 0 : 1;
	}


	/*!
		this method calculates the logarithm
		it is used by ToString_CreateNewMantissaAndExponent() method

		it's not too complicated
		because x=+1*2^exponent (mantissa is one) then during the calculation
		the Ln(x) will not be making the long formula from LnSurrounding1()
		and only we have to calculate 'Ln(base)' but it'll be calculated
		only once, the next time we will get it from the 'history'

        x is greater than 0
		base is in <2,16> range
	*/
	uint ToString_Log(const Big<exp,man> & x, uint base)
	{
		TTMATH_REFERENCE_ASSERT( x )

		Big<exp,man> temp;
		temp.SetOne();

		if( x == temp )
		{
			// log(1) is 0
			SetZero();

		return 0;
		}

		// there can be only a carry
		// because the 'x' is in '1+2*exponent' form then 
		// the long formula from LnSurrounding1() will not be calculated
		// (LnSurrounding1() will return one immediately)
		uint c = Ln(x);


		/*
		 *
		 *	this is only temporarily (for testing)
		 *
		 */

//		static Big<exp,man> log_history[15] = { 0l,0l,0l,0l,0l,0l,0l,0l,0l,0l,
//			0l,0l,0l,0l,0l };
		static Big<exp,man> log_history[15] = { 0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0 };

		Big<exp,man> * log_value = log_history + base - 2;

		if( log_value->IsZero() )
		{
			// we don't have 'base' in 'log_history' then we calculate it now
			Big<exp,man> base_(base);
			c += temp.Ln(base_);
		    c += Div(temp);

			// the next time we'll get the 'Ln(base)' from the history,
			// this 'log_history' can have (16-2+1) items max

			*log_value = temp;
		}
		else
		{
			// we've calculated the 'Ln(base)' beforehand and we're using it now

			c += Div( *log_value );
		}

	return (c==0)? 0 : 1;
	}


	/*!
		an auxiliary method for converting into the string (private)

		this method moving all bits from mantissa into the right side
		the exponent tell us how many times moving (the exponent is <=0)
	*/
	uint ToString_MoveMantissaIntoRight()
	{
		if( exponent.IsZero() )
			return 0;
		
		// exponent can't be greater than zero
		// because we would cat the highest bits of the mantissa
		if( !exponent.IsSign() )
			return 1;

		if( exponent <= -sint(man*TTMATH_BITS_PER_UINT) )
			// if 'exponent' is <= than '-sint(man*TTMATH_BITS_PER_UINT)'
			// it means that we must cut the whole mantissa
			// (there'll not be any of the valid bits)
			return 1;

		// e will be from (-man*TTMATH_BITS_PER_UINT, 0>
		sint e = -( exponent.ToInt() );
		mantissa.Rcr(e,0);

	return 0;
	}


	/*!
		a special method similar to the 'ToString_CreateNewMantissaAndExponent'
		when the 'base' is equal 2

		we use it because if base is equal 2 we don't have to make those
		complicated calculations and the output is directly from the source
		(there will not be any small distortions)

		(we can make that speciality when the base is 4,8 or 16 as well 
		but maybe in further time)
	*/
	uint ToString_CreateNewMantissaAndExponent_Base2(	std::string & new_man,
														Int<exp+1> & new_exp     ) const
	{
		for( sint i=man-1 ; i>=0 ; --i )
		{
			uint value = mantissa.table[i]; 

			for( uint bit=0 ; bit<TTMATH_BITS_PER_UINT ; ++bit )
			{
				if( (value & TTMATH_UINT_HIGHEST_BIT) != 0 )
					new_man += '1';
				else
					new_man += '0';

				value <<= 1;
			}
		}

		new_exp = exponent;

	return 0;
	}


	/*!
		an auxiliary method for converting into the string

		this method roundes the last character from the new mantissa
		(it's used in systems where the base is different from 2)
	*/
	uint ToString_RoundMantissa(std::string & new_man, uint base, Int<exp+1> & new_exp) const
	{
		// we must have minimum two characters
		if( new_man.length() < 2 )
			return 0;

		std::string::size_type i = new_man.length() - 1;

		// we're erasing the last character
		uint digit = UInt<man>::CharToDigit( new_man[i] );
		new_man.erase( i, 1 );
		uint carry = new_exp.AddOne();

		// if the last character is greater or equal 'base/2'
		// we'll add one into the new mantissa
		if( digit >= base / 2 )
			ToString_RoundMantissa_AddOneIntoMantissa(new_man, base);

	return carry;
	}
	

	/*!
		an auxiliary method for converting into the string

		this method addes one into the new mantissa
	*/
	void ToString_RoundMantissa_AddOneIntoMantissa(std::string & new_man, uint base) const
	{
		if( new_man.empty() )
			return;

		sint i = sint( new_man.length() ) - 1;
		bool was_carry = true;

		for( ; i>=0 && was_carry ; --i )
		{
			// we can have the comma as well because
			// we're using this method later in ToString_CorrectDigitsAfterComma_Round()
			// (we're only ignoring it)
			if( new_man[i] == TTMATH_COMMA_CHARACTER_1 )
				continue;

			// we're adding one
			uint digit = UInt<man>::CharToDigit( new_man[i] ) + 1;

			if( digit == base )
				digit = 0;
			else
				was_carry = false;

			new_man[i] = UInt<man>::DigitToChar( digit );
		}

		if( i<0 && was_carry )
			new_man.insert( new_man.begin() , '1' );
	}


	/*!
		an auxiliary method for converting into the string

		this method sets the comma operator and/or puts the exponent
		into the string
	*/
	uint ToString_SetCommaAndExponent(	std::string & new_man, uint base, Int<exp+1> & new_exp,
										bool always_scientific,
										sint  when_scientific,
										sint  max_digit_after_comma ) const
	{
	uint carry = 0;

		if( new_man.empty() )
			return carry;

		Int<exp+1> scientific_exp( new_exp );

		// 'new_exp' depends on the 'new_man' which is stored like this e.g:
		//  32342343234 (the comma is at the end)
		// we'd like to show it in this way:
		//  3.2342343234 (the 'scientific_exp' is connected with this example)

		sint offset = sint( new_man.length() ) - 1;
		carry += scientific_exp.Add( offset );
		// there shouldn't have been a carry because we're using
		// a greater type -- 'Int<exp+1>' instead of 'Int<exp>'

		if( !always_scientific )
		{
			if( scientific_exp > when_scientific || scientific_exp < -sint(when_scientific) )
				always_scientific = true;
		}

		// 'always_scientific' could be changed
		if( !always_scientific )
			ToString_SetCommaAndExponent_Normal(new_man, base, new_exp, max_digit_after_comma);
		else
			// we're passing the 'scientific_exp' instead of 'new_exp' here
			ToString_SetCommaAndExponent_Scientific(new_man, base, scientific_exp, max_digit_after_comma);

	return (carry==0)? 0 : 1;
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_SetCommaAndExponent_Normal(std::string & new_man, uint base, 
										Int<exp+1> & new_exp, sint max_digit_after_comma) const
	{
		//if( new_exp >= 0 )
		if( !new_exp.IsSign() )
			return ToString_SetCommaAndExponent_Normal_AddingZero(new_man, new_exp);
		else
			return ToString_SetCommaAndExponent_Normal_SetCommaInside(new_man, base, new_exp, max_digit_after_comma);
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_SetCommaAndExponent_Normal_AddingZero(std::string & new_man,
																Int<exp+1> & new_exp) const
	{
		// we're adding zero characters at the end
		// 'i' will be smaller than 'when_scientific' (or equal)
		uint i = new_exp.ToInt();
		
		if( new_man.length() + i > new_man.capacity() )
			// about 6 characters more (we'll need it for the comma or something)
			new_man.reserve( new_man.length() + i + 6 );
		
		for( ; i>0 ; --i)
			new_man += '0';
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_SetCommaAndExponent_Normal_SetCommaInside(std::string & new_man,
							uint base, Int<exp+1> & new_exp, sint max_digit_after_comma) const
	{
		// new_exp is < 0 

		sint new_man_len = sint(new_man.length()); // 'new_man_len' with a sign
		sint e = -( new_exp.ToInt() ); // 'e' will be positive

		if( new_exp > -new_man_len )
		{
			// we're setting the comma within the mantissa
			
			sint index = new_man_len - e;
			new_man.insert( new_man.begin() + index, TTMATH_COMMA_CHARACTER_1);
		}
		else
		{
			// we're adding zero characters before the mantissa

			uint how_many = e - new_man_len;
			std::string man_temp(how_many+1, '0');

			man_temp.insert( man_temp.begin()+1, TTMATH_COMMA_CHARACTER_1);
			new_man.insert(0, man_temp);
		}

		ToString_CorrectDigitsAfterComma(new_man, base, max_digit_after_comma);
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_SetCommaAndExponent_Scientific(	std::string & new_man,
													uint base,
													Int<exp+1> & scientific_exp,
													sint max_digit_after_comma ) const
	{
		if( new_man.empty() )
			return;
		
		new_man.insert( new_man.begin()+1, TTMATH_COMMA_CHARACTER_1 );

		ToString_CorrectDigitsAfterComma(new_man, base, max_digit_after_comma);
	
		if( base == 10 )
		{
			new_man += 'e';

			if( !scientific_exp.IsSign() )
				new_man += "+";
		}
		else
		{
			// the 10 here is meant as the base 'base'
			// (no matter which 'base' we're using there'll always be 10 here)
			new_man += "*10^";
		}

		std::string temp_exp;
		scientific_exp.ToString( temp_exp, base );

		new_man += temp_exp;
	}


	/*!
		an auxiliary method for converting into the string

		we can call this method only if we've put the comma operator into the mantissa's string
	*/
	void ToString_CorrectDigitsAfterComma(std::string & new_man, uint base,
															sint max_digit_after_comma) const
	{
		switch( max_digit_after_comma )
		{
		case -1:
			// the mantissa will be unchanged
			break;
		
		case -2:
			ToString_CorrectDigitsAfterComma_CutOffZeroCharacters(new_man);
			break;

		default:
			ToString_CorrectDigitsAfterComma_Round(new_man, base, max_digit_after_comma);
			break;
		}
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_CorrectDigitsAfterComma_CutOffZeroCharacters(std::string & new_man) const
	{
		// minimum two characters
		if( new_man.length() < 2 )
			return;

		// we're looking for the index of the last character which is not zero
		uint i = uint( new_man.length() ) - 1;
		for( ; i>0 && new_man[i]=='0' ; --i );

		// if there is another character than zero at the end
		// we're finishing
		if( i == new_man.length() - 1 )
			return;

		// if directly before the first zero is the comma operator
		// we're cutting it as well
		if( i>0 && new_man[i]==TTMATH_COMMA_CHARACTER_1 )
			--i;

		new_man.erase(i+1, new_man.length()-i-1);
	}


	/*!
		an auxiliary method for converting into the string
	*/
	void ToString_CorrectDigitsAfterComma_Round(std::string & new_man, uint base,
															sint max_digit_after_comma) const
	{
		// first we're looking for the comma operator
		std::string::size_type index = new_man.find(TTMATH_COMMA_CHARACTER_1, 0);

		if( index == std::string::npos )
			// nothing was found (actually there can't be this situation)
			return;

		// we're calculating how many digits there are at the end (after the comma)
		// 'after_comma' will be greater than zero because at the end
		// we have at least one digit
		std::string::size_type after_comma = new_man.length() - index - 1;

		// if 'max_digit_after_comma' is greater than 'after_comma' (or equal)
		// we don't have anything for cutting
		if( std::string::size_type(max_digit_after_comma) >= after_comma )
			return;

		uint last_digit = UInt<man>::CharToDigit( new_man[ index + max_digit_after_comma + 1 ], base );

		// we're cutting the rest of the string
		new_man.erase(index + max_digit_after_comma + 1, after_comma - max_digit_after_comma);

		if( max_digit_after_comma == 0 )
		{
			// we're cutting the comma operator as well
			// (it's not needed now because we've cut the whole rest after the comma)
			new_man.erase(index, 1);
		}

		if( last_digit >= base / 2 )
			// we must round here
			ToString_RoundMantissa_AddOneIntoMantissa(new_man, base);
	}




public:


	/*!
		a method for converting a string into its value

		it returns 1 if the value will be too big -- we cannot pass it into the range
		of our class Big<exp,man>

		that means only digits before the comma operator can make this value too big, 
		all digits after the comma we can ignore

		'source' - pointer to the string for parsing

		if 'after_source' is set that when this method will have finished its job
		it set the pointer to the new first character after this parsed value
	*/
	uint FromString(const char * source, uint base = 10, const char ** after_source = 0)
	{
	bool is_sign;

		if( base<2 || base>16 )
		{
			if( after_source )
				*after_source = source;

			return 1;
		}

		SetZero();
		FromString_TestNewBase( source, base );
		FromString_TestSign( source, is_sign );

		uint c = FromString_ReadPartBeforeComma( source, base );

		if( FromString_TestCommaOperator(source) )
			c += FromString_ReadPartAfterComma( source, base );

		if( base==10 && FromString_TestScientific(source) )
			c += FromString_ReadPartScientific( source );

		if( is_sign && !IsZero() )
			ChangeSign();

		if( after_source )
			*after_source = source;

	return (c==0)? 0 : 1;
	}



private:


	/*!
		we're testing whether a user wants to change the base

		if there's a '#' character it means that the user wants the base to be 16,
		if '&' the base will be 2
	*/
	void FromString_TestNewBase( const char * & source, uint & base )
	{
		UInt<man>::SkipWhiteCharacters(source);

		if( *source == '#' )
		{
			base = 16;
			++source;
		}
		else
		if( *source == '&' )
		{
			base = 2;
			++source;
		}
	}


	/*!
		we're testing whether the value is with the sign

		(this method is used from 'FromString_ReadPartScientific' too)
	*/
	void FromString_TestSign( const char * & source, bool & is_sign )
	{
		UInt<man>::SkipWhiteCharacters(source);

		is_sign = false;

		if( *source == '-' )
		{
			is_sign = true;
			++source;
		}
		else
		if( *source == '+' )
		{
			++source;
		}
	}


	/*!
		we're testing whether is there a comma operator
	*/
	bool FromString_TestCommaOperator(const char * & source)
	{
		if( (*source == TTMATH_COMMA_CHARACTER_1) || 
			(*source == TTMATH_COMMA_CHARACTER_2 && TTMATH_COMMA_CHARACTER_2 != 0 ) )
		{
			++source;

		return true;
		}

	return false;
	}


	/*!
		this method reads the first part of a string
		(before the comma operator)
	*/
	uint FromString_ReadPartBeforeComma( const char * & source, uint base )
	{
		sint character;
		Big<exp, man> temp;
		Big<exp, man> base_( base );
		
		UInt<man>::SkipWhiteCharacters( source );

		for( ; (character=UInt<man>::CharToDigit(*source, base)) != -1 ; ++source )
		{
			temp = character;

			if( Mul(base_) )
				return 1;

			if( Add(temp) )
				return 1;
		}

	return 0;
	}


	/*!
		this method reads the second part of a string
		(after the comma operator)
	*/
	uint FromString_ReadPartAfterComma( const char * & source, uint base )
	{
	sint character;
	uint c = 0, index = 1;
	Big<exp, man> part, power, old_value, base_( base );

		// we don't remove any white characters here

		power.SetOne();

		for( ; (character=UInt<man>::CharToDigit(*source, base)) != -1 ; ++source, ++index )
		{
			part = character;

			if( power.Mul( base_ ) )
				// there's no sens to add the next parts, but we can't report this
				// as an error (this is only inaccuracy)
				break;

			if( part.Div( power ) )
				break;

			// every 5 iteration we make a test whether the value will be changed or not
			// (character must be different from zero to this test)
			bool testing = (character != 0 && (index % 5) == 0);

			if( testing )
				old_value = *this;

			// there actually shouldn't be a carry here
			c += Add( part );

			if( testing && old_value == *this )
				// after adding 'part' the value has not been changed
				// there's no sense to add any next parts
				break;
		}

		// we could break the parsing somewhere in the middle of the string,
		// but the result (value) still can be good
		// we should set a correct value of 'source' now
		for( ; UInt<man>::CharToDigit(*source, base) != -1 ; ++source );

	return (c==0)? 0 : 1;
	}


	/*!
		we're testing whether is there the character 'e'

		this character is only allowed when we're using the base equals 10
	*/
	bool FromString_TestScientific(const char * & source)
	{
		UInt<man>::SkipWhiteCharacters(source);

		if( *source=='e' || *source=='E' )
		{
			++source;

		return true;
		}

	return false;
	}


	/*!
		this method reads the exponent (after 'e' character) when there's a scientific
		format of value and only when we're using the base equals 10
	*/
	uint FromString_ReadPartScientific( const char * & source )
	{
	uint c = 0;
	Big<exp, man> new_exponent, temp;
	bool was_sign = false;

		FromString_TestSign( source, was_sign );
		FromString_ReadPartScientific_ReadExponent( source, new_exponent );

		if( was_sign )
			new_exponent.ChangeSign();

		temp = 10;
		c += temp.PowBInt( new_exponent );
		c += Mul(temp);

	return (c==0)? 0 : 1;
	}


	/*!
		this method reads the value of the extra exponent when scientific format is used
		(only when base == 10)
	*/
	uint FromString_ReadPartScientific_ReadExponent( const char * & source, Big<exp, man> & new_exponent )
	{
	sint character;
	Big<exp, man> base, temp;

		UInt<man>::SkipWhiteCharacters(source);

		new_exponent.SetZero();
		base = 10;

		for( ; (character=UInt<man>::CharToDigit(*source, 10)) != -1 ; ++source )
		{
			temp = character;

			if( new_exponent.Mul(base) )
				return 1;

			if( new_exponent.Add(temp) )
				return 1;
		}

	return 0;
	}


public:


	/*!
		a method for converting a string into its value		
	*/
	uint FromString(const std::string & string, uint base = 10)
	{
		return FromString( string.c_str(), base );
	}


	/*!
		a constructor for converting a string into this class
	*/
	Big(const char * string)
	{
		FromString( string );
	}


	/*!
		a constructor for converting a string into this class
	*/
	Big(const std::string & string)
	{
		FromString( string.c_str() );
	}


	/*!
		an operator= for converting a string into its value
	*/
	Big<exp, man> & operator=(const char * string)
	{
		FromString( string );

	return *this;
	}


	/*!
		an operator= for converting a string into its value
	*/
	Big<exp, man> & operator=(const std::string & string)
	{
		FromString( string.c_str() );

	return *this;
	}



	/*!
	*
	*	methods for comparing
	*
	*/


	/*!
		this method performs the formula 'abs(this) < abs(ss2)'
		and returns the result

		(in other words it treats 'this' and 'ss2' as values without a sign)
	*/
	bool SmallerWithoutSignThan(const Big<exp,man> & ss2) const
	{
		// we should check the mantissas beforehand because sometimes we can have
		// a mantissa set to zero but in the exponent something another value
		// (maybe we've forgotten about calling CorrectZero() ?)
		if( mantissa.IsZero() )
		{
			if( ss2.mantissa.IsZero() )
				// we've got two zeroes
				return false;
			else
				// this==0 and ss2!=0
				return true;
		}

		if( ss2.mantissa.IsZero() )
			// this!=0 and ss2==0
			return false;

		// we're using the fact that all bits in mantissa are pushed
		// into the left side -- Standardizing()
		if( exponent == ss2.exponent )
			return mantissa < ss2.mantissa;

	return exponent < ss2.exponent;
	}


	/*!
		this method performs the formula 'abs(this) > abs(ss2)'
		and returns the result

		(in other words it treats 'this' and 'ss2' as values without a sign)
	*/
	bool GreaterWithoutSignThan(const Big<exp,man> & ss2) const
	{
		// we should check the mantissas beforehand because sometimes we can have
		// a mantissa set to zero but in the exponent something another value
		// (maybe we've forgotten about calling CorrectZero() ?)
		if( mantissa.IsZero() )
		{
			if( ss2.mantissa.IsZero() )
				// we've got two zeroes
				return false;
			else
				// this==0 and ss2!=0
				return false;
		}

		if( ss2.mantissa.IsZero() )
			// this!=0 and ss2==0
			return true;

		// we're using the fact that all bits in mantissa are pushed
		// into the left side -- Standardizing()
		if( exponent == ss2.exponent )
			return mantissa > ss2.mantissa;

	return exponent > ss2.exponent;
	}


	/*!
		this method performs the formula 'abs(this) == abs(ss2)'
		and returns the result

		(in other words it treats 'this' and 'ss2' as values without a sign)
	*/
	bool EqualWithoutSign(const Big<exp,man> & ss2) const
	{
		// we should check the mantissas beforehand because sometimes we can have
		// a mantissa set to zero but in the exponent something another value
		// (maybe we've forgotten about calling CorrectZero() ?)
		if( mantissa.IsZero() )
		{
			if( ss2.mantissa.IsZero() )
				// we've got two zeroes
				return true;
			else
				// this==0 and ss2!=0
				return false;
		}

		if( ss2.mantissa.IsZero() )
			// this!=0 and ss2==0
			return false;

		if( exponent==ss2.exponent && mantissa==ss2.mantissa )
			return true;

	return false;
	}


	bool operator<(const Big<exp,man> & ss2) const
	{
		if( IsSign() && !ss2.IsSign() )
			// this<0 and ss2>=0
			return true;

		if( !IsSign() && ss2.IsSign() )
			// this>=0 and ss2<0
			return false;

		// both signs are the same

		if( IsSign() )
			return ss2.SmallerWithoutSignThan( *this );

	return SmallerWithoutSignThan( ss2 );
	}




	bool operator==(const Big<exp,man> & ss2) const
	{
		if( IsSign() != ss2.IsSign() )
			return false;

	return EqualWithoutSign( ss2 );
	}




	bool operator>(const Big<exp,man> & ss2) const
	{
		if( IsSign() && !ss2.IsSign() )
			// this<0 and ss2>=0
			return false;

		if( !IsSign() && ss2.IsSign() )
			// this>=0 and ss2<0
			return true;

		// both signs are the same

		if( IsSign() )
			return ss2.GreaterWithoutSignThan( *this );

	return GreaterWithoutSignThan( ss2 );
	}



	bool operator>=(const Big<exp,man> & ss2) const
	{
		return !operator<( ss2 );
	}


	bool operator<=(const Big<exp,man> & ss2) const
	{
		return !operator>( ss2 );
	}


	bool operator!=(const Big<exp,man> & ss2) const
	{
		return !operator==(ss2);
	}





	/*!
	*
	*	standard mathematical operators 
	*
	*/


	/*!
		an operator for changing the sign

		it's not changing 'this' but the changed value will be returned
	*/
	Big<exp,man> operator-() const
	{
		Big<exp,man> temp(*this);

		temp.ChangeSign();

	return temp;
	}


	Big<exp,man> operator-(const Big<exp,man> & ss2) const
	{
	Big<exp,man> temp(*this);

		temp.Sub(ss2);

	return temp;
	}

	Big<exp,man> & operator-=(const Big<exp,man> & ss2) const
	{
		Sub(ss2);

	return *this;
	}


	Big<exp,man> operator+(const Big<exp,man> & ss2) const
	{
	Big<exp,man> temp(*this);

		temp.Add(ss2);

	return temp;
	}


	Big<exp,man> & operator+=(const Big<exp,man> & ss2) const
	{
		Add(ss2);

	return *this;
	}


	Big<exp,man> operator*(const Big<exp,man> & ss2) const
	{
	Big<exp,man> temp(*this);

		temp.Mul(ss2);

	return temp;
	}


	Big<exp,man> & operator*=(const Big<exp,man> & ss2) const
	{
		Mul(ss2);

	return *this;
	}


	Big<exp,man> operator/(const Big<exp,man> & ss2) const
	{
	Big<exp,man> temp(*this);

		temp.Div(ss2);

	return temp;
	}


	Big<exp,man> & operator/=(const Big<exp,man> & ss2) const
	{
		Div(ss2);

	return *this;
	}


	/*!
		this method makes an integer value by skipping any fractions

		for example:
			10.7 will be 10
			12.1  -- 12
			-20.2 -- 20
			-20.9 -- 20
			-0.7  -- 0
			0.8   -- 0
	*/
	void SkipFraction()
	{
		if( IsZero() )
			return;

		if( !exponent.IsSign() )
			// exponent >=0 -- the value don't have any fractions
			return;

		if( exponent <= -sint(man*TTMATH_BITS_PER_UINT) )
		{
			// the value is from (-1,1), we return zero
			SetZero();
			return;
		}

		// exponent is in range (-man*TTMATH_BITS_PER_UINT, 0)
		sint e = exponent.ToInt();
	
		mantissa.ClearFirstBits( -e );
		
		// we don't have to standardize 'Standardizing()' the value because
		// there's at least one bit in the mantissa
		// (the highest bit which we didn't touch)
	}


	/*!
		this method remains only a fraction from the value

		for example:
			30.56 will be 0.56
			-12.67 -- -0.67
	*/
	void RemainFraction()
	{
		if( IsZero() )
			return;

		if( !exponent.IsSign() )
		{
			// exponent >= 0 -- the value doesn't have any fractions
			// we return zero
			SetZero();
			return;
		}

		if( exponent <= -sint(man*TTMATH_BITS_PER_UINT) )
		{
			// the value is from (-1,1)
			// we don't make anything with the value
			return;
		}

		// e will be from (-man*TTMATH_BITS_PER_UINT, 0)
		sint e = exponent.ToInt();

		sint how_many_bits_leave = sint(man*TTMATH_BITS_PER_UINT) + e; // there'll be a subtraction -- e is negative
		mantissa.Rcl( how_many_bits_leave, 0);

		// there'll not be a carry because the exponent is too small
		exponent.Sub( how_many_bits_leave );

		// we must call Standardizing() here
		Standardizing();
	}




	/*!
		this method rounds to the nearest integer value
		(it returns a carry if it was)

		for example:
			2.3 = 2
			2.8 = 3

			-2.3 = -2
			-2.8 = 3
	*/
	uint Round()
	{
	Big<exp,man> half;
	uint c;

		half.SetDotOne();

		if( IsSign() )
		{
			// 'this' is < 0
			c = Sub( half );
		}
		else
		{
			// 'this' is >= 0
			c = Add( half );
		}

		SkipFraction();

	return c;
	}





	/*!
	*
	*	input/output operators for standard streams
	*
	*/

	friend std::ostream & operator<<(std::ostream & s, const Big<exp,man> & l)
	{
	std::string ss;

		l.ToString(ss);
		s << ss;

	return s;
	}


	friend std::istream & operator>>(std::istream & s, Big<exp,man> & l)
	{
	std::string ss;
	
	// 'char' for operator>>
	unsigned char z;
	bool was_comma = false;

		// operator>> omits white characters if they're set for ommiting
		s >> z;

		if( z=='-' || z=='+' )
		{
			ss += z;
			s >> z; // we're reading a next character (white characters can be ommited)
		}

		// we're reading only digits (base=10) and only one comma operator
		while(	s.good() &&
			(	UInt<man>::CharToDigit(z, 10)>=0 || (!was_comma && z==TTMATH_COMMA_CHARACTER_1) )
			 )
		{
			if( z == TTMATH_COMMA_CHARACTER_1 )
				was_comma = true;

			ss += z;
			z = s.get();
		}

		// we're leaving the last readed character
		// (it's not belonging to the value)
		s.unget();

		l.FromString( ss );

	return s;
	}

};


} // namespace

#endif
