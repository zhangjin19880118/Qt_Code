/* ************************************************************************
 *       Filename:  05_test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017年04月08日 10时42分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 3

//一个结构体代表一个单词
struct dict
{
	char *key; //单词
	char *content; //单词对应的解析
};

int init_dict( struct dict ** p)
{
	//分配3个结构体
	*p = (struct dict *)malloc( MAX * sizeof(struct dict) );
	if( *p == NULL)
	{
		return 0;
	}

	memset(*p, 0, MAX * sizeof(struct dict) );

	//第一个单词
	//(*p)[0].key = (char *)malloc( sizeof(char) * ( strlen("a") + 1 )  );
	//单词
	(*p)[0].key = (char *)malloc( strlen("a") + 1  );
	memset( (*p)[0].key, 0, strlen("a") + 1);
	strcpy( (*p)[0].key, "a");

	//对应的解析
	(*p)[0].content = (char *)malloc( strlen("测试a") + 1  );
	memset( (*p)[0].content, 0, strlen("测试a") + 1);
	strcpy( (*p)[0].content, "测试a");

	//第二个单词
	//单词
	(*p)[1].key = (char *)malloc( strlen("b") + 1  );
	memset( (*p)[1].key, 0, strlen("b") + 1);
	strcpy( (*p)[1].key, "b");

	//对应的解析
	(*p)[1].content = (char *)malloc( strlen("测试b") + 1  );
	memset( (*p)[1].content, 0, strlen("测试b") + 1);
	strcpy( (*p)[1].content, "测试b");

	//第三个单词
	//单词
	(*p)[2].key = (char *)malloc( strlen("c") + 1  );
	memset( (*p)[2].key, 0, strlen("c") + 1);
	strcpy( (*p)[2].key, "c");

	//对应的解析
	(*p)[2].content = (char *)malloc( strlen("测试c") + 1  );
	memset( (*p)[2].content, 0, strlen("测试c") + 1);
	strcpy( (*p)[2].content, "测试c");



	return 3;
}

void free_dict( struct dict *p, int n)
{
	//先释放成员
	int  i = 0;
	for( i = 0; i < n; ++i)
	{
		if(  p[i].key != NULL)
		{
			free( p[i].key );
		}
		if( p[i].content != NULL)
		{
			free( p[i].content );
		}
	}
	
	//循环外面
	free(p);

}

int search_dict(struct dict *p, int n, char *key, char *content)
{
	int i = 0;
	for( i = 0; i < n; ++i)
	{
		if( 0 == strcmp(key, p[i].key ) )
		{
			strcpy(content, p[i].content);
			return 0;
		}
	}

	return -1;
}


int main()
{
	struct dict * p;
	//初始化，堆区分配好空间，文件读取内容，存放
	int n = init_dict( &p ); //返回值为单词个数
	if(n == 0)
	{
		return -1;
	}

	//如果返回0， 说明有，如果返回-1，说明没有这个单词
	//如果有内容，查询后的解析放在 content数组中
	char content[1024] = {0};
	int ret = search_dict( p, n, "c", content );
	if( ret == 0)
	{
		printf("content = %s\n", content);
	}


	//释放堆区的空间
	free_dict( p, n); 
	


	return 0;
}


