# C++17 & SFML 2D Grid Puzzle Engine (Sokoban) 📦

**Developer:** Mert Emin İlhan  
**Repository:** [https://github.com/mertemin1/puzzlegame](https://github.com/mertemin1/puzzlegame)  

A 2D grid-based puzzle game engine built from scratch using **Modern C++ (C++17)** and the **SFML (Simple and Fast Multimedia Library)**. Inspired by classic *Sokoban* mechanics, the engine features an object-oriented entity/grid architecture, a custom text-based level parser, and a cross-platform `Makefile` build system.

[![Language: C++17](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://isocpp.org/)
[![Library: SFML](https://img.shields.io/badge/Library-SFML-green.svg)](https://www.sfml-dev.org/)
[![Platform: Linux & Windows](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg)](#)

---

## ✨ Technical Features & Architecture

- **Object-Oriented Grid & Entity System:** Encapsulates map layout, rendering layers, and game state validation within `Grid` (`grid.cpp`/`grid.hpp`) while managing entity movement, collision rules, and sprite rendering via `Sprite` (`sprite.cpp`/`sprite.hpp`).
- **Custom Level Parser:** Dynamically constructs 2D game worlds of arbitrary dimensions at runtime by parsing human-readable `.txt` map files passed via command-line arguments.
- **Sokoban Collision & Push Physics:** Implements directional tile-based collision detection—allowing the player to push single boxes onto target coordinates while preventing box pulling or multi-box pushing.
- **Win-Condition State Tracking:** Continuously evaluates target tile occupancy during the game loop; once all boxes (`o`) align with target points (`?`), the engine outputs a completion log (`<level_path> finished. Congratulations`) to the standard output and cleanly terminates the SFML window (`window.close()`).
- **Cross-Platform Build System:** Includes a custom `Makefile` that automatically detects the host OS (`Windows_NT` vs. Linux) and links against the bundled platform-specific SFML headers and binaries (`SFML/windows` or `SFML/linux`).

---

## 🛠️ Tech Stack

- **Language:** C++17 (`g++`)
- **Multimedia & Graphics API:** SFML (Graphics, Window, System modules)
- **Build System:** GNU Make (Cross-platform `Makefile`)

---

## 🚀 Building the Project

Ensure you have **`g++`** (with C++17 support) and **GNU Make** installed on your system. Platform-specific SFML configurations are organized inside the `SFML/` directory.

```bash
# Clone the repository
git clone https://github.com/mertemin1/puzzlegame.git
cd puzzlegame

# Compile the project using Make
make
```

- **On Windows:** Produces `Sokoban.exe` linked against `SFML/windows`.
- **On Linux:** Produces `Sokoban` linked against `SFML/linux`.

---

## 📖 Usage & Gameplay

The executable requires the path to a level configuration file as a command-line argument. Four pre-built levels (`level1.txt` to `level4.txt`) are available in the `levels/` directory.

### Running a Level

- **Linux:**
  ```bash
  ./Sokoban levels/level1.txt
  ```
- **Windows:**
  ```bash
  ./Sokoban.exe levels/level1.txt
  ```

### Controls & Mechanics

| Key | Action |
| :---: | :--- |
| **`W`** | Move Up |
| **`A`** | Move Left |
| **`S`** | Move Down |
| **`D`** | Move Right |

- **Objective:** Push every box onto a designated target tile. When all target tiles are occupied, the level is completed, a congratulatory message is printed to the terminal, and the game window closes automatically.

---

## 🗺️ Custom Level Design Format

You can create custom levels by adding new `.txt` files inside the `levels/` directory:

1. **Header (Line 1):** Two space-separated integers defining the grid's `width` and `height` (e.g., `7 5`).
2. **Grid Layout (Subsequent Lines):** ASCII characters representing the entities on each tile:

| Character | Entity / Tile Type | Description |
| :---: | :--- | :--- |
| `#` | **Wall** | Impassable boundary or obstacle tile (`wall.png`) |
| `!` | **Player** | Starting position of the player character (`character.png`) |
| `o` | **Box** | Pushable crate entity (`box.png`) |
| `?` | **Target** | Goal coordinate where a box must be placed (`target.png`) |
| ` ` *(Space)* | **Floor** | Empty walkable background tile (`floor.png`) |

### Example Level File (`levels/example_level.txt`)

```text
7 5
#######
#     #
# !o? #
#     #
#######
```

---

## 📁 Project Structure

```text
puzzlegame/
├── main.cpp                # Application entry point, CLI parsing, game loop & window termination
├── grid.cpp / grid.hpp     # 2D map parsing, layered rendering & win-condition evaluation
├── sprite.cpp / sprite.hpp # Entity behavior, W/A/S/D input handling & push collision logic
├── Makefile                # OS-aware cross-platform build script (Windows & Linux)
├── levels/                 # Custom ASCII level definition files
│   ├── level1.txt
│   ├── level2.txt
│   ├── level3.txt
│   └── level4.txt
├── src/                    # 2D sprite & tile texture assets
│   ├── box.png
│   ├── character.png
│   ├── floor.png
│   ├── target.png
│   └── wall.png
└── SFML/                   # Platform-specific SFML headers and library files
    ├── linux/
    └── windows/
```

---

## 📄 License

This project is open-source and available under the MIT License.