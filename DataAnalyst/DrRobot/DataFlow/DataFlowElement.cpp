//
//  DataFlowElement.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "DataFlowElement.h"
#include "BaseFilter.h"
#include "BaseDataSource.h"

namespace DrRobot
{
    bool DataFlowElement::run()
    {
        return false;
    }
    
    bool DataFlowElement::reset()
    {
        mExecuted = false;
        mSuccessed = true;
        mParameters.clear();
        mAvailableParameters.clear();
        
        return true;
    }
    
    bool DataFlowElement::exportTo()
    {
        return false;
    }
    
    Collection* DataFlowElement::getResult(const vector<string>& fields)
    {
        if(ELEMENT_FILTER != type() && ELEMENT_SOURCE != type())
        {
            return NULL;
        }
        
        if(!mExecuted)
        {
            run();
        }
        
        if(mSuccessed && mExecuted)
        {
            if(ELEMENT_FILTER == type())
                return (static_cast<BaseFilter*>(mTargetHandle))->getData(fields);
            else if(ELEMENT_SOURCE == type())
                return (static_cast<BaseDataSource*>(mTargetHandle))->getData(fields);
                
        }
        
        return NULL;
    }

    const char* DataFlowElement::getDBTableName()
    {
        return mTargetTable.c_str();
    }
    
    void DataFlowElement::setParameters(const vector<string>& values)
    {
        ASSERT(values.size()>0);
        ASSERT(values.size()<=mAvailableParameters.size());
        
        mParameters.clear();
        
        addParameterImpl(values);
    }
    
    void DataFlowElement::addParameters(const vector<string>& values)
    {
        ASSERT(values.size()>0);
        ASSERT((values.size()+mParameters.size())<=mAvailableParameters.size());
        
        addParameterImpl(values);
    }
    
    void DataFlowElement::addParameterImpl(const vector<string>& values)
    {
        unsigned long index=mParameters.size();
        vector<string>::const_iterator it = values.begin();
        while(it != values.end())
        {
            mParameters[mAvailableParameters[index]] = *it;
            fprintf(stderr,"DataFlowElement:parameters:%s\n",mParameters[mAvailableParameters[index]].c_str());
            index++;
            it++;
        }
        
        ASSERT(index<=mAvailableParameters.size()+1);
    }
    
    void DataFlowElement::setParameter(const string key, const string value)
    {
        string strKey = key;
        std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
        mParameters[strKey] = value;
    }
    
    const string DataFlowElement::parameter(const string key)
    {
        string strKey = key;
        std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
        if(hasParameter(strKey))
        {
            return mParameters[strKey];
        }
        
        return "";
    }
        
    void* DataFlowElement::getTargetHandle()
    {
        return NULL;
    }
    
    bool DataFlowElement::serialize(zen::XmlOut& outXML, const string name)
    {
        if(mSourceElement){
            outXML[name]["source"](mSourceElement->name());
        }
        return true;
    }
    
    bool DataFlowElement::deserialize(zen::XmlIn& inXML)
    {
        string parameterVal;
        for(vector<string>::const_iterator i= mAvailableParameters.begin(); i != mAvailableParameters.end(); ++i)
        {
            if(inXML["parameters"][*i])
            {
                inXML["parameters"][*i](parameterVal);
                setParameter(*i, parameterVal);
            }
        }
        
        return true;
    }
}
