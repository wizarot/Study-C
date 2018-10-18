#include <stdio.h>

int main()
{
	int i;
	// printf("Please input a value:");

	// 行輸入數字
	// scanf("%d", &i);
	// printf("Your input: %d\n", i);

	// 輸入字符
	// i = getchar();
	// putchar(i);

	// 輸入字符串
	char str[10];
	printf("Please input a string:\n");
	gets( str );
	puts( str );
	// getch();d

	return 0;
}