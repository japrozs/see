#include <stdio.h>
#include <stdbool.h>

typedef struct{
	int x;
	float y;
	char z;
} mystr;

typedef union{
	int x;
	float y;
	char z;
} myunion;

typedef struct {
	char *name;
	bool is_robot;
	union{
		char *personality;
		int firmware_version;
	};
} character;

void print_character(character* c){
	printf("Characters :: %s\n", c->name);
	if(c->is_robot){
		printf("version :: %d\n", c->firmware_version);
	}else{
		printf("personality :: %s\n",c->personality);
	}
}

int main(){
	mystr s;
	s.x = 45;
	s.y = 9.87;
	s.z = 'H';

	myunion u;
	u.x = 45;
	u.y = 9.87;
	u.z = 'H';

	printf("struct size :: %lu\n", sizeof(mystr));
	printf("struct :: {%d, %f, %c}\n", s.x, s.y, s.z);
	printf("union size :: %lu\n", sizeof(myunion));
	printf("union :: {%d, %f, %c}\n", u.x, u.y, u.z);

	character hansolo;
	character r2d2;

	hansolo.name = "Han Solo";
	hansolo.is_robot = false;
	hansolo.personality = "Scruffy looking NerfHerder";

	r2d2.name = "R2D2";
	r2d2.is_robot = true;
	r2d2.firmware_version = 42;

	print_character(&hansolo);
	print_character(&r2d2);

	return 0;
}
