#pragma once
#include <iostream>
using namespace std;

#define MAX_MAT_SIZE 1000

typedef enum {
	INIT_TEST = 0x00,
	INIT_MASK = 0x01
}init_opt;

class Mat {
	int mat[MAX_MAT_SIZE];
	int n, m;

	void initTestMat();
	void initMask(int k);
public:
	void set_dim(int n, int m) { this->n = n; this->m = m; };
	int get_n() { return n; };
	int get_m() { return m; };
	void printMat();
	void paddMe(int xpad, int ypad);
	void unpadMe(int xpad, int ypad);
	int wSum(Mat& oth, int offset = 0);
	Mat* corr2D(Mat& mask);
	Mat(init_opt init = INIT_TEST, int n = 3, int m = 4);
	Mat(Mat& oth, int xpad = 0, int ypad = 0);
	~Mat() { memset((this->mat), 0, sizeof(int) * (this->n * this->m)); this->n = 0; this->m = 0; };
};
