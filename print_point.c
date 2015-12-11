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

#define TOTAL 19000

int main(int argc, char const *argv[]) {
	int count;
	int point_data[TOTAL][5] = {};// id x y nearest flag
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み
	BMPStruct point_bmp;
	RGB rgb;

	if (fp_csv == NULL) {
		printf("file open error");
		exit(1);
	}
	fseek( fp_csv, 0, SEEK_SET );

	rgb.b = 255;
	rgb.g = 255;
	rgb.r = 255;
	printf("houu\n");
	makeBMP(&point_bmp, 10000, 10000, rgb);
	rgb.b = 0;
	rgb.g = 0;
	rgb.r = 0;
	printf("jouu\n");
	
	count = 0;
	while( fscanf( fp_csv, "%d,%d,%d", &point_data[count][0], &point_data[count][1], &point_data[count][2]) != EOF) {
	//	printf("%d,%d,%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2], point_data[count][3], point_data[count][4]);
		putColor(point_bmp, (point_data[count][1]-1), (point_data[count][2]-1), rgb);
		putColor(point_bmp, (point_data[count][1]-1), (point_data[count][2]  ), rgb);
		putColor(point_bmp, (point_data[count][1]-1), (point_data[count][2]+1), rgb);
		putColor(point_bmp, (point_data[count][1]  ), (point_data[count][2]-1), rgb);
		putColor(point_bmp, (point_data[count][1]  ), (point_data[count][2]  ), rgb);
		putColor(point_bmp, (point_data[count][1]  ), (point_data[count][2]+1), rgb);
		putColor(point_bmp, (point_data[count][1]+1), (point_data[count][2]-1), rgb);
		putColor(point_bmp, (point_data[count][1]+1), (point_data[count][2]  ), rgb);
		putColor(point_bmp, (point_data[count][1]+1), (point_data[count][2]+1), rgb);
		printf("%d\n", count);
		count ++;
	}

	writeBMP(point_bmp, "points.bmp");
	
	fclose(fp_csv);

	return 0;
}