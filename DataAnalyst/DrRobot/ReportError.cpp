//
//  ReportError.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/29/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "ReportError.h"
#include <string>
#include <stdio.h>
namespace DrRobot{
static ReportEorr sErrorReporter;

void setError(const char * message)
{
    //For Debug.
    fprintf(stderr,"%s\n",message);
    
    sErrorReporter.setError(message);
}

const std::string getLastError()
{
    return sErrorReporter.getLastError();
}

void clearError(){
    sErrorReporter.clearError();
}

}//end of namespace