//
//  GNUPlot_Controller.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//
// A wrapper class for raw pointer of GNU Plot Device Handle.
//

#ifndef __DataAnalyst__GNUPlot_Controller__
#define __DataAnalyst__GNUPlot_Controller__
#include <string>
#include "RefCounted.h"
#include "gnuplot_i.h"
#include "PassRefPtr.h"
#include "Collection.h"
using namespace std;

namespace DrRobot{

class GNUPlotter;
    
class GNUPlot_Controller:public RefCounted<GNUPlot_Controller>
{
public:
    static PassRefPtr<GNUPlot_Controller> create();
    
public:
    ~GNUPlot_Controller();
    GNUPlot_Controller();
    GNUPlot_Controller(gnuplot_ctrl* dev);
    gnuplot_ctrl* getDev() const{return mDev;};
    
    void plot_x_int(int * data, string* labels, int size, const char *title, GNUPlotter* plotter);
    void plot_x(float * data, string* labels, int size, const char *title, GNUPlotter* plotter);
    bool plot(Collection* data, const bool hasXticLabel,GNUPlotter* plotter);
    void setOutputFile(const string fileName);
    void sendCommand(const string command);
private:
    gnuplot_ctrl* mDev;
private:
    GNUPlot_Controller(const GNUPlot_Controller&);
    GNUPlot_Controller& operator=(const GNUPlot_Controller&);
    
    void doPrePlotActions(GNUPlotter* plotter);
    void doInitialActions();
    bool testCollection(Collection* data,const bool hasXticLabel);
    bool canConvertToNumber(const string& numberAsString);
};
    
}//namespace DrRobot
#endif /* defined(__DataAnalyst__GNUPlot_Controller__) */
