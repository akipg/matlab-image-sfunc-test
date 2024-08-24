
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    unsigned char* data;
    int width;
    int height;
} MyImage;


MyImage read_png_file_to_grayscale(const char *filename) {
    MyImage img;
    int n;
    unsigned char *data = stbi_load(filename, &img.width, &img.height, &n, 0);
    if (data == NULL) {
        fprintf(stderr, "Error loading MyImage %s\n", filename);
        exit(EXIT_FAILURE);
    }

    img.data = (unsigned char *)malloc(img.width * img.height);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int index = y * img.width + x;
            int src_index = index * n;
            unsigned char r = data[src_index];
            unsigned char g = data[src_index + 1];
            unsigned char b = data[src_index + 2];
            unsigned char gray = (r + g + b) / 3;
            img.data[index] = gray;
        }
    }

    stbi_image_free(data);
    return img;
}


MyImage edge_detection(const MyImage *src) {
    MyImage dest;
    dest.width = src->width;
    dest.height = src->height;
    dest.data = (unsigned char *)malloc(dest.width * dest.height);

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int y = 1; y < src->height - 1; y++) {
        for (int x = 1; x < src->width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int index = (y + i) * src->width + (x + j);
                    unsigned char pixel = src->data[index];
                    sumX += pixel * gx[i + 1][j + 1];
                    sumY += pixel * gy[i + 1][j + 1];
                }
            }

            int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
            if (magnitude > 255) magnitude = 255;
            if (magnitude < 0) magnitude = 0;

            int index = y * src->width + x;
            dest.data[index] = (unsigned char)magnitude;
        }
    }

    return dest;
}


MyImage enhance_edges(const MyImage *gray, const MyImage *edges) {
    MyImage result;
    result.width = gray->width;
    result.height = gray->height;
    result.data = (unsigned char *)malloc(result.width * result.height);

    for (int y = 0; y < gray->height; y++) {
        for (int x = 0; x < gray->width; x++) {
            int index = y * gray->width + x;
            int enhanced = gray->data[index] + edges->data[index];
            if (enhanced > 255) enhanced = 255;
            result.data[index] = (unsigned char)enhanced;
        }
    }

    return result;
}

void save_png_file(const char *filename, const MyImage *img) {
    if (stbi_write_png(filename, img->width, img->height, 1, img->data, img->width) == 0) {
        fprintf(stderr, "Error saving MyImage to %s\n", filename);
        exit(EXIT_FAILURE);
    }
}


MyImage create_block_noise_image(int width, int height, int block_size) {
    MyImage noise_img;
    noise_img.width = width;
    noise_img.height = height;
    noise_img.data = (unsigned char *)malloc(width * height);

    srand(time(NULL)); // Seed the random number generator

    for (int y = 0; y < height; y += block_size) {
        for (int x = 0; x < width; x += block_size) {
            // Generate a random grayscale value for the block
            unsigned char gray_value = rand() % 256;

            // Fill the block with the random grayscale value
            for (int by = 0; by < block_size && (y + by) < height; by++) {
                for (int bx = 0; bx < block_size && (x + bx) < width; bx++) {
                    int index = (y + by) * width + (x + bx);
                    noise_img.data[index] = gray_value;
                }
            }
        }
    }

    return noise_img;
}

int proc() {
    const char *filename = "example.png";
    MyImage img = read_png_file_to_grayscale(filename);

    MyImage edge = edge_detection(&img);
    MyImage enhanced = enhance_edges(&img, &edge);

    save_png_file("output.png", &enhanced);
    
    free(img.data);
    free(edge.data);
    free(enhanced.data);
    
    return 0;
}
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define u_1_width 1
#define u_2_width 1
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void create_noise_image_Outputs_wrapper(const int32_T *width,
			const int32_T *height,
			const int32_T *noise_size,
			uint64_T *img_adr)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
printf("creating noise image\n");
    MyImage *noise_img = (MyImage*)malloc(sizeof(MyImage));
    *noise_img = create_block_noise_image(*width, *height, *noise_size);
    
    *img_adr = (uint64_T)noise_img;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


