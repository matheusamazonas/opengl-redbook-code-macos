OpenGL Red Book Code for MacOS
=========================

Code for OpenGL Programming Guide, Eighth Edition

Running on MacOS 10.9.4
Using GLFW instead of GLUT/FreeGLUT
OpenGL 4.1
GLFW 3.0.4

To compile the code:
g++ source_file.cpp -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lGLEW -o program_name

We need to use the Cocoa, IOKit and CoreVideo frameworks to use GLFW
http://www.glfw.org/docs/latest/build.html#build_link_osx



