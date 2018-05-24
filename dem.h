//Author: Tasmania University
#include <stdlib.h>
#include <stdio.h>

int** make_dem(int size, int roughness) {
    int x, y, step, cx, cy;
	int seed = time(NULL);
	srand(seed);
	int** dem = malloc(size * sizeof *dem);
	for (x = 0; x < size; x++) {
		dem[x] = malloc(size * sizeof *dem[x]);
		for (y = 0; y < size; y++) {
			dem[x][y] = -1;
		}
	}
	int r = roughness;

	dem[0][0] =				50 - r / 2 + rand() % r;
	dem[size-1][0] =		50 - r / 2 + rand() % r;
	dem[0][size-1] =		50 - r / 2 + rand() % r;
	dem[size-1][size-1] =	50 - r / 2 + rand() % r;

	for (step = (size - 1); step > 0; step /= 2) {
		r = r > 1 ? r / 2:r;
		if (r < 1) r = 1;
		for (cx = 0; cx < (size-1) / step; cx++) {
			for (cy = 0; cy < (size-1) / step; cy++) {
				int a = dem[cx*step][cy*step];
				int b = dem[cx*step+step][cy*step];
				int c = dem[cx*step][cy*step+step];
				int d = dem[cx*step+step][cy*step+step];

				dem[cx*step + step / 2][cy*step + step / 2] = (a + b + c + d) / 4 + rand() % r - r/2;

				dem[cx*step + step / 2][cy*step]		= (a + b) / 2 + rand() % r - r/2;
				dem[cx*step][cy*step + step / 2]		= (a + c) / 2 + rand() % r - r/2;
				dem[cx*step + step][cy*step + step / 2] = (b + d) / 2 + rand() % r-r/2;
				dem[cx*step + step/2][cy*step + step]	= (c + d) / 2 + rand() % r-r/2;
			}
		}
	}
	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			dem[x][y] = dem[x][y]<0	? 0 : dem[x][y];
			dem[x][y] = dem[x][y]>99? 99: dem[x][y];
		}
	}
	return dem;
}

int cost_funcA(int diff) {
	int cost = 1;
	if (diff > 0) cost += diff * diff;
	return cost;
}

int cost_funcB(int diff) {
	int cost = 1;
	if (diff > 0)
		cost += diff * diff;
	else
		cost += diff;
	return cost;
}

void print_2D(int** array2D, int size) {
    int x, y;
	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			if (array2D[x][y] > 0) {
				printf("%2d ", array2D[x][y]);
			}
			else {
				printf("() ");
			}
		}
		printf("\n");
	}
}

void print_2D_ascii(int** array2D, int size) {
	char *shades = " .-:=+*#%@";
	int x, y;
	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			if (array2D[x][y] >= 0) {
				char shade = shades[array2D[x][y] * 10 / 100];
				printf("%c%c", shade, shade);
			} else {
				printf("()");
			}
		}
		printf("\n");
	}
}
