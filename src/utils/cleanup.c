#include "../../includes/utils.h"

int    ft_error(char *error_msg)
{
    write(2, "ERROR: ", 7);
    printf("%s\n", error_msg);
    exit (1);
}