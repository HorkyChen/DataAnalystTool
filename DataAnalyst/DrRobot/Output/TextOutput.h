//
//  TextOutput.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/15/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__TextOutput__
#define __DataAnalyst__TextOutput__
#include "BasePlot.h"
#include "Collection.h"

namespace DrRobot{
class TextOutput:public BasePlot
{
public:
    TextOutput(const string& title):BasePlot(title){}
    virtual bool plot(Collection * collection,const string& xticLabelColumn);
    virtual bool exportToFile(Collection * collection, const string& xticLabelColumn, const string& fileName);
private:
    bool generateTextFile(Collection * collection,const string xticLabelColumn, const string fileName);
};
}
#endif /* defined(__DataAnalyst__TextOutput__) */
