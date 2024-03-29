// list_utils.c
#include "list_utils.h"
#include "graphics.h"
#include <time.h>
int *generate_random_list(int size, int region_width)
{
    int *list = (int *)malloc(size * sizeof(int));

    // 使用当前时间作为随机种子
    srand(time(NULL));

    // 填充随机数据
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % 150;
    }
    return list;
}
