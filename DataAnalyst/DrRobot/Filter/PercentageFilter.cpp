//
//  PercentageFilter.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/2/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "PercentageFilter.h"

namespace DrRobot{
    void PercentageFilter::getColumns(vector<string>& list)
    {
        list.push_back("percentage");
        if(!m_groupFields.empty())
            list.push_back(m_groupFields);
    }
    
    string PercentageFilter::packSQLStatement()
    {
        //select A,round(B/(select sum(B) from _data)*100,2) from _data group by A
        string statement = "create view "+m_targetView+" as ";
        statement += "select "+m_groupFields+",round("+m_targetField+"/";
        statement += "(select sum("+m_targetField+") from "+m_sourceView+")*100,2) as percentage";
        statement += " from "+m_sourceView+" group by "+m_groupFields;
        
        return statement;
    }
}
