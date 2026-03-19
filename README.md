# Cube3D

## Ray Casting

### What is Ray Casting ?

### The Algorithm

First we need basic informations for the ray casting to work properly such as:

- `MAP\_WIDTH`
- `MAP\_HEIGHT`
- `SCREEN\_WIDTH`
- `SCREEN\_HEIGHT`
- `TILE\_SIZE` = min($\frac{SCREEN\_WIDTH}{MAP\_WIDTH}, \frac{SCREEN\_HEIGHT}{MAP\_HEIGHT})$
- PI

#### Goal

Because the map is flat and suronded by walls. When you look in front of you, you can only see 3 things. The sky, a wall and the floor.

The goal is to draw a like and depending on the distance we met an wall the wall part will be smaller or bigger. The sky and floor part will always be the same lenght. Then we repeat this process for the entire `SCREE\_WIDTH`

For simplification a tile is 1*1 units the walls height is 2 so the floor hight is 0, ceiling height is 2 and camera hight is 1.

the formula to cut the vertical line in 3 is:

$low = \frac{SCREEN\_HEIGHT}{2} - \frac{TILE\_SIZE}{2} * \frac{d_1}{d_2}\\$
$higth = \frac{SCREEN\_HEIGHT}{2} + \frac{TILE\_SIZE}{2} * \frac{d_1}{d_2}\\$

If no wall are met the value return is `INFINITY`¹

1: The INFINITY macro expands to the compiler built-in function __builtin_inff(). It represents positive mathematical infinity and typically evaluates to a constant expression of type float.
