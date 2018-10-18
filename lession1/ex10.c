#include <stdio.h>

int main(int argc, char const *argv[])
{
	// 测试命令行参数
	int i;
	for (int i = 1; i < argc; ++i)
	{
		printf("参数 %d: %s \n", i, argv[i]);
	}

	char *states[] = {
        "第一个", "第二条",
        "第三条", "第4条"
    };
    int num_states = 4;

    for(i = 0; i < num_states; i++) {
        printf("数组 %d: %s\n", i, states[i]);
    }

	return 0;
}