#include <iostream>
#include "../Polinoms/Polinoms.h"

using namespace std;

int main()
{
	size_t globalflag = true;

	while (globalflag)
	{
		Polinom First;
		Polinom Second;
		bool flag = false;

		cout << "Enter your first polinom (-3.2*x^0*y^3*z^2 enter as -3.2 32):\n";
		while (!flag)
		{
			try
			{
				cin >> First;
				flag = true;
			}
			catch (const char* e)
			{
				cout << e << '\n';
				cout << "Enter your correct polinom:\n";
				flag = false;
			}
		}

		bool flag0 = false;
		while (!flag0)
		{
			flag = false;
			cout << "Enter your second polinom (-3.2*x^0*y^3*z^2 enter as -3.2 32):\n";
			while (!flag)
			{
				try
				{
					cin >> Second;
					flag = true;
				}
				catch (const char* e)
				{
					cout << e << '\n';
					cout << "Enter your correct polinom:\n";
					flag = false;
				}
			}

			cout << "Select an operation (+, -, *, a(multiplication by a constant)):\n";
			char op;
			flag = false;
			while (!flag)
			{
				cin >> op;
				switch (op)
				{
				case '+':
				{
					First = First + Second;
					cout << "First + Second = " << First << '\n';
					flag = true;
					break;
				}
				case '-':
				{
					First = First - Second;
					cout << "First - Second = " << First << '\n';
					flag = true;
					break;
				}
				case 'a':
				{
					double a;
					cout << "Enter a constant:\n";
					cin >> a;
					cout << "Multiply the first(1) or second(2)?\n";
					size_t choice;
					cin >> choice;
					if (choice == 1)
					{
						First = First * a;
						cout << "First * " << a << " = " << First << '\n';
					}
					else
					{
						First = Second * a;
						cout << "Second * " << a << " = " << First << '\n';
					}
					flag = true;
					break;
				}
				case '*':
				{
					try
					{
						First = First * Second;
						cout << "First * Second = " << First << '\n';
						flag = true;
						break;
					}
					catch (const char* e)
					{
						cout << e << '\n';
					}
				}
				default:
					cout << "Enter correct operation:\n";
					break;
				}
			}

			cout << "Do you want finish(1) or start over(2) or continue with the results(3)?\n";
			size_t choice;
			cin >> choice;
			if (choice == 1)
			{
				flag0 = true;
				globalflag = false;
			}
			if (choice == 2)
			{
				flag0 = true;
			}
		}
	}
}
