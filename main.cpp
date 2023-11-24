#include "Mat.h"

void main()
{
	Mat m1;
	Mat m3(INIT_MASK);
	Mat* corr;

	cout << "mat m1" << endl;
	m1.printMat();
	cout << "mask" << endl;
	m3.printMat();
	cout << "corr" << endl;
	corr = m1.corr2D(m3);
}