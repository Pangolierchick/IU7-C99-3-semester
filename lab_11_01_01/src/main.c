#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "my_snprintf.h"
#include "mystring.h"

#define BUFF_LEN                50UL

int main(void)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%s%x%c%s%d\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(NULL, 0, msg, -0x7fffffff, "|||", 0, '/', "|||", INT_MIN);
    std_res = snprintf(NULL, 0, msg, -0x7fffffff, "|||", 0, '/', "|||", INT_MIN);

    printf("a: %s\n", my_buff);
    printf("b: %s\n", std_buff);
    printf("%d %d\n", my_res, std_res);

    return 0;
}
