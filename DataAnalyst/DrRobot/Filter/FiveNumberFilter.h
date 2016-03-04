//
//  FiveNumberFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/13/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__FiveNumberFilter__
#define __DataAnalyst__FiveNumberFilter__

#include "BaseFilter.h"
#include <string>

using namespace std;

namespace DrRobot{
    class FiveNumberFilter:public BaseFilter
    {
    public:
        FiveNumberFilter(const string& sourceView,const string& targetField,
                         const string& groupFields,const string& targetView)
        :BaseFilter(sourceView,targetField,groupFields,targetView){}
        
        FiveNumberFilter(const string& sourceView,const string& targetView)
        :BaseFilter(sourceView,targetView){}
        
        virtual void getColumns(vector<string>& list);
    protected:
        virtual string packSQLStatement();
    };
    
}
#endif /* defined(__DataAnalyst__FiveNumberFilter__) */
