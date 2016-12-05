#ifndef REGIONQUERY
#define REGIONQUERY
#include<algorithm>
#include<cmath>
using namespace std;

void regionQuery(int* neighbours,int &k, unsigned char* R, unsigned char* G,unsigned  char* B,int n0,int n, int rows, int cols,unsigned short *label,bool *label0)
{
     double E = 20*20;   
     int x=n/cols+1;
     int y=n%cols+1;
     int dr,dr0,dr1,dg,dg0,dg1,db,db0,db1;
     double ratio1,ratio2;
     ratio1=0.62;
     ratio2=0.38;
     dr0= R[n];
     dg0= G[n];
     db0= B[n];
     dr= R[n0];//n0 is the seed
     dg= G[n0];
     db= B[n0];
//      int db2,dr2,dg2,dist2;
     double dist,dist0;
    
  //Get pixels around pixel n
      if (x>1&&x<rows&&y>1&&y<cols)
      {
//        r1=0;u1=0;l1=0;d1=0;
        //go to right
          if(!label[n+1]&&!label0[n+1])
          {
          dr1= R[n+1];
          dg1= G[n+1];
          db1= B[n+1];
          
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;

        if (dist < E)
        {   
            label0[n+1]=1;
            neighbours[k]=n+1;
            k++;
        }
          }    
          
           //go to up
           if(!label[n-cols]&&!label0[n-cols])
          {
          dr1= R[n-cols];
          dg1= G[n-cols];
          db1= B[n-cols];
          
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
       
        if (dist < E )
        {
            label0[n-cols]=1;
            neighbours[k]=n-cols;
            k++;
        }
           }
          
           //go to left 
          if(!label[n-1]&&!label0[n-1])
          {
          dr1= R[n-1];
          dg1= G[n-1];
          db1= B[n-1];
    
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
  
        if (dist < E )
        {
            label0[n-1]=1;
            neighbours[k]=n-1;
            k++;
        }
           }
          
        //do to down
           if(!label[n+cols]&&!label0[n+cols])
          {
          dr1= R[n+cols];
          dg1= G[n+cols];
          db1= B[n+cols];
          
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
   
        if (dist < E )
        {
            label0[n+cols]=1;
            neighbours[k]=n+cols;
            k++;
        }
           }
      }
        
     //image down borderline
      if (x==rows&&y>0&&y<cols)
      {
          if(!label[n-1]&&!label0[n-1])
          {
          dr1= R[n-1];
          dg1= G[n-1];
          db1= B[n-1];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
          
        if (dist < E )
        {
            label0[n-1]=1;
            neighbours[k]=n-1;
            k++;
        }
           }
          
         if(!label[n+1]&&!label0[n+1])
          {
          dr1= R[n+1];
          dg1= G[n+1];
          db1= B[n+1];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
          
        if (dist < E)
        {
             label0[n+1]=1;
             neighbours[k]=n+1;
             k++;
        }
          }    
          
      } 
  //image right border
          if (x<rows&&y==cols)
          {
              if(!label[n+cols]&&!label0[n+cols])
          {
          dr1= R[n+cols];
          dg1= G[n+cols];
          db1= B[n+cols];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
       
        if (dist < E )
        {
            label0[n+cols]=1;
            neighbours[k]=n+cols;
            k++;
        }
           }
              
         //go to left 
            if(!label[n-1]&&!label0[n-1])
          {
          dr1= R[n-1];
          dg1= G[n-1];
          db1= B[n-1];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
          
        if (dist < E )
        {
            label0[n-1]=1;
            neighbours[k]=n-1;
            k++;
        }
           }
          }
     
     //image left border
          if (x<rows&&y==1)
          {
              
              if(!label[n+cols]&&!label0[n+cols])
          {
          dr1= R[n+cols];
          dg1= G[n+cols];
          db1= B[n+cols];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;

        if (dist < E )
        {
            label0[n+cols]=1;
            neighbours[k]=n+cols;
            k++;
        }
           }
             
        
          //go to right
     if(!label[n+1]&&!label0[n+1])
          {
          
          dr1= R[n+1];
          dg1= G[n+1];
          db1= B[n+1];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
 
        if (dist < E)
        {
            label0[n+1]=1;
              neighbours[k]=n+1;
            k++;
        }
          }    
            
                   
          }
          
    //image up border
          if (x==1&&y>1&&y<cols)
          {
               if(!label[n+cols]&&!label0[n+cols])
          {
          dr1= R[n+cols];
          dg1= G[n+cols];
          db1= B[n+cols];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
 
        if (dist < E )
        {
            label0[n+cols]=1;
            neighbours[k]=n+cols;
            k++;

        }
           }
             //go to right
       if(!label[n+1]&&!label0[n+1])
          {
          dr1= R[n+1];
          dg1= G[n+1];
          db1= B[n+1];
          dist =(dr1-dr0)*(dr1-dr0)+(dg1-dg0)*(dg1-dg0)+(db1-db0)*(db1-db0);
          dist0 =(dr1-dr)*(dr1-dr)+(dg1-dg)*(dg1-dg)+(db1-db)*(db1-db);
          dist=ratio1*dist0+ratio2*dist;
   
        if (dist < E)
        {
            label0[n+1]=1;
            neighbours[k]=n+1;
            k++;
        }
          }     
          }
    return;
}
#endif
