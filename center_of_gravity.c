//
//  center_of_gravity.c
//
//  Created by YukiSato on 2015/08/08.
//  Copyright (c) 2015年 YukiSato. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 100
#define WIDTH 100
#define HEIGHT 100

int main(int argc, const char * argv[]) {
	int count;
	int point_data[TOTAL][5] = {};// id x y nearest flag
	double gravity_x = 0, gravity_y = 0, A = 0;
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み

	if (fp_csv == NULL) {
		printf("file open error\n");
		exit(1);
	}

	count = 0;
	while( fscanf( fp_csv, "%d,%d,%d,%d,%d", &point_data[count][0], &point_data[count][1], &point_data[count][2], &point_data[count][3], &point_data[count][4]) != EOF) {
	//	printf("%d,%d,%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2], point_data[count][3], point_data[count][4]);
		count ++;
	}

	for (int i = 0; i < count; i++) {
		if (i == (count - 1)) {
			A += ((point_data[0][1] - point_data[i][1]) * (point_data[0][2] + point_data[i][2]));
		} else {
			A += ((point_data[i+1][1] - point_data[i][1]) * (point_data[i+1][2] + point_data[i][2]));
		}
	}
	A = fabs(A);
	A *= 0.5;

	for (int i = 1; i < count - 1; i++) {
		gravity_x += (abs(((point_data[i][1] - point_data[0][1]) * (point_data[i][2] + point_data[0][2])) + ((point_data[i+1][1] - point_data[i][1]) * (point_data[i+1][2] + point_data[i][2])) + ((point_data[0][1] - point_data[i+1][1]) * (point_data[0][2] + point_data[i+1][2]))) / 2) * ((point_data[0][1] + point_data[i][1] + point_data[i+1][1]) / 3);
		gravity_y += (abs(((point_data[i][1] - point_data[0][1]) * (point_data[i][2] + point_data[0][2])) + ((point_data[i+1][1] - point_data[i][1]) * (point_data[i+1][2] + point_data[i][2])) + ((point_data[0][1] - point_data[i+1][1]) * (point_data[0][2] + point_data[i+1][2]))) / 2) * ((point_data[0][2] + point_data[i][2] + point_data[i+1][2]) / 3);
	}
	gravity_x /= A;
	gravity_y /= A;

	printf("gravity_x = %lf\ngravity_y = %lf\n", gravity_x, gravity_y);

	return 0;
}
