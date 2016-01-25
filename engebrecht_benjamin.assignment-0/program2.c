#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

	int num = atoi(argv[1]);

	int findNumber(int i) {

		if (i%2 == 1) {

			return findNumber(i-1);

		} else if (i == 0) {

			return 1;

		} else {

			return findNumber(i-1) + findNumber(i-2);

		}

	}

	int numerator = findNumber(num);

	int denominator = findNumber(num+1);

	printf("%d/%d\n", numerator, denominator);

	return 0;
}