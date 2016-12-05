#ifndef INITIALIZE
#define INITIALIZE

#include"pixelQuery.h"
#include<cmath>
using namespace std;

void neighb0(unsigned short* label,int n, int Rows, int Cols,int ngb[5])
    {
         int j=0;
         int x,y;
         x=n/Cols;
         y=n%Cols;
         if(y>0&&label[n-1]!=label[n])ngb[j++]=label[n-1];
         if(x>0&&label[n-Cols]!=label[n])ngb[j++]=label[n-Cols];
         if(y<Cols-1&&label[n+1]!=label[n])ngb[j++]=label[n+1];
         if(x<Rows-1&&label[n+Cols]!=label[n])ngb[j++]=label[n+Cols];
    }

void supiel_neighbs(unsigned short* label,int *neighb,int ngb[5],int np, int Rows, int Cols, int &num_neighb)//unsigned char* L, unsigned char* a, unsigned char* b, int Rows, int Cols,int n,int* L0,int* a0,int* b0)
    {
    neighb0(label,np,Rows,Cols,ngb);  
    pixelQuery(neighb,ngb,num_neighb);
    }

#endif