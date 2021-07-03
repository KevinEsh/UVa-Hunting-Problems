#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class BigNum
{
public:
	BigNum();
	BigNum(vector<int>, bool);
	BigNum(string, bool);
	~BigNum();

	inline bool get_sign();
	inline int get_size();
	inline void set_sign(bool);
	inline int get_digit(int);
	inline string get_number();

	BigNum operator+(BigNum&);
	BigNum operator-(BigNum&);
	BigNum operator*(BigNum&);
	bool operator==(BigNum&);
	bool operator<=(BigNum&);
	bool operator<(BigNum&);

private:
	vector<int> digits;
	int size;
	bool positive;
};


BigNum::BigNum()
	: size(0), positive(true)
{
}

BigNum::BigNum(vector<int> digits_, bool positive_)
	: digits(digits_), size(digits_.size()), positive(positive_)
{
}

BigNum::BigNum(string number_, bool positive_)
	: positive(positive_)
{
	size = number_.size();

	for (int i = 0; i < size; i++) {
		digits.push_back(number_[size - i - 1] - '0');
	}
}

BigNum::~BigNum()
{
}

inline bool BigNum::get_sign()
{
	return this->positive;
}

inline void BigNum::set_sign(bool sign)
{
	this->positive = sign;
	return;
}

inline int BigNum::get_size()
{
	return size;
}

inline int BigNum::get_digit(int d)
{
	if (size <= d) return 0;
	return digits[d];
}

inline string BigNum::get_number()
{
	string number = "";
	if (!this->positive) number += "-";
	for (int i = size - 1; i >= 0; i--) {
		number += to_string(digits[i]);
	}
	return number;
}

BigNum BigNum::operator+(BigNum& other)
{
	vector<int> new_number;
	int max_size = (this->size > other.get_size()) ? this->size : other.get_size();
	int sum, carry = 0;

	//Regla del signo.
	if (this->positive ^ other.get_sign()) {
		bool tsign = this->positive;
		bool osign = other.get_sign();
		this->positive = true;
		other.set_sign(true);
		auto result = *this - other;
		this->positive = tsign;
		other.set_sign(osign);
		result.set_sign((*this < other) ? osign : tsign);
		return result;
	}

	//Proceso de suma por signo
	for (int i = 0; i < max_size; i++)
	{
		sum = this->get_digit(i) + other.get_digit(i) + carry;

		if (sum >= 10) { sum = sum % 10; carry = 1; }
		else carry = 0;

		new_number.push_back(sum);
	}

	//acarreo al final del vector
	if (carry > 0) new_number.push_back(carry);

	BigNum number(new_number, this->positive);
	return number;
}

BigNum BigNum::operator-(BigNum& other)
{

	vector<int> new_number;
	int max_size = (this->size > other.get_size()) ? this->size : other.get_size();
	int carry = 0;
	int a, b;
	bool greater = (other < *this);

	//Regla del signo.
	if (this->positive ^ other.get_sign()) {
		bool tsign = this->positive;
		bool osign = other.get_sign();
		this->positive = true;
		other.set_sign(true);
		auto result = *this + other;
		this->positive = tsign;
		other.set_sign(osign);
		result.set_sign(tsign);
		return result;
	}

	//Proceso de resta por digitos
	for (int i = 0; i < max_size; i++)
	{
		a = greater ? this->get_digit(i) - carry : other.get_digit(i) - carry;
		b = greater ? other.get_digit(i) : this->get_digit(i);
		if (a < b) {
			a += 10;
			carry = 1;
		}
		else carry = 0;

		new_number.push_back(a - b);
	}

	//Limpieza de ceros al final del vector
	for (int i = new_number.size() - 1; i >= 1; i--) {
		if (!new_number[i]) new_number.pop_back();
		else break;
	}

	BigNum number(new_number, greater ? this->positive : !other.get_sign());
	return number;
}

BigNum BigNum::operator*(BigNum& other)
{

	vector<int> new_number;
	int max_size = (this->size > other.get_size()) ? this->size : other.get_size();
	int sum, carry = 0;

	for (int i = 0; i < this->size; i++)
	{
		carry = 0;

		for (int j = 0; j < other.get_size(); j++) {
			sum = this->get_digit(i) * other.get_digit(j) + carry;

			if (sum >= 10) { carry = sum / 10; sum = sum % 10; }
			else carry = 0;

			if (new_number.size() <= i + j) new_number.push_back(sum);
			else {
				new_number[i + j] += sum;
				if (new_number[i + j] >= 10) {
					carry += new_number[i + j] / 10;
					new_number[i + j] = new_number[i + j] % 10;
				}
			}
		}

		if (carry > 0) new_number.push_back(carry);
	}

	if (this->positive && other.get_sign() || !this->positive && !other.get_sign()) {
		BigNum number(new_number, true);
		return number;
	}
	else {
		BigNum number(new_number, false);
		return number;
	}
}

bool BigNum::operator== (BigNum& other) {
	if (this->size != other.get_size()) return false;
	if (this->positive != other.get_sign()) return false;
	for (int i = 0; i < this->size; i++) {
		if (this->digits[i] != other.get_digit(i)) return false;
	}
	return true;
}

bool BigNum::operator< (BigNum& other) {
	if (this->size < other.get_size()) return true;
	for (int i = size - 1; i >= 0; --i) {
		if (this->digits[i] < other.get_digit(i)) return true;
		else if (this->digits[i] > other.get_digit(i)) return false;
	}
	return false;
}

bool BigNum::operator<= (BigNum& other) {
	if (this->size < other.get_size()) return true;
	for (int i = size - 1; i >= 0; --i) {
		if (this->digits[i] < other.get_digit(i)) return true;
		else if (this->digits[i] > other.get_digit(i)) return false;
	}
	return true;
}
