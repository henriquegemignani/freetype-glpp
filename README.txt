Freetype GL++ - A C++ Wrapper for Freetype GL
=============================================

 This library is merely a wrapper of the Freetype GL by Nicolas P. Rougier.
 WWW: http://code.google.com/p/freetype-gl/

============================== 
  COMPILING
==============================
 Pre-requisites:
  - CMake 2.8.5 (or later)
  - C++ compiler (tested against GCC 4.4 and MSVC10/11)
  - Freetype GL, which in turn depends on:
    - OpenGL
    - GLEW
    - Freetype
    
 This repository provides a copy of Freetype GL, GLEW and Freetype, in case
 they are unavaiable on your development setup.
 
 With the pre-requisites out of the way, the following commands should be
 enough to compile the lib:
 
 $ mkdir build
 $ cd build
 $ cmake ..
 $ cmake --build .