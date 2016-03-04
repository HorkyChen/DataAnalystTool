//
//  AverageFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/22/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef DataAnalyst_AverageFilter_h
#define DataAnalyst_AverageFilter_h

#include "BaseFilter.h"
#include <string>

using namespace std;

namespace DrRobot{
    
    class AverageFilter:public BaseFilter
    {
    public:
        AverageFilter(const string& sourceView,const string& targetField,
                      const string& groupFields,const string& targetView)
        :BaseFilter(sourceView,targetField,groupFields,targetView){}
        
        AverageFilter(const string& sourceView,const string& targetView)
        :BaseFilter(sourceView,targetView){}
        
        virtual void getColumns(vector<string>& list) {
            list.push_back("average");
            if(!m_groupFields.empty())
                list.push_back(m_groupFields);
        };
    protected:
        virtual string packSQLStatement(){
            string statement = "create view "+m_targetView+" as ";
            statement += "select avg("+m_targetField+") as average";
            if(!m_groupFields.empty())
                statement += ","+m_groupFields;
            statement += " from "+m_sourceView;
            
            if(!m_groupFields.empty())
                statement += " group by "+m_groupFields;
            return statement;
        }
    };
    
}
#endif
