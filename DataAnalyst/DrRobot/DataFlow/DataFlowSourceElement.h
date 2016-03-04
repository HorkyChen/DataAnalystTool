//
//  DataFlowSourceElement.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DataFlowSourceElement__
#define __DataAnalyst__DataFlowSourceElement__

#include "DataFlowElement.h"
#include "ReportError.h"
/*
 One parameter for Source Element:
   filepath
 For CSV File:
   seperator, headerless
 */
namespace DrRobot{
    
    class DataFlowSourceElement:public DataFlowElement
    {
    public:
        DataFlowSourceElement()
        :DataFlowElement()
        {
            initAvailableParameters();
        }
        
        DataFlowSourceElement(const string& _name, int _type)
        :DataFlowElement(_name,_type)
        {
            initAvailableParameters();
        }
        
        ~DataFlowSourceElement(){reset();};
        virtual bool run();
        virtual bool reset();
        virtual const char* getDBTableName();
        virtual void getColumns(vector<string>& list);
        
        virtual bool serialize(zen::XmlOut& outXML, const string name);
    protected:
        virtual void* getTargetHandle();
        virtual void initAvailableParameters();
    };
    
}
#endif /* defined(__DataAnalyst__DataFlowSourceElement__) */
