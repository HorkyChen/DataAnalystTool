//
//  DataFlowFilterElement.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "DataFlowFilterElement.h"
#include "FilterFactory.h"
#include "ReportError.h"

namespace DrRobot
{
    bool DataFlowFilterElement::run()
    {
        if(mExecuted)
        {
            return true;
        }
        
        if(!mSourceElement)
        {
            setError("Not specify source element for the filter.");
            return false;
        }
        
        if(!mSourceElement->run())
        {
            return false;
        }
        
        if(!mTargetHandle)
        {
            mTargetHandle = getTargetHandle();
        }
        
        if(!mTargetHandle)
        {
            setError("Not support this filter!");
            return false;
        }
        
        if(mParameters.size()!=3)
        {
            setError("Invalid Parameters.");
            return false;
        }
        
        fprintf(stderr,"DataFlowFilterElement:targetField:%s,groupField:%s\n",parameter("targetField").c_str(),parameter("groupfields").c_str());

        (static_cast<BaseFilter*>(mTargetHandle))->setFields(parameter("targetField"),parameter("groupfields"));
        
        mSuccessed = (static_cast<BaseFilter*>(mTargetHandle))->execute();
        mExecuted = true;
        
        return mSuccessed;
    }
    
    bool DataFlowFilterElement::reset()
    {
        delete (static_cast<BaseFilter*>(mTargetHandle));
        mTargetHandle = NULL;
        
        return DataFlowElement::reset();
    }
    
    const char* DataFlowFilterElement::getDBTableName()
    {
        if(mTargetTable.length()>0)
        {
            return mTargetTable.c_str();
        }
        
        mTargetTable = mName;
        
        return mTargetTable.c_str();
    }
    
    void* DataFlowFilterElement::getTargetHandle()
    {
        if(mTargetHandle)
        {
            return mTargetHandle;
        }
        
        if(mParameters.size()<1)
        {
            mSuccessed = false;
            setError("Invalid Parameters.");
            return NULL;
        }
        
        if(!mSourceElement)
        {
            mSuccessed = false;
            setError("Not specify data source!");
            return NULL;
        }
        
        return FilterFactory::createFilter(parameter("type"),mSourceElement->getDBTableName(),getDBTableName());
    }
    
    void DataFlowFilterElement::getColumns(vector<string>& list)
    {
        //Get the columns from the Filter.
        if(!mTargetHandle)
        {
            mTargetHandle = getTargetHandle();
        }
        
        if(mTargetHandle)
        {
            static_cast<BaseFilter*>(mTargetHandle)->getColumns(list);
        }
        else
        {
            setError("Not support this filter!");
            return;
        }
        
        if(list.size() == 0)
        {
            //If there is no any columns, that means they are same as source element.
            ASSERT(mSourceElement);
            mSourceElement->getColumns(list);
        }
    }
    
    void DataFlowFilterElement::initAvailableParameters()
    {
        mAvailableParameters.push_back("type");
        mAvailableParameters.push_back("targetfield");
        mAvailableParameters.push_back("groupfields");
    }
    
    bool DataFlowFilterElement::serialize(zen::XmlOut& outXML, const string name)
    {
        outXML[name]["name"](mName); 
        outXML[name]["type"]("filter");
        outXML[name]["parameters"]["type"](parameter("type"));
        outXML[name]["parameters"]["targetfield"](parameter("targetfield"));
        outXML[name]["parameters"]["groupfields"](parameter("groupfields"));
        
        return DataFlowElement::serialize(outXML, name);;
    }

}
