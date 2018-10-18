#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i;
	while(i<argc){

		printf("参数%i: %s\n", i, argv[i] );
		i++;
	}
	return 0;
}