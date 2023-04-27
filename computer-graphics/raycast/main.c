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

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "image.h"
#include "sphere.h"
#include "vector.h"

/**
 * @brief Field View
 */
#define CAMERA_FOV 30

/**
 * @name Image Resolution
 */
/**@{*/
#define IMAGE_HEIGHT 1920 /**< Height */
#define IMAGE_WIDTH  1080 /**< Width  */
/**@}*/

/* Import definitions. */
extern image_t render(
	sphere_t *spheres,
	int nspheres,
	unsigned width,
	unsigned height,
	float fov);

/**
 * @brief Ray Trace Algorithm
 */
int main(int argc, char **argv)
{
	/* Number of spheres. */
	#define NR_SPHERES 6
	
	image_t img;                  /* Image.      */
	sphere_t spheres[NR_SPHERES]; /* Spheres.    */
	unsigned long end;            /* End time.   */
	unsigned long start;          /* Start time. */

	((void) argc);
	((void) argv);
	
	clock_setup();
	
	/* Ground sphere. */
	spheres[0] = sphere_create(
					VECTOR(0, -10004, -20), /* Center         */
					10000,                  /* Radius         */
					VECTOR(0.2, 0.2, 0.2),  /* Surface Color  */
					0,                      /* Reflection     */
					0,                      /* Transparency   */
					VECTOR(0, 0, 0));       /* Emission Color */
	
	/* Red sphere. */
	spheres[1] = sphere_create(
					VECTOR(0, 0, -20),        /* Center         */
					4,                        /* Radius         */
					VECTOR(1.00, 0.32, 0.36), /* Surface Color  */
					1,                        /* Reflection     */
					0.5,                      /* Transparency   */
					VECTOR(0, 0, 0));         /* Emission Color */
	
	/* Yellow sphere. */
	spheres[2] = sphere_create(
					VECTOR(5, -1, -15),
					2,
					VECTOR(0.90, 0.76, 0.46),
					1,
					0.0,
					VECTOR(0, 0, 0));
	
	/* Blue sphere. */
	spheres[3] = sphere_create(
					VECTOR(5, 0, -25),
					3,
					VECTOR(0.65, 0.77, 0.97),
					1,
					0.0,
					VECTOR(0, 0, 0));
	
	/* Gray sphere. */
	spheres[4] = sphere_create(
					VECTOR(-5.5, 0, -15),
					3,
					VECTOR(0.90, 0.90, 0.90),
					1,
					0.0,
					VECTOR(0, 0, 0));
	
	/* Light source. */
	spheres[5] = sphere_create(
					VECTOR(0, 30, -30),
					3,
					VECTOR(0, 0, 0),
					0,
					0,
					VECTOR(3, 3, 3));
	
	/* Ray tracing. */
	printf("rendering scene...\n");
	start = clock_read();
		img = render(
			spheres,
			NR_SPHERES,
			IMAGE_HEIGHT,
			IMAGE_WIDTH,
			CAMERA_FOV
		);
	end = clock_read();

	printf("timing statistics:\n");
	printf("  total time:    %8lu\n", clock_diff(start, end));

	/* Export image. */
	image_export("out.ppm", img, IMAGE_PPM);
	
	/* House keeping. */
	for (int i = 0; i < NR_SPHERES; i++)
		sphere_destroy(spheres[i]);
	image_destroy(img);
	
	return (EXIT_SUCCESS);
}
