/* ============================================================================
 * Freetype GL++ - A C++ FreeType-GL wrapper
 * Platform:       Any
 * WWW:            https://github.com/henriquegemignani/freetype-glpp
 * ----------------------------------------------------------------------------
 * Copyright 2013 Henrique Gemignani. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY HENRIQUE GEMIGNANI ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL HENRIQUE GEMIGNANI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Henrique Gemignani.
 * ============================================================================
 * 
 *  This library is merely a wrapper of the Freetype GL by Nicolas P. Rougier.
 *  WWW: http://code.google.com/p/freetype-gl/
 * 
 * ============================================================================
 */
#ifndef FREETYPEGLXX_VEC234_H_
#define FREETYPEGLXX_VEC234_H_

namespace freetypeglxx {

/**
 * Tuple of 4 elements.
 *
 * Each field can be addressed using several aliases:
 *  - First component:  <b>x</b>, <b>r</b>, <b>red</b> or <b>vstart</b>
 *  - Second component: <b>y</b>, <b>g</b>, <b>green</b> or <b>vcount</b>
 *  - Third component:  <b>z</b>, <b>b</b>, <b>blue</b>, <b>width</b> or <b>istart</b>
 *  - Fourth component: <b>w</b>, <b>a</b>, <b>alpha</b>, <b>height</b> or <b>icount</b>
 *
 */
template<typename T>
union tvec4 {
    T data[4];
    struct {
        T x;      /**< Alias for first component  */
        T y;      /**< Alias for second component */
        T z;      /**< Alias for third component  */
        T w;      /**< Alias for fourht component */
    };
    struct {
        T x_;     /**< Alias for first component  */
        T y_;     /**< Alias for second component */
        T width;  /**< Alias for third component  */
        T height; /**< Alias for fourth component */
    };
    struct {
        T r;      /**< Alias for first component  */
        T g;      /**< Alias for second component */
        T b;      /**< Alias for third component  */
        T a;      /**< Alias for fourth component */
    };
    struct {
        T red;    /**< Alias for first component  */
        T green;  /**< Alias for second component */
        T blue;   /**< Alias for third component  */
        T alpha;  /**< Alias for fourth component */
    };
    struct {
        T vstart; /**< Alias for first component  */
        T vcount; /**< Alias for second component */
        T istart; /**< Alias for third component  */
        T icount; /**< Alias for fourth component */
    };
};
 
/**
 * Tuple of 3 elements.
 *
 * Each field can be addressed using several aliases:
 *  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
 *  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
 *  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
 *
 */
template<typename T>
union tvec3 {
	T data[3];    /**< All compoments at once     */
	struct {
        T x;      /**< Alias for first component  */
        T y;      /**< Alias for second component */
        T z;      /**< Alias for third component  */
    };
	struct {
        T r;      /**< Alias for first component  */
        T g;      /**< Alias for second component */
        T b;      /**< Alias for third component  */
    };
	struct {
        T red;    /**< Alias for first component  */
        T green;  /**< Alias for second component */
        T blue;   /**< Alias for third component  */
    };
};

/**
 * Tuple of 2 elements.
 *
 * Each field can be addressed using several aliases:
 *  - First component: <b>x</b>, <b>s</b> or <b>start</b>
 *  - Second component: <b>y</b>, <b>t</b> or <b>end</b>
 *
 */
template<typename T>
union tvec2
{
    T data[2];    /**< All compoments at once     */
    struct {
        T x;      /**< Alias for first component  */
        T y;      /**< Alias for second component */
    };
    struct {
        T s;      /**< Alias for first component  */
        T t;      /**< Alias for second component */
    };
    struct {
        T start;  /**< Alias for first component  */
        T end;    /**< Alias for second component */
    };
};

typedef tvec4<int> ivec4;
typedef tvec3<int> ivec3;
typedef tvec2<int> ivec2;

typedef tvec4<float> vec4;
typedef tvec3<float> vec3;
typedef tvec2<float> vec2;

} // namespace freetypeglxx

#endif // FREETYPEGLXX_VEC234_H_
