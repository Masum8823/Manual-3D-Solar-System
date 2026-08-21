# Manual 3D Solar System using OpenGL

An interactive 3D Solar System developed using C++ and OpenGL/GLUT for CG Lab.

## Technologies

- C++
- OpenGL
- GLUT / FreeGLUT

## Project Goal

The project demonstrates fundamental computer graphics concepts through a manually implemented 3D Solar System.

## Planned Concepts

- 3D object modeling
- Transformations
- Rotation
- Translation
- Scaling
- Mirroring
- Perspective projection
- Camera control
- Animation
- Lighting
- Keyboard interaction

## Development Progress

This project is being developed step by step to understand and implement each computer graphics concept separately.

---

# Manual 3D Solar System

A Computer Graphics Lab project developed using OpenGL and GLUT.

## Step 01 — OpenGL Project Initialization

In this step, the basic OpenGL/GLUT project structure was created.

### Concepts Learned

- GLUT window initialization
- OpenGL display callback
- Basic OpenGL initialization
- Background color
- Main rendering loop
- Window creation and configuration

### Current Progress

At this stage, the project contains only a basic OpenGL window with a dark background.

No 3D objects or animation have been added yet.

---

## Step 02 — Custom 3D Sphere

In this step, a custom 3D sphere was implemented without using GLUT's built-in sphere function.

### Concepts Learned

- Spherical coordinate system
- Latitude and longitude
- Trigonometric functions
- 3D vertex generation
- `GL_QUAD_STRIP`
- Surface normals
- Mathematical construction of 3D objects

### Sphere Generation

The sphere vertices are calculated using:

x = cos(latitude) × cos(longitude)

y = cos(latitude) × sin(longitude)

z = sin(latitude)

The calculated coordinates are then multiplied by the sphere radius.

### Current Progress

The project now contains a mathematically generated 3D sphere.

---