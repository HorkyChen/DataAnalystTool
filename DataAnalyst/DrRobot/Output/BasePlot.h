//
//  BasePlot.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__BasePlot__
#define __DataAnalyst__BasePlot__

#include <string>
#include "Collection.h"
using namespace std;

namespace DrRobot{
    class BasePlot
    {
    public:
        BasePlot():mTitle(""){}
        BasePlot(const string& title):mTitle(title){}
        
        /*@xticLabelColumn -> Column which contains xtic labels*/
        virtual bool plot(Collection * collection, const string& xticLabelColumn){return false;};
        virtual bool exportToFile(Collection * collection, const string& xticLabelColumn, const string& fileName) {return false;};
        const string& title(){return mTitle;};
    private:
        string mTitle;
    };
}
#endif /* defined(__DataAnalyst__BasePlot__) */
