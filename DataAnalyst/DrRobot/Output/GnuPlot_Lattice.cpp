//
//  GnuPlot_Lattice.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/28/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//
#include <string>
#include "GnuPlot_Lattice.h"
#include "ReportError.h"
#include "Assertions.h"
#include "Collection.h"

using namespace std;

extern const string getFullPath(const char *path);

namespace DrRobot{
    
    bool GnuPlot_Lattice::plot(Collection * collection, const string& xticLabelColumn)
    {
        if(!doPreCheck(collection)){
            return false;
        }
        
        long colCount = collection->length();
        
        if(colCount==0 || colCount>10){
            setError("The data exceed the limitation(10x10) which is not suitable for lattice.");
            return false;
        }
        
        char command[1024]={0};
        
        string dataFile = getFullPath("tempfile.txt");
        if(!collection->writeToFile(dataFile))
            return false;
        
        mDevController->sendCommand("reset\nunset xtic\nunset ytic\nset xlabel ''");
        sprintf(command,"set multiplot title \"%s\" layout %d,%d",
                title().c_str(),colCount,colCount);
        mDevController->sendCommand(command);
        
        for(int j=0;j<colCount;j++)
        {
            for(int i=0;i<colCount;i++)
            {
                if(j==0)
                {
                    sprintf(command,"set xlabel ''\nset title '%s'",collection->getField(i)->name().c_str());
                    mDevController->sendCommand(command);
                }
                else
                {
                    mDevController->sendCommand("set xlabel ''\nset title ''");
                }
                
                if(i==0)
                {
                    sprintf(command,"set ylabel '%s'",
                            collection->getField(j)->name().c_str());
                    mDevController->sendCommand(command);
                }
                else
                {
                    mDevController->sendCommand("set ylabel ''");
                }
                
                sprintf(command,"plot '%s' using %d:%d title '' pt 7",
                        dataFile.c_str(),i+1,j+1);
                mDevController->sendCommand(command);
            }
        }
        
        mDevController->sendCommand("unset multiplot");
        
        return true;
    }
}//End of namespace