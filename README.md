## A simple OpenGL renderer
I develop this in my spare time.\
Feature list:
- Multiple lights
- Physically based rendering

### Compilation (GNU/Linux)
    git clone --recursive https://github.com/Jan-Stangelj/Renderer.git
    cd Renderer
    mkdir build
    cmake -S . -B build
    cd build
    make

### Compilation (Windows)
You should be able to clone this project and use cmake GUI to compile it
for your platform of choice (eg. Visual Studio).

### Assets and 3rd party liraries
[PolyHaven](https://polyhaven.com/)\
[Glad](https://glad.dav1d.de/)\
[GLFW](https://www.glfw.org/)\
[glm](https://github.com/g-truc/glm)\
[stb](https://github.com/g-truc/glm)\
[assimp](https://github.com/assimp/assimp)