# Ray Casting Algorithm

This project implements a ray casting algorithm for a 2D game. The algorithm is used to determine the distance from the player to the nearest wall in a given direction.

## Algorithm Steps

1. **Find the coordinate of the first intersection point.**
2. **Find y and x step (the distance between the intersection points).**
3. **Convert intersection point (x, y) into map index [i][j].**
   - If the intersection hits a wall, stop the loop.
   - Else, find the next intersection point.
4. **Calculate the distance between the player and the intersection point.**

## Functions

### `normalize_angle`

```c
double normalize_angle(double angle)
Normalizes the given angle to be within the range [0, 2 * PI)
```

### `calculate_distance`
```c
float calculate_distance(t_data *data, float angle)
Calculates the distance to the nearest intersection point in the given direction
```
### `start_h_y`
```c
void start_h_y(t_data *data, float angl, float *h_y)
Determines the starting y-coordinate for horizontal intersections based on the ray's angle
```
### `start_v_x`
```c
void start_h_y(t_data *data, float angl, float *h_y)
Determines the starting x-coordinate for vertical intersections based on the ray's angle
```
### `get_h_inter`
```c
float get_h_inter(t_data *data, float angl)
Gets the horizontal intersection point for a given angle. It calculates the x and y steps, iterates through potential intersection points, and returns the distance to the nearest wall
```
### `get_v_inter`
```c
float get_v_inter(t_data *data, float angl)
Gets the vertical intersection point for a given angle. It calculates the x and y steps, iterates through potential intersection points, and returns the distance to the nearest wall
```

### resources ###
1.  **Basic Trigonometry ==> https://www.youtube.com/watch?v=eqde2Ez276k**