/*******************************************************************************
* Program: imageio.h
* Purpose: This header file contains function prototypes for functions that
* dynamically allocate and free 8-bit (unsigned char) images. It also contains
* prototypes for functions that read and write images to files in raw PGM
* format. This code was written to be used as a teaching resource.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
#ifndef _PGMIO_
#define _PGMIO_

unsigned char** allocate_image(int rows, int cols);

void free_image(unsigned char** image, int rows);

int read_pgm_image(char* infilename, unsigned char*** image, int* rows, int* cols);

int write_pgm_image(char* outfilename, unsigned char** image, int rows,
	int cols, char* comment, int maxval);

int write_gray_bmp(char* outfilename, unsigned char** image, short int rows, short int cols);
#endif