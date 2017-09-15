#include <iostream>
#include <cmath>
#include <ctime>

int methodNumberOne(long long x)
{
	x = (1664525 * x + 1013904223) % 2147483648;
	return x;
}

using namespace std;
int main()
{
	int a[10] = {0};
	static const int N = 100000;
	int typeOfMethod, x, j, i,currEl;
	double temp;
	x = time(0);
	while(cin >> typeOfMethod);//универсально
	switch(typeOfMethod)
	{
		case 1:
		{
			for (i = 0; i < N; ++i)
			{
				x = methodNumberOne(x);
				temp = double(x) / 2147483648;
				//x = currEl;
				++a[int(temp * 10)];
			}
			for (i = 0; i < 10; ++i)
			{
				cout << "( " << double(i) / 10 << "; " << double(i + 1) / 10 << ") : ";
				for (j = 0; j < double(a[i]) / 1000; ++j)
					cout << "*";
				cout << endl;
			}
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			break;
		}
		case 8:
		{
			break;
		}
		case 9:
		{
			break;
		}
		case 10:
		{
			break;
		}
	}
	system("pause");
	return 0;
}