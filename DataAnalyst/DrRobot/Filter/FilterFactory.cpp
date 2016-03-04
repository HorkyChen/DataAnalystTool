//
//  FilterFactory.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "FilterFactory.h"
#include "DrRobot.h"
#include "FiveNumberFilter.h"
#include "AverageFilter.h"
#include "PassFilter.h"
#include "PercentageFilter.h"
#include "OrderByFilter.h"

namespace DrRobot{
    
    void FilterFactory::registerFilters(DrRobot* drRobot)
    {
        drRobot->registerFilter("PassFilter","不做任何处理，直接传值到下一步");
        drRobot->registerFilter("FiveNumberFilter","基础统计之Five-Number");
        drRobot->registerFilter("AverageFilter","计算平均值");
        drRobot->registerFilter("PercentageFilter","计算数据占比");
        drRobot->registerFilter("OrderyByFilter","将数据进行排序");
    }
    
    BaseFilter * FilterFactory::createFilter(const string& name,
                                             const string& sourceView, const string& targetView)
    {
        if(name=="FiveNumberFilter")
        {
            return new FiveNumberFilter(sourceView,targetView);
        }
        else if (name == "AverageFilter")
        {
            return new AverageFilter(sourceView,targetView);
        }
        else if (name == "PassFilter")
        {
            return new PassFilter(sourceView,targetView);
        }
        else if (name == "PercentageFilter")
        {
            return new PercentageFilter(sourceView,targetView);
        }
        else if (name == "OrderyByFilter")
        {
            return new OrderyByFilter(sourceView,targetView);
        }
        
        return NULL;
    }
    
}
