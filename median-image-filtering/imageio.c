/*******************************************************************************
* Program: imageio.c
* Purpose: This souce code file contains functions for dynamically allocating
* and freeing 8-bit (unsigned char) images. It also contains functions for
* reading and writing images to files in raw PGM format. This code was written
* to be used as a teaching resource.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageio.h"

/*******************************************************************************
* Function: allocate_image
* Purpose: This function allocates an image. The image is an array of pointers
* to arrays. The array of pointers will have a length of the number of rows,
* and each of these pointers will point to a separate one dimensional array
* whose length is the number of columns in the image. This scheme was used
* because it allows the image to be accessed using the syntax image[r][c]
* yet still allow the image to be any size.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
unsigned char** allocate_image(int rows, int cols)
{
    unsigned char** image = NULL;
    int r, br;

    /****************************************************************************
    * Allocate an array of pointers of type (unsigned char *). The array is
    * allocated to have a length of the number of rows.
    ****************************************************************************/
    if ((image = (unsigned char**)calloc(rows, sizeof(unsigned char*))) == NULL) {
        fprintf(stderr, "Error allocating the array of pointers in allocate_image().\n");
        return((unsigned char**)NULL);
    }

    /****************************************************************************
    * For each row, allocate an array of type (unigned char).
    ****************************************************************************/
    for (r = 0; r < rows; r++) {
        if ((image[r] = (unsigned char*)calloc(cols, sizeof(unsigned char))) == NULL) {
            fprintf(stderr, "Error allocating an array in allocate_image().\n");
            for (br = 0; br < r; br++) free(image[br]);
            free(image);
            return((unsigned char**)NULL);
        }
    }

    return(image);
}

/*******************************************************************************
* Function: free_image
* Purpose: This function frees the memory that was previously allocated to
* store an image.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
void free_image(unsigned char** image, int rows)
{
    int r;

    /****************************************************************************
    * Free each row of the image.
    ****************************************************************************/
    for (r = 0; r < rows; r++) free(image[r]);

    /****************************************************************************
    * Free the array of pointers.
    ****************************************************************************/
    free(image);
}

/******************************************************************************
* Function: read_pgm_image
* Purpose: This function reads in an image in raw PGM format. Because the PGM
* format includes the number of columns and the number of rows in the image,
* these are read from the file. Memory to store the image is allocated in this
* function. All comments in the header are discarded in the process of reading
* the image. Upon failure, this function returns 0, upon sucess it returns 1.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
******************************************************************************/
int read_pgm_image(char* infilename, unsigned char*** image, int* rows,
    int* cols)
{
    FILE* fp;
    int r;
    char buf[71];

    /***************************************************************************
    * Open the input image file for reading. If the file can not be opened for
    * reading return an error code of 0.
    ***************************************************************************/
    if ((fp = fopen_s(&fp, infilename, "r")) == NULL) {
        fprintf(stderr, "Error reading the file %s in read_pgm_image().\n",
            infilename);
        return(0);
    }

    /***************************************************************************
    * Verify that the image is in PGM format, read in the number of columns
    * and rows in the image and scan past all of the header information.
    ***************************************************************************/
    fgets(buf, 70, fp);
    if (strncmp(buf, "P5", 2) != 0) {
        fprintf(stderr, "The file %s is not in PGM format in ", infilename);
        fprintf(stderr, "read_pgm_image().\n");
        fclose(fp);
        return(0);
    }
    do { fgets(buf, 70, fp); } while (buf[0] == '#');  /* skip all comment lines */
    sscanf_s(buf, "%d %d", cols, rows);
    do { fgets(buf, 70, fp); } while (buf[0] == '#');  /* skip all comment lines */

    /***************************************************************************
    * Allocate memory to store the image.
    ***************************************************************************/
    if (((*image) = allocate_image(*rows, *cols)) == NULL) return(0);

    /***************************************************************************
    * Read in the image from the file, one row at a time.
    ***************************************************************************/
    for (r = 0; r < (*rows); r++) {
        if ((*cols) != fread((*image)[r], 1, (*cols), fp)) {
            fprintf(stderr, "Error reading the image data in read_pgm_image().\n");
            fclose(fp);
            free_image((*image), *rows);
            return(0);
        }
    }

    fclose(fp);
    return(1);
}

/******************************************************************************
* Function: write_pgm_image
* Purpose: This function writes an image in raw PGM format. A comment can be
* written to the header if coment != NULL. If there is a comment, it can
* be up to 70 characters long.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
******************************************************************************/
int write_pgm_image(char* outfilename, unsigned char** image, int rows,
    int cols, char* comment, int maxval)
{
    FILE* fp;
    int r;

    /***************************************************************************
    * Open the output image file for writing.
    ***************************************************************************/
    if ((fp = fopen_s(&fp, outfilename, "w")) == NULL) {
        fprintf(stderr, "Error writing the file %s in write_pgm_image().\n",
            outfilename);
        return(0);
    }

    /***************************************************************************
    * Write the header information to the PGM file.
    ***************************************************************************/
    fprintf(fp, "P5\n");
    if (comment != NULL)
        if (strlen(comment) <= 70) fprintf(fp, "# %s\n", comment);
    fprintf(fp, "%d %d\n", cols, rows);
    fprintf(fp, "%d\n", maxval);

    /***************************************************************************
    * Write the image data to the file.
    ***************************************************************************/
    for (r = 0; r < rows; r++) {
        if (cols != fwrite(image[r], 1, cols, fp)) {
            fprintf(stderr, "Error writing the image data in write_pgm_image().\n");
            fclose(fp);
            return(0);
        }
    }

    fclose(fp);
    return(1);
}