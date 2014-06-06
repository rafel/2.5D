#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

/* Window size*/
#define WINDOW_WIDTH 1920.0f
#define WINDOW_HEIGHT 1080.0f
//#define WINDOW_WIDTH 1366.0f
//#define WINDOW_HEIGHT 768.0f

// Ratio coordinates
#define WCX float(WINDOW_WIDTH/1920.0f)
#define WCY float(WINDOW_HEIGHT/1080.0f)
#define MAX_Z 1000.0f


#define WINDOW_MODE GLFW_FULLSCREEN	// Uncomment for fullscreen
//#define WINDOW_MODE GLFW_WINDOW			// Uncomment for window screen

// Include GL
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

//#define HIDE_MOUSE	// Uncomment to hide mouse



/* Defines graphics */
#define OPENGL_MAJOR_VERSION 2
#define OPENGL_MINOR_VERSION 1
#define GLSL_FILE_PATH "res//shader//"
#define TEXTURE_FILE_PATH "res//texture//"


/* MATH */
#define M_E         2.71828182845904523536028747135266250   /* e */
#define M_LOG2E     1.44269504088896340735992468100189214   /* log 2e */
#define M_LOG10E    0.434294481903251827651128918916605082  /* log 10e */
#define M_LN2       0.693147180559945309417232121458176568  /* log e2 */
#define M_LN10      2.30258509299404568401799145468436421   /* log e10 */
#define M_2PI        6.28318530718							/* pi*2 */
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2 */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4 */
#define M_1_PI      0.318309886183790671537767526745028724  /* 1/pi */
#define M_2_PI      0.636619772367581343075535053490057448  /* 2/pi */
#define M_2_SQRTPI  1.12837916709551257389615890312154517   /* 2/sqrt(pi) */
#define M_SQRT2     1.41421356237309504880168872420969808   /* sqrt(2) */
#define M_SQRT1_2   0.707106781186547524400844362104849039  /* 1/sqrt(2) */



#endif