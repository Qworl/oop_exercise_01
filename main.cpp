#include <iostream>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <numeric>
#include <stdexcept>
using namespace std;

class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}
	Rational(int numerator, int denominator) {
		if (denominator == 0) {
			throw invalid_argument("Denominator should not be equal to zero");
		}
		p = numerator;
		q = denominator;
		Reduce();
	}
	void SetNumerator(int new_value) {
		p = new_value;
	}
	void SetDenominator(int new_value) {
		p = new_value;
	}
	int Numerator() const {
		return p;
	}
	int Denominator() const {
		return q;
	}
private:
	int p;
	int q;
	int Gcd(int a, int b) {
		while (b != 0) {
			int t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
	void Reduce() {
		int tmp = Gcd(p, q);
		p /= tmp;
		q /= tmp;
		if (p * q < 0) {
			p = -abs(p);
			q = abs(q);
		}
		else if (p < 0 && q < 0) {
			p = abs(p);
			q = abs(q);
		}
		if (p == 0) {
			q = 1;
		}
	}
};

bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw invalid_argument("Division by zero");
	}
	return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	return (lhs - rhs).Numerator() < 0;
}

ostream& operator<<(ostream& stream, const Rational& old) {
	stream << old.Numerator() << '/' << old.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& new_ratio) {
	int p = new_ratio.Numerator(), q = new_ratio.Denominator();
	char tmp = '.';
	if (stream >> p && stream >> tmp && tmp == '/' && stream >> q) {
		new_ratio = Rational(p, q);
	}
	return stream;
}

int main() {
	Rational a, b, c;
	try{
		cin >> a >> b >> c;
		cout << "a - b = " << (a - b) << endl; 
		cout << "a * c = " << (a * c) << endl; 
		cout << "b + c = " << (b + c) << endl; 
		cout << "1 / b = " << (Rational(1,1) / c) << endl; 
	} catch(invalid_argument& arg){
		cout << arg.what() << endl;
		return -1;
	}
	return 0;
}
