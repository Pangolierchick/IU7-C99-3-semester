#include <stdio.h>
#include "funcs.h"
#include "list.h"

int main(void)
{
    const char *in_file  = "in.txt";
    const char *out_file = "out.txt";
    
    
    list_t *list = init_list();

    if (list == NULL)
        return 1;

    FILE *fi = fopen(in_file, "r");
    FILE *fo = fopen(out_file, "w");

    if (fi == NULL)
    {
        clean_list(list);
        return 1;
    }
    
    if (read_from_file(fi, list))
    {
        clean_list(list);
        fclose(fi);
        fclose(fo);
    }

    list = reverse_list(list);

    write_to_file(fo, list);

    clean_list(list);
    fclose(fi);
    fclose(fo);

    return 0;
}
