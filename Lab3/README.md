# Lab 3

- Initializes a window, loads a 3D model, and sets up shaders.
- Allows the user to choose between writing or reading OBJ files.
- In the write mode, the user can input vertex [x y z r g b w h], coordinates for vertex, point colours, and texture, and face data, which the program stores and saves to an OBJ file.
- In the read mode, the user provides an OBJ file, which the program reads, displays vertex and face data, and then enters a rendering loop.
- In the rendering loop, the program sets up OpenGL, renders the model with shader and texture mapping, and allows for user interaction to move the model.
