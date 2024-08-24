
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
#include <math.h>
#include <stdlib.h>

typedef struct {
    unsigned char* data;
    int width;
    int height;
} MyImage;

/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
#define y_1_width 1

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
void test_Outputs_wrapper(const real_T *u0,
			uint64_T *y0,
			real_T *y1,
			const real_T *p0, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
    MyImage *img = (MyImage*)malloc(sizeof(MyImage));
    
    int width = 10;
    int height = 10;
    img->width = width;
    img->height= height;
    img->data = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
    for(int y=0; y<height; ++y){
        for(int x=0; x<width; ++x){
            int idx = y * width + x;
            img->data[idx] = idx*255/(width*height);
        }
    }
    
    y0[0] = (uint64_T)img;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


