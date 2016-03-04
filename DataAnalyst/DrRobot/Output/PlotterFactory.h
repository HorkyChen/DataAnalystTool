//
//  PlotterFactory.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__PlotterFactory__
#define __DataAnalyst__PlotterFactory__

#include <string>
#include <vector>
#include "BasePlot.h"

using namespace std;

namespace DrRobot{
    class DrRobot;
    
    class PlotterFactory{
    public:
        static void registerPlotters(DrRobot* drRobot);
        static BasePlot * createPlotter(const string name,const string title);
    };
    
}
#endif /* defined(__DataAnalyst__PlotterFactory__) */
