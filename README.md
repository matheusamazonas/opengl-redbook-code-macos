OpenGL Red Book Code for MacOS
=========================

Code for [“OpenGL Programming Guide: The Official Guide to Learning OpenGL”](http://www.opengl-redbook.com/) by Dave Shreiner, 8th edition. This code doesn’t belong to me, it’s simply an adaptation of the book’s code to MacOS X. Although it is possible to use FreeGLUT as a OpenGL Toolkit, I use GLFW.

* Running on MacOS 10.9.4 (Mavericks)
* Using [GLFW 3.0.4](http://www.glfw.org/) instead of GLUT/FreeGLUT (as the book does);
* OpenGL 4.1;

To compile the code:
g++ source_file.cpp -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lGLEW -o program_name

We need to use the Cocoa, IOKit and CoreVideo frameworks to use GLFW
http://www.glfw.org/docs/latest/build.html#build_link_osx

Original Book Code available at:
http://www.opengl-redbook.com/



