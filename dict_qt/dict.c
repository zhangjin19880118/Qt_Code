
#include "dict.h"

#include <stdlib.h>
#include <string.h>



void format_string(char *str)//去掉字符串结尾的回车，空格字符
{
    int i = strlen(str) - 1;
    for( ; i >= 0; i--)
	{
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\r')
		{
			str[i + 1] = '\0';
			break;
		}
	}	
}

int get_dict_size(FILE *pfile)//得到字典文件中词条总数
{
	if (pfile == NULL)
		return 0;

	int i = 0;
	char buf[2048];
	while (!feof(pfile))
	{
		fgets(buf, sizeof(buf), pfile);
		fgets(buf, sizeof(buf), pfile);
		i++;//读取两行后，计数器加1
	}
	return i;
}

//打开字典文件，并读取文件内容
int open_dict(struct dict **p, const char *dict_filename)
{
	FILE *pfile = fopen(dict_filename, "r");
	if (pfile == NULL)
		return 0;//打开文件失败，函数返回

	int dict_size = get_dict_size(pfile);//得到字典文件中词条总数
	if (dict_size == 0)
		return 0;

	*p = (struct dict *)malloc(sizeof(struct dict) * dict_size);//根据字典文件词条总数分配内存
	memset(*p, 0, sizeof(struct dict) * dict_size);//将分配内存初始化为0

	char buf[2048] = { 0 };
	size_t len = 0;
	int i = 0;
	fseek(pfile, 0L, SEEK_SET);//设置读取位置为字典文件开始
	while (!feof(pfile))//循环读取文件，直到文件末尾
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);//读取文件一行
		len = strlen(buf);//得到读取到字符串长度
		if (len > 0)
		{
			(*p)[i].key = (char *)malloc(len);//根据字符串长度分配内存
			memset((*p)[i].key, 0, len);
			format_string(buf);//去掉字符串结尾的空格和回车
			strcpy((*p)[i].key, &buf[1]);//将读取到的内容拷贝到key中
		}

		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);
		len = strlen(buf);
		if (len > 0)
		{
			(*p)[i].content = (char *)malloc(len);
			memset((*p)[i].content, 0, len);
			strcpy((*p)[i].content, &buf[6]);
		}
		i++;
	}
	fclose(pfile);//关闭字典文件

	return i;//返回读取到的字典词条数
}

//根据关键字key,在字典中查找内容
int search_dict(const struct dict *p, int size, const char *key, char *content)
{
	int i = 0;
	for (i = 0; i < size; i++)//遍历字典
	{
		if ((p[i].key == NULL) || (p[i].content == NULL))
			continue;

		if (strcmp(p[i].key, key) == 0)
		{
			strcpy(content, p[i].content);
			return 1;//找到符合条件记录，返回1
		}
	}
	return 0;//没有找到符合条件记录，返回0
}

//释放内存
void free_dict(struct dict *p, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)//循环释放key与content成员内存
	{
		if (p[i].key)
			free(p[i].key);
		if (p[i].content)
			free(p[i].content);
	}
	free(p);//释放p内存
}
