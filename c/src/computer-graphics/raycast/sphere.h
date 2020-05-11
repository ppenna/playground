/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SPHERE_H_
#define SPHERE_H_

	#include "vector.h"

	/*
	 * Sphere.
	 */
	struct sphere
	{
		float radius;            /* Radius.         */
		float radius2;           /* Radius^2.       */
		float transparency;      /* Transparency.   */
		float reflection;        /* Reflection.     */
		struct vector surface_color;  /* Surface color.  */
		struct vector emission_color; /* Emission color. */
		struct vector center;         /* Center.         */
	};
	
	/*
	 * Opaque pointer to a sphere.
	 */
	typedef struct sphere * sphere_t;
	
	/*
	 * Returns the center of a sphere.
	 */
	extern struct vector sphere_center(sphere_t s);
	
	/*
	 * Creates a sphere.
	 */
	extern sphere_t sphere_create
	(struct vector c, float r, struct vector sc, float rf, float t, struct vector ec);
	
	/*
	 * Destroys a sphere.
	 */
	extern void sphere_destroy(sphere_t s);
	
	/*
	 * Asserts if a ray intercepts a sphere.
	 */
	extern int sphere_intersects
	(sphere_t s, struct vector rayorig, struct vector raydir, float *t0, float *t1);

#endif /* SPHERE_H_ */
