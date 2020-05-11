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
#include <math.h>
#include <stdlib.h>
#include <utils.h>
#include "sphere.h"
#include "vector.h"

/*
 * Returns the center of a sphere.
 */
struct vector sphere_center(struct sphere *s)
{
	/* Sanity check. */
	assert(s != NULL);
	
	return (s->center);
}

/*
 * Creates a sphere.
 */
struct sphere *sphere_create(
	struct vector c,
	float r,
	struct vector sc,
	float rf,
	float t,
	struct vector ec
)
{
	struct sphere *s;
	
	/* Sanity check. */
	assert(r > 0);
	assert(t >= 0);
	assert(t >= 0);
	
	s = smalloc(sizeof(struct sphere));
	
	/* Initialize sphere. */
	s->radius = r;
	s->radius2 = r*r;
	s->transparency = t;
	s->reflection = rf;
	s->surface_color = sc;
	s->emission_color = ec;
	s->center = c;
	
	return (s);
}

/*
 * Destroys a sphere.
 */
void sphere_destroy(struct sphere *s)
{
	/* Sanity check. */
	assert(s != NULL);
	
	free(s);
}

/*
 * Asserts if a ray intercepts a sphere.
 */
int sphere_intersects
(struct sphere *s, struct vector rayorig, struct vector raydir, float *t0, float *t1)
{
	float d2;
	float tca;
	float thc;
	struct vector l;
	
	/* Sanity check. */
	assert(s != NULL);
	
	l = vector_sub(s->center, rayorig);
	
	tca = vector_dot(l, raydir);
	
	if (tca < 0)
		return (0);
	
	d2 = vector_dot(l, l) - tca*tca;
	
	if (d2 > s->radius2)
		return (0);
	
	thc = sqrt(s->radius2 -d2);
	
	if ((t0 != NULL) && (t1 != NULL))
	{
		*t0 = tca - thc;
		*t1 = tca + thc;
	}
	
	return (1);
}
