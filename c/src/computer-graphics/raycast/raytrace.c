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

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "sphere.h"
#include "vector.h"
#include "scene.h"

#undef INFINITY
#undef PI

#define BIAS 0.001
#define PI 3.141592653589793
#define INFINITY FLT_MAX

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define min(a, b) (((a) < (b)) ? (a) : (b))

static struct vector compute_color(
	sphere_t s,
	struct vector phit,
	struct vector nhit,
	sphere_t *spheres,
	int nspheres)
{
	struct vector lightdir;      /* Light Direction      */
	struct vector surface_color; /* Color of the Surface */

	/* Computer color. */
	surface_color = VECTOR(0, 0, 0);
	for (int i = 0; i < nspheres; i++)
	{
		int transmission;

		/* Skip objects.  */
		if (spheres[i]->emission_color.x <= 0)
			continue;

		transmission = 1;

		lightdir = vector_sub(spheres[i]->center, phit);
		lightdir = vector_normalize(lightdir);
		
		/* Check if light source is blocked. */
		for (int j = 0; j < nspheres; j++)
		{	
			if (i == j)
				continue;
			
			/* Shade this point. */
			if (sphere_intersects(spheres[j], nhit, lightdir, NULL, NULL))
			{
				transmission = 0;
				break;
			}
		}
		
		if (transmission)
		{
			struct vector tmp1;

			tmp1 = vector_scalar(s->surface_color, max(0, vector_dot(nhit, lightdir)));
			tmp1 = vector_cross(tmp1, spheres[i]->emission_color);
			
			surface_color = vector_add(surface_color, tmp1);
		}
	}

	return (surface_color);
}

/**
 * @brief Casts a ray into a scene.
 *
 * @param raysrc   Ray source.
 * @param raydir   Ray direction.
 * @param spheres  Spheres.
 * @param nspheres Number of spheres.
 *
 * @returns The color reflected by the ray cast.
 */
struct vector raytrace(
	struct vector raysrc,
	struct vector raydir,
	sphere_t *spheres,
	int nspheres)
{
	sphere_t s;                  /* Intersected Sphere                 */
	float tnear;                 /* Distance to Intersected Sphere     */
	struct vector color;         /* Resulting Color                    */
	
	s = nearest_object(raysrc, raydir, spheres, nspheres, &tnear);
	
	/* There is no intersection
	 * so return background color.
	 */
	if (s == NULL)
		return (VECTOR(2, 2, 2));

	color = s->surface_color;

	return (color);
}

image_t render(
	sphere_t *spheres,
	int nspheres,
	unsigned width,
	unsigned height,
	float fov)
{
	image_t img;           /* Output Image */
	struct vector raydir;  /* Ray direction.  */
	float invwidth;     /* width^-1  */
	float invheight;    /* height^-1 */
	float angle;
	float aspectratio; /* Image's aspect ratio. */


	img = image_create(width, height);
	
	invwidth = 1.0/width;
	invheight = 1.0/height;

	aspectratio = width / ((float)height);
	angle = tan(PI*0.5*fov/180.0);

	for (unsigned y = 0; y < height; y++)
	{
		for (unsigned x = 0; x < width; x++)
		{
			struct vector pixel;

			float xx = (2 * ((x + 0.5) * invwidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invheight)) * angle;
			
			raydir = vector_normalize(VECTOR(xx, yy, -1));
			
			pixel = raytrace(VECTOR(0, 0, 0), raydir, spheres, nspheres);
			
			IMAGE(img, x, y).r = (unsigned char) (min(1.0, pixel.x)*255);
			IMAGE(img, x, y).g = (unsigned char) (min(1.0, pixel.y)*255);
			IMAGE(img, x, y).b = (unsigned char) (min(1.0, pixel.z)*255);
		}
	}
	
	return (img);
}
