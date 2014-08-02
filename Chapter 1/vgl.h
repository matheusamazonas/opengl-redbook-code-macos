#ifndef __VGL_H__
#define __VGL_H__

#define GLFW_INCLUDE_GLCOREARB

#define GLEW_STATIC

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#ifdef USE_GL3W

#include <GL3/g2l3.h>
#include <GL3/gl3w.h>

#else
/*
#ifdef _MSC_VER
#  ifdef _DEBUG
#    if (_MSC_VER >= 1600)
#      pragma comment (lib, "glew_static_vs2010_d.lib")
#    else
#      pragma comment (lib, "glew_static_d.lib")
#    endif
#  else
#    if (_MSC_VER >= 1600)
#      pragma comment (lib, "glew_static_vs2010.lib")
#    else
#      pragma comment (lib, "glew_static.lib")
#    endif
#  endif
#endif
*/
#endif

#define FREEGLUT_STATIC

#define BUFFER_OFFSET(x)  ((const void*) (x))

#endif /* __VGL_H__ */
