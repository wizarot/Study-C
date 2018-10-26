#include <stdio.h>

// 尝试使用传指针,打印内容
void print_data(int *ages,int size){
	printf("%p\n",ages );
	for (int i = 0; i < size; ++i)
	{
		printf("<6> %d \n",ages[i]);
	}
	// printf("%p\n", ages);
}

// void print_names(char *names[]){
// 	int size  = sizeof( *names) / sizeof(char* );
// 	for (int i = 0; i < size; ++i)
// 	{
// 		printf("%s\n", names[i]);
// 	}

// }

int main(int argc, char *argv[])
{
	// 数组
	int ages[] = {23,43,12,89,2};

	// 字符串数组
	char *names[] = {
		"α" , "β" , "ɣ", "d", "e"
	};

	// 计算大小
	int count = sizeof(ages) / sizeof(int);
	int size = sizeof(names) / sizeof(char*);
	printf("names size %d\n", size);
	int i = 0;
	// 遍历i索引数组
	for (int i = 0; i < count; ++i)
	{
		printf("<1> %s 的年龄是:%d \n", names[i],ages[i]);
	}
	printf("------------------\n");

	// 指向整数的指针
	int *cur_age = ages;
	// “指向‘指向字符的指针’的指针”
	char **cur_name = names;

	for (int i = 0; i < count; ++i)
	{
		// 遍历ages和names，但是使用“指针加偏移i”。*(cur_name+i)和name[i]是一样的，你应该把它读作“‘cur_name指针加i’的值”。
		printf("<2> %s 的年龄是:%d \n", *(cur_name+i),*(cur_age+i));
	}
	printf("------------------\n");

	for (int i = 0; i < count; ++i)
	{
		// 这里展示了访问数组元素的语法和指针是相同的。
		printf("<3> %s 的年龄是:%d \n", cur_name[i],cur_age[i]);
	}
	printf("------------------\n");

	// 听说这是一种非常傻的用法?
	// 通过将cur_name和cur_age置为names和age数组的起始位置来初始化for循环
	// for循环的测试部分比较cur_age指针和ages起始位置的距离
	// for循环的增加部分增加了cur_name和cur_age的值，这样它们可以只想names和ages的下一个元素。
	for (cur_name=names,cur_age=ages; (cur_age - ages) < count; cur_name++ , cur_age++)
	{
		// cur_name和cur_age的值现在指向了相应数组中的一个元素，我们我可以通过*cur_name和*cur_age来打印它们，这里的意思是“cur_name和cur_age指向的值”。
		printf("<4> %s 的年龄是:%d \n", *cur_name,*cur_age);
	}
	printf("------------------\n");

	//  从后向前遍历指针
	cur_name = names;
	cur_age = ages;
	for (int i = count-1; i >= 0; i--)
	{
		// printf("%d\n", i);
		// 既然直接当数组用就可以,那么为什么还要声明指针呢? 当然优化执行速度这点我可以理解.
		printf("<5> %s 的年龄是:%d \n", names[i],ages[i]);// 数组方式访问
		printf("<5> %s 的年龄是:%d \n", *(cur_name+i),*(cur_age+i));// 指针方式访问
		printf("<5> 指针位置:%p \n", (cur_name+i));// 指针方式访问

	}

	printf("------------------\n");
	print_data(ages,count);
	// print_names(names);


	return 0;
}