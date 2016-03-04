//
//  DrRobot.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DrRobot__
#define __DataAnalyst__DrRobot__

#include <string>
#include <vector>
#include <zenxml/xml.h>
#include "tree.hh"
#include "RefPtr.h"

using namespace std;

class DataFlowElement;

namespace DrRobot{
    class DrRobot;
    DrRobot* getDrRobot();
    
    class DrRobot{
    public:
        ~DrRobot();
    private:
            class FilterItem{
                public:
                    FilterItem(const string& _name, const string& _description)
                    :name(_name)
                    ,description(_description)
                    {}
                public:
                    string name;
                    string description;
                };
    private:
        vector<FilterItem> mFilterSet;
        vector<FilterItem> mPlotterSet;
        vector<string> mFields;
        vector<string> mExportedFiles;
        
        tree<RefPtr<DataFlowElement>> mDataFlowTree;
    public:
        void registerFilter(const string& name, const string& description);
        void registerPlotter(const string name, const string& description);
        
        unsigned long getFilterCount(){return mFilterSet.size();}
        const char * getFilterName(int index);
        const char * getFilterDescription(int index);
        
        unsigned long getPlotterCount(){return mPlotterSet.size();}
        const char * getPlotterName(int index);
        const char * getPlotterDescription(int index);
        
        bool createNewElement(const string& srcElementName, const string newElementName, int nElementType);
        bool hasDataFlowElement(const string& name);
        bool removeDataFlowElement(const string& name);
        
        bool setElementParameter(const string& targetElementName, const vector<string>& parameters);
        bool addElementParameter(const string& targetElementName, const vector<string>& parameters);
        bool setElementParameter(const string& targetElementName, const string& key, const string& value);
        
        bool run();
        bool generateReport();
        bool clearElements();
        bool stopAllUsedResources();
        
        const vector<string>& getSourceFields();
        bool getOutputFieldsOfElement(const string& name, vector<string>& list);
        void resetElementToUnExecuted(const string& name);
        
        void setWorkingPath(const string& path) {mWorkingPath = path;};
        const string getWorkingPath(){return mWorkingPath;};
        
        void setPlotFilePath(const string& path) {mPlotFilePath = path;};
        const string getPlotFilePath(){return mPlotFilePath;};
        const string getReportFilePath();
        const string getLastErrorString();
        
        bool serializeToFile(const string filename);
        bool deserializeFromFile(const string filename);
    private:
        DataFlowElement* getDataFlowElement(const string& name);
        void runElements(typename tree<RefPtr<DataFlowElement>>::iterator iRoot);
        bool runWithConfiguration(bool toExport);
        string getExportingElementName();
        void exportElements(zen::XmlOut& out, typename tree<RefPtr<DataFlowElement>>::iterator iRoot);
    private:
        string mWorkingPath;
        string mPlotFilePath;
        int mExportingElementIndex;
    };
    
}
#endif /* defined(__DataAnalyst__DrRobot__) */
