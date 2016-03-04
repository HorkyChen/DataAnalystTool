//
//  FiveNumberFilter.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/13/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "FiveNumberFilter.h"
namespace DrRobot{
    void FiveNumberFilter::getColumns(vector<string>& list)
    {
        list.push_back("average");
        list.push_back("summary");
        list.push_back("maximum");
        list.push_back("minimum");
        list.push_back("standardDev");
    }
    
    string FiveNumberFilter::packSQLStatement()
    {
        string statement = "create view "+m_targetView+" as ";
        statement += "select "+m_groupFields+",avg("+m_targetField+") as average,";
        statement += "sum("+m_targetField+") as summary,";
        statement += "max("+m_targetField+") as maximum,";
        statement += "min("+m_targetField+") as minimum,";
        statement += "stdev("+m_targetField+") as standardDev";
        statement += " from "+m_sourceView+" group by "+m_groupFields;
        
        return statement;
    }
}
