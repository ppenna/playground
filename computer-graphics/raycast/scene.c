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

#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "sphere.h"
#include "vector.h"

#undef INFINITY
#undef PI

#define PI 3.141592653589793
#define INFINITY FLT_MAX

/**
 * The nearest_object() function finds the nearest sphere in the scene
 * that is intercepted by the ray.
 */
sphere_t nearest_object(
	struct vector raysrc,
	struct vector raydir,
	sphere_t *spheres,
	int nspheres,
	float *tnear
)
{
	float t0;
	float t1;
	sphere_t s;

	t0 = INFINITY;
	t1 = INFINITY;
	*tnear = INFINITY;
	s = NULL;
	
	/*
	 * Find closest sphere in the scene 
	 * that the ray intercepts.
	 */
	for (int i = 0; i < nspheres; i++)
	{
		/* This sphere is intercepted. */
		if (sphere_intersects(spheres[i], raysrc, raydir, &t0, &t1))
		{
			if (t0 < 0)
				t0 = t1;
			
			/* Closest sphere found. */
			if (t0 < *tnear)
			{
				*tnear = t0;
				s = spheres[i];
			}
		}
	}

	return (s);
}
