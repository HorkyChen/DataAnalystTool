//
//  DrRobot.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "DrRobot.h"
#include <algorithm>
#include "FilterFactory.h"
#include "PlotterFactory.h"
#include "DataFlowElement.h"
#include "DataFlowSourceElement.h"
#include "DataFlowFilterElement.h"
#include "DataFlowPlotterElement.h"
#include "CppSQLite3.h"
#include "ReportBuilder.h"
#include "ReportError.h"

const string getFullPath(const char *path);

namespace DrRobot{
    static DrRobot sDrRobotInstance;
    static bool sInitialized = false;
    
    DrRobot* getDrRobot()
    {
        if(!sInitialized)
        {
            FilterFactory::registerFilters(&sDrRobotInstance);
            PlotterFactory::registerPlotters(&sDrRobotInstance);
            sInitialized = true;
        }
        
        return &sDrRobotInstance;
    }
    
    DrRobot::~DrRobot()
    {
        mFilterSet.clear();
        mPlotterSet.clear();
        mDataFlowTree.clear();
    }
    
    void DrRobot::registerFilter(const string& name, const string& description)
    {
        FilterItem newItem(name,description);
        mFilterSet.push_back(newItem);
    }
    
    void DrRobot::registerPlotter(const string name, const string& description)
    {
        FilterItem newItem(name,description);
        mPlotterSet.push_back(newItem);
    }
    
    const char * DrRobot::getFilterName(int index)
    {
        if(index>=0 && index<mFilterSet.size())
            return mFilterSet[index].name.c_str();
        else 
            return NULL;
    }

    const char * DrRobot::getFilterDescription(int index)
    {
        if(index>=0 && index<mFilterSet.size())
        {
            return mFilterSet[index].description.c_str();
        }
        else
            return NULL;
    }
    
    const char * DrRobot::getPlotterName(int index)
    {
        if(index>=0 && index<mPlotterSet.size())
            return mPlotterSet[index].name.c_str();
        else 
            return NULL;
    }

    const char * DrRobot::getPlotterDescription(int index)
    {
        if(index>=0 && index<mPlotterSet.size())
            return mPlotterSet[index].description.c_str();
        else
            return NULL;
    }
    
    const vector<string>& DrRobot::getSourceFields()
    {
        mFields.clear();
        
        if(mDataFlowTree.size()>0)
        {
            tree<RefPtr<DataFlowElement>>::leaf_iterator iter = mDataFlowTree.begin();
            (*iter).get()->getColumns(mFields);
        }
        return mFields;
    }
    
    
    void DrRobot::runElements(typename tree<RefPtr<DataFlowElement>>::iterator iRoot) 
	{
        if (mDataFlowTree.number_of_children(iRoot) == 0) {
            if((*iRoot).get()->type()==DataFlowElement::ELEMENT_PLOTTER)
                (*iRoot).get()->run();
		}
        else {
            typename tree<RefPtr<DataFlowElement>>::sibling_iterator iChildren;
            for (iChildren = mDataFlowTree.begin(iRoot); iChildren != mDataFlowTree.end(iRoot); ++iChildren) {
                runElements(iChildren);
			}
		}
    }
    
    bool DrRobot::runWithConfiguration(bool toExport)
    {
        bool result = true;
        clearError();
                
        if(mDataFlowTree.empty())
        {
            setError("No existing elements!");
            return false;
        }
        
        tree<RefPtr<DataFlowElement>>::leaf_iterator iter = mDataFlowTree.begin_leaf();
        while(iter != mDataFlowTree.end_leaf()){
            DataFlowElement* element = (*iter).get();
            if(element->type() != DataFlowElement::ELEMENT_PLOTTER)
            {
                iter++;
                continue;
            }
            
            if(toExport){
                if(!element->exportTo()){
                    result = false;
                    break;
                }
                else{
                    mExportedFiles.push_back(element->getTargetFileName());
                }
            }
            else if(!element->run()){
                result = false;
                break;
            }
            
            iter++;
        }

        return result;
    }
    
    bool DrRobot::generateReport()
    {
        if(runWithConfiguration(true))
        {
            ReportBuilder builder;
            builder.generateReport(mExportedFiles);
            mExportedFiles.clear();
            return true;
        }
        
        return false;
    }
    
    const string DrRobot::getReportFilePath()
    {
        return getFullPath(ReportBuilder::getReportFileName());
    }
    
    bool DrRobot::run()
    {
        return runWithConfiguration(false);
    }
    
    bool DrRobot::clearElements()
    {
        mDataFlowTree.clear();
        
        stopAllUsedResources();
        
        return true;
    }
    
    void DrRobot::resetElementToUnExecuted(const string& name)
    {
        DataFlowElement* element = getDataFlowElement(name);
        
        if(element)
        {
            element->resetToUnexecuted();
        }
    }
    
    bool DrRobot::stopAllUsedResources()
    {
        shutDownDB();
        return true;
    }
    
    bool DrRobot::createNewElement(const string& srcElementName, const string newElementName, int nElementType)
    {        
        switch(nElementType)
        {
            case DataFlowElement::ELEMENT_SOURCE:
                {
                    if(mDataFlowTree.size()>0)
                    {
                        setError("Only one data source could be supported!");
                        return false;
                    }
                    
                    removeDataFlowElement(newElementName);
                    
                    DataFlowSourceElement* element = new DataFlowSourceElement(newElementName,DataFlowElement::ELEMENT_SOURCE);
                    
                    mDataFlowTree.insert(mDataFlowTree.begin(), adoptRef<DataFlowElement>(element));
                }
                break;
            case DataFlowElement::ELEMENT_FILTER:
                {
                    if(mDataFlowTree.size() == 0)
                    {
                        setError("Not specify data source yet!");
                        return false;
                    }
                    
                    tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), srcElementName.c_str());
                    
                    if(iterSrcElement == mDataFlowTree.end())
                    {
                        setError("Invalid source element!");
                        return false;
                    }
                    
                    removeDataFlowElement(newElementName);
                    
                    DataFlowFilterElement *element = new DataFlowFilterElement(newElementName,DataFlowElement::ELEMENT_FILTER);
                    element->setSourceElement((*iterSrcElement).get());
                    
                    mDataFlowTree.append_child(iterSrcElement,adoptRef<DataFlowElement>(element));
                }
                break;
            case DataFlowElement::ELEMENT_PLOTTER:
                {
                    if(mDataFlowTree.size() == 0)
                    {
                        setError("Not specify data source yet!");
                        return false;
                    }
                    
                    tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), srcElementName.c_str());
                    if(iterSrcElement == mDataFlowTree.end())
                    {
                        setError("Invalid source element!");
                        return false;
                    }
                    
                    removeDataFlowElement(newElementName);
                    
                    DataFlowPlotterElement* element = new DataFlowPlotterElement(newElementName,DataFlowElement::ELEMENT_PLOTTER);
                    element->setSourceElement((*iterSrcElement).get());

                    mDataFlowTree.append_child(iterSrcElement,adoptRef<DataFlowElement>(element));
                }
                break;
            default:
                CRASH();
        }
        return true;
    }
    
    DataFlowElement* DrRobot::getDataFlowElement(const string& name)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), name.c_str());
        if(iterSrcElement != mDataFlowTree.end())
        {
            return ((*iterSrcElement).get());
        }
        return NULL;
    }
    
    bool DrRobot::removeDataFlowElement(const string& name)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), name.c_str());
        if(iterSrcElement != mDataFlowTree.end())
        {
            mDataFlowTree.erase(iterSrcElement);
            return true;
        }
        
        return false;
    }
    
    bool DrRobot::hasDataFlowElement(const string& name)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), name.c_str());
        return (iterSrcElement != mDataFlowTree.end());
    }
    
    bool DrRobot::setElementParameter(const string& targetElementName, const vector<string>& parameters)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), targetElementName.c_str());
        if(iterSrcElement != mDataFlowTree.end())
        {
            (*iterSrcElement).get()->setParameters(parameters);
            return true;
        }
        
        setError("Not found the target element.");
        return false;
    }
    
    bool DrRobot::setElementParameter(const string& targetElementName, const string& key, const string& value)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), targetElementName.c_str());
        if(iterSrcElement != mDataFlowTree.end())
        {
            (*iterSrcElement).get()->setParameter(key,value);
            return true;
        }
        
        setError("Not found the target element.");
        return false;
    }
    
    bool DrRobot::addElementParameter(const string& targetElementName, const vector<string>& parameters)
    {
        tree<RefPtr<DataFlowElement>>::iterator iterSrcElement = find(mDataFlowTree.begin(), mDataFlowTree.end(), targetElementName.c_str());
        if(iterSrcElement != mDataFlowTree.end())
        {
            (*iterSrcElement).get()->addParameters(parameters);
            return true;
        }
        
        setError("Not found the target element.");
        return false;
    }
    
    bool DrRobot::getOutputFieldsOfElement(const string& name, vector<string>& list)
    {
        DataFlowElement* element = getDataFlowElement(name);
        
        if(element)
        {
            element->getColumns(list);
            return true;
        }
        return false;
    }
    
    const string DrRobot::getLastErrorString()
    {
        return getLastError();
    }
    
    bool DrRobot::deserializeFromFile(const string filename)
    {
        mDataFlowTree.clear();
        
        zen::XmlDoc doc;
        try
        {
            doc = zen::load(filename.c_str()); 
        }
        catch (const zen::XmlError& e) 
        {
            setError("Failed to load file.");
            return false;
        }
        
        zen::XmlIn in(doc);
        int elementCount = 0;
        bool result = true;
        
        in["ElementCount"](elementCount);
        
        if(elementCount <= 0){
            setError("Invalid file content.");
            return false;
        }
        
        for(int i=0;i<elementCount;i++)
        {
            char xmlElementName[10] = {0};
            string elementName;
            string type;
            string source;
            
            sprintf(xmlElementName,"Element%d",i);
            zen::XmlIn xmlElement = in[xmlElementName];
            
            xmlElement["type"](type);
            xmlElement["source"](source);
            xmlElement["name"](elementName);
            
            if(!type.compare("source"))
            {
                createNewElement(source,elementName,DataFlowElement::ELEMENT_SOURCE);
            }
            else if(!type.compare("filter"))
            {
                createNewElement(source,elementName,DataFlowElement::ELEMENT_FILTER);
            }
            else if (!type.compare("plotter"))
            {
                createNewElement(source,elementName,DataFlowElement::ELEMENT_PLOTTER);
            }
            
            //deserialize with each element
            if(!getDataFlowElement(elementName)->deserialize(xmlElement))
            {
                result = false;
                break;
            }
        }
        
        return result;
    }
    
    bool DrRobot::serializeToFile(const string filename)
    {
        if(mDataFlowTree.empty())
        {
            setError("No existing elements for exporting!");
            return false;
        }
        
        zen::XmlDoc doc; 
        zen::XmlOut out(doc); 
        
        mExportingElementIndex = 0;
        
        out["ElementCount"](mDataFlowTree.size());
        for(typename tree<RefPtr<DataFlowElement>>::sibling_iterator iRoots = mDataFlowTree.begin(); iRoots != mDataFlowTree.end(); ++iRoots) {
            exportElements(out,iRoots);
		}
        
        try
        {
            zen::save(doc, filename.c_str()); 
        }
        catch (const zen::XmlFileError& e) 
        {
            setError("Failed to save exporting file!");
            return false;
        }
        
        return true;
    }
    
    void DrRobot::exportElements(zen::XmlOut& out, typename tree<RefPtr<DataFlowElement>>::iterator iRoot) 
    {
        (*iRoot).get()->serialize(out,getExportingElementName());
        
        typename tree<RefPtr<DataFlowElement>>::sibling_iterator iChildren;
        for (iChildren = mDataFlowTree.begin(iRoot); iChildren != mDataFlowTree.end(iRoot); ++iChildren) {
            exportElements(out, iChildren);
        }
    }
    
    string DrRobot::getExportingElementName()
    {
        char sElementName[10] = {0};
        sprintf(sElementName,"Element%d",mExportingElementIndex++);
        return string(sElementName);
    }
}


const string getFullPath(const char *path){
    string fullPath = DrRobot::getDrRobot()->getWorkingPath();
    fullPath = fullPath+"/"+path;
    return fullPath;
}

const string getPlotFileFullPath(const char *path){
    string fullPath = DrRobot::getDrRobot()->getPlotFilePath();
    fullPath = fullPath+"/"+path;
    return fullPath;
}

