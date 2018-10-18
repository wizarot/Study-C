#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i;

	if (argc <= 2)
	{
		printf("一个或更少参数 \n");
	}else if (argc >2 && argc <= 4)
	{
		printf("多个参数(少于3个)\n");
	}else{
		printf("参数实在太多了\n");
	}
	return 0;
}