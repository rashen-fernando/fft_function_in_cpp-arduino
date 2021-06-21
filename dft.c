#include<stdio.h>
#include<stdint.h>
#include <complex.h>
#define _USE_MATH_DEFINES // for C
#include <math.h>

void plot(double x,double f);
void dft(double z[],double complex ft[],int N);
int main()
{
    FILE *data = NULL;
    FILE *gnupl = NULL;
    int n = 44100;
    int buff_size=n;
    data=fopen("data.tmp","w");                     //for gnuplot
    gnupl=_popen("gnuplot -persitent","w");
    double sampling_freq=44100;
    double Ts=1/sampling_freq;




    //time
    double t[n];
    for(int i=0;i<n;i++)
    {
        t[i]=i*Ts;
        //printf(" %lf \n",t[i]);    
    }



    //signal getting from ffmpeg throygh piping
    double y[buff_size];
    int16_t buff[buff_size];
    FILE *pipein;
    pipein = _popen("ffmpeg -i A5.wav -f s16le -ac 1 -", "r");
    fread(buff, 2 ,buff_size, pipein);
    _pclose(pipein);




//converting to double to send to dft
   for(int j=0;j<buff_size;j++)
   {
         //y[j]=20*sin(2*M_PI*10*j/n)+10*sin(2*M_PI*1*j/n);
         y[j]=(double)buff[j];
        //printf(" %lf %d\n",y[j],buff[j]);
    }


//------------------------------------------------------------------------------------------------------------------------------------------

//Fourier
    double complex ft[n];              //minimum freq corressponds with buffer size.to denote minimum frequency we need 441000/(1/n) samples in freq domain
    dft(y,ft,n);




//absolute vale for plotting purposes
    for(int k=0;k<n/2;k++)
    {   
        ft[k]=cabs(ft[k]);
       //printf(" %lf +i %lf \n ",creal(ft[k]),cimag(ft[k]));
    }





//saving data to a file "data" to be send to gnuplot  
   for(int u=0;u<4000;u++)
   {
       //double fr_steps=u/(n/sampling_freq);
       fprintf(data,"%d %lf \n",u,ft[u]);
       //plot(ft[u],u);
   }



double fun_freq=1/(n/sampling_freq);
printf("FUndamental Frequency - %lf",fun_freq);
//gnuplot
    fprintf(gnupl,"%s \n","set title\"demo\"");
    fprintf(gnupl,"%s \n","plot 'data.tmp' with boxes");

    return 0;
}





void dft(double *z,double complex * ft,int N)
{
    double complex q=(-2*M_PI/N);
    
    for(int i=0;i<4000;i++)
    {
        double complex s=0;
        for(int j=0;j<N-1;j++)
        { 
            s=s+(cos(q*i*j)+sin(q*i*j)*I)*z[j]; 
        }
        //printf("%f + %f i\n",crealf(s/N),cimagf(s/N));
        ft[i]=s/N;
    }  
}





void plot(double x,double f)
{
    printf("%lf   ",f);
    double i=0;
    while(i<x)
    {
        printf("*");
        i=i+.5;
    }
    printf("\n");
    
}

