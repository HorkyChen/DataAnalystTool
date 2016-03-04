//
//  GNUPlotter.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__GNUPlotter__
#define __DataAnalyst__GNUPlotter__
#include "BasePlot.h"
#include "Collection.h"
#include "gnuplot_i.h"
#include "GNUPlot_Controller.h"
#include "RefPtr.h"

namespace DrRobot{
    class GNUPlotter : public BasePlot
    {
    public:
        GNUPlotter();
        GNUPlotter(const string title,const char* style);
        GNUPlotter(const string title,const char* style,const GNUPlotter& plotter);
        ~GNUPlotter();
    private:
        string mStyle;
        bool mInvolveMultiFields;
    protected:
        RefPtr<GNUPlot_Controller> mDevController;
        bool doPreCheck(Collection * collection);
    public:
        virtual bool plot(Collection * collection, const string& xticLabelColumn);
        virtual bool exportToFile(Collection * collection, const string& xticLabelColumn, const string& fileName);
        
        void close();
        void setPlotStyle(const char* style){mStyle = style;};
        PassRefPtr<GNUPlot_Controller> getPlotDevice()const {return mDevController;};
        
        const string style()const {return mStyle;};
        
        virtual bool hasCommandFile(){return false;};
        virtual const char* commandFile(){return NULL;};
        virtual const char* prePlotCmdString();
        virtual const char* postPlotCmdString();
    private:
        bool plotNode(const Node * node, const Node *labelNode);
        gnuplot_ctrl* plotDev(){return mDevController.get()->getDev();};
    };
}
#endif /* defined(__DataAnalyst__GNUPlotter__) */
