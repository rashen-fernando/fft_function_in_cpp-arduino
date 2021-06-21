#include <string>
#include <sstream>
#include <iostream>

#include <fstream>
#include<math.h>
using namespace std;

int const NoOfSample=128;



void fft(float X[][2],float fourier[][2]);
void odd(float y[][2],float oddout[][2]);
void even(float z[][2],float evenout[][2]);
float maximum(float arr[][2],float * freqval);

main()
{
      int sample_count=0;
      float buff_mic[NoOfSample][2];
     //readcsv and check code
     ifstream myfile;
      myfile.open("file.csv");

      for(int h=0;h<NoOfSample;h++)
      {
        string line;
        getline(myfile,line);
        buff_mic[h][0]=std::stof(line);
        buff_mic[h][1]=0;
      }

      float FourierOutput[NoOfSample/2][2];
      
      fft(buff_mic,FourierOutput);

//finding the max val
      float AmplitudeofFreq;
      float freqIndex = maximum(FourierOutput,&AmplitudeofFreq);
      cout << AmplitudeofFreq <<endl;

      
}






void odd(float y[][2],float oddout[][2])
{
  
  int rows=sizeof(y)/sizeof(y[0]);      //int cols=sizeof(y[0])/sizeof(y[0][0]);      //float oddarray[rows][cols];
  
    for(int i=1;i<rows;i=i+2)
    {
      oddout[i][0]=y[i][0];
      oddout[i][1]=y[i][1];
    }
    //return oddarray;
}



void even(float z[][2],float evenout[][2])
{
  int rows=sizeof(z)/sizeof(z[0]);        //int cols=sizeof(z[0])/sizeof(z[0][0]);      //float evenarray[rows][cols];
  
    for(int i=0;i<rows;i=i+2)
    {
      evenout[i][0]=z[i][0];
      evenout[i][1]=z[i][1];
    }
    //return evenarray;
}






void fft(float X[][2],float fourier[][2])
{
  
  int rows=sizeof(X)/sizeof(X[0]);
  //int cols=sizeof(X[0])/sizeof(X[0][0]);
  
  if(rows==1)
  {
    fourier[0][0]= X[0][0];
    fourier[0][1]= X[0][1];
  }
  else
  {
    float oddcomponents[rows/2][2];
    float evencomponents[rows/2][2];
  
    odd(X,oddcomponents);
    even(X,evencomponents);
    
    float oddFourier[rows/2][2];
    fft(oddcomponents,oddFourier);
    
    float evenFourier[rows/2][2];
    fft(evencomponents,evenFourier);


    //float fftout[rows][cols];

    for(int k=0;k<rows/2;k++)
    {
      float angle=2*3.14*k/rows;
      fourier[k][0] = evenFourier[k][0]+cos(angle)*oddFourier[k][0]-sin(angle)*oddFourier[k][1];
      fourier[k][1] = evenFourier[k][1]+cos(angle)*oddFourier[k][1]+sin(angle)*oddFourier[k][0];
      
      fourier[rows/2+k][0] = evenFourier[k][0]-cos(angle)*oddFourier[k][0]+sin(angle)*oddFourier[k][1];
      fourier[rows/2+k][1] = evenFourier[k][1]-cos(angle)*oddFourier[k][1]-sin(angle)*oddFourier[k][0];
      
    }
    //return fourier;
  }
}


float maximum(float arr[][2],float * freqval)
{
  int index;
  freqval=0;
  int rows=sizeof(arr)/sizeof(arr[0]);
    for(int u=0;u<rows;u++)
    {
      if(pow(*freqval,2)<(pow(arr[u][0],2)+pow(arr[u][1],2)))
      {
        float freqval=sqrt(pow(arr[u][0],2)+pow(arr[u][1],2));
        index = u;
      }
       
    }
    return index;
}






  