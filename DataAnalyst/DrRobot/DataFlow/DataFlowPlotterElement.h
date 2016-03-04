//
//  DataFlowPlotterElement.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DataFlowPlotterElement__
#define __DataAnalyst__DataFlowPlotterElement__

#include "DataFlowElement.h"
/*
 two parameters for Plotter Element:
 type, title, xticlabelfield(Optional),targetfield1(Optional),targetfield2(Optional), targetfield3(Optional),...
 */
namespace DrRobot{
    
    class DataFlowPlotterElement:public DataFlowElement
    {
    public:
        DataFlowPlotterElement()
        :DataFlowElement()
        {
            initAvailableParameters();
        }
        
        DataFlowPlotterElement(const string& _name, int _type)
        :DataFlowElement(_name,_type)
        {
            initAvailableParameters();
        }
        
        ~DataFlowPlotterElement(){reset();};
        virtual bool run();
        virtual bool reset();
        virtual bool exportTo();
        virtual string getTargetFileName();
        
        virtual bool serialize(zen::XmlOut& outXML, const string name);
    protected:
        virtual void* getTargetHandle();
        virtual void initAvailableParameters();
    private:
        bool executeWithConfig(bool exportTo);
    };
    
}

#endif /* defined(__DataAnalyst__DataFlowPlotterElement__) */
