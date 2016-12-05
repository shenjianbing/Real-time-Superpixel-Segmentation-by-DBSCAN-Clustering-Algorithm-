#ifndef DBSCAN
#define DBSCAN
#include"regionQuery.h"
#include"supiel_neighbs.h"
using namespace std;

//DBSCAN superpixel segmentation algorithm
int numb(int *a)
    {
    for(int i=0;;i++)
        if (a[i]==0&&a[i+1]==0)return i;
       return 0;
    }
void mergin(int n,unsigned char* R, unsigned char* G, unsigned char* B,int Rows,
        int Cols,unsigned short* label, double *labelsL,double *labelsa,double *labelsb,double*labelsx,double *labelsy)
{
    int k,bl,m;
     int *ngt,*ngt1;//*lab,*ngt1;
 int pixelnum=Rows*Cols;
    ngt=new int [100];
//     lab= new int [100];
   ngt1=new int [100];
   
    for(int i=0;i<100;i++){ngt[i]=0;ngt1[i]=0;}//lab[i]=0;ngt1[i]=0;}
    ngt[0]=n;
    //lab[0]=n;
    k=1;m=0;
    for(int j=0;j<k;j++)
    {
        n=ngt[j];
        bl=1;
        if(label[n+1]==label[n]) 
        { 
            for(int i=0;bl==1;i++)
            { 
                if(ngt[i]==n+1) bl=0;
                if(ngt[i]==0) {ngt[i]=n+1;k++;break;}
            }
        }
        else
        {
            ngt1[m]=n+1;
            m++;
        }
        
        bl=1;
        if(label[n-1]==label[n]) 
        {
            for(int i=0;bl==1;i++)
            { 
                if(ngt[i]==n-1) bl=0;
                if(ngt[i]==0){ ngt[i]=n-1;k++;break;}
            }
           
        }
         else
        {
            ngt1[m]=n-1;
            m++;
        }
        
        bl=1;
        if(label[n+Cols]==label[n]) 
        {
            for(int i=0;bl==1;i++)
            { 
                if(ngt[i]==n+Cols) bl=0;
                if(ngt[i]==0){ ngt[k]=n+Cols;k++;break;}
            }
            
        }
         else
        {
            ngt1[m]=n+Cols;
            m++;
        }
        
        bl=1;
        if(label[n-Cols]==label[n]) 
        {
            for(int i=0;bl==1;i++)
            {
                if(ngt[i]==n-Cols) bl=0;
                if(ngt[i]==0) {ngt[k]=n-Cols;k++;break;}
            }
        }
         else
        {
            ngt1[m]=n-Cols;
            m++;
        }
        if(k>30)break;
        
    }
       if(k<30)
       {
           int t,lab;
           double ll=0,aa=0,bb=0,x=0,y=0;
           for(int i=0;i<k;i++)
           {
               t=ngt[i];
               ll=ll+R[t];
               aa=aa+G[t];
               bb=bb+B[t];
//                x=x+t/Cols;
//                y=y+t%Cols;
           }
           ll=ll/k;
           aa=aa/k;
           bb=bb/k;
//            x=x/k;
//            y=y/k;
           double dist,mx=10000;
           int tlab;
           for(int i=0;i<m;i++)
           {
               t= ngt1[i];
               if(t<pixelnum&&t>0)
               {
//                lab=label[t];
               
                dist=(ll-R[t])*(ll-R[t])+(aa-G[t])*+(aa-G[t])+(bb-B[t])*(bb-B[t]);
//                  dist=dist+((labelsx[lab]-x)*(labelsx[lab]-x)+(labelsy[lab]-y)*(labelsy[lab]-y))*1;
               if(dist<mx)
               {
                   mx=dist;
                   tlab=t;
               }
               }
           }
           for(int i=0;i<k;i++)label[ngt[i]]=label[tlab];
       }
     delete [] ngt;
   delete [] ngt1;
}

void DBscan( unsigned char* R, unsigned char* G, unsigned char* B,int Rows,int Cols,unsigned short* label,double supnumber,int &realnumber,int post)
{
    int pixel=Rows*Cols;
    supnumber=supnumber*1.1;
    supnumber=  pixel/supnumber;
    unsigned int *labnumb; //number pixels in superpixel
	labnumb=new unsigned int[pixel];
    int Nc=0,nb;
    bool *label0;
    label0=new bool[pixel];
    for(int i=0;i<pixel;i++)label0[i]=0;
    
    int **ngbC; //record detail pixel in each superpixel 
    ngbC=new int*[pixel];
    int *neighbours=new int[supnumber*2];
    for(int i=0;i<supnumber*2;i++)neighbours[i]=0;
    int numbngb;
     
     //////////***********clustering stage******************///////////// 
    for(int i=0;i<pixel;i++)
    {
        if(!label[i])
        {
            Nc=Nc+1;        //Nc is the superpixel number
            numbngb=0;
            label[i]=Nc;
            label0[i]=1;    //label0 is a sign, if label0[i]=1, pixel i have a label, Otherwise contrary
            regionQuery(neighbours,numbngb, R, G, B,i,i, Rows, Cols, label, label0);// and find its neighbours
            
            int ind=0;
            int num=1;
            
            while(ind<numbngb)//
            {
                nb = neighbours[ind];
                label[nb] = Nc;   // mark it as visited.
//                 ngbC[Nc][num]=nb;
                num=num+1;
                   // Find the neighbours of this neighbour and 
                   // add them to the neighbours list
                   if  (i<Cols&&num<(supnumber*1.33))
                   {
                       regionQuery(neighbours,numbngb,R, G, B,i,nb, Rows, Cols,label,label0);
                   }
                   else if(num<supnumber) 
                   {
                       regionQuery(neighbours,numbngb, R, G, B,i,nb, Rows, Cols,label,label0);
                   }
               ind = ind + 1;
            }
            
            ngbC[Nc]=new int[num];
            ngbC[Nc][0]=i;
             for(int k=0;k<ind;k++)
             {
                 ngbC[Nc][k+1]=neighbours[k];
                 neighbours[k]=0;
             }
            labnumb[Nc]=ind+1;
        }
    }
     //////////////////////////merging stage/////////////////////////////////////
     int dr0,dg0,db0,Nc1=Nc;
     double R0,G0,B0,dr1,dg1,db1,x0,x1,y0,y1;
     double *labelsR,*labelsG,*labelsB,*labelsx,*labelsy;
     labelsR=new double[Nc+1];
     labelsG=new double[Nc+1];
     labelsB=new double[Nc+1];
     labelsx=new double[Nc+1];
     labelsy=new double[Nc+1];
     int t;
     double labels;
     /////////////find initail superpixel central//////////////
      for (int n=1;n<=Nc;n++)
     {
          labelsR[n]=0;
          labelsG[n]=0;
          labelsB[n]=0;
          labelsx[n]=0;
          labelsy[n]=0;
           for(int j=0;j<labnumb[n];j++)
             {
               t=ngbC[n][j];
               labelsR[n]=labelsR[n]+R[t];
               labelsG[n]=labelsG[n]+G[t];
               labelsB[n]=labelsB[n]+B[t];
               labelsx[n]=labelsx[n]+t/Cols;
               labelsy[n]=labelsy[n]+t%Cols;
             }
           labels=labnumb[n];
           labelsR[n]=labelsR[n]/labels;
           labelsG[n]=labelsG[n]/labels;
           labelsB[n]=labelsB[n]/labels;
           labelsx[n]=labelsx[n]/labels;
           labelsy[n]=labelsy[n]/labels;
      }
    
   
      
    int ngb[5],num_neighb;
    for(int i=0;i<5;i++)ngb[i]=0;
    
    int *neighb=new int[5000];
    for(int i=0;i<5000;i++)neighb[i]=0;
    
     for (int n=1;n<=Nc;n++)
     {
        if (labnumb[n]<supnumber&&labnumb[n]>0)
        {
            
            num_neighb=-1;
            
            for(int j=0;j<labnumb[n];j++)
            {
                 supiel_neighbs(label,neighb,ngb,ngbC[n][j],Rows,Cols,num_neighb);
            }
             
           double minlab=100000,dista;
           int minnum=0,mn;
                    
            R0=labelsR[n];
            G0=labelsG[n];
            B0=labelsB[n];
            x0= labelsx[n];
            y0= labelsy[n];
            for (int m=0;m<num_neighb+1;m++)
            {  
                mn=neighb[m];
               
                dr1= labelsR[mn];
                dg1= labelsG[mn];
                db1= labelsB[mn];
                x1= labelsx[mn];
                y1= labelsy[mn];
                
                double dist =(dr1-R0)*(dr1-R0)+(dg1-G0)*(dg1-G0)+(db1-B0)*(db1-B0);
                dista=(x0-x1)*(x0-x1)+(y0-y1)*(y0-y1);
                dist=dist+dista*2;
                 if (dist<minlab)
                 {
                     minlab=dist;
                     minnum=mn;
                 }
             }
           
            if (minnum!=0)
            {
                for(int j=0;j<labnumb[minnum];j++)
                {
                    neighb[j]=ngbC[minnum][j];
                }
                delete [] ngbC[minnum];
                ngbC[minnum]= new int [labnumb[minnum]+labnumb[n]];
                
                for(int j=0;j<labnumb[minnum];j++)
                {
                    ngbC[minnum][j]=neighb[j];
                    neighb[j]=0;
                }
                for(int j=0;j<labnumb[n];j++)
                {
                    label[ngbC[n][j]]=minnum;
                    ngbC[minnum][labnumb[minnum]+j]=ngbC[n][j];
                 }
                
                labelsR[minnum]=(labelsR[minnum]*labnumb[minnum]+labelsR[n]*labnumb[n])/(labnumb[minnum]+labnumb[n]);
                labelsG[minnum]=(labelsG[minnum]*labnumb[minnum]+labelsG[n]*labnumb[n])/(labnumb[minnum]+labnumb[n]);
                labelsB[minnum]=(labelsB[minnum]*labnumb[minnum]+labelsB[n]*labnumb[n])/(labnumb[minnum]+labnumb[n]);
                labelsx[minnum]=(labelsx[minnum]*labnumb[minnum]+labelsx[n]*labnumb[n])/(labnumb[minnum]+labnumb[n]);
                labelsy[minnum]=(labelsy[minnum]*labnumb[minnum]+labelsy[n]*labnumb[n])/(labnumb[minnum]+labnumb[n]);
                        
                labnumb[minnum]=labnumb[minnum]+labnumb[n];
                labnumb[n]=0;
            }
                Nc1=Nc1-1;
         }
      }
    realnumber=Nc1;
    //--------------post processing-----------------//
    if(post==1)
    {
     int lr,ll,lu,ld,l,n;
     for(int i=1;i<Rows-1;i++)
         for(int j=1;j<Cols-1;j++)
         {
             n=i*Cols+j;
             if(n>(Rows*Cols)/8)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/6)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/5)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/5+1500)
             {
                 int yui=0;
             }
              if(n>(Rows*Cols)/5+2500)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/4)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/3+5000)
             {
                 int yui=0;
             }
              if(n>(Rows*Cols)/3+10000)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/3+15000)
             {
                 int yui=0;
             }
              if(n>(Rows*Cols)/3+20000)
             {
                 int yui=0;
             }
             if(n>(Rows*Cols)/2)
             {
                 int yui=0;
             }
             l=label[n];
             lr=label[n+1];
             ll=label[n-1];
             lu=label[n-Cols];
             ld=label[n+Cols];
             
             if(lr!=l&&ll!=l)
             {
                 if(labnumb[lr]>=labnumb[ll])
                 {
                     label[n]=ll;
                     mergin(n+Cols,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                     mergin(n-Cols,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                 }
                 else
                 {
                     label[n]=lr;
                     mergin(n+Cols,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                     mergin(n-Cols,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                 }
             }
             if(lu!=l&&ld!=l)
             {
                 if(labnumb[lu]>=labnumb[ld])
                 {
                     label[n]=ld;
                     mergin(n+1,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                     mergin(n-1,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                 }
                 else 
                 {
                     label[n]=lu;
                     mergin(n+1,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                     mergin(n-1,R,G,B,Rows,Cols,label,labelsR,labelsG,labelsB,labelsx,labelsy);
                 }
             }
     }
    }
     delete [] labnumb;
     delete [] label0;
     for(int i=1;i<Nc;i++)
         delete [] ngbC[i];
     delete [] ngbC;
     delete [] labelsR;
     delete [] labelsG;
     delete [] labelsB;
     delete [] labelsx;
     delete [] labelsy;
     }
    
    

	


#endif