//
//  SmoothLinePlotter.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/8/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__SmoothLinePlotter__
#define __DataAnalyst__SmoothLinePlotter__

#include <string>
#include "GNUPlotter.h"
using namespace std;

namespace DrRobot{
    
    class SmoothLinePlotter:public GNUPlotter{
    public:
        SmoothLinePlotter()
        :GNUPlotter()
        {
        }
        
        SmoothLinePlotter(const string title)
        :GNUPlotter(title,"points")
        {
        }
        
        SmoothLinePlotter(const string title,const char* style,const GNUPlotter& plotter)
        :GNUPlotter(title,style,plotter)
        {
        }
    public:
        virtual bool hasCommandFile(){return true;};
        virtual const char* commandFile(){return "PointsWithSmoothLine.gp";};
    };
    
}//namespace DrRobot

#endif /* defined(__DataAnalyst__SmoothLinePlotter__) */
