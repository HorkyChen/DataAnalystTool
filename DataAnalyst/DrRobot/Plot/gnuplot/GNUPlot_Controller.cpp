//
//  GNUPlot_Controller.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/17/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//
#include <sstream>
#include "GNUPlot_Controller.h"
#include "GNUPlotter.h"
#include "Assertions.h"
#include "ReportError.h"

extern const string getPlotFileFullPath(const char *path);
extern const string getFullPath(const char *path);

namespace DrRobot{
    
    const char* gnuplot_initialize_script = "gnuplot_init.gp";
    
    PassRefPtr<GNUPlot_Controller> GNUPlot_Controller::create()
    {
        return adoptRef<GNUPlot_Controller>(new GNUPlot_Controller(gnuplot_init()));
    }
    
    GNUPlot_Controller::GNUPlot_Controller()
    :mDev(0)
    {
        ;
    }
    
    GNUPlot_Controller::GNUPlot_Controller(gnuplot_ctrl* dev)
    :mDev(dev)
    {
        doInitialActions();
    }
    
    GNUPlot_Controller::~GNUPlot_Controller()
    {
        if(mDev)
        {
            gnuplot_close(mDev,false);
        }
        
        mDev=0;
    }
    
    void GNUPlot_Controller::plot_x_int(int * data, string* labels, int size, const char *title,GNUPlotter* plotter)
    {
        ASSERT(mDev);
        
        if(!plotter)
        {
            return;
        }
        
        doPrePlotActions(plotter);
        
        gnuplot_plot_x_int(mDev, data, labels, size, title!=NULL?title:plotter->title().c_str());
    }
    
    void GNUPlot_Controller::plot_x(float * data, string* labels, int size, const char *title,GNUPlotter* plotter)
    {
        ASSERT(mDev);
        
        if(!plotter)
        {
            return;
        }
        
        doPrePlotActions(plotter);
        
        gnuplot_plot_x(mDev, data, labels, size, title!=NULL?title:plotter->title().c_str());
    }
    
    bool GNUPlot_Controller::plot(Collection* data, const bool hasXticLabel,GNUPlotter* plotter)
    {
        ASSERT(data && mDev);
        
        if(!plotter)
        {
            return false;
        }
        
        if(!testCollection(data,hasXticLabel))
        {
            setError("Invalid data to plot!");
            return false;
        }
        
        string dataFile = getFullPath("tempfile.txt");
        if(!data->writeToFile(dataFile))
            return false;
        
        string scriptFile = getPlotFileFullPath("general_plot_cmd.gp");
        long columnCount = data->length();
        
        if(hasXticLabel)
        {
            columnCount--;
        }
        gnuplot_set_terminal_as_needed(mDev);
        
        gnuplot_cmd(mDev,"call '%s' '%s' %d '%s'",scriptFile.c_str()
                        ,dataFile.c_str()
                        ,columnCount
                        ,plotter->style().c_str());
        
        gnuplot_reset_terminal_as_needed(mDev);
        return true;
    }
    
    void GNUPlot_Controller::doPrePlotActions(GNUPlotter* plotter)
    {
        ASSERT(mDev);
        
        //gnuplot_cmd(mDev, plotter->prePlotCmdString());
        
        if(plotter->hasCommandFile()){
            string fullPath = getPlotFileFullPath(plotter->commandFile());
            gnuplot_set_commandFile(mDev, fullPath.c_str());
        }
        else{
            gnuplot_setstyle(mDev, plotter->style().c_str());
        }
    }
    
    void GNUPlot_Controller::setOutputFile(const string fileName)
    {
        ASSERT(mDev);
        
        gnuplot_set_outputFile(mDev, fileName.c_str());
    }
    
    void GNUPlot_Controller::doInitialActions()
    {
        if(!mDev)
            return;
        
        string fullPath = getPlotFileFullPath(gnuplot_initialize_script);
        gnuplot_cmd(mDev,"call '%s'", fullPath.c_str());
    }
    
    //Rough checking for the output node whether it could convert to numeric.
    //Numeric characters: 0-9,+,-,.,E,e
    bool GNUPlot_Controller::testCollection(Collection* data,const bool hasXticLabel)
    {
        ASSERT(data);
        bool result = true;
        
        long count = data->length();
        if(hasXticLabel){
            count --;
        }
        
        if(count<=0)
            return false;
        
        long checkingCnt = data->rowCount()/2;
        if(checkingCnt>50)
            checkingCnt = 50;
        else if (checkingCnt<1)
            checkingCnt = 1;
           
        for(long i=0;i<count;i++)
        {
            Node *node = data->getField(i);
            if(STRING != node->type())
                continue;
            
            
            for(long j=0;j<checkingCnt;j++)
            {
                if(!canConvertToNumber(node->getValue(j)))
                {
                    result = false;
                    break;
                }
            }
            
            if(!result)
                break;
        }
        
        return result;
    }
    
    bool GNUPlot_Controller::canConvertToNumber(const string& numberAsString)
    {
        float valor;
        
        std::stringstream stream(numberAsString);
        stream >> valor;
        if (stream.fail()) {
            return false;
        }
        return true;
    }
    
    void GNUPlot_Controller::sendCommand(const string command)
    {
        if(!mDev)
            return;
        
        gnuplot_cmd(mDev, command.c_str());
    }
} //end fo namespace
