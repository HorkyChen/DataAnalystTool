//
//  CSVDataSource.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__CSVDataSource__
#define __DataAnalyst__CSVDataSource__

#include <string>
#include "BaseDataSource.h"
#include "CSVparser.hpp"

namespace DrRobot{

class CSVDataSource : public BaseDataSource
{
private:
    DrRobot::CSVParser mFileParser;
public:
    CSVDataSource(const string& filePath)
    :BaseDataSource(filePath)
    ,mFileParser(filePath.c_str(),eFILE)
    {
    };
    
    CSVDataSource(const string& filePath,const string& seperator)
    :BaseDataSource(filePath)
    ,mFileParser(filePath.c_str(),seperator.c_str()[0],eFILE)
    {
    };
    
    bool parser();
    
    void getColumns(vector<string>& list);
    
    virtual DrRobot::Collection* getData(const vector<string> fields);
};

}
#endif /* defined(__DataAnalyst__CSVDataSource__) */
