#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"

RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f)
{
	int size = width*height, i, j, k, l;
	RGB *ret = (RGB*)malloc(size * sizeof(RGB));
	if (f == MEAN) {
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				double sumr = 0, sumg = 0, sumb = 0;;
				int count = 0;
				for (k = i - n / 2; k <= i + n / 2; k++) {
					if (k>=0&&k<height) for (l = j - n / 2; l <= j + n / 2; l++) {
						if (l >= 0 && l < width) {
							sumr += image[k*width+l].r;
							sumg += image[k*width + l].g;
							sumb += image[k*width + l].b;
							count++;
						}
					}
				}
				ret[i*width + j].r = sumr / count;
				ret[i*width + j].g = sumg / count;
				ret[i*width + j].b = sumb / count;
			}
		}
	}
	else {
		int *r, *g, *b;
		r = (int*)malloc(n*n * sizeof(int));
		g = (int*)malloc(n*n * sizeof(int));
		b = (int*)malloc(n*n * sizeof(int));
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				int count = 0;
				for (k = i - n / 2; k <= i + n / 2; k++) {
					if (k >= 0 && k<height) for (l = j - n / 2; l <= j + n / 2; l++) {
						if (l >= 0 && l < width) {
							r[count]= image[k*width + l].r;
							g[count] = image[k*width + l].g;
							b[count] = image[k*width + l].b;
							count++;
						}
					}
				}
				for (k = 0; k < count; k++) {
					int min = k;
					for (l = k + 1; l < count; l++) {
						if (r[min] > r[l]) {
							min = l;
						}
					}
					int c = r[k];
					r[k] = r[min];
					r[min] = c;
				}
				for (k = 0; k < count; k++) {
					int min = k;
					for (l = k + 1; l < count; l++) {
						if (g[min] > g[l]) {
							min = l;
						}
					}
					int c = g[k];
					g[k] = g[min];
					g[min] = c;
				}
				for (k = 0; k <count; k++) {
					int min = k;
					for (l = k + 1; l < count; l++) {
						if (b[min] > b[l]) {
							min = l;
						}
					}
					int c = b[k];
					b[k] = b[min];
					b[min] = c;
				}
				if (count % 2 == 0) {
					ret[i*width + j].r = (r[count / 2] + r[count / 2 - 1])/2;
					ret[i*width + j].g = (g[count / 2] + g[count / 2 - 1]) / 2;
					ret[i*width + j].b = (b[count / 2] + b[count / 2 - 1]) / 2;
				}
				else {
					ret[i*width + j].r = r[count / 2];
					ret[i*width + j].g = g[count / 2];
					ret[i*width + j].b = b[count / 2];
				}
			}
		}

	}
	return ret;
}
