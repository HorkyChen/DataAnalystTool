//
//  OrderyByFilter.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/12/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "OrderyByFilter.h"

namespace DrRobot{
    void PercentageFilter::getColumns(vector<string>& list)
    {
        list.push_back("ordered");
    }
    
    string PercentageFilter::packSQLStatement()
    {
        string statement = "create view "+m_targetView+" as ";
        statement += "select * from "+m_sourceView;
        statement += " order by "+m_targetField;
        
        return statement;
    }
}