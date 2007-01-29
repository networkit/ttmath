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



#ifndef headerfilettmathint
#define headerfilettmathint

/*!
	\file ttmathint.h
    \brief template class Int<uint>
*/

#include "ttmathuint.h"

namespace ttmath
{


/*!
	\brief it implements the big integer value with the sign

	value_size - how many bytes specify our value (value_size = 1 -> 4 bytes -> 32 bits)
	value_size = 1,2,3,4,5,6....
*/
template<uint value_size>
class Int : public UInt<value_size>
{
public:

	/*!
		this method sets the max value which this class can hold
		(all bits will be one besides the last one)
	*/
	void SetMaxValue()
	{
		UInt<value_size>::SetMaxValue();
		UInt<value_size>::table[value_size-1] = ~ TTMATH_UINT_HIGHEST_BIT;
	}


	/*!
		this method sets the min value which this class can hold
		(all bits will be zero besides the last one which is one)
	*/
	void SetMinValue()
	{
		UInt<value_size>::SetZero();
		UInt<value_size>::table[value_size-1] = TTMATH_UINT_HIGHEST_BIT;
	}


	/*!
		this method sets -1 as the value
		(-1 is equal the max value in an unsigned type)
	*/
	void SetSignOne()
	{
		UInt<value_size>::SetMaxValue();
	}


	/*!
		we change the sign of the value

		if it isn't possible to change the sign this method returns 1
		else return 0 and changing the sign
	*/
	uint ChangeSign()
	{
	Int<value_size> temp;
	
		temp.SetMinValue();

		/*
			if the value is equal that one which has been returned from SetMinValue
			that means we can't change sign because the value is too big (bigger about one)

			e.g. when value_size = 1 and value is -2147483648 we can't change it to the
			2147483648 because the max value which can be held is 2147483647

			we don't change the value and we're using this fact somewhere in some methods
			(if we look on our value without the sign we get the correct value 
			eg. -2147483648 in Int<1> will be 2147483648 on the UInt<1> type)
		*/
		if( operator==(temp) )
			return 1;

		temp.SetZero();
		temp.UInt<value_size>::Sub(*this);

		operator=(temp);

	return 0;
	}



	/*!	
		this method sets the sign

		e.g. 1  -> -1
		     -2 -> -2
		
		from a positive value we always make a negative value
	*/
	void SetSign()
	{
		if( IsSign() )
			return;

		ChangeSign();
	}



	/*!
		this method returns true if there's the sign

		(the highest bit will be converted to the bool)
	*/
	bool IsSign() const
	{
		return UInt<value_size>::IsTheHighestBitSet();
	}



	/*!
		it returns the absolute value

		it can return carry (1) (look on ChangeSign() for details)
	*/
	uint Abs()
	{
		if( !IsSign() )
			return 0;

	return ChangeSign();
	}




	/*!
	*
	*	basic mathematic functions
	*
	*/

	/*!
		this method adds two value with sign and returns carry

		we're using methods from the base class because values are stored with U2
		we must only make the carry correction

		this = p1(=this) + p2

		when p1>=0 i p2>=0 carry is set when the highest bit of value is set
		when p1<0  i p2<0  carry is set when the highest bit of value is clear
		when p1>=0 i p2<0  carry will never be set
		when p1<0  i p2>=0 carry will never be set
	*/
	uint Add(const Int<value_size> & ss2)
	{
		bool p1_is_sign = IsSign();
		bool p2_is_sign = ss2.IsSign();

		UInt<value_size>::Add(ss2);		

		if( !p1_is_sign && !p2_is_sign )
		{
			if( UInt<value_size>::IsTheHighestBitSet() )
				return 1;
		}

		if( p1_is_sign && p2_is_sign )
		{	
			if( ! UInt<value_size>::IsTheHighestBitSet() )
				return 1;
		}

	return 0;
	}


	/*!	
		this method subtracts two values with the sign

		we don't use the previous Add because the method ChangeSign can
		sometimes return carry 

		this = p1(=this) - p2

		when p1>=0 i p2>=0 carry will never be set
		when p1<0  i p2<0  carry will never be set
		when p1>=0 i p2<0  carry is set when the highest bit of value is set
		when p1<0  i p2>=0 carry is set when the highest bit of value is clear
	*/
	uint Sub(const Int<value_size> & ss2)
	{
		bool p1_is_sign = IsSign();
		bool p2_is_sign = ss2.IsSign();

		UInt<value_size>::Sub(ss2);		

		if( !p1_is_sign && p2_is_sign )
		{
			if( UInt<value_size>::IsTheHighestBitSet() )
				return 1;
		}

		if( p1_is_sign && !p2_is_sign )
		{	
			if( ! UInt<value_size>::IsTheHighestBitSet() )
				return 1;
		}

	return 0;
	}


	/*!
		this method adds one to the value and returns carry
	*/
	uint AddOne()
	{
	Int<value_size> temp;

		temp.SetOne();

	return Add(temp);
	}


	/*!
		this method subtracts one from the value and returns carry
	*/
	uint SubOne()
	{
	Int<value_size> temp;

		temp.SetOne();

	return Sub(temp);
	}



	/*!
		multiplication this = this * ss2

		it returns carry if the result is too big
		(we're using the method from the base class but we have to make
		one correction in account of signs)
	*/
	uint Mul(Int<value_size> ss2)
	{
	bool ss1_is_sign, ss2_is_sign;

		ss1_is_sign = IsSign();
		ss2_is_sign = ss2.IsSign();

		/*
			we don't have to check the carry from Abs (values will be correct
			because next we're using the method Mul from the base class UInt
			which is without a sign)
		*/
		Abs();
		ss2.Abs();

		if( UInt<value_size>::Mul(ss2) )
			return 1;


		/*
			we have to examine the sign of result now
			but if the result is with the sign then:
				1. if the signs were the same that means the result is too big
				(the result must be without a sign)
				2. if the signs were diffrent that means if the result
				is different from that one which has been returned from SetMinValue()
				that is carry (result too big) but if the result is equal SetMinValue()
				there'll be ok (and the next SetSign will has no effect because
				the value is actually negative -- look at description of that case
				in ChangeSign())
		*/
		if( IsSign() )
		{
			/*
				there can be one case where signs are different and
				the result will be equal the value from SetMinValue()
				(there is ok situation)
			*/
			if( ss1_is_sign != ss2_is_sign )
			{
				Int<value_size> temp;
				temp.SetMinValue();
				
				if( operator!=(temp) )
					/*
						the result is too big
					*/
					return 1;
			}
			else
			{
				/*
					the result is too big
				*/
				return 1;
			}
		}

		if( ss1_is_sign != ss2_is_sign )
			SetSign();


	return 0;
	}


	/*!
		division this = this / ss2
		function returns the remainder

		for example: (result means this)
			 20 /  3 --> result:  6   remainder:  2
			-20 /  3 --> result: -6   remainder: -2
			 20 / -3 --> result: -6   remainder:  2
			-20 / -3 --> result:  6   remainder: -2

		in other words: this(old) = result * this(new) + remainder
	*/
	Int<value_size> Div(Int<value_size> ss2)
	{
	bool ss1_is_sign, ss2_is_sign;
	Int<value_size> remainder;

		ss1_is_sign = IsSign();
		ss2_is_sign = ss2.IsSign();

		/*
			we don't have to test the carry from Abs as well as in Mul
		*/
		Abs();
		ss2.Abs();

		remainder = UInt<value_size>::Div(ss2);

		if( ss1_is_sign != ss2_is_sign )
			SetSign();

		if( ss1_is_sign )
			remainder.SetSign();

	return remainder;
	}
	




	/*!
	*
	*	convertion methods
	*
	*/

	/*!
		this method convert an UInt<another_size> type to this class

		this operation has mainly sense if the value from p
		can be held in this type

		it returns a carry if the value 'p' is too big
	*/
	template<uint argument_size>
	uint FromInt(const Int<argument_size> & p)
	{
		uint min_size = (value_size < argument_size)? value_size : argument_size;
		uint i;

		for(i=0 ; i<min_size ; ++i)
			UInt<value_size>::table[i] = p.table[i];


		if( i < value_size )
		{	
			uint fill = (p.table[argument_size-1] & TTMATH_UINT_HIGHEST_BIT)? TTMATH_UINT_MAX_VALUE : 0;

			for( ; i<value_size ; ++i)
				UInt<value_size>::table[i] = fill;
		}
		else
		{
			uint test = (UInt<value_size>::table[value_size-1] & TTMATH_UINT_HIGHEST_BIT)? TTMATH_UINT_MAX_VALUE : 0;

			for( ; i<argument_size ; ++i)
				if( p.table[i] != test )
					return 1;
		}

	return 0;
	}


	/*!
		this operator convert an UInt<another_size> type to this class

		it doesn't return a carry
	*/
	template<uint argument_size>
	Int<value_size> & operator=(const Int<argument_size> & p)
	{
		FromInt(p);

	return *this;
	}


	/*!
		the default assignment operator
	*/
	Int<value_size> & operator=(const Int<value_size> & p)
	{
		FromInt(p);

	return *this;
	}


	/*!
		this method convert an sint type to this class
	*/
	Int<value_size> & operator=(sint i)
	{
		if(i<0)
			SetSignOne();
		else
			UInt<value_size>::SetZero();

		UInt<value_size>::table[0] = uint(i);

	return *this;
	}


	/*!
		constructor for converting an uint to this class
	*/
	Int(sint i)
	{
		operator=(i);
	}


	/*!
		constructor for converting string to this class (with base=10)
	*/
	Int(const char * s)
	{
		FromString(s);
	}


	/*!
		constructor for converting string to this class (with base=10)
	*/
	Int(const std::string & s)
	{
		FromString( s.c_str() );
	}


	/*!
		default constructor

		we don't clear table etc.
	*/
	Int()
	{
	}


	/*!
		the copying constructor
	*/
	template<uint argument_size>
	Int(const Int<argument_size> & u) : UInt<value_size>::size(value_size)
	{
		// look that 'size' we still set as 'value_size' and not as u.value_size

		operator=(u);
	}


	/*!
		a destructor
	*/
	virtual ~Int()
	{
	}

	/*!
		this method returns the lowest value from table with the sign

		we must be sure when we using this method whether the value
		will hold in an sint type or not (the rest value from table must be zero or -1)
	*/
	sint ToInt() const
	{
		return sint( UInt<value_size>::table[0] );
	}


	/*!	
		this method converts the value to a string with a base equal 'b'
	*/
	void ToString(std::string & result, uint b = 10) const
	{
		if( IsSign() )
		{
			Int<value_size> temp(*this);
			temp.Abs();

			temp.UInt<value_size>::ToString(result, b);
			result.insert(result.begin(), '-');
		}
		else
		{
			UInt<value_size>::ToString(result, b);
		}
	}




	/*!
		this method converts a string into its value
		it returns carry=1 if the value will be too big or an incorrect base 'b' is given

		string is ended with a non-digit value, for example:
			"-12" will be translated to -12
			as well as:
			"- 12foo" will be translated to 12 too

		existing first white characters will be ommited
		(between '-' and a first digit can be white characters too)
	*/
	uint FromString(const char * s, uint b = 10)
	{
	bool is_sign = false;
	
		UInt<value_size>::SkipWhiteCharacters(s);

		if( *s == '-' )
		{
			is_sign = true;
			UInt<value_size>::SkipWhiteCharacters(++s);
		}
		else
		if( *s == '+' )
		{
			UInt<value_size>::SkipWhiteCharacters(++s);
		}

		if( UInt<value_size>::FromString(s,b) )
			return 1;

		if( is_sign )
		{
		Int<value_size> mmin;

			mmin.SetMinValue();

			/*
				the reference to mmin will be automatically converted to the reference
				to a UInt type
				(this value can be equal mmin -- look at a description in ChangeSign())
			*/
			if( UInt<value_size>::operator>( mmin ) )
				return 1;

			ChangeSign();
		}
		else
		{
		Int<value_size> mmax;

			mmax.SetMaxValue();

			if( UInt<value_size>::operator>( mmax ) )
					return 1;
		}

	return 0;
	}


	/*!
		this method converts a string into its value
		it returns carry=1 if the value will be too big or an incorrect base 'b' is given
	*/
	uint FromString(const std::string & s, uint b = 10)
	{
		return FromString( s.c_str() );
	}


	/*!
		this operator converts a string into its value (with base = 10)
	*/
	Int<value_size> & operator=(const char * s)
	{
		FromString(s);

	return *this;
	}


	/*!
		this operator converts a string into its value (with base = 10)
	*/
	Int<value_size> & operator=(const std::string & s)
	{
		FromString( s.c_str() );

	return *this;
	}




	/*!
	*
	*	methods for comparing
	*
	*	operators == and != will be the same as in the base class (UInt<value_size>)
	*
	*/

	bool operator<(const Int<value_size> & l) const
	{
		sint i=value_size-1;

		sint a1 = sint(UInt<value_size>::table[i]);
		sint a2 = sint(l.table[i]);

		if( a1 != a2 )
			return a1 < a2;


//		 comparison as int
//		if( int(UInt<value_size>::table[i]) != int(l.table[i]) )
//			return int(UInt<value_size>::table[i]) < int(l.table[i]);

		for(--i ; i>=0 ; --i)
		{
			if( UInt<value_size>::table[i] != l.table[i] )
				// comparison as unsigned int
				return UInt<value_size>::table[i] < l.table[i];
		}

	// they're equal
	return false;
	}


	bool operator>(const Int<value_size> & l) const
	{
		sint i=value_size-1;
		

		sint a1 = sint(UInt<value_size>::table[i]);
		sint a2 = sint(l.table[i]);

		if( a1 != a2 )
			return a1 > a2;

		// comparison as int
//		if( int(UInt<value_size>::table[i]) != int(l.table[i]) )
//			return int(UInt<value_size>::table[i]) > int(l.table[i]);

		for(--i ; i>=0 ; --i)
		{
			if( UInt<value_size>::table[i] != l.table[i] )
				// comparison as unsigned int
				return UInt<value_size>::table[i] > l.table[i];
		}

	// they're equal
	return false;
	}


	bool operator<=(const Int<value_size> & l) const
	{
		sint i=value_size-1;
		

		sint a1 = sint(UInt<value_size>::table[i]);
		sint a2 = sint(l.table[i]);

		if( a1 != a2 )
			return a1 < a2;

		// comparison as int
//		if( int(UInt<value_size>::table[i]) != int(l.table[i]) )
//			return int(UInt<value_size>::table[i]) < int(l.table[i]);

		for(--i ; i>=0 ; --i)
		{
			if( UInt<value_size>::table[i] != l.table[i] )
				// comparison as unsigned int
				return UInt<value_size>::table[i] < l.table[i];
		}

	// they're equal
	return true;
	}


	bool operator>=(const Int<value_size> & l) const
	{
		sint i=value_size-1;
		

		sint a1 = sint(UInt<value_size>::table[i]);
		sint a2 = sint(l.table[i]);

		if( a1 != a2 )
			return a1 > a2;

		// comparison as int
//		if( int(UInt<value_size>::table[i]) != int(l.table[i]) )
//			return int(UInt<value_size>::table[i]) > int(l.table[i]);

		for(--i ; i>=0 ; --i)
		{
			if( UInt<value_size>::table[i] != l.table[i] )
				// comparison as unsigned int
				return UInt<value_size>::table[i] > l.table[i];
		}

	// they're equal
	return true;
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
	Int<value_size> operator-() const
	{
	Int<value_size> temp(*this);

		temp.ChangeSign();
		
	return temp;
	}


	Int<value_size> operator-(const Int<value_size> & p2) const
	{
	Int<value_size> temp(*this);

		temp.Sub(p2);

	return temp;
	}


	Int<value_size> & operator-=(const Int<value_size> & p2)
	{
		Sub(p2);

	return *this;
	}


	Int<value_size> operator+(const Int<value_size> & p2) const
	{
	Int<value_size> temp(*this);

		temp.Add(p2);

	return temp;
	}


	Int<value_size> & operator+=(const Int<value_size> & p2)
	{
		Add(p2);

	return *this;
	}


	Int<value_size> operator*(const Int<value_size> & p2) const
	{
	Int<value_size> temp(*this);

		temp.Mul(p2);

	return temp;
	}


	Int<value_size> & operator*=(const Int<value_size> & p2)
	{
		Mul(p2);

	return *this;
	}


	Int<value_size> operator/(const Int<value_size> & p2) const
	{
	Int<value_size> temp(*this);

		temp.Div(p2);

	return temp;
	}


	Int<value_size> & operator/=(const Int<value_size> & p2)
	{
		Div(p2);

	return *this;
	}


	Int<value_size> operator%(const Int<value_size> & p2) const
	{
	Int<value_size> temp(*this);
	Int<value_size> remainder = temp.Div( p2 );

	return remainder;
	}


	Int<value_size> & operator%=(const Int<value_size> & p2)
	{
	Int<value_size> temp(*this);
	Int<value_size> remainder = temp.Div( p2 );

		operator=(remainder);

	return *this;
	}


	/*!
		Prefix operator e.g ++variable
	*/
	UInt<value_size> & operator++()
	{
		AddOne();

	return *this;
	}

	/*!
		Postfix operator e.g variable++
	*/
	UInt<value_size> operator++(int)
	{
	UInt<value_size> temp( *this );

		AddOne();

	return temp;
	}


	UInt<value_size> & operator--()
	{
		AddOne();

	return *this;
	}


	UInt<value_size> operator--(int)
	{
	UInt<value_size> temp( *this );

		SubOne();

	return temp;
	}



	/*!
	*
	*	input/output operators for standard streams
	*
	*/

	friend std::ostream & operator<<(std::ostream & s, const Int<value_size> & l)
	{
	std::string ss;

		l.ToString(ss);
		s << ss;

	return s;
	}



	friend std::istream & operator>>(std::istream & s, Int<value_size> & l)
	{
	std::string ss;
	
	// char for operator>>
	unsigned char z;
	
		// operator>> omits white characters if they're set for ommiting
		s >> z;

		if( z=='-' || z=='+' )
		{
			ss += z;
			s >> z; // we're reading a next character (white characters can be ommited)
		}

		// we're reading only digits (base=10)
		while( s.good() && UInt<value_size>::CharToDigit(z, 10)>=0 )
		{
			ss += z;
			z = s.get();
		}

		// we're leaving the last readed character
		// (it's not belonging to the value)
		s.unget();

		l.FromString(ss);

	return s;
	}

};

} // namespace


#endif
