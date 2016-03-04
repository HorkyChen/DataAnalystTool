//
//  GNUPlotter.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "GNUPlotter.h"
#include <iostream>
#include "ReportError.h"
using namespace std;

namespace DrRobot{
    GNUPlotter::GNUPlotter()
    :mDevController(NULL)
    ,mStyle("points")
    {
    }
    
    GNUPlotter::GNUPlotter(const string title,const char* style)
    :BasePlot(title)
    ,mDevController(0)
    ,mStyle(style)
    {
    }
    
    GNUPlotter::GNUPlotter(const string title,const char* style,const GNUPlotter& plotter)
    :BasePlot(title)
    ,mDevController(plotter.getPlotDevice())
    ,mStyle(style)
    {
    }
    
    GNUPlotter::~GNUPlotter()
    {
    }
    
    void GNUPlotter::close()
    {
        mDevController = NULL;
    }
    
    bool GNUPlotter::plot(Collection * collection, const string& xticLabelColumn)
    {
        if(!doPreCheck(collection)){
            return false;
        }
        
        bool hasXticLabel = collection->indexOf(xticLabelColumn)>=0;
        return mDevController->plot(collection,hasXticLabel,this);
    }
    
    bool GNUPlotter::doPreCheck(Collection * collection)
    {
        if(!collection){
            setError("No valid data for plotting.");
            return false;
        }
        
        if(!mDevController){
            mDevController = GNUPlot_Controller::create();
        }
        
        if(!mDevController)
        {
            setError("Cannot initialize the gnuplot! Please install it.");
            return false;
        }
        
        return true;
    }
    /* 
     * The original implementation.
     *
    bool GNUPlotter::plot(Collection * collection, const string& xticLabelColumn)
    {
        if(!collection){
            setError("No valid data for plotting.");
            return false;
        }
        
        if(!mDevController){
            mDevController = GNUPlot_Controller::create();
        }
        
        if(!mDevController)
        {
            setError("Cannot initialize the gnuplot! Please install it.");
            return false;
        }
        
        mInvolveMultiFields = collection->length()>1;
        
        int lableColumnIndex = -1;
        Node * lableNode = NULL;
        if(!xticLabelColumn.empty()){
            lableColumnIndex = collection->indexOf(xticLabelColumn);
            lableNode = collection->getField(lableColumnIndex);
        }
        
        bool result = true;
        for(int i=0;i<collection->length();i++){
            if(i==lableColumnIndex)
                continue;
            
            if(!plotNode(collection->getField(i), lableNode)){
                result = false;
                break;
            }
        }
        
        return result;
    }
     */
    
    bool GNUPlotter::plotNode(const Node * node, const Node *labelNode)
    {
        if(!node){
            setError("Node is null for plotting.");
            return false;
        }
        
        int* data = NULL;
        string* labels = NULL;
        const char * title = mInvolveMultiFields?node->name().c_str():NULL;
        
        if(labelNode){
            vector<string>* values = (vector<string> *)labelNode->getValues();
            labels = &(*values)[0];
        }
        
        try{
            switch(node->type()){
                case INTEGER:
                {
                    vector<int>* values = (vector<int> *)node->getValues();
                    data = &(*values)[0];
                    
                    mDevController->plot_x_int(data, labels, node->size(), title, this);
                }
                    break;
                case NUMERIC:
                {
                    vector<float>* values = (vector<float> *)node->getValues();
                    float* data = &(*values)[0];
                    mDevController->plot_x(data, labels, node->size(), title, this);
                }
                    break;
                case STRING:
                {
                    //Try to convert data type.
                    Node *newNode = Node::convertNodeType(node,NUMERIC);
                    vector<float>* values = (vector<float> *)newNode->getValues();
                    float* data = &(*values)[0];
                    mDevController->plot_x(data, labels, node->size(), title, this);
                }
                    break;
            }
        }
        catch(...){
            setError("Error happened in plotting.");
            return false;
        }
        
        return true;
    }
    
    
    const char* GNUPlotter::prePlotCmdString()
    {
        return "";
    }
    
    const char* GNUPlotter::postPlotCmdString()
    {
        return NULL;
    }
    
    bool GNUPlotter::exportToFile(Collection * collection, const string& xticLabelColumn, const string& fileName)
    {
        ASSERT(fileName.length());
        
        if(!mDevController){
            mDevController = GNUPlot_Controller::create();
        }
        
        mDevController->setOutputFile(fileName);
        
        return plot(collection, xticLabelColumn);
    }
}