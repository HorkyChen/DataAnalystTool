//
//  FilterFactory.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__FilterFactory__
#define __DataAnalyst__FilterFactory__

#include <string>
#include "BaseFilter.h"

using namespace std;

namespace DrRobot{
    
    class DrRobot;
    
    class FilterFactory{
    public:
        static void registerFilters(DrRobot* drRobot);
        
        static BaseFilter * createFilter(const string& name,
                                         const string& sourceView, const string& targetView);
    };
    
}
#endif /* defined(__DataAnalyst__FilterFactory__) */
