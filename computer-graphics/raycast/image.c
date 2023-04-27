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
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "image.h"

/*
 * Creates a image.
 */
struct image *image_create(unsigned width, unsigned height)
{
	struct image *img;  /* Image.       */
	unsigned dimension; /* width*height */
	
	/* Sanity check. */
	assert(width > 0);
	assert(height > 0);
	
	img = smalloc(sizeof(struct image));
	
	/* Initialize image. */
	dimension = width*height;
	img->width = width;
	img->height = height;
	img->dimension = dimension;
	img->pixels = smalloc(dimension*sizeof(struct pixel));
	
	return (img);
}
	
/*
 * Destroys a image.
 */
extern void image_destroy(struct image *img)
{
	/* Sanity check. */
	assert(img != NULL);
	
	free(img->pixels);
	free(img);
}

/*
 * Exports an image to PPM format.
 */
static void image_export_ppm(FILE *file, struct image *img)
{
	fprintf(file, "P6\n%u %u\n255\n", img->width, img->height);
	for (unsigned i = 0; i < img->dimension; i++)
	{
		fprintf(file, "%c%c%c", 
			img->pixels[i].r,
			img->pixels[i].g,
			img->pixels[i].b);
	}
}

/*
 * Exports an image to a file type.
 */
void image_export(const char *filename, struct image *img, unsigned type)
{
	FILE *file;
	
	/* Sanity check. */
	assert(filename != NULL);
	assert(img != NULL);
	
	/* Open output file. */
	file = fopen(filename, "w");
	if (file == NULL)
		error("cannot image_export()");
	
	/* Parse file type. */
	switch (type)
	{
		/* Portable Pixmap Image. */
		case IMAGE_PPM:
			image_export_ppm(file, img);
			break;
		
		default:
			warning("unknown image file type");
	}
	
	/* Close output file. */
	fclose(file);
}
