#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include "fractal.h"
#include "image.h"

/*	TODO: define a struct which wraps the arguments to generate_fractal_region()	*/
struct region_data {
    color_t *image_data;
    float width;
    float height;
    float start_y;
    unsigned int rows;
};
/*
	generates part of the fractal region, computing data for a number of rows
	beginning from start_y
	arguments:	data: a struct wrapping the data needed to generated the fractal
					- a pointer to the color data region of memory
					- the width of the image
					- the height of the image
					- the starting row for filling out data
					- the number of rows to fill out
	returns:	NULL
*/
void *gen_fractal_region(void *data) {
	/*	TODO: unpack the data struct and call generate_fractal_region()	*/
        struct region_data *ptr = data;
        color_t *image_data = ptr->image_data;
        float width   = ptr->width;
        float height  = ptr->height;
        float start_y = ptr->start_y;
        unsigned int rows = ptr->rows;
        generate_fractal_region(image_data, width, height, start_y, rows);
        free(ptr);
	return NULL;
}

int generate_fractal(char *file, float width, float height, int workers) {
    /*	TODO: initialize several threads which will compute a unique
	region of the fractal data, and have them each execute
	gen_fractal_region().	*/
    color_t *fractal_data = malloc(sizeof(color_t)*width*height);
    pthread_t thread[workers];
    for(int i=0;i<workers;i++) {
        struct region_data *reg = malloc(sizeof(struct region_data));
        reg->image_data = fractal_data;
        reg->width   = width;
        reg->height  = height;
        reg->rows  = height/workers;
        reg->start_y = i*height/workers;
        pthread_create(&thread[i],0,gen_fractal_region,reg);
    }
    
    for (int i=0;i<workers;i++) {
            pthread_join(thread[i],0);
    }
    
    /*
		save the generated fractal data into the file specified by argv[1]
    */
    if (save_image_data(file, fractal_data, width, height)) {
	fprintf(stderr, "error saving to image file.\n");
	free(fractal_data);
	return 1;
    }
    free(fractal_data);
    printf("Complete.\n");
    return 0;
}
