
````markdown
*This project has been created as part of the 42 curriculum by hkonte, ikhelil.*

# cub3D

## Description

`cub3D` is a small program that creates a fake 3D view from a 2D map.

The idea is simple:  
we have a maze seen from above (2D), and the program gives the illusion that we are inside it, like in a first-person game.

To do that, we use a method called **raycasting**:
the program sends lines (rays) in front of the player and checks where they hit a wall, then draws the walls based on the distance.

The rendering is done using the MiniLibX graphical library.

---

## What the program does

- Reads a `.cub` file (the map + textures + colors)
- Checks if everything is valid
- Opens a window and displays the scene
- Renders walls with different textures depending on orientation
- Handles floor and ceiling colors
- Lets the player move inside the map

---

## How it works

For each frame:
- The program sends rays from the player
- Each ray moves through the map using the **DDA algorithm**
- When a wall is hit, the distance is calculated
- A vertical line is drawn on the screen

This creates a 3D effect from a 2D map.

---

## Controls

- `W` / `S` → move forward / backward  
- `A` / `D` → move left / right  
- `←` / `→` → look left / right  
- `ESC` to quit  

---

## How to run

```bash
make
./cub3D maps/good.cub
````

### Requirements

* Linux
* `cc`
* X11 (for MiniLibX)
* `make`

---

## Map file (.cub)

The file contains:

### Textures

```
NO path_to_texture
SO path_to_texture
WE path_to_texture
EA path_to_texture
```

### Colors

```
F 220,100,0
C 225,30,0
```

### Map example

```
111111
100001
1000N1
111111
```

* `1` = wall
* `0` = empty space
* `N/S/E/W` = player position

---

## Rules checked by the program

* There must be **only one player**
* The map must be **closed (surrounded by walls)**
* All textures must exist and be readable
* Colors must be valid (0–255)
* No invalid characters are allowed
* The file must end with `.cub`

If something is wrong, the program exits with:

```
Error
```

and a clear message explaining the issue.

---

## Project files

* `main.c` → program entry
* `map.c` → parsing the `.cub` file
* `check.c` → map validation
* `backtrack.c` → raycasting (DDA)
* `render.c` → drawing the frame
* `player.c` → movement and rotation
* `game.c` → window and main loop
* `free.c` → memory cleanup

---

## Technical Notes

* Rendering is done with MiniLibX
* Raycasting is implemented using the DDA algorithm
* Collision detection prevents walking through walls
* Memory is properly freed to avoid leaks

---

## Resources

* [https://lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html)
* MiniLibX (42 documentation)
* `man open`, `read`, `malloc`, `free`, `math`


## Tests

We tested:

* valid maps
* invalid maps
* missing textures
* wrong characters
* multiple or missing player
* non-closed maps
* memory leaks (Valgrind)


