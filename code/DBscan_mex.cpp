#include <mex.h>
#include <matrix.h>
#include <map>
#include <time.h>
#include "DBscan.h"


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	unsigned char* R, *G, *B;
	int Rows;int Cols;
	unsigned short* label;
	unsigned short* output;
	double supnumber;
	unsigned char* img;
	int *outputNumSuperpixels;


	Rows = mxGetM(prhs[0]);
	Cols = mxGetN(prhs[0]) / 3;
	img = (unsigned char*)mxGetPr(prhs[0]);
	supnumber = ((double*)(mxGetPr(prhs[1])))[0];

	int pixel = Rows*Cols;
	R = new  unsigned char[pixel];
	G = new  unsigned char[pixel];
	B = new  unsigned char[pixel];
	label = new unsigned short[pixel];

	for (int j = 0;j < Cols;j++)
		for (int i = 0;i < Rows;i++)
		{
			R[i*Cols + j] = img[j*Rows + i];
			G[i*Cols + j] = img[j*Rows + i + pixel];
			B[i*Cols + j] = img[j*Rows + i + pixel + pixel];
			label[j*Rows + i] = 0;
		}

	//--------------------------
	//  Compute superpixels
	//--------------------------
	int realnumber = 0;
	DBscan(R, G, B, Rows, Cols, label, supnumber, realnumber);


	plhs[0] = mxCreateNumericMatrix(Rows, Cols, mxUINT16_CLASS, mxREAL);
	output = (unsigned short*)mxGetPr(plhs[0]);

	//Sort labels from 1 to max, use heap instead of vector can make it faster
	map<unsigned short, unsigned short> o2n; // old label to new label, unorganized to organized number
	//vector<unsigned short> old_label;
	int pixel_num = pixel, new_label = 1;
	map<unsigned short, unsigned short>::iterator mit;
	//vector<unsigned short>::iterator vit;
	for (int i = 0; i < pixel_num; i++) {
		int old_label = label[i];
		if (o2n.find(old_label) == o2n.end()) {
			// Assign new label number
			o2n[old_label] = new_label;
			new_label++;
		}
	}

	for (int i = 0; i < pixel_num; i++) {
		label[i] = o2n[label[i]];
	}


	for (int j = 0;j < Cols;j++)
	{
		for (int i = 0;i < Rows;i++)
			output[j*Rows + i] = label[i*Cols + j];
	}

	delete[] R;
	delete[] G;
	delete[] B;
	delete[] label;

}
