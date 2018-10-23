#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("Hello test!\n");

// 测试和理解字符串和指针
	char *str1 = "Abcdefg hello!";

	char *str2[] = {"1","aa","jj"};

	printf("%s\n",str2[2]);



	return 0;
}