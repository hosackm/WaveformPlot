//
//  plotter.c
//  WaveformPlot
//
//  Created by Matthew Hosack on 8/5/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//

#include <stdio.h>
#include "plotter.h"
#include "gnuplot_i.h"

#define REFRESH_MS 50
#define SAMPLERATE 44100
#define NSAMPLES (SAMPLERATE / (1000/REFRESH_MS))

static double samples[NSAMPLES];
static unsigned long writeindex = 0;
static gnuplot_ctrl *handle;

static void plot();

void plotter_init(){
    handle = gnuplot_init();
    gnuplot_setstyle(handle, "lines") ;
    gnuplot_cmd(handle, "set yrange [-1.0:1.0]");
    gnuplot_cmd(handle, "set xrange [0:2205]");
    gnuplot_cmd(handle, "set title 'Microphone Input'");
    gnuplot_cmd(handle, "set xlabel 'Sample'");
    gnuplot_cmd(handle, "set ylabel 'Amplitude'");
}

void plotter_close(){
    gnuplot_close(handle);
}

void plotter_write(const float* in, float *out, unsigned long numFrames){
	unsigned long i;

	for(i = 0; i < numFrames; ++i)
	{
		samples[writeindex] = *out++ = *in;
		
		writeindex++;
		if (writeindex == NSAMPLES) {
			//samples buffer full. time to plot
			writeindex -= NSAMPLES;
			plot();
		}
	}
}

static void plot(){
    gnuplot_resetplot(handle);
    gnuplot_plot_x(handle, samples, NSAMPLES, "");
}