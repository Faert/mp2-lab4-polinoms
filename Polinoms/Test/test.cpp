#include "pch.h"

#include "../Polinoms/Polinoms.h"

TEST(List, can_create)
{
	ASSERT_NO_THROW(List<int> A);
}

TEST(List, can_add_and_add_change_size)
{
	List<int> B;
	EXPECT_EQ(0, B.size());
	B.add(0);
	EXPECT_EQ(1, B.size());
	B.add(1);
	EXPECT_EQ(2, B.size());
	B.add(2);
	EXPECT_EQ(3, B.size());
	size_t i = 0;
	for (List<int>::Iter it = B.begin(); it != B.end(); ++it, i++)
	{
		EXPECT_EQ(*it, i);
	}
}

TEST(List, can_remove_and_remove_change_size)
{
	List<int> B;
	EXPECT_EQ(0, B.size());
	B.add(0);
	EXPECT_EQ(1, B.size());
	B.remove();
	EXPECT_EQ(0, B.size());
	B.add(0);
	EXPECT_EQ(1, B.size());
	B.add(1);
	EXPECT_EQ(2, B.size());
	B.remove();
	EXPECT_EQ(1, B.size());
	B.remove();
	EXPECT_EQ(0, B.size());
}

TEST(List, can_copy)
{
	List<int> B;
	EXPECT_EQ(0, B.size());
	B.add(0);
	EXPECT_EQ(1, B.size());
	B.add(1);
	EXPECT_EQ(2, B.size());
	B.add(2);
	EXPECT_EQ(3, B.size());
	List<int> C(B);
	size_t i = 0;
	for (List<int>::Iter it = C.begin(); it != C.end(); ++it, i++)
	{
		EXPECT_EQ(*it, i);
		(*it)++;
	}
	for (List<int>::Iter it = C.begin(), it1 = B.begin(); it != C.end(); ++it, ++it1, i++)
	{
		EXPECT_NE(*it, *it1);
	}
}

TEST(List, can_Merge_Sort)
{
	List<int> B;
	B.add(0);
	B.add(1);
	B.add(2);
	B.add(2);
	B.add(1);
	
	List<int> S;
	S.add(2);
	S.add(2);
	S.add(1);
	S.add(1);
	S.add(0);

	B = Merge_Sort(B);

	for (List<int>::Iter itB = B.begin(), itS = S.begin(); itB != B.end(); ++itB, ++itS)
	{
		EXPECT_EQ(*itB, *itS);
	}
}

TEST(Monom, can_create_and_copy)
{
	Monom a(3, 4);
	Monom b(a);
	EXPECT_EQ(a.a, 3);
	EXPECT_EQ(a.power, 4);
	EXPECT_TRUE(a == b);
}

TEST(Monom, monom_operations)
{
	Monom a(3, 3);
	Monom b(a);
	b = b * (-1);
	EXPECT_EQ(-3, b.a);
	EXPECT_EQ(a.power, b.power);
	a = a + b;
	EXPECT_EQ(true, a.is_zero());
	Monom c(7, 7);
	EXPECT_ANY_THROW(c + a);
	EXPECT_ANY_THROW(c * a);
	a = b * (-1);
	Monom d(6, 11);
	Monom e(18, 14);
	EXPECT_TRUE(e == (d * a));
}

TEST(Polinom, Polinom_create_and_copy)
{
	Monom a(3, 4);
	Monom b(a*(-1));
	Polinom P;
	P.add(a);
	P.add(b);
	Polinom::Iter it = P.begin();
	EXPECT_EQ(*it, a);
	EXPECT_EQ(*(it.next()), b);
	Polinom P1(P);
	EXPECT_EQ(P, P1);
}

TEST(Polinom, Polinom_Sort)
{
	Polinom P;
	Monom a(3, 4);
	Monom b(a);
	Monom c(6, 78);
	Monom d(-7.5, 78);
	Monom g(1, 100);
	Monom t(1, 10);
	P.add(a);
	P.add(b*(-1));
	P.add(c);
	P.add(d);
	P.add(g);
	P.add(t);
	Polinom P1;
	P1.add(g);
	P1.add(Monom(-1.5, 78));
	P1.add(t);
	EXPECT_EQ(P.Sort(), P1);
}

TEST(Polinom, Polinom_operations)
{
	Polinom P;
	Monom a(3, 6);
	Monom b(a);
	Monom c(6, 44);
	P.add(a);
	P.add(b * (-1));
	P.add(c);
	Polinom P1(P*(-1));
	Polinom A;
	EXPECT_EQ(A, P + P1);
	EXPECT_EQ(P*2, P - P1);
	EXPECT_ANY_THROW(P * P);
	P.add(Monom(3, 33));
	P = P.Sort();
	A.add(Monom(36, 88));
	A.add(Monom(36, 77));
	A.add(Monom(9, 66));
	EXPECT_EQ(P * P, A);
}