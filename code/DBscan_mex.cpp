#include<mex.h>
#include<matrix.h>
#include<time.h>
#include"DBscan.h"


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{  
	unsigned char* R,* G,* B;
	int Rows;int Cols;
	unsigned short* label;
	unsigned short* output;
    double supnumber;
    int post;
	unsigned char* img;
    int *outputNumSuperpixels;
	

	Rows=mxGetM(prhs[0]);
	Cols=mxGetN(prhs[0])/3;
	img=(unsigned char*)mxGetPr(prhs[0]);
    supnumber=((double*)(mxGetPr(prhs[1])))[0];
    post=((double*)(mxGetPr(prhs[2])))[0];

	int pixel=Rows*Cols;
	R=new  unsigned char[pixel];
	G=new  unsigned char[pixel];
	B=new  unsigned char[pixel];
	label=new unsigned short[pixel];
	
     for(int j=0;j<Cols;j++)
       for(int i=0;i<Rows;i++)
	{
		R[i*Cols+j]=img[j*Rows+i];
		G[i*Cols+j]=img[j*Rows+i+pixel];
		B[i*Cols+j]=img[j*Rows+i+pixel+pixel];
        label[j*Rows+i]=0;
	}

    //--------------------------
    //  Compute superpixels
    //--------------------------
    int realnumber=0;
    DBscan(R,G,B,Rows,Cols,label,supnumber,realnumber,post);
    
    
	plhs[0]=mxCreateNumericMatrix(Rows,Cols,mxUINT16_CLASS,mxREAL);
	output=(unsigned short*)mxGetPr(plhs[0]);

   for(int j=0;j<Cols;j++)
    {
        for(int i=0;i<Rows;i++)
		output[j*Rows+i]=label[i*Cols+j];
    }
    
    delete [] R;
	delete [] G;
 	delete [] B;
	delete [] label;

}