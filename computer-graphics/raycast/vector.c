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
#include "vector.h"

#define EPSILON 0.000001

struct vector VECTOR(float x, float y, float z)
{
	struct vector v;

	v.x = x;
	v.y = y;
	v.z = z;

	return (v);
}


/*
 * Adds v2 to v1.
 */
struct vector vector_add(struct vector v1, struct vector v2)
{
	struct vector v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return (v);
}

/*
 * Cross product.
 */
struct vector vector_cross(struct vector v1, struct vector v2)
{
	struct vector v;

	v.x = v1.x*v2.x;
	v.y = v1.y*v2.y;
	v.z = v1.z*v2.z;

	return (v);
}

/*
 * Dot product.
 */
float vector_dot(struct vector v1, struct vector v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

/*
 * Multiplies a 3D vector by -1.
 */
struct vector vector_invert(struct vector v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;

	return (v);
}

/*
 * Normalizes a 3D vector.
 */
struct vector vector_normalize(struct vector v)
{
	float norm2;    /* normal^2  */
	float norminv;  /* normal^-1 */

	norm2 = v.x*v.x + v.y*v.y + v.z*v.z;

	if (norm2 < EPSILON)
		return (v);

	norminv = 1 / sqrt(norm2);
	v.x *= norminv;
	v.y *= norminv;
	v.z *= norminv;

	return (v);
}

/*
 * Scalar product.
 */
struct vector vector_scalar(struct vector v, float a)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;

	return (v);
}

/*
 * Subtracts v2 from v1.
 */
struct vector vector_sub(struct vector v1, struct vector v2)
{
	struct vector v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;

	return (v);
}
