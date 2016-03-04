//
//  DataFlowFilterElement.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DataFlowFilterElement__
#define __DataAnalyst__DataFlowFilterElement__

#include "DataFlowElement.h"

/*
 Three parameters for Filter Element:
    type, targetfield, groupfields
 */

namespace DrRobot{
    
    class DataFlowFilterElement:public DataFlowElement
    {
    public:
        DataFlowFilterElement()
        :DataFlowElement()
        {
            initAvailableParameters();
        }
        
        DataFlowFilterElement(const string& _name, int _type)
        :DataFlowElement(_name,_type)
        {
            initAvailableParameters();
        }
        
        ~DataFlowFilterElement(){reset();};
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

#endif /* defined(__DataAnalyst__DataFlowFilterElement__) */
