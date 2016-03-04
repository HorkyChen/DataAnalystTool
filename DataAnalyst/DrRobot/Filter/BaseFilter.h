//
//  BaseFilter.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/13/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__BaseFilter__
#define __DataAnalyst__BaseFilter__

#include "Collection.h"
using namespace std;
namespace DrRobot{
    class BaseFilter
    {
    public:
        BaseFilter(const string& sourceView, const string& targetField,
                   const string& groupFields,const string& targetView);
        BaseFilter(const string& sourceView, const string& targetView);
        
        void setFields(const string& targetField,
                       const string& groupFields)
        {
            m_targetField = targetField;
            m_groupFields = groupFields;
        }
        
        bool execute();
        bool revert();
        Collection* getData(const vector<string> fields);
        virtual void getColumns(vector<string>& list){};
    private:
        BaseFilter(){}
        Node_Type typeOfField(int sqlite_data_type);
    private:
        Collection mCollection;
    protected:
        virtual string packSQLStatement() {return "";};   
        string m_sourceView;
        string m_groupFields;
        string m_targetField;
        string m_targetView;
    };
    
}

#endif /* defined(__DataAnalyst__BaseFilter__) */
