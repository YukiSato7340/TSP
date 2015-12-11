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

double angle_calculation(double, double, double, double, double, double);
double med3(double, double, double);
void quick_sort(double[TOTAL][5], int, int);
void graham_scan(double[TOTAL][5], double[TOTAL][5], int, int);
int measure(int, int, int, int);
int do_travel(int[TOTAL][5]);

int main(int argc, const char * argv[]) {
	int count, amount, flag, j;
	double point_data[TOTAL][5] = {};// id x y angle flag
	double post_data[TOTAL][5] = {};// id x y angle flag
	double get_data[TOTAL][5] = {};// id x y angle flag
	int result_data[TOTAL][5] = {};// id x y nearest flag
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
			post_data[i][j] = point_data[i][j];
		}
	}
 
	flag = 0;
	amount = 0;

	while(1) {
		flag ++;
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < 5; j++) {
				get_data[i][j] = 0.0;
			}
		}

		graham_scan(post_data, get_data, count, flag);
		for (int i = 0; i < count; i++) {
			printf("post_data[%2d] = %2d %2d %2d %3.6lf %d\n", i, (int)post_data[i][0], (int)post_data[i][1], (int)post_data[i][2], post_data[i][3], (int)post_data[i][4]);
			for (int j = 0; j < 5; j++) {
				post_data[i][j] = 0.0;
			}
		}
	//	amount = 0;
		for (int i = 0; i < count; i++) {
			if ((i != 0) && ((int)get_data[i][0] == 0)) {
				amount = i;
				break;
			}	
			printf("get_data[%2d] = %2d %2d %2d %3.6lf %d\n", i, (int)get_data[i][0], (int)get_data[i][1], (int)get_data[i][2], get_data[i][3], (int)get_data[i][4]);
			fprintf(fp_result, "%d,%d,%d,%d\n", (int)get_data[i][0], (int)get_data[i][1], (int)get_data[i][2], (int)get_data[i][4]);
		}
		printf("flag = %d count = %d amount = %d\n", flag, count, amount);

		for (int i = 0; i < amount; i++) {
			point_data[(int)get_data[i][0]][4] = (double)flag;
		}
		j = 0;
		for (int i = 0; i < TOTAL; i++) {
			printf("point_data[%d] flag = %d\n", (int)point_data[i][0], (int)point_data[i][4]);
			if ((int)point_data[i][4] == -1) {
				printf("point_data[%d] flag = %d\n", (int)point_data[i][0], (int)point_data[i][4]);
				for (int k = 0; k < 5; k++) {
					post_data[j][k] = point_data[i][k];
				}
				j++;
			}
		}

		printf("j = %d count = %d amount = %d\n", j, count, amount);
		count -= amount;
		if (j == count) {
			printf("true\n");
		} 		
		if (count <= 2) {
			printf("last tow points.\n");
			flag ++;
			for (int i = 0; i < count; ++i) {
				fprintf(fp_result, "%d,%d,%d,%d\n", (int)post_data[i][0], (int)post_data[i][1], (int)post_data[i][2], flag);
			}
			break;
		}
	}
	
	fclose(fp_csv);
	fclose(fp_result);

	return 0;
}

double angle_calculation(double o_x, double o_y, double a_x, double a_y, double b_x, double b_y) {
	double angle, angle1, angle2;
	double point1_x, point1_y, point2_x, point2_y;
	
	point1_x = a_x - o_x;
	point1_y = a_y - o_y;
	point2_x = b_x - o_x;
	point2_y = b_y - o_y;
	
	//事象判別
	if (point1_x == 0) {
		
	}
	
	angle1=acos(point1_x/sqrt(point1_x*point1_x+point1_y*point1_y));
	angle1=angle1*180.0/M_PI;
	if(point1_y < 0) {
		angle1=360.0-angle1;
	}
	
	angle2=acos(point2_x/sqrt(point2_x*point2_x+point2_y*point2_y));
	angle2=angle2*180.0/M_PI;
	if(point2_y < 0) { 
		angle2=360.0-angle2;
	}
 
	angle = angle2 - angle1;
	if (angle < 0) {
		angle += 360;
	}
	//printf("角度=%lf",angle);
	return angle;
}

double med3(double x, double y, double z) {/* x, y, z の中間値を返す */
	if (x < y) {
		if (y < z) return y;
		else if (z < x) return x;
		else return z;
	} else {
		if (z < y) return y;
		else if (x < z) return x;
		else return z;
	}
}

void quick_sort(double point_data[TOTAL][5], int left, int right)/*
 * クイックソート
 * data  : ソートする配列
 * left  : ソートするデータの開始位置 0
 * right : ソートするデータの終了位置 TOTAL - 1
 */{
	if (left < right) {
		int i = left, j = right;
		double pivot = med3(point_data[i][3], point_data[i + (j - i) / 2][3], point_data[j][3]); /* (i+j)/2ではオーバーフローしてしまう */
		double tmp[5];
		while (1) { /* a[] を pivot 以上と以下の集まりに分割する */
			while (point_data[i][3] < pivot) i++; /* data[i] >= pivot となる位置を検索 */
			while (pivot < point_data[j][3]) j--; /* data[j] <= pivot となる位置を検索 */
			if (i >= j) break;
			for (int k = 0; k < 5; ++k) {
				tmp[k] = point_data[i][k];
				point_data[i][k] = point_data[j][k];
				point_data[j][k] = tmp[k]; /* a[i],a[j] を交換 */
			}
			i++;
			j--;
		}
		quick_sort(point_data, left, i - 1);  /* 分割した左を再帰的にソート */
		quick_sort(point_data, j + 1, right); /* 分割した右を再帰的にソート */
	}
//	return point_data;	
}

void graham_scan(double post_data[TOTAL][5], double get_data[TOTAL][5], int total, int flag) {
	int min, count;
	double sorted_by_angle_data[TOTAL][5];
	
	//yの最小値を見つける
	min = 0;
	for (int i = 1; i < total; i++) {
		if (((int)post_data[min][2] > (int)post_data[i][2]) || (((int)post_data[min][2] == (int)post_data[i][2]) && ((int)post_data[min][1] > (int)post_data[i][1]))) {
			min = i;
		}
	}
	
	//角度のリストを作成
	for (int i = 0; i < total; i++) {
		if (i == min) {
			post_data[i][3] = -1.0;//0.0;
		} else {
			post_data[i][3] = angle_calculation(post_data[min][1], post_data[min][2], post_data[min][1]+1, post_data[min][2], post_data[i][1], post_data[i][2]);
		}
		for (int j = 0; j < 5; ++j) {
			sorted_by_angle_data[i][j] = post_data[i][j];
		}
	}
	
	//角度のリストをソート
	quick_sort(sorted_by_angle_data, 0, total-1);
	
	//初期点挿入
	for (int i = 0; i < 4; ++i) {
		get_data[0][i] = sorted_by_angle_data[0][i];
		get_data[1][i] = sorted_by_angle_data[1][i];
	}
	get_data[0][4] = flag;
	get_data[1][4] = flag;

	count = 2;
	//比較参照　削除
	for (int i = 2; i < total; i++) {
		if (angle_calculation(get_data[count-1][1], get_data[count-1][2], get_data[count-2][1], get_data[count-2][2], sorted_by_angle_data[i][1], sorted_by_angle_data[i][2]) >= 180.0) {//凸包頂点だった時
			for (int j = 0; j < 4; ++j) {
				get_data[count][j] = sorted_by_angle_data[i][j];
			}
			get_data[count][4] = (double)flag;
			count ++;
		} else {//凸包頂点でなかった時
			do {//遡って凸包頂点になるまで戻る
				for (int j = 0; j < 4; ++j) {
					get_data[count-1][j] = 0.0;
				}
				get_data[count-1][4] = -1.0;
				count --;
			} while (angle_calculation(get_data[count-1][1], get_data[count-1][2], get_data[count-2][1], get_data[count-2][2], sorted_by_angle_data[i][1], sorted_by_angle_data[i][2]) < 180.0);
			for (int j = 0; j < 4; ++j) {
				get_data[count][j] = sorted_by_angle_data[i][j];
			}
			get_data[count][4] = (double)flag;
			count ++;
		}
	}
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
