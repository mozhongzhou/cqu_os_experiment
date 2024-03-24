// list_utils.h
#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include <stdlib.h>

#define N 7           // 需要生成的列表数量和线程数量
#define LIST_SIZE 300 // 每个列表的大小
#define GAP 2         // 每个条形的间隔

// 生成一个随机的非负整数列表
int *generate_random_list(int size, int region_width);

#endif // LIST_UTILS_H