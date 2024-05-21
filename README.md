# 操作系统第四次实验报告

20220815 2024/4/28

## 一、任务记录

## 二、代码理解

## 三、进步

## 四、参考文献

启用你的内存分配器
修改文件 userapp/Makefile，把
COBJS+= lib/malloc.o ../lib/tlsf/tlsf.o
改为
COBJS+= myalloc.o

---

在 main 函数中调用 test_allocator();

---

/******\*******D O N O T T O U C H A N Y T H I N G B E L O W******\*******/
static void tsk_malloc(void _pv)
{
int i, c = (int)pv;
char \*\*a = malloc(c _ sizeof(char \*));
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

#define MESSAGE(foo) printf("%s, line %d: %s", **FILE**, **LINE**, foo)
void test_allocator()
{
char *p, *q, \*t;

MESSAGE("[1] Test malloc/free for unusual situations\r\n");

MESSAGE(" [1.1] Allocate small block ... ");
p = malloc(17);
if (p == NULL)
{
printf("FAILED\r\n");
return;
}
p[0] = p[16] = 17;
printf("PASSED\r\n");

MESSAGE(" [1.2] Allocate big block ... ");
q = malloc(4711);
if (q == NULL)
{
printf("FAILED\r\n");
return;
}
q[4710] = 47;
printf("PASSED\r\n");

MESSAGE(" [1.3] Free big block ... ");
free(q);
printf("PASSED\r\n");

MESSAGE(" [1.4] Free small block ... ");
free(p);
printf("PASSED\r\n");

MESSAGE(" [1.5] Allocate huge block ... ");
q = malloc(32 _ 1024 _ 1024 - sizeof(struct chunk));
if (q == NULL)
{
printf("FAILED\r\n");
return;
}
q[32 * 1024 * 1024 - sizeof(struct chunk) - 1] = 17;
free(q);
printf("PASSED\r\n");

MESSAGE(" [1.6] Allocate zero bytes ... ");
if ((p = malloc(0)) != NULL)
{
printf("FAILED\r\n");
return;
}
printf("PASSED\r\n");

MESSAGE(" [1.7] Free NULL ... ");
free(p);
printf("PASSED\r\n");

MESSAGE(" [1.8] Free non-allocated-via-malloc block ... ");
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

MESSAGE(" [1.9] Various allocation pattern ... ");
int i;
size_t pagesize = sysconf(\_SC_PAGESIZE);
for (i = 0; i < 7411; i++)
{
p = malloc(pagesize);
p[pagesize - 1] = 17;
q = malloc(pagesize _ 2 + 1);
q[pagesize _ 2] = 17;
t = malloc(1);
t[0] = 17;
free(p);
free(q);
free(t);
}

char \*_a = malloc(2741 _ sizeof(char \*));
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

if (chunk_head->next != NULL || chunk_head->size != 32 _ 1024 _ 1024)
{
printf("FAILED\r\n");
return;
}
printf("PASSED\r\n");

MESSAGE(" [1.10] Allocate using calloc ... ");
int \*x = calloc(17, 4);
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

MESSAGE(" [2.1] Allocate 17 bytes by realloc(NULL, 17) ... ");
p = realloc(NULL, 17);
if (p == NULL)
{
printf("FAILED\r\n");
return;
}
p[0] = p[16] = 17;
printf("PASSED\r\n");
MESSAGE(" [2.2] Increase size by realloc(., 4711) ... ");
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

MESSAGE(" [2.3] Decrease size by realloc(., 17) ... ");
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

MESSAGE(" [2.4] Free block by realloc(., 0) ... ");
p = realloc(p, 0);
if (p != NULL)
{
printf("FAILED\r\n");
return;
}
else
printf("PASSED\r\n");

MESSAGE(" [2.5] Free block by realloc(NULL, 0) ... ");
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
char _s1 = malloc(1024 _ 1024),
_s2 = malloc(1024 _ 1024);
t1 = task_create(s1 + 1024 _ 1024, tsk_malloc, (void _)5000);
t2 = task_create(s2 + 1024 _ 1024, tsk_malloc, (void _)5000);
task_wait(t1, NULL);
task_wait(t2, NULL);
free(s1);
free(s2);

if (chunk_head->next != NULL || chunk_head->size != 32 _ 1024 _ 1024)
{
printf("FAILED\r\n");
return;
}
printf("PASSED\r\n");
}
/******\*******D O N O T T O U C H A N Y T H I N G A B O V E******\*******/
