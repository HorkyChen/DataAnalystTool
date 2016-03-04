//
//  OrderyByFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/12/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__OrderyByFilter__
#define __DataAnalyst__OrderyByFilter__

#include "BaseFilter.h"
#include <string>

using namespace std;

namespace DrRobot{
    class OrderyByFilter:public BaseFilter
    {
    public:
        OrderyByFilter(const string& sourceView,const string& targetField,
                         const string& groupFields,const string& targetView)
        :BaseFilter(sourceView,targetField,groupFields,targetView){}
        
        OrderyByFilter(const string& sourceView,const string& targetView)
        :BaseFilter(sourceView,targetView){}

    protected:
        virtual string packSQLStatement(){
            string statement = "create view "+m_targetView+" as ";
            statement += "select * from "+m_sourceView;
            statement += " order by "+m_targetField;
            
            return statement;
        }
    };
    
}


#endif /* defined(__DataAnalyst__OrderyByFilter__) */
