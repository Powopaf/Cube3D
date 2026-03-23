*This project has been created as part of the 42 curriculum by pifourni and sbrochar.*

# Cube3D

## Description

Cube3D is a first-person 3D rendering project built in C as part of the 42 curriculum.
It uses a classic raycasting approach with MiniLibX to project a 2D grid map into a pseudo-3D scene, including wall-slice rendering, face-based wall coloring, and basic floor/ceiling drawing.
The project is currently in a prototype stage, with rendering logic in place and parser/game features to be expanded.

## Instructions

To build the project make install those librairies: \
`sudo apt update && sudo apt install xorg libxext-dev zlib1g-dev libbsd-dev`
They are needed for the compilation of the minilibx. Then `make` and you can launch the game with `./cub3D`

### Map

The map must end in `.cub` here is a valid map :

```sh
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Raycating explanation

### Definition

Ray casting is a rendering technique where you shoot one ray per screen column from the player/camera into a 2D map to find the first wall hit, then use that hit distance to draw a vertical wall slice with the correct height.

In short:

Closer hit = taller wall slice
Farther hit = shorter wall slice

### How it works

## Ressources

https://lodev.org/cgtutor/raycasting.html \
https://timallanwheeler.com/blog/2023/04/01/wolfenstein-3d-raycasting-in-c/ \
https://harm-smits.github.io/42docs/libs/minilibx
