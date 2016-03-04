//
//  GnuPlot_Lattice.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/28/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__GnuPlot_Lattice__
#define __DataAnalyst__GnuPlot_Lattice__

#include <string>
#include "GNUPlotter.h"

namespace DrRobot{
    
    class GnuPlot_Lattice:public GNUPlotter{
    public:
        GnuPlot_Lattice()
        :GNUPlotter()
        {
        }
        
        GnuPlot_Lattice(const string title)
        :GNUPlotter(title,"points")
        {
        }
        
        GnuPlot_Lattice(const string title,const char* style,const GNUPlotter& plotter)
        :GNUPlotter(title,style,plotter)
        {
        }
    public:
        virtual bool plot(Collection * collection, const string& xticLabelColumn);
    };
    
}//namespace DrRobot

#endif /* defined(__DataAnalyst__GnuPlot_Lattice__) */
