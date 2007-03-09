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



#ifndef headerfilettmathobject
#define headerfilettmathobject

#include "ttmathtypes.h"

#include <string>
#include <map>
#include <algorithm>


namespace ttmath
{


class Objects
{
public:

	struct ObjectValue
	{
		std::string value;
		int param;

		ObjectValue() {}
		ObjectValue(const std::string & v, int p) : value(v), param(p) {}
	};

	typedef std::map<std::string, ObjectValue> Table;
	typedef	Table::const_iterator CIterator;

	ErrorCode Add(const std::string & name, const std::string & value, int param = 0)
	{
		if( !CorrectCharacters(name) )
			return err_incorrect_name;

		if( AreBigLetters(name) )
		{
			std::string name_copy(name);
			ToSmallLetters(name_copy);

			return AddAfterChecking(name_copy, value, param);
		}
		else
			return AddAfterChecking(name, value, param);
	}


	bool Empty() const
	{
		return table.empty();
	}

	void Clear()
	{
		return table.clear();
	}

	CIterator Begin() const
	{
		return table.begin();
	}

	CIterator End() const
	{
		return table.end();
	}

	ErrorCode Edit(const std::string & name, const std::string & value, int param = 0)
	{
		Table::iterator i = table.find(name);

		if( i == table.end() )
			// we don't have this variable in our table
			return err_unknown_object;
	
		i->second.value = value;
		i->second.param = param;

	return err_ok;
	}


	ErrorCode Delete(const std::string & name)
	{
		Table::iterator i = table.find(name);

		if( i == table.end() )
			// we don't have this variable in our table
			return err_unknown_object;

		table.erase( i );

	return err_ok;
	}


	ErrorCode GetValue(const std::string & name, const char * * value) const
	{
		Table::const_iterator i = table.find(name);

		if( i == table.end() )
		{
			// we don't have this variable in our table
			*value = 0;
			return err_unknown_object;
		}

		*value = i->second.value.c_str();

	return err_ok;
	}

	ErrorCode GetValueParam(const std::string & name, const char * * value, int * param) const
	{
		Table::const_iterator i = table.find(name);

		if( i == table.end() )
		{
			// we don't have this variable in our table
			*value = 0;
			return err_unknown_object;
		}

		*value = i->second.value.c_str();
		*param = i->second.param;

	return err_ok;
	}

	Table * GetTable()
	{
		return &table;
	}


private:

	Table table;


	bool CorrectCharacter(int c, bool digit)
	{
		if( (c>='a' && c<='z') || (c>='A' && c<='Z') )
			return true;

		if( digit && (c>='0' && c<='9') )
			return true;

	return false;
	}


	bool CorrectCharacters(const std::string & name)
	{
		if( name.empty() )
			return false;

		if( !CorrectCharacter(name[0], false) )
			return false;

		std::string::const_iterator i=name.begin();

		for(++i ; i!=name.end() ; ++i)
			if( !CorrectCharacter(*i, true) )
				return false;
		
	return true;
	}
	

	static int SmallLetter(int c)
	{
		if( c>='A' && c<='Z' )
			return c-'A'+'a';

	return c;
	}


	static bool AreBigLetters(const std::string & name)
	{
		std::string::const_iterator i;

		for(i=name.begin() ; i!=name.end() ; ++i)
			if( *i>='A' && *i<='Z' )
				return true;

	return false;
	}


	void ToSmallLetters(std::string & name)
	{
		std::string::iterator i;

		for(i=name.begin() ; i!=name.end() ; ++i)
			*i = SmallLetter(*i);
	}


	ErrorCode AddAfterChecking(const std::string & name, const std::string & value, int param)
	{
		Table::iterator i = table.find(name);

		if( i != table.end() )
			// we have this object in our table
			return err_object_exists;

		table.insert( std::make_pair(name, ObjectValue(value, param)) );

	return err_ok;
	}

};

} // namespace

#endif
