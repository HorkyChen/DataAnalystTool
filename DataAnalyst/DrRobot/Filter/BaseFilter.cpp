//
//  BaseFilter.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/13/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "BaseFilter.h"
#include "CppSQLite3.h"
#include <algorithm>

namespace DrRobot{
    
    BaseFilter::BaseFilter(const string& sourceView,const string& targetField,
                           const string& groupFields,const string& targetView)
    :m_sourceView(sourceView)
    ,m_targetField(targetField)
    ,m_groupFields(groupFields)
    ,m_targetView(targetView)
    {
    }
    
    BaseFilter::BaseFilter(const string& sourceView, const string& targetView)
    :m_sourceView(sourceView)
    ,m_targetView(targetView)
    {}
    
    bool BaseFilter::execute()
    {
        CppSQLite3DB *db = getSQLiteDB();
        if(db)
        {
            if(db->viewExists(m_targetView.c_str())){
                revert();
            }
            
            string statement = packSQLStatement();
            db->execDML(statement.c_str());
        }
        
        mCollection.clear();
        
        return true;
    }
    
    bool BaseFilter::revert()
    {
        CppSQLite3DB *db = getSQLiteDB();
        if(db)
        {
            string statement = "drop view "+m_targetView;
            db->execDML(statement.c_str());
        }
        
        mCollection.clear();
        
        return true;
    }
    
    DrRobot::Collection* BaseFilter::getData(const vector<string> fields)
    {
        if(mCollection.length()>0)
        {
            return &mCollection;
        }
        
        CppSQLite3DB *db = getSQLiteDB();
        
        if(!db)
        {
            return NULL;
        }
        
        string statement = "select * from "+m_targetView;
        
        CppSQLite3Query q = db->execQuery(statement.c_str());
        
        vector<int> validColumns;
        
        for (int fld = 0; fld < q.numFields(); fld++)
        {
            if((fields.size()==0 && q.fieldName(fld)!=string("_id")) 
               || find(fields.begin(),fields.end(),q.fieldName(fld))!= fields.end())
            {
                validColumns.push_back(fld);
                mCollection.appendField(q.fieldName(fld),typeOfField(q.fieldDataType(fld)));
            }
        }
        
        vector<string> rowValues;
        while (!q.eof())
        {
            rowValues.clear();
            q.fillRowValues(rowValues, validColumns);
            mCollection.addRow(rowValues);
            q.nextRow();
        }
        
        return &mCollection;
    }
    
    
    DrRobot::Node_Type BaseFilter::typeOfField(int sqlite_data_type)
    {
        DrRobot::Node_Type result = DrRobot::STRING;
        
        switch(sqlite_data_type)
        {
            case SQLITE_INTEGER:
                result = DrRobot::INTEGER;
                break;
            case SQLITE_FLOAT:
                result = DrRobot::NUMERIC;
                break;
        }
        return result;
    }
    
}
