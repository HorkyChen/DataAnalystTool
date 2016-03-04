//
//  DataFlowSourceElement.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "DataFlowSourceElement.h"
#include "CSVDataSource.h"
#include "BaseConfig.h"

namespace DrRobot
{
    bool DataFlowSourceElement::run()
    {
        if(mExecuted)
        {
            return true;
        }
        
        if(!mTargetHandle)
        {
            mTargetHandle = getTargetHandle();
        }
        
        mSuccessed = (static_cast<CSVDataSource*>(mTargetHandle))->parser();
        
        mExecuted = true;

        return mSuccessed;
    }
    
    bool DataFlowSourceElement::reset()
    {
        delete static_cast<CSVDataSource*>(mTargetHandle);
        mTargetHandle = NULL;
        
        return DataFlowElement::reset();
    }
    
    const char* DataFlowSourceElement::getDBTableName()
    {
        if(!mSuccessed)
        {
            return mTargetTable.c_str();
        }
        
        return DATA_SOURCE_TABLE_NAME;
    }
    
    void* DataFlowSourceElement::getTargetHandle()
    {
        if(mTargetHandle)
        {
            return mTargetHandle;
        }
        
        if(mParameters.empty())
        {
            mSuccessed = false;
            setError("Not specify the file path.");
            return NULL;
        }
        
        CSVDataSource* handle = NULL;
        if(mParameters.size()==2){
            handle = new CSVDataSource(parameter("filepath"),parameter("seperator"));
        }
        else{
            handle = new CSVDataSource(parameter("filepath"));
        }
        
        return handle;
    }
    
    void DataFlowSourceElement::getColumns(vector<string>& list)
    {
        if(!mTargetHandle)
        {
            mTargetHandle = getTargetHandle();
        }
        
        if(mTargetHandle)
        {
            reinterpret_cast<CSVDataSource*>(mTargetHandle)->getColumns(list);
        }
    }
    
    void DataFlowSourceElement::initAvailableParameters()
    {
        mAvailableParameters.push_back("filepath");
        mAvailableParameters.push_back("seperator");
        mAvailableParameters.push_back("headerless");
    }
  
    bool DataFlowSourceElement::serialize(zen::XmlOut& outXML, const string name)
    {
        outXML[name]["name"](mName); 
        outXML[name]["type"]("source"); 
        outXML[name]["parameters"]["filepath"](parameter("filepath"));
        outXML[name]["parameters"]["seperator"](parameter("seperator"));
        outXML[name]["parameters"]["headerless"](parameter("headerless"));
        
        return DataFlowElement::serialize(outXML, name);
    }
}
