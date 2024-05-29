/**
 * vim: filetype=c:fenc=utf-8:ts=4:et:sw=4:sts=4
 */

#include <sys/types.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>

#define FREE 0
#define USED 1

struct chunk
{
  char signature[4];  /* "OSEX" */
  struct chunk *next; /* ptr. to next chunk */
  int state;          /* 0 - free, 1 - used */
  int size;           /* size of this chunk */
};

static struct chunk *chunk_head = NULL;

void *g_heap;
/// start ///////////////////////////////////////
static volatile int lock = 0;
// Simple spinlock functions
void lock_heap()
{
  while (__sync_lock_test_and_set(&lock, 1))
  {
    // spin until the lock is acquired
  }
}

void unlock_heap()
{
  __sync_lock_release(&lock);
}

//////////////////////////finish///////////

void *tlsf_create_with_pool(uint8_t *heap_base, size_t heap_size)
{
  chunk_head = (struct chunk *)heap_base;
  strncpy(chunk_head->signature, "OSEX", 4);
  chunk_head->next = NULL;
  chunk_head->state = FREE;
  chunk_head->size = heap_size;
  return NULL;
}

// to do
// 功能:
// 分配大小为size字节的内存块，并返回块起始地址
// 如果size是0，返回NULL

void *malloc(size_t size)
{
  if (size == 0)
  {
    return NULL;
  }
  lock_heap();
  struct chunk *current = chunk_head;

  while (current)
  {
    if (current->state == FREE && current->size >= size)
    {
      if (current->size > size + sizeof(struct chunk))
      {
        struct chunk *new_chunk = (struct chunk *)((uint8_t *)current + sizeof(struct chunk) + size);
        strncpy(new_chunk->signature, "OSEX", 4);
        new_chunk->next = current->next;
        new_chunk->state = FREE;
        new_chunk->size = current->size - size - sizeof(struct chunk);

        current->next = new_chunk;
        current->size = size;
      }

      current->state = USED;
      unlock_heap();
      return (void *)((uint8_t *)current + sizeof(struct chunk));
    }

    current = current->next;
  }
  unlock_heap();
  return NULL;
}

// to do
// 功能：
// 释放ptr指向的内存块
// 如果ptr是NULL，直接返回

// 提示：
//  怎么根据ptr得到chunk？ struct trunk *achunk = (struct chunk *)(((uint8_t *)ptr) - sizeof(struct chunk));

// 要求：
// 必须验证ptr的有效性
// 判断achunk->signature是否等于“OSEX”
// 必须合并相邻的空闲块

void free(void *ptr)
{
  if (ptr == NULL)
  {
    // 临界区结束
    return;
  }
  lock_heap();
  struct chunk *achunk = (struct chunk *)((uint8_t *)ptr - sizeof(struct chunk));

  if (strncmp(achunk->signature, "OSEX", 4) == 0)
  {
    achunk->state = FREE;

    // Merge with next chunk if it's free
    if (achunk->next && achunk->next->state == FREE)
    {
      achunk->size += sizeof(struct chunk) + achunk->next->size;
      achunk->next = achunk->next->next;
    }

    // Merge with previous chunk if it's free
    struct chunk *current = chunk_head;
    while (current && current->next != achunk)
    {
      current = current->next;
    }
    if (current && current->state == FREE)
    {
      current->size += sizeof(struct chunk) + achunk->size;
      current->next = achunk->next;
    }
  }
  unlock_heap();
}

// to do
// 功能
// 为num个元素的数组分配内存，每个元素占size字节
// 把分配的内存初始化成0

void *calloc(size_t num, size_t size)
{

  size_t total_size = num * size;
  void *ptr = malloc(total_size);
  if (ptr)
  {
    memset(ptr, 0, total_size);
  }

  return ptr;
}

// to do
// 功能
// 重新分配oldptr指向的内存块，新内存块有size字节
// 如果oldptr是NULL，该函数等价于malloc(size)
// 如果size是0，该函数等价于free(oldptr)

//     把旧内存块的内容复制到新内存块
//     如果新内存块比较小，只复制旧内存块的前面部分
//     如果新内存块比较大，复制整个旧内存块，而且不用初始化多出来的那部分
//     如果新内存块还在原来的地址oldptr，返回oldptr；否则返回新地址
//     要求
//     必须验证oldptr的有效性
//     必须合并相邻的空闲块

void *realloc(void *oldptr, size_t size)
{

  if (oldptr == NULL)
  {

    return malloc(size);
  }
  if (size == 0)
  {
    free(oldptr);

    return NULL;
  }
  lock_heap();
  struct chunk *achunk = (struct chunk *)((uint8_t *)oldptr - sizeof(struct chunk));

  if (strncmp(achunk->signature, "OSEX", 4) != 0)
  {
    unlock_heap();
    return NULL;
  }

  if (achunk->size >= size)
  {
    if (achunk->size > size + sizeof(struct chunk))
    {
      struct chunk *new_chunk = (struct chunk *)((uint8_t *)achunk + sizeof(struct chunk) + size);
      strncpy(new_chunk->signature, "OSEX", 4);
      new_chunk->next = achunk->next;
      new_chunk->state = FREE;
      new_chunk->size = achunk->size - size - sizeof(struct chunk);

      achunk->next = new_chunk;
      achunk->size = size;
    }
    unlock_heap();
    return oldptr;
  }
  unlock_heap();
  void *newptr = malloc(size);
  if (newptr)
  {
    memcpy(newptr, oldptr, achunk->size);
    free(oldptr);
  }

  return newptr;
}

/*************D O  N O T  T O U C H  A N Y T H I N G  B E L O W*************/
static void tsk_malloc(void *pv)
{
  int i, c = (int)pv;
  char **a = malloc(c * sizeof(char *));
  for (i = 0; i < c; i++)
  {
    a[i] = malloc(i + 1);
    a[i][i] = 17;
  }
  for (i = 0; i < c; i++)
  {
    free(a[i]);
  }
  free(a);

  task_exit(0);
}

#define MESSAGE(foo) printf("%s, line %d: %s", __FILE__, __LINE__, foo)
void test_allocator()
{
  char *p, *q, *t;

  MESSAGE("[1] Test malloc/free for unusual situations\r\n");

  MESSAGE("  [1.1]  Allocate small block ... ");
  p = malloc(17);
  if (p == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  p[0] = p[16] = 17;
  printf("PASSED\r\n");

  MESSAGE("  [1.2]  Allocate big block ... ");
  q = malloc(4711);
  if (q == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  q[4710] = 47;
  printf("PASSED\r\n");

  MESSAGE("  [1.3]  Free big block ... ");
  free(q);
  printf("PASSED\r\n");

  MESSAGE("  [1.4]  Free small block ... ");
  free(p);
  printf("PASSED\r\n");

  MESSAGE("  [1.5]  Allocate huge block ... ");
  q = malloc(32 * 1024 * 1024 - sizeof(struct chunk));
  if (q == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  q[32 * 1024 * 1024 - sizeof(struct chunk) - 1] = 17;
  free(q);
  printf("PASSED\r\n");

  MESSAGE("  [1.6]  Allocate zero bytes ... ");
  if ((p = malloc(0)) != NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  printf("PASSED\r\n");

  MESSAGE("  [1.7]  Free NULL ... ");
  free(p);
  printf("PASSED\r\n");

  MESSAGE("  [1.8]  Free non-allocated-via-malloc block ... ");
  int arr[5] = {0x55aa4711, 0x5a5a1147, 0xa5a51471, 0xaa551741, 0x5aa54171};
  free(&arr[4]);
  if (arr[0] == 0x55aa4711 &&
      arr[1] == 0x5a5a1147 &&
      arr[2] == 0xa5a51471 &&
      arr[3] == 0xaa551741 &&
      arr[4] == 0x5aa54171)
  {
    printf("PASSED\r\n");
  }
  else
  {
    printf("FAILED\r\n");
    return;
  }

  MESSAGE("  [1.9]  Various allocation pattern ... ");
  int i;
  size_t pagesize = sysconf(_SC_PAGESIZE);
  for (i = 0; i < 7411; i++)
  {
    p = malloc(pagesize);
    p[pagesize - 1] = 17;
    q = malloc(pagesize * 2 + 1);
    q[pagesize * 2] = 17;
    t = malloc(1);
    t[0] = 17;
    free(p);
    free(q);
    free(t);
  }

  char **a = malloc(2741 * sizeof(char *));
  for (i = 0; i < 2741; i++)
  {
    a[i] = malloc(i + 1);
    a[i][i] = 17;
  }
  for (i = 0; i < 2741; i++)
  {
    free(a[i]);
  }
  free(a);

  if (chunk_head->next != NULL || chunk_head->size != 32 * 1024 * 1024)
  {
    printf("FAILED\r\n");
    return;
  }
  printf("PASSED\r\n");

  MESSAGE("  [1.10] Allocate using calloc ... ");
  int *x = calloc(17, 4);
  for (i = 0; i < 17; i++)
    if (x[i] != 0)
    {
      printf("FAILED\r\n");
      return;
    }
    else
      x[i] = i;
  free(x);
  printf("PASSED\r\n");

  MESSAGE("[2] Test realloc() for unusual situations\r\n");

  MESSAGE("  [2.1]  Allocate 17 bytes by realloc(NULL, 17) ... ");
  p = realloc(NULL, 17);
  if (p == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  p[0] = p[16] = 17;
  printf("PASSED\r\n");
  MESSAGE("  [2.2]  Increase size by realloc(., 4711) ... ");
  p = realloc(p, 4711);
  if (p == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  if (p[0] != 17 || p[16] != 17)
  {
    printf("FAILED\r\n");
    return;
  }
  p[4710] = 47;
  printf("PASSED\r\n");

  MESSAGE("  [2.3]  Decrease size by realloc(., 17) ... ");
  p = realloc(p, 17);
  if (p == NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  if (p[0] != 17 || p[16] != 17)
  {
    printf("FAILED\r\n");
    return;
  }
  printf("PASSED\r\n");

  MESSAGE("  [2.4]  Free block by realloc(., 0) ... ");
  p = realloc(p, 0);
  if (p != NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  else
    printf("PASSED\r\n");

  MESSAGE("  [2.5]  Free block by realloc(NULL, 0) ... ");
  p = realloc(realloc(NULL, 0), 0);
  if (p != NULL)
  {
    printf("FAILED\r\n");
    return;
  }
  else
    printf("PASSED\r\n");

  MESSAGE("[3] Test malloc/free for thread-safe ... ");

  int t1, t2;
  char *s1 = malloc(1024 * 1024),
       *s2 = malloc(1024 * 1024);
  t1 = task_create(s1 + 1024 * 1024, tsk_malloc, (void *)5000);
  t2 = task_create(s2 + 1024 * 1024, tsk_malloc, (void *)5000);
  task_wait(t1, NULL);
  task_wait(t2, NULL);
  free(s1);
  free(s2);

  if (chunk_head->next != NULL || chunk_head->size != 32 * 1024 * 1024)
  {
    printf("FAILED: ");
    if (chunk_head->next != NULL)
    {
      printf("Next chunk is not NULL. ");
    }
    if (chunk_head->size != 32 * 1024 * 1024)
    {
      printf("Chunk size is not 32MB.");
    }
    printf("\n");
    return;
  }

  printf("PASSED\r\n");
}
/*************D O  N O T  T O U C H  A N Y T H I N G  A B O V E*************/
// [1] Test malloc/free for unusual situations:

// 1.1: 分配一个小块内存并释放。
// 1.2: 分配一个大块内存并释放。
// 1.3: 释放之前分配的大块内存。
// 1.4: 释放之前分配的小块内存。
// 1.5: 分配一个超大块内存，然后释放。
// 1.6: 尝试分配 0 字节内存。
// 1.7: 尝试释放 NULL 指针。
// 1.8: 尝试释放非由 malloc 分配的内存块。
// 1.9: 分配一系列不同大小的内存块并释放。
// 1.10: 使用 calloc 分配内存并检查初始化是否正确。
// [2] Test realloc() for unusual situations:

// 2.1: 使用 realloc 分配 17 字节内存并检查初始化。
// 2.2: 使用 realloc 增加已分配内存的大小，并检查数据是否保留。
// 2.3: 使用 realloc 减小已分配内存的大小，并检查数据是否保留。
// 2.4: 使用 realloc 释放内存。
// 2.5: 使用 realloc 释放 NULL 指针。
// [3] Test malloc/free for thread-safe:

// 使用多线程测试内存分配和释放的线程安全性。