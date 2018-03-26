
// Copyright 2018 Karthik


/* Header Files **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include <string.h>



/* Global Variables **********************************************************/
enum colors {BLACK, WHITE, RED, GREEN, BLUE, YELLOW};
typedef float opacity;
int width = 1980;
int height = 1080;

cairo_t *cr;
cairo_surface_t *surface;


/* Function Prototypes *******************************************************/
void initialize_with_image_surface(int width, int height);
void create_background(cairo_t *cr, int color);
void save_image(cairo_surface_t *surface);
void clear_memory();
void create_dynamic_background();
char* itoa(int, char*, int);


char *
itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


void initialize_with_image_surface(int width, int height) {
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);
}


void create_background(cairo_t *cr, int color) {
	if (color == BLACK) {
		printf("Black: %d\n", BLACK);
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_rectangle(cr, 0, 0, width, height);
		cairo_fill(cr);
	}
}


void save_image(cairo_surface_t *surface) {
	cairo_surface_write_to_png(surface, "filename.png");
 }

void clear_memory() {
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}


void create_dynamic_background() {
	for (int i = 0; i < 300; ++i) {
		cairo_set_source_rgb(cr, i / 500.0, i / 150.0, i * 0.0002);
		cairo_rectangle(cr, 0, 0, width, height);
		cairo_fill(cr);
		
		char name[30] = "filename";
		char num[10];
		char ext[10] = ".png";
		itoa(i, num, 10);
		strcat(name, num);
		strcat(name, ext); 
		
		cairo_surface_write_to_png(surface, name);
		printf("r: %f, g: %f, b: %f\n", i / 500.0, i / 150.0 , i* 0.0002);
	}

}

int main(int argc, char *argv[])
{
	initialize_with_image_surface(width, height);
	create_background(cr, BLACK);
	save_image(surface);


	create_dynamic_background();
	clear_memory();
	
	return 0;

}
