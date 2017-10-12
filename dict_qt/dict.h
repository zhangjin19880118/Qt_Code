//防止头文件重复包含
#pragma once
#include <stdio.h>  //FILE


struct dict
{
    char *key;
    char *content;
};

#ifdef __cplusplus
extern "C" {
#endif

void format_string(char *str);//去掉字符串结尾的回车，空格字符


int get_dict_size(FILE *pfile);//得到字典文件中词条总数


//打开字典文件，并读取文件内容
int open_dict(struct dict **p, const char *dict_filename);

//根据关键字key,在字典中查找内容
int search_dict(const struct dict *p, int size, const char *key, char *content);


//释放内存
void free_dict(struct dict *p, int size);

#ifdef __cplusplus
}
#endif
