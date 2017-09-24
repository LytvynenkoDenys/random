#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
using namespace std;

long long inverse(long long b) {
	long long m = 1231525;
	long long ex = m - 2;
	if (b == 1)
		return 1;
	long long r = 1;
	while (ex)
	{
		if (ex & 1)r = (r * b) % m;
		ex = ex >> 1;
		b = (b * b) % m;
	}
	return r;
}

int methodNumberOne(long long x)
{
	x = (1664525 * x + 1013904223) % 2147483648;
	return x;
}

int methodNumberTwo(long long x)
{
	x = (1 * x * x + 2 * x + 13) % 1299721;
	return x;
}

int methodNumberThree(long long &x, int &xPrevPrev, int &xPrev)
{
	x = (xPrevPrev + xPrev) % 1299721;
	xPrevPrev = xPrev;
	xPrev = x;
	return x;
}

int methodNumberFour(long long x)
{
	x = (5 * inverse(x) + 2) % 1299721;
	return x;
}

int methodNumberFive(long long x)
{
	long long a, b, z;
	a = methodNumberOne(x);
	b = methodNumberTwo(x);
	z = abs((a - b)) % 2147483648;
	return z;
}

double methodNumberSix(long long &seed){
	double s = 0;
	for (int i = 0; i < 12; ++i)
	{
		seed = methodNumberFive(seed);
		s +=  seed / 2147483648.;
	}
	return s - 6;
}

pair<double,double> methodNumberSeven(pair <int, int>& seed)
{
	double a, b, x1, x2, t, v1, v2, s;
	do{
		seed.first = methodNumberFive(seed.first);
		seed.second = methodNumberOne(seed.second);
		a = seed.first / 2147483648.;
		b = seed.second / 2147483648.;
		v1 = 2 * a - 1;
		v2 = 2 * b - 1;
		s = v1 * v1 + v2 * v2;
	} while (s >= 1);
	t = sqrt((-1) * 2 * log(s) / s);
	x1 = v1 * t;
	x2 = v2 * t;
	return make_pair(x1, x2);
}

double methodNumberEight(long long& seed)
{
	double a, u1, v1 , u, v;
	
	do
	{
		seed = methodNumberOne(seed);
		u1 = methodNumberOne(seed);
	} while (u1 == 0);
	u = u1 / 2147483648.;
	//cout << u << " ";
	do{
		seed = methodNumberOne(seed);
		v1 = methodNumberOne(seed);
		v = v1 / 2147483648.;
		//cout << v << " ";
		a = sqrt(8. / 2.7182) * (v - 0.5) / u;
	} while (a * a > (-1) * 4 * log(u));
	return a;
}

double methodNumberNine(long long& seed)
{
	double u1, u;
	static const double MU = 17;
	do
	{
		seed = methodNumberOne(seed);
		u1 = methodNumberOne(seed);
	} while (u1 == 0);
	u = u1 / 2147483648.;
	return (-1) * MU * log(u);
}

double methodNumberTen(long long &seed)
{
	double u, u1, y, x, v1, v;
	double a = 1;
	do{
		seed = methodNumberOne(seed);
		u1 = methodNumberOne(seed);
		u = u1 / 2147483648.;
		y = tan(u * 3.1415926);
		x = sqrt(2 * a - 1) * y + a - 1;
		v1 = methodNumberFour(seed);
		v = v1 / 2147483648.;
	} while (x <= 0 || v > (1 + y * y) * pow(M_E, (a - 1) * log(x / (a - 1)) - sqrt(2 * a - 1) * y));
	return x;
}

void diagramm(int a[10])
{
	int i, j;
	for (i = 0; i < 10; ++i)
	{
		cout << fixed << setprecision(1) << "( " << double(i) / 10 << "; " << double(i + 1) / 10 << ") : ";
		for (j = 0; j < double(a[i]) / 1000; ++j)
			cout << "*";
		cout << endl;
	}
}

void diagramm2(int a[60])
{
	int i, j;
	for (i = -30; i < 30; ++i)
	{
		cout << fixed << setprecision(1);
		cout << "( ";
		cout.width(3);
		cout << double(i) / 10;
		cout << "; ";
		cout.width(4);
		cout << double(i + 1) / 10;
		cout << ") : ";
		for (j = 0; j < double(a[i+30]) / 100; ++j)
			cout << "*";
		cout << endl;
	}
}

void diagramm3(int a[100])
{
	int i, j;
	for (i = 0; i < 100; ++i)
	{
		cout << "( ";
		cout.width(3);
		cout << i;
		cout << "; ";
		cout.width(3);
		cout << i + 1;
		cout << ") : ";
		for (j = 0; j < double(a[i])/1000; ++j)
			cout << "*";
		cout << endl;
	}
}

using namespace std;
int main()
{
	int xPrev, xPrevPrev;
	int a[10] = {0};
	static const int N = 100000;
	int typeOfMethod, i;
	long long x;
	double temp;
	while (cin >> typeOfMethod)
	{
		for (i = 0; i < 10; ++i)
			a[i] = 0;
		x = time(0);
		temp = 0;
		switch (typeOfMethod)
		{
			case 1:
			{
				  for (i = 0; i < N; ++i)
				  {
					  x = methodNumberOne(x);
					  temp = double(x) / 2147483648;
					  ++a[int(temp * 10)];
				  }
				  diagramm(a);
				  break;
			}
			case 2:
			{
				  for (i = 0; i < N; ++i)
				  {
					  x = methodNumberTwo(x);
					  temp = double(x) / 1299721;
					  ++a[int(temp * 10)];
				  }
				  diagramm(a);
				  break;
			}
			case 3:
			{
				  xPrevPrev = methodNumberTwo(x);
				  xPrev = methodNumberTwo(x);
				  for (i = 0; i < N; ++i)
				  {
					  x = methodNumberThree(x, xPrevPrev, xPrev);
					  temp = double(x) / 1299721;
					  ++a[int(temp * 10)];
				  }
				  diagramm(a);
				  break;
			}
			case 4:
			{
				  for (i = 0; i < N; ++i)
				  {
					  x = methodNumberFour(x);
					  temp = double(x) / 1299721;
					  ++a[int(temp * 10)];
				  }
				  diagramm(a);
				  break;
			}
			case 5:
			{
				  for (i = 0; i < N; ++i)
				  {
					  x = methodNumberFive(x);
					  temp = double(x) / 2147483648;
					  ++a[int(temp * 10)];
				  }
				  diagramm(a);
				  break;
			}
			case 6:
			{
					  double a;
					  int count[60];
					  for (i = 0; i < 60; ++i)
						  count[i] = 0;
				  for (i = 0; i < N; ++i)
				  {
					  a = methodNumberSix(x);
					  ++count[int((a+6) * 5)];
					 // cout << a << " ";
				  }
				 diagramm2(count);
				  break;
			}
			case 7:
			{
					  int count[60];
					  for (i = 0; i < 60; ++i)
						  count[i] = 0;
					  pair<double, double> z;
					  pair <int, int> seed;
					 seed.first = time(0);
					  seed.second = time(0);
					  for (i = 0; i < N; ++i)
					  {
						  z = methodNumberSeven(seed);
						temp = (double(z.first));
						++count[int((temp + 6)* 5)];
					  }
					  diagramm2(count);
				  break;
			}
			case 8:
			{
					  double z;
					  for (i = 0; i < N; ++i)
					  {
						  z = methodNumberEight(x);
						  ++a[int(z * 10)];
					  }
					  diagramm(a);
				  break;
			}
			case 9:
			{
					  int hundred[100];
					  double z;
					  for (i = 0; i < 100; ++i)
						  hundred[i] = 0;
					  for (i = 0; i < N; ++i)
					  {
						  z = methodNumberNine(x);
						 ++hundred[abs(int(z))];
					  }
					  diagramm3(hundred);
				  break;
			}
			case 10:
			{
					   int hundred[100];
					   double z;
					   int S = 0;
					   for (i = 0; i < 100; ++i)
						   hundred[i] = 0;
					   for (i = 0; i < N; ++i)
					   {
						   z = methodNumberTen(x);
						if(z <= 100)
							++hundred[int(z)];
						else
						{
							cout << z << " " << endl;
							++S;
						}
						}
					   diagramm3(hundred);
					   cout << S / double(N);
				   break;
			}
		}
	}
	system("pause");
	return 0;
}