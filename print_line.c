//
//  main.c
//  printLine
//
//  Created by YukiSato on 2015/05/13.
//  Copyright (c) 2015年 YukiSato. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP.h"

#define TOTAL 100
#define AMOUNT 12

void line(BMPStruct, int, int, int, int);
void v_line_u(BMPStruct bmp, int x, int y1, int y2, RGB rgb);
void v_line_d(BMPStruct bmp, int x, int y1, int y2, RGB rgb);

int main(int argc, char const *argv[]) {
	int count, firstpoint_x, firstpoint_y;
	int point_data[TOTAL][5] = {};// id x y nearest flag
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み
	BMPStruct line_bmp, point_bmp;
	RGB rgb;

	if (fp_csv == NULL) {
		printf("file open error");
		exit(1);
	}
	fseek( fp_csv, 0, SEEK_SET );

	rgb.b = 255;
	rgb.g = 255;
	rgb.r = 255;
	makeBMP(&line_bmp, 1000, 1000, rgb);
	makeBMP(&point_bmp, 1000, 1000, rgb);
	rgb.b = 0;
	rgb.g = 0;
	rgb.r = 0;
	
	count = 0;
	while( fscanf( fp_csv, "%d,%d,%d,%d", &point_data[count][0], &point_data[count][1], &point_data[count][2], &point_data[count][3]) != EOF) {
	//	printf("%d,%d,%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2], point_data[count][3], point_data[count][4]);

		if (point_data[count][3] % 2 == 0) {
			rgb.g = 0;
			rgb.b = 255;
			rgb.r = 0;
		} else {
			rgb.g = 255;
			rgb.b = 0;
			rgb.r = 100;
		}

		putColor(line_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10-1), rgb);
		putColor(line_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10  ), rgb);
		putColor(line_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10+1), rgb);
		putColor(line_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10-1), rgb);
		putColor(line_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10  ), rgb);
		putColor(line_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10+1), rgb);
		putColor(line_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10-1), rgb);
		putColor(line_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10  ), rgb);
		putColor(line_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10+1), rgb);
		rgb.b = 0;
		rgb.g = 0;
		rgb.r = 0;
		putColor(point_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10-1), rgb);
		putColor(point_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10  ), rgb);
		putColor(point_bmp, (point_data[count][1]*10-1), (point_data[count][2]*10+1), rgb);
		putColor(point_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10-1), rgb);
		putColor(point_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10  ), rgb);
		putColor(point_bmp, (point_data[count][1]*10  ), (point_data[count][2]*10+1), rgb);
		putColor(point_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10-1), rgb);
		putColor(point_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10  ), rgb);
		putColor(point_bmp, (point_data[count][1]*10+1), (point_data[count][2]*10+1), rgb);

		count ++;
	}

	firstpoint_x = point_data[0][1];
	firstpoint_y = point_data[0][2];
	for (int j = 1; j < AMOUNT; j++) {
		for (int i = 0; i<count; i++) {
			if (point_data[i][3] == j && point_data[i+1][3] == j) {
				line(line_bmp, point_data[i][1]*10, point_data[i][2]*10, point_data[i+1][1]*10, point_data[i+1][2]*10);
				if (i == (count-2)) {
					line(line_bmp, point_data[i+1][1]*10, point_data[i+1][2]*10, firstpoint_x*10, firstpoint_y*10);
				}
			} else if (point_data[i][3] == j && point_data[i+1][3] == (j+1)) {
				line(line_bmp, point_data[i][1]*10, point_data[i][2]*10, firstpoint_x*10, firstpoint_y*10);
				firstpoint_x = point_data[i+1][1];
				firstpoint_y = point_data[i+1][2];
			}
		}
	}

	writeBMP(line_bmp, "line_result.bmp");
	writeBMP(point_bmp, "point_result.bmp");
	
	fclose(fp_csv);

	return 0;
}

void v_line_u(BMPStruct bmp, int x, int y1, int y2, RGB rgb) {
	putColor(bmp, x, y1, rgb);
	for(int y = y1; y <= y2; y++) {
		putColor(bmp, x, y, rgb);
	}
}

void v_line_d(BMPStruct bmp, int x, int y1, int y2, RGB rgb) {
	putColor(bmp, x, y1,rgb);
	for(int y = y1; y >= y2; y--) {
		putColor(bmp, x, y, rgb);
	}
}

void line(BMPStruct bmp, int x1, int y1, int x2, int y2) {
	int x, t;
	float a;
	RGB rgb;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	
	if(x1 > x2) {
		t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t;
	}
	
	a = (float)((y2 - y1) + 1) / ((x2 - x1) + 1);
	
	if(y2 > y1) {
		for(x = x1; x < x2; x++) {
			v_line_u(bmp, x, (int)(y1 + a * (x - x1)), (int)(y1 + a * (x  - x1 + 1) - 1), rgb);
		}
		v_line_u(bmp, x2, (int)(y1 + a * (x - x1)), y2, rgb);
	} else {
		for(x = x1; x < x2; x++) {
			v_line_d(bmp, x, (int)(y1 + a * (x - x1)), (int)(y1 + a * (x - x1 + 1) + 1), rgb);
		}
		v_line_d(bmp, x2, (int)(y1 + a * (x - x1)), y2, rgb);
	}
}