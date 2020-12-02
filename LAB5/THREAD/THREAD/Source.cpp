#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB
#include "pthread.h"
#include <stdio.h>

int sells = 0, products = 0;
void* processA(void* mess)
{
	while (1)
	{
		sells++;
		printf("Sells = %d\n", sells);
	}
}
void* processB(void* mess)
{
	while (1)
	{
		products++;
		printf("Products = %d\n", products);
	}
}
int main()
{
	pthread_t pA, pB;
	pthread_create(&pA, NULL, &processA, NULL);
	pthread_create(&pB, NULL, &processB, NULL);
	while (1);
	return 0;
}
