//
//  DataFlowPlotterElement.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "DataFlowPlotterElement.h"
#include "PlotterFactory.h"
#include "BasePlot.h"
#include "ReportError.h"

const string getFullPath(const char *path);

namespace DrRobot
{
    bool DataFlowPlotterElement::run()
    {
        return executeWithConfig(false);
    }
    
    bool DataFlowPlotterElement::exportTo()
    {
        return executeWithConfig(true);
    }
    
    bool DataFlowPlotterElement::executeWithConfig(bool exportTo)
    {
        if(mExecuted)
        {
            return true;
        }
        
        vector<string> fieldsList;
        
        if(!mTargetHandle)
        {
            mTargetHandle = getTargetHandle();
        }
        
        if(mTargetHandle && mSourceElement)
        {
            if(!mSourceElement->run())
            {
                return false;
            }
            
            char field[16] = {0};
            string xticLabelField = parameter("xticlabelfield");
            
            for(int i=1;i<=5;i++)
            {    
                sprintf(field,"targetfield%d",i);
                if(hasParameter(field))
                {
                    fieldsList.push_back(parameter(field));
                }
                else
                    break;
            }
            
            if(fieldsList.size() == 0)
            {
                mSourceElement->getColumns(fieldsList);
            }
            else
            {
                if(!xticLabelField.empty()){
                    fieldsList.push_back(xticLabelField);
                }    
            }
            
            
            if(exportTo)
            {
                string exportedFileName = getTargetFileName();
                mSuccessed = (static_cast<BasePlot*>(mTargetHandle))->exportToFile(mSourceElement->getResult(fieldsList),xticLabelField,exportedFileName);
            }
            else
            {
                mSuccessed = (static_cast<BasePlot*>(mTargetHandle))->plot(mSourceElement->getResult(fieldsList),xticLabelField);
            }
            mExecuted = true;
        }
        else
        {
            mSuccessed = false;
            setError("Not specify the filter element.");
        }
        
        return mSuccessed;
    }
    
    bool DataFlowPlotterElement::reset()
    {
        delete (static_cast<BasePlot*>(mTargetHandle));
        mTargetHandle = NULL;
        
        return DataFlowElement::reset();
    }
    
    void* DataFlowPlotterElement::getTargetHandle()
    {
        if(mTargetHandle)
        {
            return mTargetHandle;
        }
        
        if(!hasParameter("type"))
        {
            return PlotterFactory::createPlotter("points","");
        }
        
        return PlotterFactory::createPlotter(parameter("type"),parameter("title"));
    }
    
    string DataFlowPlotterElement::getTargetFileName()
    {
        if(parameter("type") == "Text")
        {
            return name()+".html";
        }
        else 
        {
            return name()+".svg";
        }
    }
    
    void DataFlowPlotterElement::initAvailableParameters()
    {
        mAvailableParameters.push_back("type");
        mAvailableParameters.push_back("title");
        mAvailableParameters.push_back("xticlabelfield");
        mAvailableParameters.push_back("targetfield1");
        mAvailableParameters.push_back("targetfield2");
        mAvailableParameters.push_back("targetfield3");
        mAvailableParameters.push_back("targetfield4");
        mAvailableParameters.push_back("targetfield5");
    }
    
    bool DataFlowPlotterElement::serialize(zen::XmlOut& outXML, const string name)
    {
        outXML[name]["name"](mName); 
        outXML[name]["type"]("plotter");
        outXML[name]["parameters"]["type"](parameter("type"));
        outXML[name]["parameters"]["title"](parameter("title"));
        outXML[name]["parameters"]["xticlabelfield"](parameter("xticlabelfield"));
        outXML[name]["parameters"]["targetfield1"](parameter("targetfield1"));
        outXML[name]["parameters"]["targetfield2"](parameter("targetfield2"));
        outXML[name]["parameters"]["targetfield3"](parameter("targetfield3"));
        outXML[name]["parameters"]["targetfield4"](parameter("targetfield4"));
        outXML[name]["parameters"]["targetfield5"](parameter("targetfield5"));
        
        return DataFlowElement::serialize(outXML, name);;
    }
    
}
