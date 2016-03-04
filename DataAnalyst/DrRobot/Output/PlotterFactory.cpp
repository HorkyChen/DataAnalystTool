//
//  PlotterFactory.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//
#include <algorithm>

#include "PlotterFactory.h"
#include "TextOutput.h"
#include "GNUPlotter.h"
#include "DrRobot.h"
#include "SmoothLinePlotter.h"
#include "GnuPlot_PieChart.h"
#include "GnuPlot_Lattice.h"

namespace DrRobot{
    
    static vector<string> basicPlotterList;
    
    void PlotterFactory::registerPlotters(DrRobot* drRobot)
    {
        drRobot->registerPlotter("Text","输出文本内容");
        drRobot->registerPlotter("Lines","绘线");
        drRobot->registerPlotter("Points","绘点");
        drRobot->registerPlotter("Linespoints","绘制带点线段");
        drRobot->registerPlotter("Boxes","绘制箱图(Boxes)");
        drRobot->registerPlotter("ErrorBars","绘制误差线(ErrorBars)");
        drRobot->registerPlotter("BoxesErrorBars","绘制误差线(ErrorBars)及箱图(Boxes)");
        drRobot->registerPlotter("Steps","绘制梯形(Steps)");
        drRobot->registerPlotter("Impulses","绘制垂线(Impulses)");
        drRobot->registerPlotter("Piechart","绘制饼图(Pie Char)");
        drRobot->registerPlotter("Lattice","绘制相关性");
        
        basicPlotterList.push_back("Lines");
        basicPlotterList.push_back("Points");
        basicPlotterList.push_back("Linespoints");
        basicPlotterList.push_back("Boxes");
        basicPlotterList.push_back("Boxeserrorbars");
        basicPlotterList.push_back("Steps");
        basicPlotterList.push_back("Impulses");
        
        drRobot->registerPlotter("SmoothLine","绘制平滑曲线");
    }
    
    BasePlot * PlotterFactory::createPlotter(const string name,const string title)
    {
        vector<string>::iterator it = find (basicPlotterList.begin(), basicPlotterList.end(), name);
        if(it != basicPlotterList.end())
        {
            string plotName = name;
            std::transform(plotName.begin(), plotName.end(), plotName.begin(), ::tolower);
            return new GNUPlotter(title,plotName.c_str());
        }
        
        if(name=="Text")
        {
            return new TextOutput(title);
        }
        else if(name=="SmoothLine")
        {
            return new SmoothLinePlotter(title);
        }
        else if(name=="Piechart")
        {
            return new GnuPlot_PieChart(title);
        }
        else if(name=="Lattice")
        {
            return new GnuPlot_Lattice(title);
        }
        
        return NULL;
    }

}
