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

#ifndef IMAGE_H_
#define IMAGE_H_

	/*
	 * Pixel.
	 */
	struct pixel
	{
		unsigned char r; /* Red value.   */
		unsigned char g; /* Green value. */
		unsigned char b; /* Blue value.  */
	};

	/* Image file types. */
	#define IMAGE_PPM 0 /* ppm file type. */

	/*
	 * Raw image.
	 */
	struct image
	{
		unsigned width;       /* Width (in pixels).   */
		unsigned height;      /* Height (int pixels). */
		unsigned dimension;   /* width*height.        */
		struct pixel *pixels; /* Pixels.              */
	};
	
	/*
	 * Opaque pointer to a image.
	 */
	typedef struct image * image_t;
	
	#define IMAGE(img, x, y) \
		(img->pixels[(y)*img->width + (x)])
	
	/*
	 * Creates an image.
	 */
	extern image_t image_create(unsigned width, unsigned height);
	
	/*
	 * Destroys an image.
	 */
	extern void image_destroy(image_t img);
	
	/*
	 * Exports an image to a file type.
	 */
	extern void image_export(const char *filename, image_t img, unsigned type);

#endif /* IMAGE_H_ */
