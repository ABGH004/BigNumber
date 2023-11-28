#include<iostream>
#include "bigNumber.hpp"

int main()
{
	// constructors test
	bigNumber bN1("8129");
	
	bigNumber bN2;
	
	uint8_t* array{new uint8_t[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}};
	bigNumber bN3(array, 10);
	
	bigNumber bN4;
	
	bigNumber bN5(-8229);

	// output stream test
	std::cout << "bN1: " << bN1 << "    bN2: " << bN2 << "    bN3: " << bN3 << "    bN4: " << bN4 << "    bN5: " << bN5 << std::endl;
	
	// inc/dec test
	bN2 = bN1++;
	bN4 = ++bN3;
	std::cout << "bN2 = bN1++ bN2: " << bN2 << "    bN1: " << bN1 << "    bN4 = ++bN3 bN4: " << bN4 << "    bN3: " << bN3 << std::endl;
	bN2 = bN1--;
	bN4 = --bN3;
	std::cout << "bN2 = bN1-- bN2: " << bN2 << "    bN1: " << bN1 << "    bN4 = --bN3 bN4: " << bN4 << "    bN3: " << bN3 << std::endl;
	
	// input stream test
	std::cout << "bN2: ";
	std::cin >> bN2;
	std::cout << "bN4: ";
	std::cin >> bN4;

	// shift test
	std::cout << "bN2: " << bN2 << std::endl;
    bN2.shiftL();
	std::cout << "bN2(left shifted once): " << bN2 << std::endl;
	bN2.shiftL(5);
	std::cout << "bN2(left shifted five times): " << bN2 << std::endl;
	bN2.shiftR();
	std::cout << "bN2(right shifted once): " << bN2 << std::endl;
	bN2.shiftR(5);
	std::cout << "bN2(right shifted five times): " << bN2 << std::endl;
	 
	// comparison test
	std::cout << "(bN2 > bN4): " << (bN2 > bN4) << std::endl;
	std::cout << "(bN2 < bN4): " << (bN2 < bN4) << std::endl;
	std::cout << "(bN2 == bN4): " << (bN2 == bN4) << std::endl;
	std::cout << "(bN2 != bN4): " << (bN2 != bN4) << std::endl;
	
	// addition/subtraction test
	std::cout << "bN2 + bN4: " << bN2 + bN4 << std::endl;
	std::cout << "bN4 + bN2: " << bN4 + bN2 << std::endl;
	std::cout << "bN2 - bN4: " << bN2 - bN4 << std::endl;
	std::cout << "bN4 - bN2: " << bN4 - bN2 << std::endl;
	
	// multiplication test
	int num;
	std::cout << "one digit integer: ";
	std::cin >> num;
	std::cout << "bN2 * num: " << bN2 * num << std::endl;
	std::cout << "bN2 * bN4: " << bN2 * bN4 << std::endl;
	std::cout << "bN4 * bN2: " << bN4 * bN2 << std::endl;

	// power test
	try
	{
		std::cout << "(bN2^bN4): " << (bN2^bN4) << std::endl;
	}
	catch( char const* errorMessage )
	{
		std::cerr << errorMessage << std::endl;
	}
	
	// factorial test
	try
	{
		std::cout << "bN2 factorial: " << bN2.factorial() << std::endl;
	}

	catch( char const* errorMessage )
	{
		std::cerr << errorMessage << std::endl;
	}
	
	return 0;
}
