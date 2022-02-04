#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#ifdef DEBUG
#include <string.h>
#include <dlfcn.h>

typedef void * (* malloc_like_function)(size_t);
void *malloc(size_t size){
	malloc_like_function sysmalloc = (malloc_like_function)dlsym(RTLD_NEXT, "malloc");
	void *result = sysmalloc(size);
	memset(result, 0xCD, size);
	return result;
}

#endif

int main(){
	int *p1 = new int;
	int *p2 = new int;

	*p1 = 0;

	printf("%d, %d\n", *p1, *p2);
}

