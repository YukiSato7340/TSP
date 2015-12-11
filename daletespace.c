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

#define TOTAL 190000
#define WIDTH 100
#define HEIGHT 100

int main(int argc, char const *argv[]) {
	int count;
	int point_data[TOTAL][5] = {};// id x y nearest flag
	int result_data[TOTAL][5] = {};// id x y nearest flag
	FILE *fp_csv = fopen(argv[1], "r");//csv読み込み
	FILE *fp_result = fopen(argv[2], "w");//結果出力用

	if (fp_csv == NULL) {
		printf("file open error\n");
		exit(1);
	}
	count = 0;
	printf("houu\n");
	while( fscanf( fp_csv, "%d %d %d", &point_data[count][0], &point_data[count][1], &point_data[count][2]) != EOF) {
	//	printf("%d,%d,%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2], point_data[count][3], point_data[count][4]);
		printf("koko\n");
		fprintf( fp_result, "%d,%d,%d\n", point_data[count][0], point_data[count][1], point_data[count][2]);
		count ++;
	}

	fclose(fp_csv);
	fclose(fp_result);

	return 0;
}