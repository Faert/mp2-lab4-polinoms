#pragma once

#include "list.h"

class Monom
{
public:
	double a; //coefficient
	int power;

	Monom(double a_ = 0, int power_ = 0) : a(a_), power(power_) {};
	Monom(const Monom& other) : a(other.a), power(other.power) {};

	bool is_zero();

	bool operator>=(const Monom& other) const;
	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;

	Monom operator+(const Monom& other) const;
	Monom& operator*(double a_);
	Monom operator*(const Monom& other) const;

	friend istream& operator>>(istream& in, Monom& other);
	friend ostream& operator<<(ostream& out, const Monom& other);
};

class Polinom : public List<Monom>
{
public:
	Polinom() : List<Monom>() { };
	Polinom(const List<Monom>& other) : List<Monom>(other) { };

	bool operator==(const Polinom& other) const;
	bool operator!=(const Polinom& other) const;

	Polinom operator+(const Polinom& other) const;
	Polinom operator-(const Polinom& other) const;
	Polinom operator*(double a_) const;
	Polinom operator*(const Polinom& other) const;

	Polinom Sort();

	friend istream& operator>>(istream& in, Polinom& other);
	friend ostream& operator<<(ostream& out, const Polinom& other);
};
