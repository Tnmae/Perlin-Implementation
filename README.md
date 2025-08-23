# 🌄 Terrain Generation in C++ with OpenGL

This project implements multiple terrain generation algorithms in C++ using OpenGL, fully written from scratch without relying on external terrain libraries. The goal is to demonstrate classic procedural terrain techniques, visualize their differences, and provide a learning resource for graphics and game development.

## ✨ Features

- ### Midpoint Displacement
  - Recursive fractal algorithm that generates realistic heightmaps.

  - Produces natural, mountainous terrain with controllable roughness.

- ### Fault Formation
  - Geologically inspired terrain generation technique.

  - Creates sharp ridges and valleys by iteratively "faulting" the terrain grid.

- ### Fractal Perlin Noise
  - Implementation of Perlin Noise from scratch (gradient noise).

  - Used in fractal form (multiple octaves) to create smooth, natural terrains.

- ### fBm with Value Noise
  - Implementation of Value Noise (smoothed lattice-based noise).

  - Combined in fractal Brownian motion (fBm) to generate terrain with finer details.

- ### FIR Filtering (Smoothing)
  - Implements a Finite Impulse Response (FIR) filter to post-process generated heightmaps.

  - Helps smooth out sharp edges and reduce high-frequency noise.

  - Useful for polishing rough terrains from fault formation or midpoint displacement.

- ### Heightmap Loading
  - Supports loading grayscale images as heightmaps.

  - White pixels = high elevation, black pixels = low elevation.

  - Enables importing terrain from external tools (e.g., World Machine, Gaea, Photoshop).

## 🛠️ Tech Stack

- C++17

- OpenGL 3.3+ Core Profile

- GLFW – window & input handling

- GLAD – OpenGL function loader

- stb_image – image loading (used for heightmaps & textures)

- Assimp – (optional, for model extensions)

## 📂 Project Structure

```
terrain_gen/
├── include/         # Header files (noise, terrain, basic utility functions etc.)
├── src/             # Source files
│   ├── main.cpp     # Entry point
│   ├── terrain.cpp  # Terrain mesh generation & rendering
│   ├── noise.cpp    # Noise algorithms (Perlin, Value, value noise implementation etc.)
│   ├── heightmap.cpp  # Terrain generation from image heightmaps
├── resources/
│   ├── models/
│   ├── textures/
│   ├── shaders/
├── CMakeLists.txt   # Build configuration
├── ./build.sh       # build script
└── README.md        # Documentation

```

## 🚀 Build & Run

```
https://github.com/Tnmae/Perlin-Implementation.git
cd Perlin-Implementation
./build.sh
```

## 🎮 Controls

- **W/A/S/D** – Move camera.

- **Mouse** – Look around.

- **Ctrl/Space** - For switching in negative/positive y-axis.

- **Q** - for switching between wireframe and fill mode.

## 📸 Preview
