#include "../includes/cub3d.h"

int isRayFacingDown(float rayAngle)
{
    return (rayAngle > 0 && rayAngle < M_PI);
}

int isRayFacingUp(float rayAngle)
{
    return !isRayFacingDown(rayAngle);
}

int isRayFacingRight(float rayAngle)
{
    return (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
}

int isRayFacingLeft(float rayAngle)
{
    return !isRayFacingRight(rayAngle);
}
