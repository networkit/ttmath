#include <ttmath/ttmath.h>
#include <iostream>

int main(int argc, char ** argv)
{
	typedef ttmath::Big<TTMATH_BITS(TTMATH_TEST_BIG_EXPONENT), TTMATH_BITS(TTMATH_TEST_BIG_MANTISSA)> MyBig;
	ttmath::Parser<MyBig> parser;
	std::string all_input;

	for(int i=1 ; i<argc ; ++i)
	{
		if( i > 1 )
			all_input += ' ';
			
		all_input += argv[i];
	}

	std::cout << all_input << " = ";
	ttmath::ErrorCode err = parser.Parse(all_input);

	if( err == ttmath::err_ok )
	{
		for(size_t i=0 ; i < parser.stack.size() ; ++i)
		{
			if( i > 0 )
				std::cout << " ; ";
			
			std::cout << parser.stack[i].value;
		}
		
		std::cout << std::endl;
	}
	else
	{
		std::cout << "error: " << static_cast<int>(err) << std::endl;
	}
	
	return 0;
}
