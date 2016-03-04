//
//  GnuPlot_PieChart.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/21/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "GnuPlot_PieChart.h"
#include "ReportError.h"
#include "Assertions.h"

namespace DrRobot{
    const char* selectedColors[20] = {"red","orange","blue","forest-green","dark-magenta","yellow","grey","green","#8b1a0e","#5e9c36","magenta","cyan","magenta","","","","","","",""};
    
    bool GnuPlot_PieChart::plot(Collection * collection, const string& xticLabelColumn)
    {
        if(!doPreCheck(collection)){
            return false;
        }
        
        long count = collection->rowCount();
        
        if(count==0 || count>20){
            setError("The data exceed the limitation which is not suitable for pie chart.");
            return false;
        }
        
        mDevController->sendCommand("set angles degrees\nset size square\nset style fill solid 1.0 border -1");
        
        Node *xticNode = NULL;
        if(collection->indexOf(xticLabelColumn)>=0){
            xticNode = collection->getField(xticLabelColumn);
        }
        
        Node *dataNode = collection->getField(0);
        ASSERT(dataNode);
        
        float oldV = 0.0;
        float newV = 0.0;
        for(long i=0;i<count;i++)
        {
            newV = atof(dataNode->getValue(i).c_str());
            
            char command[1024]={0};
            sprintf(command,"set object %ld circle at screen 0.45,0.45 size screen 0.3 arc [%d:%d] fillcolor rgb \"%s\" front",i+1,(int)floor(oldV/100*360),(int)floor((newV+oldV)/100*360),selectedColors[i]);
            
            mDevController->sendCommand(command);
            if(xticNode)
            {
                int angel = floor((oldV+newV/2)/100*360);
                string label = xticNode->getValue(i);
                sprintf(command,"set label %ld '%s' at  screen (0.45+0.35*cos(%d)),(0.45+0.35*sin(%d))",i+1,label.c_str(),angel,angel);
                mDevController->sendCommand(command);
            }
            
            oldV += newV;
        }
        
        mDevController->sendCommand("unset border\nunset tics\nunset key\nplot x with lines lc rgb \"#ffffff\"\n");
        return true;
    }
}//End of namespace