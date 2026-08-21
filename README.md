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

## Step 03 — Manual Orbital Paths

In this step, manual circular orbital paths were added using mathematical equations.

### Concepts Learned

- Circle equation
- Trigonometric functions
- `GL_LINE_LOOP`
- X-Z plane
- Manual geometric path generation
- Reusable drawing functions

### Orbit Generation

The orbital path is generated using:

x = r × cos(θ)

z = r × sin(θ)

The Y coordinate remains 0, so the orbit is created on the X-Z plane.

### Current Progress

The project now contains a custom 3D sphere with multiple manually generated orbital paths.

---

## Step 04 — Sun and Basic 3D Scene

In this step, the central Sun was organized into a separate drawing function and basic 3D depth handling was introduced.

### Concepts Learned

- Function-based object organization
- Depth testing
- Depth buffer
- Double buffering
- `GL_DEPTH_TEST`
- `GLUT_DEPTH`
- `glutSwapBuffers()`
- Basic 3D scene structure

### Current Progress

The project now contains:

- A custom 3D sphere
- A central Sun
- Multiple manual orbital paths
- Depth testing
- Double buffering

The project is now prepared for adding moving planetary objects.

---

## Step 05 — Planetary Transformation System

In this step, a reusable planetary transformation system was introduced.

A planet was placed at a specific distance from the Sun and animated using rotation and translation.

### Concepts Learned

- `glPushMatrix()`
- `glPopMatrix()`
- Translation
- Rotation
- Transformation order
- Matrix stack
- Reusable object functions
- Continuous animation
- GLUT timer callback

### Transformation

The planet uses:

1. Rotation around the Y-axis
2. Translation away from the Sun

The combination of these transformations creates orbital movement.

### Current Progress

The project now contains:

- Custom 3D sphere
- Manual orbital path
- Central Sun
- One animated planet
- Rotation
- Translation
- Matrix stack
- Continuous animation

---

## Step 06 — Add All Eight Planets

In this step, all eight planets were added using the reusable planetary transformation function.

### Planets Added

1. Mercury
2. Venus
3. Earth
4. Mars
5. Jupiter
6. Saturn
7. Uranus
8. Neptune

### Concepts Learned

- Function reusability
- Parameterized 3D objects
- Different object sizes
- Different object colors
- Different orbital distances
- Different animation speeds
- Multiple transformed objects

### Planet Parameters

Each planet is defined using:

- Orbital distance
- Planet size
- RGB color
- Orbital speed

### Current Progress

The project now contains a complete set of eight animated planets orbiting the central Sun.
---

## Step 07 — Custom Saturn Ring

In this step, a custom 3D ring was created for Saturn without using GLUT's built-in torus function.

### Concepts Learned

- Parametric 3D geometry
- Torus-like surface generation
- Nested loops for 3D geometry
- Rotation of child objects
- Matrix stack
- Optional object features using Boolean parameters

### Ring Generation

The ring vertices are generated mathematically using:

x = (R + r × cos(φ)) × cos(θ)

y = r × sin(φ)

z = (R + r × cos(φ)) × sin(θ)

### Current Progress

The project now contains:

- Custom 3D sphere
- Eight animated planets
- Manual orbital paths
- Central Sun
- Custom 3D Saturn ring
- Planetary transformations
- Continuous animation
---

## Step 08 — Planet Names / 3D Text

In this step, text labels were added to identify the planets.

### Concepts Learned

- 3D text positioning
- `glRasterPos3f()`
- `glutBitmapCharacter()`
- Character-by-character text rendering
- Passing strings to functions
- Boolean visibility control

### Text System

A reusable `drawText()` function was created to display text at a specific 3D world position.

Each planet now receives its name as a function parameter.

### Current Progress

The project now contains:

- Custom 3D sphere
- Eight animated planets
- Manual orbital paths
- Central Sun
- Custom Saturn ring
- Planet names
- Rotation
- Translation
- Continuous animation

---

## Step 09 — 3D Camera and Manual Perspective

In this step, a manual 3D camera system and perspective projection were implemented.

### Concepts Learned

- Camera transformation
- Camera translation
- Camera rotation
- Perspective projection
- Projection matrix
- Field of View (FOV)
- Aspect ratio
- Near and far clipping planes
- Viewport
- Window resizing

### Camera System

The camera uses:

- Zoom distance
- Horizontal movement
- Vertical movement
- Y-axis rotation

### Manual Perspective

Instead of using `gluPerspective()`, the perspective projection matrix was calculated manually.

The basic formula is:

f = 1 / tan(FOV / 2)

The resulting matrix is then loaded into the OpenGL projection matrix.

### Current Progress

The project now contains:

- Custom 3D sphere
- Eight animated planets
- Manual orbital paths
- Central Sun
- Custom Saturn ring
- Planet names
- Camera system
- Manual perspective projection
- Depth testing
- Continuous animation

---

## Step 10 — Background Star Field

In this step, a 3D background star field was added to make the solar system scene look more realistic.

### Concepts Learned

- `GL_POINTS`
- 3D point rendering
- Generating multiple objects using loops
- Deterministic object positioning
- Basic brightness variation
- Disabling lighting for background objects

### Star System

A total of 450 stars are generated in 3D space.

Each star receives an X, Y, and Z coordinate using mathematical calculations.

The star positions remain consistent every time the program runs.

### Current Progress

The project now contains:

- Custom 3D sphere
- Eight animated planets
- Manual orbital paths
- Central Sun
- Custom Saturn ring
- Planet names
- 3D camera
- Manual perspective projection
- Background star field
- Continuous animation

---

## Step 11 — Sun Glow and Scaling Transformation

In this step, a glowing effect was added to the Sun using transparency and scaling transformation.

### Concepts Learned

- Scaling transformation
- `glScalef()`
- Alpha blending
- Transparency
- `GL_BLEND`
- `glBlendFunc()`
- Matrix stack using `glPushMatrix()` and `glPopMatrix()`

### Scaling

The glow sphere is scaled using:

```cpp
glScalef(1.35f, 1.35f, 1.35f);