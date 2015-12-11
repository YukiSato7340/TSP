//
//  main.c
//  TSP
//
//  Created by YukiSato on 2015/01/26.
//  Copyright (c) 2015年 YukiSato. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 100
#define WIDTH 100
#define HEIGHT 100

int measure(int, int, int, int);
int do_travel(int[TOTAL][5]);

int main(int argc, char const *argv[]) {
	int count, distance;
	int point_data[TOTAL][5] = {};// id x y nearest flag
	int result_data[TOTAL][5] = {};// id x y nearest flag
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み
	FILE *fp_result = fopen(argv[2], "w");//結果出力用

	if (fp_csv == NULL) {
		printf("file open error\n");
		exit(1);
	}

	count = 0;
	while( fscanf( fp_csv, "%d,%d,%d,%d,%d", &point_data[count][0], &point_data[count][1], &point_data[count][2], &point_data[count][3], &point_data[count][4]) != EOF) {
	//	printf("%d,%d,%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2], point_data[count][3], point_data[count][4]);
		count ++;
	}

	distance = 0;
	
	point_data[0][4] = 1;
	for (int i = 0; i < 5; ++i) {
		result_data[0][i] = point_data[0][i];
	}

	for (int i = 0; i < TOTAL - 1; i++) {
		distance = -1;
		for (int j = 0; j < TOTAL; j++) {
			if (point_data[j][4] != 1 && ((distance == -1) || ((distance != -1) && (distance > measure(result_data[i][1], result_data[i][2], point_data[j][1], point_data[j][2]))))) {
				distance = measure(result_data[i][1], result_data[i][2], point_data[j][1], point_data[j][2]);
				result_data[i][3] = j;//point_data[j][0]
			}
		}
		point_data[result_data[i][3]][4] = 1;
		for (int k = 0; k < 5; k++) {
			result_data[i+1][k] = point_data[result_data[i][3]][k];
		}
	}

	for (int i=0; i<TOTAL; i++) {
		fprintf(fp_result, "%d,%d,%d,%d,%d\n", result_data[i][0], result_data[i][1], result_data[i][2], result_data[i][3], result_data[i][4]);
	//	printf("%d,%d,%d,%d,%d\n", result_data[i][0], result_data[i][1], result_data[i][2], result_data[i][3], result_data[i][4]);
	}

	printf("distance = %d\n", do_travel(result_data));

	fclose(fp_csv);
	fclose(fp_result);

	return 0;
}

int measure(int prev_x, int prev_y, int next_x, int next_y) {
	int x, y;
	
	x = next_x - prev_x;
	y = next_y - prev_y;
	if (x < 0) x *= -1;
	if (y < 0) y *= -1;
	
	return (x * x) + (y * y);
}

int do_travel(int data[TOTAL][5]) {
	int travel_distance = 0;
	
	for (int i=0; i<TOTAL-1; i++) {
		travel_distance += measure(data[i][1], data[i][2], data[i+1][1], data[i+1][2]);
	}
	
	return travel_distance;
}
