#ifndef INCLUDED_FILTER_H
#define INCLUDED_FILTER_H


typedef enum { MEAN, MEDIAN } filter;

typedef struct { unsigned char r, g, b; } RGB;

RGB *readPPM(const char *file, int *width, int *height, int *max);

void writePPM(const char *file, int width, int height, int max, const RGB *image);

RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f);
#endif
