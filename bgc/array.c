#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *p;
	if ((p = malloc(10 * sizeof(int))) == NULL)
	{
		fprintf(stderr, "Error allocating memory!\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 10; i++)
	{
		p[i] = i * 10;
		printf("%d :: %d\n", i, p[i]);
	}

	return 0;
}
