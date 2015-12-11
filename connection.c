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
#define AMOUNT 12

int main(int argc, char const *argv[])
{
	int x0, y0, count;
	double point_data[TOTAL][5] = {};// id x y angle flag
	double a, b, c, distance;
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み
	FILE *fp_result = fopen(argv[2], "w");//結果出力用

	if (fp_csv == NULL) {
		printf("fp_csv file open error\n");
		exit(1);
	}	
	if (fp_result == NULL) {
		printf("fp_result file open error\n");
		exit(1);
	}

	count = 0;
	while( fscanf( fp_csv, "%lf,%lf,%lf,%lf,%lf", &point_data[count][0], &point_data[count][1], &point_data[count][2], &point_data[count][3], &point_data[count][4]) != EOF) {
		point_data[count][4] = -1;
	//	printf("%d,%d,%d,%lf,%d\n", (int)point_data[count][0], (int)point_data[count][1], (int)point_data[count][2], point_data[count][3], (int)point_data[count][4]);
		count ++;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 5; j++) {
			
		}
	}


	distance = fabs(a * x0 + b * y0 + c) / sqrtl(a*a+b*b);
	return 0;
}