
# C++ SFML Puzzle Game

This is a grid-based puzzle engine built with C++17 and SFML, inspired by the classic mechanics of Sokoban.

## How to Run

Follow these steps in your terminal to compile and launch the game with a specific level:

1. **Build:**
   ```bash
   make
   

2. **Run (Providing a level file):**
   ```bash
   ./Sokoban.exe levels/level1.txt
   ```
   *Note: Use `./Sokoban levels/level1.txt` if you are on Linux.*

## Gameplay and Controls
* **Movement:** Use **W, A, S, D** keys to move.
* **Goal:** Push all boxes onto the designated target points to complete the level.
* **Mechanics:** You can only push one box at a time; pulling is not allowed.

## Creating New Levels

Levels are loaded from `.txt` files located in the `levels/` directory. To create a custom map, use the following format:

* **Line 1:** Map Width and Height (e.g., `10 10`)
* **Subsequent Lines:** The map layout using specific characters.

### Map Legend:
* `#` : Wall
* `!` : Player starting position
* `o` : Pushable box
* `?` : Target point
* ` ` (Space) : Floor

### Example Map File (level_test.txt):
```text
7 5
#######
#     #
# !o? #
#     #
#######
```

## Project Structure
* **main.cpp**: Entry point, game loop, and input handling.
* **grid.cpp/hpp**: Handles map data, rendering layers, and win-condition logic.
* **sprite.cpp/hpp**: Manages movement physics and box-pushing interactions.
* **textures.cpp/hpp**: Global texture management and asset optimization.
```
