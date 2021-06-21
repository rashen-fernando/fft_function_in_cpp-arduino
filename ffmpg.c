#include <stdio.h>
#include <stdint.h>
 

 


void main()
{
    int N=44100*5;
    // Create a 5 s audio buffer (assuming Fs = 44.1 kHz) (In the actual fft implementation the no of samples are planned to reduce to 1024)
    int16_t buf[N] ; // buffer
    int n=0;                // buffer index
    int16_t bufbeep[N] ;
     
    // Rec a wav file of 5 secs.
    FILE *piperec;
    piperec =popen("ffmpeg -f dshow -i audio=\"Microphone (Realtek High Definition Audio)\" -y -t 5 -ac 1 out.wav", "r");
    pclose(piperec);
     
    // Loading the above recorded sample file in to a buffer
    FILE *pipein;
    pipein = popen("ffmpeg -i out.wav -f s16le -ac 1 -", "r");
    fread(buf, 2, N, pipein);
    pclose(pipein);

    //exporting the above loaded file to the buffer to another filename(beep.wav) to check whether the audio data was correctly stored in the array.If so I can hear what is being recorded.
    FILE *pipeout;
    pipeout = _popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - beep.wav", "w");
    fwrite(bufbeep, 2, N, pipeout);
    _pclose(pipeout);
    
    //for (n=0 ; n<N ; ++n) printf( "%d\n", buf[n]);
     
}

//ffmpeg -f dshow -i audio="Microphone (Realtek High Definition Audio)" out.mp3
//ffmpeg -list_devices true -f dshow -i dummy
//ffmpeg -f dshow -i audio=Microphone (Realtek High Definition Audio) -f s16le -ac 1 -