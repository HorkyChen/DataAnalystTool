//
//  GnuPlot_PieChart.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/21/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__GnuPlot_PieChart__
#define __DataAnalyst__GnuPlot_PieChart__

#include <string>
#include "GNUPlotter.h"

using namespace std;

namespace DrRobot{
    
    class GnuPlot_PieChart:public GNUPlotter{
    public:
        GnuPlot_PieChart()
        :GNUPlotter()
        {
        }
        
        GnuPlot_PieChart(const string title)
        :GNUPlotter(title,"points")
        {
        }
        
        GnuPlot_PieChart(const string title,const char* style,const GNUPlotter& plotter)
        :GNUPlotter(title,style,plotter)
        {
        }
    public:
        virtual bool plot(Collection * collection, const string& xticLabelColumn);
    };
    
}//namespace DrRobot

#endif /* defined(__DataAnalyst__GnuPlot_PieChart__) */
