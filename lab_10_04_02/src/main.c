#include <stdlib.h>
#include <stdio.h>
#include "logger.h"
#include "list.h"
#include "my_error.h"
#include "funcs.h"

int main(void)
{
    int res = menu();

    INFO_PRINT("Res: %d\n", res);

    return res;
}
