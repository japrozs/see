#include <stdio.h>

struct counters {
	unsigned int little:2; // use 2 bits
	unsigned int medium:4; // use 4 bits
	unsigned int large:6; // use 6 bits
}__attribute__((packed)); // tell the compiler to pack the bits close to each other and tightly

#define NUM_LOOPS 50

int main(){
	struct counters counts;
	counts.little = 0;
	counts.medium = 0;
	counts.large = 0;
	for(int i = 0;i < NUM_LOOPS;i++){
		counts.little++;
		counts.medium++;
		counts.large++;
		printf("%u, %u, %u\n", counts.little, counts.medium, counts.large);
	}

	printf("Sizeof counts = %lu\n", sizeof(counts));

	return 0;
}
