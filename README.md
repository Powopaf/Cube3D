*This project has been created as part of the 42 curriculum by pifourni and sbrochar.*

# Cube3D

**Description**

Cube3D is a compact Wolfenstein-style raycaster written in C using MiniLibX. The goal is to implement basic 3D rendering from a 2D map (wall casting, sprites, and simple player movement) as a learning project for the 42 curriculum.

**Instructions**

- Install dependencies (Debian/Ubuntu):

```sh
sudo apt update
sudo apt install xorg libxext-dev zlib1g-dev libbsd-dev
```

- Build: `make`
- Run: `./cub3D path/to/map.cub`
- Maps live in the `Map/` folder; a valid map must end with `.cub` and include texture paths and floor/ceiling colors.

**Resources**

- Raycasting primer: https://lodev.org/cgtutor/raycasting.html
- MiniLibX docs: https://harm-smits.github.io/42docs/libs/minilibx

**AI usage**

AI-assisted edits were used to refine and shorten this README and to tidy wording. Code changes (small key-mapping update) were done manually in the source.

If you want the README expanded with usage examples, map format details, or development notes, tell me which sections to add.

**Technical details**

- Rendering approach: the engine casts one 2D ray per screen column from the player position to find the first wall intersection. The distance to that hit determines the vertical slice height drawn for that column; textures and wall face are selected based on the hit.
- Main data: `t_p` (player) holds position (`x,y`), view `angle`, `speed`, the parsed `map`, `tile_size`, pointers to `t_map` (map/meta) and `t_data` (MLX image/window). See `Include/struct.h` for full fields.
- Core files:
	- `main.c` — program start, argument parsing and MLX init.
	- `Parser/` — read `.cub` files and load textures/colors into `t_map`.
	- `Render/casting.c`, `Render/ray.c` — ray traversal and wall-slice drawing.
	- `Render/Sprite/sprite.c` — sprite ordering and drawing.
	- `Src/Game/key.c` and `Include/Game/key.h` — input handling and movement (WASD/rotation). 
- Frame loop: each frame the code updates player state from input flags, runs the renderer to fill an off-screen image, then pushes that image to the MLX window with `mlx_put_image_to_window`.
- Collision: movement attempts update `x,y` then check the map cell at the new tile; moves are reverted on wall collision.

This section is intentionally concise — tell me if you want a deeper walkthrough (ray math, DDA steps, or texture sampling). 
