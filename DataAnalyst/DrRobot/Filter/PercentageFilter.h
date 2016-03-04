//
//  PercentageFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/2/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__PercentageFilter__
#define __DataAnalyst__PercentageFilter__

#include "BaseFilter.h"
#include <string>

using namespace std;

namespace DrRobot{
    class PercentageFilter:public BaseFilter
    {
    public:
        PercentageFilter(const string& sourceView,const string& targetField,
                         const string& groupFields,const string& targetView)
        :BaseFilter(sourceView,targetField,groupFields,targetView){}
        
        PercentageFilter(const string& sourceView,const string& targetView)
        :BaseFilter(sourceView,targetView){}
        
        virtual void getColumns(vector<string>& list);
    protected:
        virtual string packSQLStatement();
    };
    
}

#endif /* defined(__DataAnalyst__PercentageFilter__) */
