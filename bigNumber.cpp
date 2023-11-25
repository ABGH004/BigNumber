#include "bigNumber.hpp"
#include <cstring>

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
	numOfDigits = len;
	digits = new uint8_t[numOfDigits];
	isNegative = 0;
	for(size_t i = 0; i < numOfDigits; ++i)
	{
		digits[i] = (array[i]);
		
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
		{
			digits[i] = (num[i + 1]-'0');
		
		}
	}
	else{
		numOfDigits = num.size();
		digits = new uint8_t[numOfDigits];
		isNegative = 0;
		for(size_t i = 0; i < numOfDigits; ++i)
		{
			digits[i] = (num[i]-'0');
		
		}
	}
}

bigNumber::bigNumber( int num )
{
	if(num < 0){
		isNegative = 1;
		numOfDigits = std::to_string(num).length() - 1;
	}
	else{
		isNegative = 0;
		numOfDigits = std::to_string(num).length();
	}
	digits = new uint8_t[numOfDigits];
	num = abs(num);
	for(int i = numOfDigits - 1; i >= 0; --i){
	
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
	for(int i = 0; i < numOfDigits; ++i)
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
	{
		digits[i] = bN.digits[i];
	}
	
	return *this;
}

//check whether its zero
bool isNull(const bigNumber& bN)
{
	for(int i = 0; i < bN.numOfDigits; ++i)
	{
		if(bN.digits[i] != 0)
			return false;
	}
	return true;
}


//shift
bigNumber bigNumber::shiftL()
{
	return shiftL(1);
}
bigNumber bigNumber::shiftL( int n )
{
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
	//if(n >= numOfDigits)
	//	return bigNumber();
	bigNumber temp = *this;
	numOfDigits -= n;
	delete []digits;
	digits = new uint8_t[numOfDigits];
	for(int i = numOfDigits-1; i >= 0; --i){
		digits[i] = temp.digits[i];
	}
	return *this;
}

// I/O stream
std::ostream& operator <<( std::ostream& output, const bigNumber& bN )
{
	if(isNull(bN)){
		output << '0';
		return output;
	}
	bool start = 0;
	if( bN.isNegative ) 
		output << '-';
	for(size_t i = 0; i < bN.numOfDigits; ++i)
	{
		if(bN.digits[i] == 0 && !start){
			continue;
		}
		else
			start = 1;
		output << (int)bN.digits[i];
	}
	return output;
}

std::istream& operator >>( std::istream& input, bigNumber& bN )
{	
	std::string num;
	input >> num;
	if ( num[0] == '-' )
	{	
		bN.numOfDigits = num.size() - 1;
		bN.digits = new uint8_t[bN.numOfDigits];
		bN.isNegative = 1;
		for(size_t i = 0; i < bN.numOfDigits; ++i)
		{
			bN.digits[i] = (num[i + 1]-'0');
		
		}
	}
	else{
		bN.numOfDigits = num.size();
		bN.digits = new uint8_t[bN.numOfDigits];
		bN.isNegative = 0;
		for(size_t i = 0; i < bN.numOfDigits; ++i)
		{
			bN.digits[i] = (num[i]-'0');
		}
	}
	return input;
}

// adding post and pre increment/decrement
bigNumber& bigNumber::operator ++()
{
	*this = (*this) + 1;
	deleteLeftZero();
	return *this;
	
}

bigNumber bigNumber::operator ++(int dummy){;}

bigNumber& bigNumber::operator --()
{
	*this = (*this) - 1;
	deleteLeftZero();
	return *this;
}

bigNumber bigNumber::operator --(int dummy){;}

// comparison
bool operator > (const bigNumber& bN1, const bigNumber& bN2)
{
	if(bN1.isNegative && !bN2.isNegative)
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
	if(bN1.numOfDigits > bN2.numOfDigits)
		return true;
	else if(bN1.numOfDigits < bN2.numOfDigits)
		return false;
	else{
		for(int i = 0; i < bN1.numOfDigits; ++i)
		{
			if(bN1.digits[i] > bN2.digits[i])
				return true;
			if(bN1.digits[i] < bN2.digits[i])
				return false;
		}
		// completely identical
		return false;
	}
}
bool operator < (const bigNumber& bN1, const bigNumber& bN2)
{
	if(bN1.isNegative && !bN2.isNegative)
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
	if(bN1.numOfDigits > bN2.numOfDigits)
		return false;
	if(bN1.numOfDigits < bN2.numOfDigits)
		return true;
	else{
		for(int i = 0; i < bN1.numOfDigits; ++i)
		{
			if(bN1.digits[i] > bN2.digits[i])
				return false;
			if(bN1.digits[i] < bN2.digits[i])
				return true;
		}
		// completely identical
		return false;
	}
}
bool operator == (const bigNumber& bN1, const bigNumber& bN2)
{
	if((!bN1.isNegative && bN2.isNegative) || (bN1.isNegative && !bN2.isNegative))
		return false;
	if(bN1.numOfDigits > bN2.numOfDigits)
		return false;
	if(bN1.numOfDigits < bN2.numOfDigits)
		return false;
	else{
		for(int i = 0; i < bN1.numOfDigits; ++i)
		{
			if(bN1.digits[i] != bN2.digits[i])
				return false;
		}
		// completely identical
		return true;
	}
}
bool operator != (const bigNumber& bN1, const bigNumber& bN2)
{
	return !(bN1 == bN2);
}


// basic arithmatic
bigNumber operator +( const bigNumber& bN1, const bigNumber& bN2 )
{
	bigNumber temp;
	bigNumber tempBN;
	int i = 1;
	int carry = 0;
	int max = std::max(bN1.numOfDigits, bN2.numOfDigits);
	int min = std::min(bN1.numOfDigits, bN2.numOfDigits);
	if(!bN1.isNegative && bN2.isNegative){
		bigNumber temp = bN2;
		temp.isNegative = 0;
		temp = bN1 - temp;
		return temp;
	}
	else if(bN1.isNegative && !bN2.isNegative){
		bigNumber temp = bN1;
		temp.isNegative = 0;
		temp = bN2 - temp;
		return temp;
	}
	if(bN1.isNegative && bN2.isNegative)
		temp.isNegative = 1;
	else if(!bN1.isNegative && !bN2.isNegative)
		temp.isNegative = 0;
	if(bN1.numOfDigits >= bN2.numOfDigits)
	{
		// max 10  min 6
		if(bN1.isNegative && !bN2.isNegative)
			return bN2 - bN1;
		// 1234567890 + 99999 = 1234667889
		// 99999 + 1234 = 101233
		tempBN.numOfDigits = max;
		tempBN.digits = new uint8_t[tempBN.numOfDigits];
		for(int k = 1; k <= min; ++k)
			tempBN.digits[max - k] = (int)(bN2.digits[min - k]);
		for(int k = min + 1; k < max; ++k)
			tempBN.digits[max - k] = 0;
	}
	else if ( bN2.numOfDigits > bN1.numOfDigits )
	{
		if(bN2.isNegative && !bN1.isNegative)
			return bN1 - bN2;
		// 1234567890 + 9,999,999,999 = 11234567889
		tempBN.numOfDigits = max;
		tempBN.digits = new uint8_t[tempBN.numOfDigits];
		for(int k = 1; k <= min; ++k)
			tempBN.digits[max - k] = (int)(bN1.digits[min - k]);
		for(int k = min + 1; k < max; ++k)
			tempBN.digits[max - k] = 0;

	
	}
	temp.numOfDigits = max + 1;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	int m;
	while (max > 0)
	{
	// 8129 + 1234567890
	// 1234576019
	// 9 + 0 + carry=0
	// m = 9
	// tempDigits[9] = 9
	// tempDigits[8] = 1
	// tempDigtis[7] = 0
	// tempDigits[6] = 6
	// carry = 1
	// tempDigits[5] = 1
	//
	//
	//
	//	if(i > bN1.numOfDigits)
	//	{
	//		for(int j = 0; j <= bN2.numOfDigits - i; ++j){
	//		//std::cout << (int)bN2.digits[j] << "  " << j << std::endl;
	//			temp.digits[j] = bN2.digits[j];
	//		}
	//		break;
	//	}
	//	
	//	if(i > bN2.numOfDigits)
	//	{
	//		for(int j = 0; j <= bN2.numOfDigits - i; ++j)
	//			temp.digits[j] = bN1.digits[j];
	//		break;
	//	}

		if(bN1.numOfDigits >= bN2.numOfDigits)
			m = bN1.digits[tempBN.numOfDigits - i] + tempBN.digits[tempBN.numOfDigits - i] + carry;
		if(bN2.numOfDigits > bN1.numOfDigits)
			m = tempBN.digits[tempBN.numOfDigits - i] + bN2.digits[tempBN.numOfDigits - i] + carry;

		temp.digits[temp.numOfDigits - i] = m%10;
		carry = m/10;
		++i;
		--max;
	};
	if (carry > 0)
	{
		temp.digits[temp.numOfDigits - i] += carry;
		++i;
	}
	//temp.deleteLeftZero();
	return temp;
}

bigNumber operator -( const bigNumber& bN1, const bigNumber& bN2 )
{
	///////////////
	////////
	////
	// TO-DO
	////
	///////
	///////////////

	// 1234567890 - 99999 = 1234467891
	// 
	//

	if(!bN1.isNegative && bN2.isNegative){
		bigNumber temp = bN2;
		temp.isNegative = 0;
		temp = bN1 + temp;
		return temp;
	}
	else if(bN1.isNegative && !bN2.isNegative){
		bigNumber temp = bN1;
		temp.isNegative = 0;
		temp = temp + bN2;
		temp.isNegative = 1;
		return temp;
	}
	//else if(bN1.isNegative && bN2.isNegative){
	//	bigNumber temp = bN1;
	//	bN1 = bN2;
	//	bN2 = temp;
	//}
	bigNumber temp;
	int max = std::max(bN1.numOfDigits, bN2.numOfDigits);
	int min = std::min(bN1.numOfDigits, bN2.numOfDigits);
	temp.numOfDigits = max;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	int t = 0;
	int8_t s;
	bigNumber tempBN1 = bN1;
	bigNumber tempBN2 = bN2;
	tempBN1.isNegative = 0;
	tempBN2.isNegative = 0;
	if(tempBN1 > tempBN2 && !(bN1.isNegative && bN2.isNegative)){
		temp.isNegative = 0;
		for(int i = 1; i <= max; ++i)
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
	if(tempBN1 > tempBN2 && (bN1.isNegative && bN2.isNegative)){
		temp.isNegative = 1;
		for(int i = 1; i <= max; ++i)
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
	if(tempBN1 < tempBN2 && !(bN1.isNegative && bN2.isNegative)){
		temp.isNegative = 1;
		for(int i = 1; i <= max; ++i)
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
	if(tempBN1 < tempBN2 && (bN1.isNegative && bN2.isNegative)){ 
		temp.isNegative = 0;
		for(int i = 1; i <= max; ++i)
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
	if(bN1 == bN2){
		delete []temp.digits;
		temp.numOfDigits = 1;
		temp.digits = new uint8_t[temp.numOfDigits];
		temp.digits[0] = 0;
	}
		
	/*int i = 1;
	int borrow = 0;
	int max = std::max(bN1.numOfDigits, bN2.numOfDigits);
	int min = std::min(bN1.numOfDigits, bN2.numOfDigits);
	if(bN1.numOfDigits == max)
		firstIsBigger = 1;
	while (min > 0)
	{
		if(firstIsBigger)
			if(
			m = bN1.digits[bN1.numOfDigits - i] - bN2.digits[bN2.numOfDigits - i];
		else
			m = bN2.digits[bN2.numOfDigits - i] - bN1.digits[bN1.numOfDigits - i];
		temp.digits[temp.numOfDigits - i] = m%10;
		borrow = m/10;
		++i;
		--min;
	};
	if (borrow > 0)
	{
		temp.digits[temp.numOfDigits - i] += borrow;
		++i;
	}*/
	
	//for(int i = 0; i < temp.numOfDigits; ++i)
	//	std::cout << (int)temp.digits[i] << std::endl;
	//temp.deleteLeftZero();
	return temp;
}

bigNumber operator *( const bigNumber& bN1, const bigNumber& bN2 )
{
	bigNumber temp1;
	temp1.numOfDigits = bN1.numOfDigits + bN2.numOfDigits;
	//int tempArr[temp.numOfDigits] = {0};
	temp1.digits = new uint8_t[temp1.numOfDigits];
	memset(temp1.digits, 0, temp1.numOfDigits);
	bigNumber tempBN = bN1;
	tempBN.isNegative = 0;
	bigNumber temp2 = temp1;
	
	if(isNull(bN1) || isNull(bN2))
		return 0;
	if((bN1.isNegative && !bN2.isNegative) || (!bN1.isNegative && bN2.isNegative))
		temp2.isNegative = 1;
	else
		temp2.isNegative = 0;

//	for(int i = 0; i < bN1.numOfDigits; ++i){
//		tempBN.shiftL(i);
	for(int j = 0; j < bN2.numOfDigits; ++j)
	{
		temp1 = temp1 + (tempBN * (int)bN2.digits[bN2.numOfDigits - j - 1]).shiftL(j);
	}
	for(int i = 1; i <= temp2.numOfDigits; ++i)
		temp2.digits[temp2.numOfDigits - i] = temp1.digits[temp1.numOfDigits - i];
	//int s;
	//int t = 0;
	//for(int i = 1; i <= bN1.numOfDigits; ++i)
	//	for(int j = 1; j <= bN2.numOfDigits; ++j)
	//	{
	//		tempArr[temp.numOfDigits - (i + j - 1)] += bN1.digits[bN1.numOfDigits - i] * bN2.digits[bN2.numOfDigits - j];
	//	}
	//for(int i = 1; i <= temp.numOfDigits; ++i)
	//{
	//	s = t + tempArr[temp.numOfDigits - i];
	//	tempArr[temp.numOfDigits - i] = s%10;
	//	t = s / 10;
	//	temp.digits[temp.numOfDigits - i] = tempArr[temp.numOfDigits - i];
	//}

	return temp2;

}

bigNumber operator *( const bigNumber& bN, int num)
{
	if(isNull(bN) || num == 0)
		return 0;
	bigNumber temp;
	temp.numOfDigits = bN.numOfDigits + 1;
	temp.digits = new uint8_t[temp.numOfDigits];
	memset(temp.digits, 0, temp.numOfDigits);
	if((num < 0 && !bN.isNegative) || (num > 0 && bN.isNegative))
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
	return temp;
}
bigNumber operator /( const bigNumber& bN1, const bigNumber& bN2 ){;}

bigNumber operator ^( const bigNumber& bN1, const bigNumber& bN2 )
{
	bigNumber temp1;
	bigNumber temp2;
	temp2 = bN1;
	++temp1;
	while(temp1 != bN2){
		std::cout << temp1 << std::endl;
	//	temp2 = bN1 * temp2;
		++temp1;
	}
	if(temp1 == bN2){
		++temp1;
		std::cout << "reacjed" << std::endl;
	}
	return temp2;
}

// bitwise shift
//bigNumber bigNumber::operator <<( int n ){;}

//bigNumber bigNumber::operator >>( int n ){;}

// factorial
bigNumber bigNumber::factorial(){;}


// add delete_left_zeroes method
// 
