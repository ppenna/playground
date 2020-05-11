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

#ifndef VECTOR_H_
#define VECTOR_H_

	/*
	 * 3D Vector.
	 */
	struct vector
	{
		float x; /* x coordinate. */
		float y; /* y coordinate. */
		float z; /* z coordinate. */
	};
	
	extern struct vector VECTOR(float x, float y, float z);
	
	/*
	 * Adds v2 to v1.
	 */
	extern struct vector vector_add(struct vector v1, struct vector v2);
	
	/*
	 * Cross product.
	 */
	extern struct vector vector_cross(struct vector v1, struct vector v2);
	
	/*
	 * Dot product.
	 */
	extern float vector_dot(struct vector v1, struct vector v2);
	
	/*
	 * Multiplies a 3D vector by -1.
	 */
	extern struct vector vector_invert(struct vector v);
	
	/*
	 * Normalizes a 3D vector.
	 */
	extern struct vector vector_normalize(struct vector v);
	
	/*
	 * Scalar product.
	 */
	extern struct vector vector_scalar(struct vector v, float a);
	
	/*
	 * Subtracts v2 from v1.
	 */
	extern struct vector vector_sub(struct vector v1, struct vector v2);

#endif /* VECTOR_H_ */
