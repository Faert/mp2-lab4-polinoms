#include "Polinoms.h"

bool Monom::is_zero()
{
	return(!bool(a));
}

bool Monom::operator>=(const Monom& other) const
{
	return power >= other.power;
}

bool Monom::operator==(const Monom& other) const
{
	return (power == other.power && a == other.a);
}

bool Monom::operator!=(const Monom& other) const
{
	return !(*this == other);
}

Monom Monom::operator+(const Monom& other) const
{
	if (power != other.power)
	{
		throw "Wrong powers!";
	}

	return Monom(a + other.a, power);
}

Monom& Monom::operator*(double a_)
{
	a *= a_;
	return *this;
}

Monom Monom::operator*(const Monom& other) const
{
	if (other.power / 100 + power / 100 > 9 || other.power / 10 % 10 + power / 10 % 10 > 9 || other.power % 10 + power % 10 > 9)
	{
		throw "Power overflow!";
	}

	return Monom(a * other.a, power + other.power);
}

istream& operator>>(istream& in, Monom& other)
{
	in >> other.a >> other.power;

	if (other.a == 0 || other.power >= 1000 || other.power < 0)
	{
		throw "Invalid input!";
	}

	return in;
}

ostream& operator<<(ostream& out, const Monom& other)
{
	if (other.a > 0)
	{
		out << "+";
	}

	out << other.a << "*x^" << other.power / 100 << "*y^" << other.power / 10 % 10 << "*z^" << other.power % 10;

	return out;
}


bool Polinom::operator==(const Polinom& other) const
{
	if (size() == other.size())
	{
		for (Iter it = begin(), other_it = other.begin(); it != nullptr; ++it, ++other_it)
		{
			if ((*it) != (*other_it))
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool Polinom::operator!=(const Polinom& other) const
{
	return(!(*this == other));
}

Polinom Polinom::operator+(const Polinom& other) const
{
	Polinom temp;

	Iter it = begin();
	Iter other_it = other.begin();

	while (it != nullptr || other_it != nullptr)
	{
		if (it == nullptr)
		{
			temp.add(*other_it);
			++other_it;
			continue;
		}

		if (other_it == nullptr || (*it).power > (*other_it).power)
		{
			temp.add(*it);
			++it;
			continue;
		}

		if ((*it).power < (*other_it).power)
		{
			temp.add(*other_it);
			++other_it;
			continue;
		}

		if ((*it).power == (*other_it).power)
		{
			if (!((*it) + (*other_it)).is_zero())
			{
				temp.add((*it) + (*other_it));
			}
			++it;
			++other_it;
		}
	}

	return temp;
}

Polinom Polinom::operator-(const Polinom& other) const
{
	Polinom temp = (*this) + (other * (-1));

	return temp;
}

Polinom Polinom::operator*(double a_) const
{
	Polinom temp(*this);

	if (a_ != 0)
	{
		for (Iter it = temp.begin(); it != nullptr; ++it)
		{
			(*it) = (*it) * a_;
		}
	}
	else
	{
		while (temp.begin() != nullptr)
		{
			temp.remove();
		}
	}

	return temp;
}

Polinom Polinom::operator*(const Polinom& other) const
{
	Polinom temp;

	Iter it = begin();
	Iter other_it = other.begin();

	if (it != nullptr && other_it != nullptr)
	{
		for (; it != nullptr; ++it)
		{
			for (other_it = other.begin(); other_it != nullptr; ++other_it)
			{
				temp.add((*it) * (*other_it));
			}
		}
	}

	temp = temp.Sort();

	return temp;
}

Polinom Polinom::Sort()
{
	if (this->size() < 2)
	{
		List temp(*this);
		return temp;
	}

	Polinom temp(Merge_Sort(*this));
	Polinom P;
	Monom s;
	Iter it = temp.begin();

	for (; it.next() != temp.end(); ++it)
	{
		s = Monom(s.a, (*it).power) + *it;
		if ((*it).power != (*(it.next())).power)
		{
			if (!s.is_zero())
			{
				P.add(s);
			}
			s = Monom(0, 0);
		}
	}
	s = Monom(s.a, (*it).power) + *it;
	if (!s.is_zero())
	{
		P.add(s);
	}

	return P;
}

istream& operator>>(istream& in, Polinom& other)
{
	other.erase();

	if (cin.peek() == '\n')
	{
		cin.get();
	}

	while (cin.peek() != '\n')
	{
		Monom temp;
		in >> temp;
		other.add(temp);
	}

	other = other.Sort();

	return in;
}

ostream& operator<<(ostream& out, const Polinom& other)
{
	if (other.begin() != nullptr)
	{
		out << List<Monom>(other);
	}
	else
	{
		out << 0;
	}

	return out;
}
