#include<iostream>
#include "bigNumber.hpp"

int main()
{
	bigNumber bN1("8129");
	bigNumber bN2;
	uint8_t* array{new uint8_t[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}};
	bigNumber bN3(array, 10);
	bigNumber bN4;
	bigNumber bN5(-8229);
	std::cout << bN1 << "    " << bN2 << "    " << bN3 << "    " << bN4 << "    " << bN5 << std::endl;
	std::cin >> bN2;
	//int num;
	//std::cin >> num;
	std::cin >> bN4;
	//bN4 = ++bN2;
	std::cout << (bN2*bN4) << std::endl;
	std::cout << (bN2^bN4) << std::endl;
	/* passed shift test
	 *std::cout << bN2 << std::endl;
	 *bN2.shiftL();
	 *std::cout << bN2 << std::endl;
	 *bN2.shiftL(5);
	 *std::cout << bN2 << std::endl;
	 *bN2.shiftR();
	 *std::cout << bN2 << std::endl;
	 *bN2.shiftR(5);
	 *std::cout << bN2 << std::endl;
	 */
	//std::cout << bN1 << "    " << bN2 << "    " << bN3 << "    " << bN4 << "    " << bN5 << std::endl;
	/* passed comparison test
	 *std::cout << (bN2 > bN4) << std::endl;
	 *std::cout << (bN2 < bN4) << std::endl;
	 *std::cout << (bN2 == bN4) << std::endl;
	 *std::cout << (bN2 != bN4) << std::endl;
	 */
	/* passed addition/subtraction test
	 *std::cout << bN2 + bN4 << std::endl;
	 *std::cout << bN4 + bN2 << std::endl;
	 *std::cout << bN2 - bN4 << std::endl;
	 *std::cout << bN4 - bN2 << std::endl;
	 */
	//std::cout << bN2 * bN4 << std::endl;
	//std::cout << bN4 * bN2 << std::endl;
	//std::cout << bN3 + bN1 << std::endl;
	//bigNumber bN4 = bN3 + bN2;
	//std::cout << bN4 << std::endl;
	//bigNumber bN5 = bN3 - bN2;
	//std::cout << bN5 << std::endl;
	return 0;
}
