#include <stdio.h>

int getaverage(int data[10]);

int main(void)
{
	int average,array[10] = {15,78,98,15,98,85,17,35,42,15};
	average = getaverage(array);
	printf("%d  %d\n",average, array[0]);
	return 0;
}

int getaverage(int data[10])
{
	int i,average = 0;
	for (i = 0;i < 10;i++) {
		average += data[i];
	}
	data[0] = 10;
	return average / 10;
}