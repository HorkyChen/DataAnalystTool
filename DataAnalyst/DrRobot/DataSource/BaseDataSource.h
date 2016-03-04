//
//  BaseDataSource.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__BaseDataSource__
#define __DataAnalyst__BaseDataSource__

#include <string>
#include "BaseConfig.h"
#include "Collection.h"

using namespace std;

namespace DrRobot{
    
class BaseDataSource
{
public:
    BaseDataSource(const string& filePath)
    :mFilePath(filePath)
    {}
    
    const char* getTableName(){ return DATA_SOURCE_TABLE_NAME; };
    
    bool parser(){return true;};
    const string getFilePath() {return mFilePath;};
    virtual Collection* getData(const vector<string> fields){return NULL;};
protected:
    Collection* getInternalData(){return &mCollection;};
private:
    Collection mCollection;
    string mFilePath;
};
    
}
#endif /* defined(__DataAnalyst__BaseDataSource__) */
