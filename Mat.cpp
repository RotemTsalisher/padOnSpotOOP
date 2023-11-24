#include "Mat.h"

Mat::Mat(init_opt init, int n, int m)
{
	if (init && 0x01)
	{
		int k;
		cout << "enter distance k = ";
		cin >> k;
		this->n = (k << 1) + 1;
		this->m = (k << 1) + 1;
		initMask(k);
	}
	else if (!(init && 0x00))
	{
		this->n = n;
		this->m = m;
		initTestMat();
	}
}
void Mat::initTestMat()
{
	*(mat) = 1;
	*(mat + 1) = 0;
	*(mat + 2) = 0;
	*(mat + 3) = 0;
	*(mat + 4) = 0;
	*(mat + 5) = 1;
	*(mat + 6) = 1;
	*(mat + 7) = 0;
	*(mat + 8) = 0;
	*(mat + 9) = 0;
	*(mat + 10) = 0;
	*(mat + 11) = 1;
}
void Mat::initMask(int k)
{
	int i, j;

	for (i = 0; i < this->n; i++)
	{
		for (j = 0; j < this->m; j++)
		{
			if (
				((i - k < 0) && (j - k < 0) && (i + j - (k << 1) >= -k)) ^
				((i - k < 0) && (j - i <= k)) ^
				((j - k < 0) && (i - j <= k)) ^
				((i - k >= 0) && (j - k >= 0) && (i + j - (k << 1) <= k)))
			{
				*(mat + m * i + j) = 1;
			}
			else
			{
				*(mat + m * i + j) = 0;
			}
		}
	}
}
void Mat::printMat()
{
	int i, j;

	cout << "PRINTING " << this->n << "x" << this->m << " MAT:" << endl;
	for (i = 0; i < this->n; i++)
	{
		for (j = 0; j < this->m; j++)
		{
			cout << "| " << *(mat + m * i + j) << " |";
		}
		cout << endl;
	}
}
Mat::Mat(Mat& oth, int xpad, int ypad)
{
	int i, j;

	this->n = oth.get_n() + (ypad << 1);
	this->m = oth.get_m() + (xpad << 1);

	for (i = 0; i < this->n; i++)
	{
		for (j = 0; j < this->m; j++)
		{
			if ( (i < ypad) || (j < xpad) || (i > (oth.get_n() - 1) + ypad) || (j >(oth.get_m() - 1) + xpad))
			{
				*(this->mat + this->m * i + j) = 0;
			}
			else
			{
				*(this->mat + this->m * i + j) = *(oth.mat + oth.get_m() * (i - ypad) + (j - xpad));
			}
		}
	}
}
void Mat::paddMe(int xpad, int ypad)
{
	int i, j,new_n,new_m;

	new_n = n + (ypad << 1);
	new_m = m + (xpad << 1);

	for (i = new_n-1; i > -1; i--)
	{
		for (j = new_m-1; j > -1; j--)
		{
			if ((i > (n - 1) + ypad) || (j > (m - 1) + xpad) || (i < ypad) || (j < xpad))
			{
				*(mat + new_m * i + j) = 0;
			}
			else
			{
				*(mat + new_m * i + j) = *(mat + m * (i - ypad) + (j - xpad));
			}
		}
	}
	n = new_n;
	m = new_m;
}
void Mat::unpadMe(int xpad, int ypad)
{
	int i, j, new_m, new_n;

	new_m = m - (xpad << 1);
	new_n = n - (ypad << 1);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			*(mat + new_m * i + j) = *(mat + m * (i + ypad) + (j + xpad));
		}
	}
	n = new_n;
	m = new_m;
}
int Mat::wSum(Mat& oth, int offset)
{
	int i, j, sum, xdim, ydim;

	xdim = (this->m < oth.get_m()) ? this->m : oth.get_m();
	ydim = (this->n < oth.get_n()) ? this->n : oth.get_n();

	sum &= 0x00;

	for (i = 0; i < ydim; i++)
	{
		for (j = 0; j < xdim; j++)
		{
			sum += (*(this->mat + offset + this->m * i + j)) * (*(oth.mat + oth.get_m() * i + j));
		}
	}
	return sum;
}
Mat* Mat::corr2D(Mat& mask)
{
	int i,j, xpad, ypad;
	Mat corr;
	
	corr.set_dim(this->n, this->m);
	xpad = (mask.get_m() - 1) >> 1;
	ypad = (mask.get_n() - 1) >> 1;

	this->paddMe(xpad, ypad);
	
	for (i = 0; i < (this->n*this->m) ; i++)
	{
		for (j = 0; j < this->m; j++)
		{
			*(corr.mat + corr.get_m()*i + j) = this->wSum(mask, (this->m*i + j));
		}

	}
	cout << "corr" << endl;
	corr.printMat();
	this->unpadMe(xpad, ypad);
	return &corr;
}