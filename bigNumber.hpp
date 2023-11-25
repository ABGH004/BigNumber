#ifndef BIGNUMBER_HPP
#define BIGNUMBER_HPP
#include <string>
#include <iostream>
#include <stdint.h>

class bigNumber
{
	public:
		
		//default constructor
		bigNumber();
		
		// constructors
		bigNumber( uint8_t*, int len );
		bigNumber( std::string );
		bigNumber( int );
		
		// copy constructor
		bigNumber( const bigNumber& );
	
		//destructor
		~bigNumber();

		// assignment
		bigNumber& operator =( const bigNumber& );
	
		// check whether its zero
		friend bool isNull(const bigNumber&);
		
		//shift
		bigNumber shiftL();
		bigNumber shiftL( int );
		bigNumber shiftR();
		bigNumber shiftR( int );

		// I/O stream
		friend std::ostream& operator <<( std::ostream&, const bigNumber& );
		friend std::istream& operator >>( std::istream&, bigNumber& );
		
		// adding post and pre increment/decrement
		bigNumber& operator ++();
		bigNumber operator ++( int );
		bigNumber& operator --();
		bigNumber operator --( int );
		
		// comparison
		friend bool operator > (const bigNumber&, const bigNumber&);
		friend bool operator < (const bigNumber&, const bigNumber&);
		friend bool operator == (const bigNumber&, const bigNumber&);
		friend bool operator != (const bigNumber&, const bigNumber&);

		// basic arithmatic
		friend bigNumber operator +( const bigNumber&, const bigNumber& );
		friend bigNumber operator -( const bigNumber&, const bigNumber& );
		friend bigNumber operator *( const bigNumber&, const bigNumber& );
		friend bigNumber operator *( const bigNumber&, int );
		friend bigNumber operator /( const bigNumber&, const bigNumber& );
		friend bigNumber operator ^( const bigNumber&, const bigNumber& );
		
		// bitwise shift
		//bigNumber operator <<( int );
		//bigNumber operator >>( int );
		
		// factorial
		bigNumber factorial();
	
	private:
		
		// number of occupied elements of array
		int numOfDigits;
		
		// array of big number's digits
		uint8_t* digits;
		
		// check whether its negative or positive
		bool isNegative;

		// delete all left zeroes
		void deleteLeftZero()
		{
			uint8_t* tempArr;
			int i;
			for(i = 0; i < numOfDigits; ++i)
				if(digits[i] != 0)
					break;
			numOfDigits-= i;
			tempArr = new uint8_t[numOfDigits];
			for(int j = 1; j <= numOfDigits; ++j)
				tempArr[numOfDigits - j] = digits[numOfDigits + i - j];
			delete [] digits;
			digits = new uint8_t[numOfDigits];
			for(int j = 0; j < numOfDigits; ++j)
				digits[j] = tempArr[j];
			delete [] tempArr;
		}

};
#endif
