#include "bigNumber.hpp"
#include <cstring>
#include <vector>
// default constructor
bigNumber::bigNumber()
{
	numOfDigits = 1;
	isNegative = 0;
	digits = new uint8_t[1];
	digits[0] = 0;
}

// constructors
bigNumber::bigNumber( uint8_t* array, int len )
{
	if( array[0] == '-' )
	{
		isNegative = 1;
		numOfDigits = len - 1;
		digits = new uint8_t[numOfDigits];
		
		for(size_t i = 0; i < numOfDigits; ++i)
			digits[i] = array[i+1] - '0';
	}

	else
	{
		isNegative = 0;
		numOfDigits = len;
		digits = new uint8_t[numOfDigits];

		for(size_t i = 0; i < numOfDigits; ++i)
			digits[i] = array[i] - '0';
	}
}

bigNumber::bigNumber( std::string num )
{
	if ( num[0] == '-' )
	{	
		numOfDigits = num.size() - 1;
		digits = new uint8_t[numOfDigits];
		isNegative = 1;

		for(size_t i = 0; i < numOfDigits; ++i)
			digits[i] = (num[i + 1]-'0');
	
	}

	else
	{
		numOfDigits = num.size();
		digits = new uint8_t[numOfDigits];
		isNegative = 0;
		
		for(size_t i = 0; i < numOfDigits; ++i)
			digits[i] = (num[i]-'0');
	}
}

bigNumber::bigNumber( int num )
{
	if( num < 0 )
	{
		isNegative = 1;
		numOfDigits = std::to_string(num).length() - 1;
	}

	else
	{
		isNegative = 0;
		numOfDigits = std::to_string(num).length();
	}

	digits = new uint8_t[numOfDigits];
	num = abs(num);
	
	for(int i = numOfDigits - 1; i >= 0; --i)
	{
		digits[i] = num%10;
		num /= 10;
	}

}

// copy constructor
bigNumber::bigNumber( const bigNumber& bN )
{
	numOfDigits = bN.numOfDigits;
	isNegative = bN.isNegative;
	digits = new uint8_t[numOfDigits];

	for(size_t i = 0; i < numOfDigits; ++i)
		digits[i] = bN.digits[i];
}

// destructor
bigNumber::~bigNumber()
{
	delete [] digits;
}

// assignment
bigNumber& bigNumber::operator =( const bigNumber& bN )
{
	// self-assignment
	if (this == &bN)
		return *this;

	if (numOfDigits > 0)
		delete [] digits;
	
	numOfDigits = bN.numOfDigits;
	isNegative = bN.isNegative;
	digits = new uint8_t[numOfDigits];
	
	for(size_t i = 0; i < numOfDigits; ++i)
		digits[i] = bN.digits[i];
	
	return *this;
}

//check whether its zero
bool isNull(const bigNumber& bN)
{
	for(size_t i = 0; i < bN.numOfDigits; ++i)
		if(bN.digits[i] != 0)
			return false;
	return true;
}


//shift
bigNumber bigNumber::shiftL()
{
	return shiftL(1);
}

bigNumber bigNumber::shiftL( int n )
{
	if(n == 0)
		return *this;
	bigNumber temp = *this;
	numOfDigits += n;
	delete []digits;
	digits = new uint8_t[numOfDigits];
	memset(digits, 0, numOfDigits);
	
	for(int i = 0; i < temp.numOfDigits; ++i)
		digits[i] = temp.digits[i];
	
	return *this;
	
}

bigNumber bigNumber::shiftR()
{
	return shiftR(1);
}

bigNumber bigNumber::shiftR( int n )
{
	if(n == 0)
		return *this;
	bigNumber temp = *this;
	numOfDigits -= n;
	delete []digits;
	digits = new uint8_t[numOfDigits];

	for(int i = numOfDigits-1; i >= 0; --i)
		digits[i] = temp.digits[i];
	
	return *this;
}

// I/O stream
std::ostream& operator <<( std::ostream& output, const bigNumber& bN )
{
	if( isNull(bN) )
	{
		output << '0';
		return output;
	}
	
	if( bN.isNegative ) 
		output << '-';
	
	for(size_t i = 0; i < bN.numOfDigits; ++i)
		output << (int)bN.digits[i];
	
	return output;
}

std::istream& operator >>( std::istream& input, bigNumber& bN )
{	
	std::string num;
	input >> num;
	bN = bigNumber(num);
	return input;
}

// post and pre increment/decrement
bigNumber& bigNumber::operator ++()
{
	*this = (*this) + 1;
	return *this;
	
}

bigNumber bigNumber::operator ++( int dummy )
{
	bigNumber temp = *this;
	*this = (*this) + 1;
	return temp;
}

bigNumber& bigNumber::operator --()
{
	*this = (*this) - 1;
	return *this;
}

bigNumber bigNumber::operator --( int dummy )
{
	bigNumber temp = *this;
	*this = (*this) - 1;
	return temp;
}

// comparison
bool operator > ( const bigNumber& bN1, const bigNumber& bN2 )
{
	if( bN1.isNegative && !bN2.isNegative )
		return false;
	
	else if ( !bN1.isNegative && bN2.isNegative )
		return true;
	
	else if ( bN1.isNegative && bN2.isNegative )
	{
		bigNumber temp1 = bN1;
		bigNumber temp2 = bN2;
		temp1.isNegative = 0;
		temp2.isNegative = 0;
		return temp1 < temp2;
	}
	
	if( bN1.numOfDigits > bN2.numOfDigits )
		return true;
	
	else if( bN1.numOfDigits < bN2.numOfDigits )
		return false;
	
	else
	{
		for(size_t i = 0; i < bN1.numOfDigits; ++i)
		{
			if( bN1.digits[i] > bN2.digits[i] )
				return true;
			
			if( bN1.digits[i] < bN2.digits[i] )
				return false;
		}
		// completely identical
		return false;
	}
}

bool operator < ( const bigNumber& bN1, const bigNumber& bN2 )
{
	if( bN1.isNegative && !bN2.isNegative )
		return true;
	
	else if ( !bN1.isNegative && bN2.isNegative )
		return false;
	
	else if ( bN1.isNegative && bN2.isNegative )
	{
		bigNumber temp1 = bN1;
		bigNumber temp2 = bN2;
		temp1.isNegative = 0;
		temp2.isNegative = 0;
		return temp1 > temp2;
	}
	
	if( bN1.numOfDigits > bN2.numOfDigits )
		return false;
	
	if( bN1.numOfDigits < bN2.numOfDigits )
		return true;
	
	else
	{
		for(size_t i = 0; i < bN1.numOfDigits; ++i)
		{
		
			if( bN1.digits[i] > bN2.digits[i] )
				return false;
			
			if( bN1.digits[i] < bN2.digits[i] )
				return true;
		}
		// completely identical
		return false;
	}
}
bool operator == ( const bigNumber& bN1, const bigNumber& bN2 )
{
	if( ( !bN1.isNegative && bN2.isNegative ) || ( bN1.isNegative && !bN2.isNegative ) )
		return false;
	
	if( bN1.numOfDigits > bN2.numOfDigits )
		return false;

	if( bN1.numOfDigits < bN2.numOfDigits )
		return false;
	
	else
	{	
		for(size_t i = 0; i < bN1.numOfDigits; ++i)
			if( bN1.digits[i] != bN2.digits[i] )
				return false;

		// completely identical
		return true;
	}
}

bool operator != ( const bigNumber& bN1, const bigNumber& bN2 )
{
	return !(bN1 == bN2);
}


// basic arithmatic
//addition
bigNumber operator +( const bigNumber& bN1, const bigNumber& bN2 )
{
	bigNumber temp;
	bigNumber tempBN;
	int i = 1;
	int carry = 0;
	
	int max = std::max(bN1.numOfDigits, bN2.numOfDigits);
	int min = std::min(bN1.numOfDigits, bN2.numOfDigits);
	
	if( !bN1.isNegative && bN2.isNegative )
	{
		bigNumber temp = bN2;
		temp.isNegative = 0;
		temp = bN1 - temp;
		return temp;
	}

	else if( bN1.isNegative && !bN2.isNegative )
	{
		bigNumber temp = bN1;
		temp.isNegative = 0;
		temp = bN2 - temp;
		return temp;
	}

	if( bN1.isNegative && bN2.isNegative )
		temp.isNegative = 1;
	
	else if( !bN1.isNegative && !bN2.isNegative )
		temp.isNegative = 0;
	
	if( bN1.numOfDigits >= bN2.numOfDigits )
	{
		if( bN1.isNegative && !bN2.isNegative )
			return bN2 - bN1;
	
		tempBN.numOfDigits = max;
		tempBN.digits = new uint8_t[tempBN.numOfDigits];
		memset(tempBN.digits, 0, tempBN.numOfDigits);
		
		for(size_t k = 1; k <= min; ++k)
			tempBN.digits[max - k] = bN2.digits[min - k];
		
		for(size_t k = min + 1; k < max; ++k)
			tempBN.digits[max - k] = 0;

	}
	else if ( bN2.numOfDigits > bN1.numOfDigits )
	{
		if( bN2.isNegative && !bN1.isNegative )
			return bN1 - bN2;
		
		tempBN.numOfDigits = max;
		tempBN.digits = new uint8_t[tempBN.numOfDigits];
		memset(tempBN.digits, 0, tempBN.numOfDigits);
		
		for(size_t k = 1; k <= min; ++k)
			tempBN.digits[max - k] = bN1.digits[min - k];
		
		for(size_t k = min + 1; k < max; ++k)
			tempBN.digits[max - k] = 0;

	
	}

	temp.numOfDigits = max + 1;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	int m;

	while ( max > 0 )
	{
		if( bN1.numOfDigits >= bN2.numOfDigits )
			m = bN1.digits[tempBN.numOfDigits - i] + tempBN.digits[tempBN.numOfDigits - i] + carry;

		if( bN2.numOfDigits > bN1.numOfDigits )
			m = tempBN.digits[tempBN.numOfDigits - i] + bN2.digits[tempBN.numOfDigits - i] + carry;
		
		temp.digits[temp.numOfDigits - i] = m%10;
		carry = m/10;
		++i;
		--max;
	}
	
	if ( carry > 0 )
	{
		temp.digits[temp.numOfDigits - i] += carry;
		++i;
	}
	
	temp.deleteLeftZero();
	return temp;
}

//subtraction
bigNumber operator -( const bigNumber& bN1, const bigNumber& bN2 )
{

	if( !bN1.isNegative && bN2.isNegative )
	{
		bigNumber temp = bN2;
		temp.isNegative = 0;
		temp = bN1 + temp;
		return temp;
	}

	else if( bN1.isNegative && !bN2.isNegative )
	{
		bigNumber temp = bN1;
		temp.isNegative = 0;
		temp = temp + bN2;
		temp.isNegative = 1;
		return temp;
	}
	
	
	int max = std::max(bN1.numOfDigits, bN2.numOfDigits);
	int min = std::min(bN1.numOfDigits, bN2.numOfDigits);

	bigNumber temp;	
	temp.numOfDigits = max;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	
	int t = 0;
	int8_t s;
	
	bigNumber absBN1 = bN1;
	bigNumber absBN2 = bN2;
	absBN1.isNegative = 0;
	absBN2.isNegative = 0;
	
	if( absBN1 > absBN2 && !( bN1.isNegative && bN2.isNegative ) )
	{
		temp.isNegative = 0;
		for(size_t i = 1; i <= max; ++i)
		{
			if ( i <= min )
				s = bN1.digits[max - i] - bN2.digits[min - i] + t;
			else
				s = bN1.digits[max - i] + t;
			if( s < 0 )
			{	
				s += 10;
				t = -1;
			}
			else
				t = 0;
			
			temp.digits[max - i] = s;
			
		}
	}

	if( absBN1 > absBN2 && ( bN1.isNegative && bN2.isNegative ) )
	{
		temp.isNegative = 1;
		for(size_t i = 1; i <= max; ++i)
		{
			if ( i <= min )
				s = bN1.digits[max - i] - bN2.digits[min - i] + t;
			else
				s = bN1.digits[max - i] + t;
			if( s < 0 )
			{	
				s += 10;
				t = -1;
			}
			else
				t = 0;
			
			temp.digits[max - i] = s;
			
		}
	}

	if( absBN1 < absBN2 && !( bN1.isNegative && bN2.isNegative ) )
	{
		temp.isNegative = 1;
		for(size_t i = 1; i <= max; ++i)
		{
			if ( i <= min )
				s = bN2.digits[max - i] - bN1.digits[min - i] + t;
			else
				s = bN2.digits[max - i] + t;
			if( s < 0 )
			{	
				s += 10;
				t = -1;
			}
			else
				t = 0;
			
			temp.digits[max - i] = s;
			
		}
	}

	if( absBN1 < absBN2 && ( bN1.isNegative && bN2.isNegative ) )
	{ 
		temp.isNegative = 0;
		for(size_t i = 1; i <= max; ++i)
		{
			if ( i <= min )
				s = bN2.digits[max - i] - bN1.digits[min - i] + t;
			else
				s = bN2.digits[max - i] + t;
			if( s < 0 )
			{	
				s += 10;
				t = -1;
			}
			else
				t = 0;
			temp.digits[max - i] = s;
			
		}
	}

	if( bN1 == bN2 ){
		delete []temp.digits;
		temp.numOfDigits = 1;
		temp.digits = new uint8_t[temp.numOfDigits];
		temp.digits[0] = 0;
	}
		
	temp.deleteLeftZero();
	return temp;
}

//multiplication
bigNumber operator *( const bigNumber& bN1, const bigNumber& bN2 )
{
	
	bigNumber temp1;
	temp1.numOfDigits = bN1.numOfDigits + bN2.numOfDigits;
	temp1.digits = new uint8_t[temp1.numOfDigits];
	memset(temp1.digits, 0, temp1.numOfDigits);
	
	bigNumber tempBN = bN1;
	tempBN.isNegative = 0;
	
	bigNumber temp2 = temp1;
	
	if( isNull(bN1) || isNull(bN2) )
		return 0;
	
	if( ( bN1.isNegative && !bN2.isNegative ) || ( !bN1.isNegative && bN2.isNegative ) )
		temp2.isNegative = 1;
	else
		temp2.isNegative = 0;

	for(size_t j = 0; j < bN2.numOfDigits; ++j)
		temp1 = temp1 + (tempBN * (int)bN2.digits[bN2.numOfDigits - j - 1]).shiftL(j);
	
	for(size_t i = 1; i <= temp2.numOfDigits; ++i)
		temp2.digits[temp2.numOfDigits - i] = temp1.digits[temp1.numOfDigits - i];
		
	temp2.deleteLeftZero();
	return temp2;

}

bigNumber operator *( const bigNumber& bN, int num)
{
	if( isNull(bN) || num == 0 )
		return 0;
	
	bigNumber temp;
	temp.numOfDigits = bN.numOfDigits + 1;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	
	if( ( num < 0 && !bN.isNegative ) || ( num > 0 && bN.isNegative ) )
		temp.isNegative = 1;
	else
		temp.isNegative = 0;

	int s;
	int t = 0;
	int i;

	for(i = 1; i <= bN.numOfDigits; ++i)
	{
		s = bN.digits[bN.numOfDigits - i] * abs(num) + t;
		temp.digits[temp.numOfDigits - i] = s%10;
		t = s / 10;
	}

	if ( t > 0 )
		temp.digits[temp.numOfDigits - i] = t;
	
	temp.deleteLeftZero();
	return temp;
}

//division
bigNumber operator /( const bigNumber& bN1, const bigNumber& bN2 )
{
	if( isNull(bN2) )
		throw("Zero division is undefined!");
	
	bigNumber absBN1 = bN1;
	absBN1.isNegative = 0;
	bigNumber absBN2 = bN2;
	absBN2.isNegative = 0;
	
	if( absBN2 > absBN1 )
		return 0;
	if( bN2 == bN1 )
		return 1;
	// when XOR of both numbers' isNegative is T
	if( absBN1 == absBN2 )
		return bigNumber(-1);
	
	
	bigNumber quotient;
	
	if( ( !bN1.isNegative && bN2.isNegative ) || ( bN1.isNegative && !bN2.isNegative ) )
		quotient.isNegative = 1;
	else
		quotient.isNegative = 0;
  	
	int index;
	quotient.numOfDigits = 0;
	int quotientDigit;
    uint8_t* result = new uint8_t[bN1.numOfDigits];
	memset(result, 0, bN1.numOfDigits);
    bigNumber t;
    
	for(index = 0; t * 10 + absBN1.digits[index] < absBN2;index++)
	{
        t = t * 10;
        t = t + absBN1.digits[index];
    }
    
	for(; index < absBN1.numOfDigits; index++)
	{
        t = t * 10 + absBN1.digits[index];
		for(quotientDigit = 9; quotientDigit * absBN2 > t;quotientDigit--);
        t = t - (quotientDigit * absBN2);
        result[quotient.numOfDigits++] = quotientDigit;
    }
	
	quotient.digits = new uint8_t[quotient.numOfDigits];
	
	for(index = 0; index < quotient.numOfDigits;index++)
        quotient.digits[index] = result[index];
	
	delete [] result;

	return quotient;
}

//power
bigNumber operator ^( const bigNumber& bN1, const bigNumber& bN2 )
{
	
	if( bN2.isNegative )
		throw("Negative power not allowed!");
	if( isNull(bN1) && isNull(bN2) )
	{
		throw("Zero powered to zero is undefined!");
	}
	
	if( isNull(bN1) )
		return 0;
	
	if( isNull(bN2) )
		return 1;

	bigNumber temp1(1);
	
	bigNumber Exponent, Base;
	Base = bN1;
    Exponent = bN2;
    while(!isNull(Exponent)){
    	if(Exponent.digits[Exponent.numOfDigits - 1] & 1)
        	temp1 = temp1 * Base;
        Base = Base * Base;
		Exponent = Exponent / 2;
	}
	
	return temp1;
}

// factorial
bigNumber bigNumber::factorial()
{
	if( isNegative )
		throw("Negative operand not allowed!");
	if( *this == 0 )
		return 1;
	
	bigNumber fact(1);
	
	for(bigNumber i(2); i < *this || i == *this; ++i)
		fact = fact * i;

	return fact;
}
