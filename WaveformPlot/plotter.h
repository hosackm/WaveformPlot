//
//  plotter.h
//  WaveformPlot
//
//  Created by Matthew Hosack on 8/5/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//

#ifndef WaveformPlot_plotter_h
#define WaveformPlot_plotter_h

#include "gnuplot_i.h"

void plotter_init();
void plotter_close();
void plotter_write(float data);
static void plot();

#endif
