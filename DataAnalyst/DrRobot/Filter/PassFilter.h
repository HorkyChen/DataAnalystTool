//
//  PassFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/22/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef DataAnalyst_PassFilter_h
#define DataAnalyst_PassFilter_h
namespace DrRobot{
    
    class PassFilter:public BaseFilter
    {
    public:
        PassFilter(const string& sourceView,const string& targetField,
                   const string& groupFields,const string& targetView)
        :BaseFilter(sourceView,targetField,groupFields,targetView){}
        
        PassFilter(const string& sourceView,const string& targetView)
        :BaseFilter(sourceView,targetView){}
    protected:
        virtual string packSQLStatement(){
            string statement = "create view "+m_targetView+" as ";
            statement += "select *";
            statement += " from "+m_sourceView;
            
            return statement;
        }
    };
    
}
#endif
