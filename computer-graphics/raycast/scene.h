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

#ifndef _SCENE_H_
#define _SCENE_H_

	#include "sphere.h"
	#include "vector.h"

	/**
	 * @brief Finds the nearest sphere in the scene.
	 *
	 * @param raysrc   Ray source.
	 * @param raydir   Ray direction.
	 * @param spheres  Spehres in the scene.
	 * @param nspheres Number of spheres.
	 * @param tnear    Distance to nearest sphere.
	 *
	 * @returns The nearest sphere in the scene that is intercepted by
	 * the ray. If no sphere is intercepted, a NULL pointer is returned
	 * instead.
	 */
	extern sphere_t nearest_object(
		struct vector raysrc,
		struct vector raydir,
		sphere_t *spheres,
		int nspheres,
		float *tnear
	);

#endif /* _SCENE_H_ */
