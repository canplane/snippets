int _floor(double x) {
	int _x = (int)x;
	if (x == _x)    return _x;
	return _x - (x < 0);
}
int _ceil(double x) {
	int _x = _floor(x);
	return _x + (x != _x);
}
int _round(double x) {
	return _floor(x + 0.5);
}


// debug :
#include <stdio.h>
#define SZ 7
double li[] = { 0, 2, 2.25, 2.5, -2, -2.25, -2.5 };
int main()
{
	for (int i = 0; i < SZ; i++)
		printf("%lf ", li[i]);
	printf("\nfloor ");
	for (int i = 0; i < SZ; i++)
		printf("%d ", _floor(li[i]));
	printf("\nceil ");
	for (int i = 0; i < SZ; i++)
		printf("%d ", _ceil(li[i]));
	printf("\nround ");
	for (int i = 0; i < SZ; i++)
		printf("%d ", _round(li[i]));
	printf("\n");
}