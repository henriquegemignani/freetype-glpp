// TODO: license text
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
