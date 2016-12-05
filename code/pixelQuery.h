#ifndef PIXELQUERY
#define PIXELQUERY
#include<vector>
using namespace std;

void pixelQuery(int *neighbours,int neighboursP[5],int &num_neighb)
{
    bool tt;
    for(int i=0;i<5;i++)
    {
        if (neighboursP[i]!=0)
        {
            tt=true;
            for(int j=0;j<num_neighb+1;j++)
                if(neighboursP[i]==neighbours[j])
                {
                    tt=false;
                    break;
                }
            if(tt==true)
            {
                neighbours[++num_neighb]=neighboursP[i];
            }
            neighboursP[i]=0;
        }
    }
        return;
}

#endif
