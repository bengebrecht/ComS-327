#include <stdio.h>
int main()
{

	static int arr[100000000];

	arr[0] = 1;

	printf("%d\n", arr[0]);

	int i;
	int j = 0;

	for (i = 1; i < 100000001; i=i+1) {
		if (i%2 == 1) {
			arr[i] = arr[j];
		} else {
			arr[i] = arr[j] + arr[j+1];
			j = j+1;
		}

		printf("%d\n", arr[i]);
	}
	return 0;
}