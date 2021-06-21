#include <LiquidCrystal.h>
#include<math.h>
#include "Complex.h"
LiquidCrystal lcd(7,8,9,10,11,12);

int const NoOfSample=128;
int sample_count=0;
Complex buff_mic[NoOfSample];


void fft(Complex X[],Complex fourier[]);
void odd(Complex y[],Complex oddout[]);
void even(Complex z[],Complex evenout[]);
float maximum(Complex arr[],float * freqval);

void setup() {
  // put your setup code here, to run once:
 
Serial.begin(9600);
//pinMode(inputin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
float mic_input=analogRead(A0);
  
  if(sample_count<NoOfSample)
    {
      buff_mic[sample_count]==mic_input;
      
      sample_count++;
    }
  else
    {
      Complex FourierOutput[NoOfSample/2];
      sample_count=0;
      fft(buff_mic,FourierOutput);

//finding the max val
      float AmplitudeofFreq;
      float freqIndex = maximum(FourierOutput,&AmplitudeofFreq);

      
      lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
      lcd.print("freq"); // Prints Sensor Val: to LCD
      lcd.print((44100/NoOfSample)*freqIndex); // Prints value on Potpin1 to LCD
      lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
      lcd.print("amlitude "); // Prints Sensor Val: to LCD
      lcd.print(AmplitudeofFreq); // Prints value on Potpin1 to LCD
    }

}






void odd(Complex y[],Complex oddout[])
{
  
  int rows=sizeof(y)/sizeof(y[0]);      //int cols=sizeof(y[0])/sizeof(y[0][0]);      //float oddarray[rows][cols];
  
    for(int i=1;i<rows;i=i+2)
    {
      oddout[i]==y[i];
      
    }
    //return oddarray;
}



void even(Complex z[],Complex evenout[])
{
  int rows=sizeof(z)/sizeof(z[0]);        //int cols=sizeof(z[0])/sizeof(z[0][0]);      //float evenarray[rows][cols];
  
    for(int i=0;i<rows;i=i+2)
    {
      evenout[i]==z[i];
   
    }
    //return evenarray;
}






void fft(Complex X[],Complex fourier[])
{
  
  int rows=sizeof(X)/sizeof(X[0]);
  //int cols=sizeof(X[0])/sizeof(X[0][0]);
  
  if(rows==1)
  {
    fourier[0]== X[0];
    
  }
  else
  {
    Complex oddcomponents[rows/2];
    Complex evencomponents[rows/2];
  
    odd(X,oddcomponents);
    even(X,evencomponents);
    
    Complex oddFourier[rows/2];
    fft(oddcomponents,oddFourier);
    
    Complex evenFourier[rows/2];
    fft(evencomponents,evenFourier);


    //float fftout[rows][cols];

    for(int k=0;k<rows/2;k++)
    {
      float angle=2*M_PI*k/rows;
      fourier[k] == evenFourier[k]+Complex(cos(angle),sin(angle))*oddFourier[k];
      
      
      fourier[rows/2+k]== evenFourier[k]-Complex(cos(angle),sin(angle))*oddFourier[k];
      
      
    }
    //return fourier;
  }
}


float maximum(Complex arr[],float * freqval)
{
  int index;
  freqval=0;
  int rows=sizeof(arr)/sizeof(arr[0]);
    for(int u=0;u<rows;u++)
    {
      if(*freqval<(arr[u].modulus()))
      {
        float freqval=arr[u].modulus();
        index = u;
      }
       
    }
    return index;
}






  
