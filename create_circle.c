
// Copyright 2018 Karthik


/* Header Files */
#include <stdio.h>
#include <cairo/cairo.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>



/* Global Variables */
typedef enum Colors {BLACK, WHITE, RED, GREEN, BLUE, YELLOW} colors;
typedef float opacity;
int width = 1980;
int height = 1080;
static int count = 0;
double increment = 0.15;
cairo_t *cr;
cairo_surface_t *surface;



/* Function Prototypes */
void initialize_with_image_surface(int width, int height);
void select_color(cairo_t *cr, colors color);
void create_background(cairo_t *cr, colors color);
void save_image(cairo_surface_t *surface, char* filename);
void clear_memory();
char* itoa(int, char*, int);
void draw_circle(cairo_t *cr, double xc, double yc, double radius,
				 double angle1, double angle2, double line_width,
				 colors color, bool fill, bool stroke);

void draw_circle_animation(cairo_t *cr, double xc, double yc,
						   double radius, double angle1,
						   double angle2, double line_width,
						   colors color, bool fill, bool stroke);

void draw_inv_circle_animation(cairo_t *cr, double xc, double yc,
							   double radius, double angle1,
							   double angle2, double line_width,
							   colors color, bool fill, bool stroke);




char *itoa (int value, char *result, int base) {
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


void select_color(cairo_t *cr, colors color) {
	switch (color) {
	case BLACK: {
		printf("Black: %d\n", BLACK);
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); 
		break;
	}

	case WHITE: {
		printf("WHITE: %d\n", WHITE);
		cairo_set_source_rgb(cr, 255.0, 255.0, 255.0);
		break;
	}

	case RED: {
		printf("RED: %d\n", RED);
		cairo_set_source_rgb(cr, 255.0, 0.0, 0.0);
		break;
	}

	case BLUE: {
		printf("BLUE: %d\n", BLUE);
		cairo_set_source_rgb(cr, 0.0, 0.0, 255.0);
		break;
	}

	case GREEN: {
		printf("GREEN: %d\n", GREEN);
		cairo_set_source_rgb(cr, 0.0, 128.0, 0.0);
		break;
	}
	case YELLOW: {
		printf("YELLOW: %d\n", YELLOW);
		cairo_set_source_rgb(cr, 255.0, 255.0, 0.0);
		break;
	}
		
	default: {
		printf("NOT A VALID COLOR\n");
		exit(EXIT_FAILURE);
		break;
	}
	}
}


void create_background(cairo_t *cr, colors color) {
	select_color(cr, color);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);
}


void draw_circle(cairo_t *cr, double xc, double yc, double radius,
				 double angle1, double angle2, double line_width,
				 colors color, bool fill, bool stroke) {
	select_color(cr, color);
	angle1 = angle1 * (M_PI / 180.0);  /* in radians */
	angle2 = angle2 * (M_PI / 180.0);  /* in radians */
	cairo_set_line_width(cr, line_width);
	cairo_arc(cr, xc, yc, radius, angle1, angle2);

	if (fill) {
		cairo_fill(cr);
		printf("Filling\n");
	}

	if (stroke) {
		cairo_stroke(cr);
		printf("Stroking\n");
		
	}

}

void draw_circle_animation(cairo_t *cr, double xc, double yc,
						   double radius, double angle1,
						   double angle2, double line_width,
						   colors color, bool fill, bool stroke) {
	select_color(cr, color);
	angle1 = angle1 * (M_PI / 180.0);  /* in radians */
	angle2 = angle2 * (M_PI / 180.0);  /* in radians */
	cairo_set_line_width(cr, line_width);


	
	char num[10];
	char ext[10] = ".png";
	
	if (angle1 < angle2) {
		for (double i = angle1; i < (angle2 + increment);) {
			cairo_arc(cr, xc, yc, radius, angle1, i);
			if (fill) {
				cairo_fill(cr);
			}

			if (stroke) {
				cairo_stroke(cr);
			}
			char name[30] = "filename";

			itoa(count, num, 10);
			strcat(name, num);
			strcat(name, ext);
			
			cairo_surface_write_to_png(surface, name);
			printf("count: %d. Completed angle2: %f\n", count, i);
			i += increment;
			count++;
		}
	}

	if (angle1 > angle2) {
		while (angle1 > angle2) {
			angle2 = (2 * M_PI) + angle2;
			printf("in while: angle1: %f, angle2: %f, i: %f\n", angle1, angle2, angle1);
		}
		
		for (double i = angle1; i < (angle2 + increment);) {
			cairo_arc(cr, xc, yc, radius, angle1, i);
			if (fill) {
				cairo_fill(cr);
			}

			if (stroke) {
				cairo_stroke(cr);
			}
			char name[30] = "filename";

			itoa(count, num, 10);
			strcat(name, num);
			strcat(name, ext); 
		
			cairo_surface_write_to_png(surface, name);
			printf("count: %d. Completed angle2: %f\n", count, i);
			i += increment;
			count++;
		}
	}
}


void draw_inv_circle_animation(cairo_t *cr, double xc, double yc,
							   double radius, double angle1,
							   double angle2, double line_width,
							   colors color, bool fill, bool stroke) {
	select_color(cr, color);
	angle1 = angle1 * (M_PI / 180.0);  /* in radians */
	angle2 = angle2 * (M_PI / 180.0);  /* in radians */
	cairo_set_line_width(cr, line_width);


	char num[10];
	char ext[10] = ".png";

	/* Normal Case */
	if (angle1 > angle2) {
		for (double i = angle1; i > (angle2 - increment);) {
			cairo_arc_negative(cr, xc, yc, radius, angle1, i);
			if (fill) {
				cairo_fill(cr);
			}

			if (stroke) {
				cairo_stroke(cr);
			}

			char name[30] = "filename";
		
			itoa(count, num, 10);
			strcat(name, num);
			strcat(name, ext); 
		
			cairo_surface_write_to_png(surface, name);
			printf("count: %d. Completed angle2: %f\n", count, i);
			i -= increment;
			count++;
		}
	}
	
	if (angle1 < angle2) {
		while (angle1 < angle2) {
			printf("%f changed to %f\n", angle2, (angle2 - (2 * M_PI)));
			printf("Now angle1: %f\n", angle1);
			angle2 = angle2 - (2 * M_PI);
		} 
		
		for (double i = angle1; i > (angle2 - increment);) {
			cairo_arc_negative(cr, xc, yc, radius, angle1, i);
			if (fill) {
				cairo_fill(cr);
			}

			if (stroke) {
				cairo_stroke(cr); 
			}
			char name[30] = "filename";

			itoa(count, num, 10);
			strcat(name, num);
			strcat(name, ext); 
		
			cairo_surface_write_to_png(surface, name);
			printf("count: %d. Completed angle2: %f\n", count, i);
			i -= increment;
			count++;
		}
	}
	
}



void save_image(cairo_surface_t *surface, char* filename) {
	cairo_surface_write_to_png(surface, filename);
}


void clear_memory() {
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}


int main(int argc, char *argv[])
{
	initialize_with_image_surface(width, height);
	create_background(cr, WHITE);
	draw_inv_circle_animation(cr, width / 2, height / 2, 150.0, 360.0, 0.0, 10.0, BLUE, false, true);
	draw_circle_animation(cr, width / 2, height / 2, 300.0, 0.0, 270.0, 10.0, BLACK, false, true);
	draw_inv_circle_animation(cr, width / 2, height / 2, 450.0, 0.0, 180.0, 10.0, RED, false, true);
	draw_circle_animation(cr, width / 2, height / 2, 600.0, 0.0, 720.0, 10.0, YELLOW, true, true);
	// draw_circle(cr, width / 2, height / 2, 300.0, 0.0, 360.0 , 10, BLUE, true, true);
	// save_image(surface, "filename.png");

	/* select_color(cr, BLACK); */
		/* double angle1 = 720.0; */
	/* angle1 = angle1 * (M_PI / 180.0);  /\* in radians *\/ */
	/* double angle2 = 0.0; */
	/* angle2 = angle2 * (M_PI / 180.0);  /\* in radians *\/ */
	/* cairo_set_line_width(cr, 10); */

	/* cairo_arc(cr, width / 2, height / 2, 300.0, angle1, angle2); */
	/* cairo_stroke(cr); */
	/* save_image(surface, "filename.png"); */


	clear_memory(); 
    return 0;
	
}
