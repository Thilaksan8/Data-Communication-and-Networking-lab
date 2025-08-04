// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:





// function prototypes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void run(asignal * inputsignal);
int sample_count;
// Implement functions here
extern int sample_count;

// implementation
float analog_signal_generator(asignal signal, int t)
{
  //TODO
  return signal.A * sin(signal.omega * t + signal.sigma);
}
void sampler(float *samples, int interval, asignal signal)
{
  //TODO
  for (int i = 0; i < sample_count; i++) {
        int t = i * interval;
        samples[i] = analog_signal_generator(signal, t);
    }
}
void quantizer1(float *samples, int *pcmpulses, int levels)
{
  //TODO
   for (int i = 0; i < sample_count; i++) {
        float normalized = (samples[i] + 1.0f) / 2.0f; // scale [-1,1] -> [0,1]
        int level = (int)(normalized * levels);
        if (level == levels) level = levels - 1;
        pcmpulses[i] = level;
    }
}
void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
  //TODO
  float Amin = -A;
    float Amax = A;

    for (int i = 0; i < sample_count; i++) {
        float normalized = (samples[i] - Amin) / (Amax - Amin); // map sample to [0,1]
        int level = (int)(normalized * levels);
        if (level == levels) level = levels - 1;
        pcmpulses[i] = level;
    }
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
  //TODO
   for (int i = 0; i < sample_count; i++) {
        int pulse = pcmpulses[i];
        for (int bit = encoderbits - 1; bit >= 0; bit--) {
            dsignal[i * encoderbits + (encoderbits - 1 - bit)] = (pulse >> bit) & 1;
        }
    }
}


//-------------------------------------------------------------

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
  return 0;
}

void run(asignal * inputsignal) 
{
  //todo
  float A, omega, sigma;
    int duration, interval, encoderbits;

    // Read input parameters
    scanf("%f %f %f %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);

    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;

    sample_count = (duration / interval) + 1;

    float *samples = malloc(sizeof(float) * sample_count);
    int *pcmpulses = malloc(sizeof(int) * sample_count);
    int *dsignal = malloc(sizeof(int) * sample_count * encoderbits);

    sampler(samples, interval, *inputsignal);
    quantizer(samples, pcmpulses, 1 << encoderbits, A);

    encoder(pcmpulses, dsignal, encoderbits);

    // Print output bitstream
    for (int i = 0; i < sample_count * encoderbits; i++) {
        printf("%d", dsignal[i]);
    }
    printf("\n");

    free(samples);
    free(pcmpulses);
    free(dsignal);
}