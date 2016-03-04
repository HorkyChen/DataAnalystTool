//
//  CSVDataSource.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <string>
#include <iostream>
#include "Collection.h"
#include "CSVDataSource.h"
#include "CSVparser.hpp"
#include "CppSQLite3.h"
#include "ReportError.h"

namespace DrRobot{
    
    bool CSVDataSource::parser()
    {
        bool result = true;

        try
        {
            mFileParser.parseContent();
            
            CppSQLite3DB* db = getSQLiteDB();
            
            if(!db)
            {
                setError("Failed to create DB.");
            }
            
            string statement = "create table ";
            statement += DATA_SOURCE_TABLE_NAME;
            statement +=  "( "; 
            string headers = "";
            
            //Print headers
            for(int j=0;j<mFileParser.columnCount();j++){
                statement += mFileParser.getHeaderElement(j)+" TEXT,";
                headers += mFileParser.getHeaderElement(j);
                if(j<mFileParser.columnCount()-1)
                {
                    headers += ",";
                }
            }
            statement+="_id INTEGER PRIMARY KEY ASC)";
            
            db->execDML(statement.c_str());
            
            for(int i=0;i<mFileParser.rowCount();i++) {
                statement = "insert into _data Values(";
                for(int j=0;j<mFileParser.columnCount();j++){
                    statement += "\""+mFileParser[i][j]+"\",";
                }
                statement += "null)";
                db->execDML(statement.c_str());
            }
            
            /*
             ** Just for debugging.
            CppSQLite3Table t = db->getTable("select * from _data;");
            
            for (int fld = 0; fld < t.numFields(); fld++)
            {
                cout << t.fieldName(fld) << "|";
            }
            cout << endl;
            for (int row = 0; row < t.numRows(); row++)
            {
                t.setRow(row);
                for (int fld = 0; fld < t.numFields(); fld++)
                {
                    if (!t.fieldIsNull(fld))
                        cout << t.fieldValue(fld) << "|";
                    else
                        cout << "NULL" << "|";
                }
                cout << endl;
            }
            */
        }
        catch (DrRobot::Error &e)
        {
            std::cerr << e.what() << std::endl;
            setError(e.what());
            result = false;
        }
        
        return result;
    }
    
    void CSVDataSource::getColumns(vector<string>& list)
    {
        for(int j=0;j<mFileParser.columnCount();j++){
            list.push_back(mFileParser.getHeaderElement(j));
        }
    }
    
    Collection* CSVDataSource::getData(const vector<string> fields)
    {
        Collection* orgData = mFileParser.getData();
        Collection* internalData = getInternalData();
        
        internalData->clear();
        
        for(std::vector<string>::const_iterator iter = fields.begin();iter!=fields.end();iter++)
        {
            Node* node = orgData->getField(*iter);
            if(node)
            {
                internalData->append(*node);
            }
        }
        return internalData;
    }
    
}