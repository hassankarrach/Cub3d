#include "../../includes/utils.h"

double get_time_in_seconds(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec + (time.tv_usec / 1000000.0));
}