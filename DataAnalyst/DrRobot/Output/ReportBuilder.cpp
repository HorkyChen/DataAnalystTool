//
//  ReportBuilder.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/10/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "ReportBuilder.h"
#include "ReportError.h"
#include "BaseUtilities.h"

extern const string getFullPath(const char *path);

namespace DrRobot{
    bool ReportBuilder::generateReport(const vector<string> exportedFiles)
    {
        if(exportedFiles.empty())
        {
            setError("Could not generate report without any valid exported file!");
            return false;
        }
        
        if(!generateHeader())
        {
            setError("Failed to generate report header!");
            return false;
        }
        
        if(!generateBody(exportedFiles))
        {
            setError("Failed to generate report body!");
            return false;
        }
        
        //Write to HTML files
        if(!writeToHTML())
        {
            setError("Failed to generate report content!");
            return false;
        }
        
        return true;
    }
    
    bool ReportBuilder::generateHeader()
    {
        mContent = "<head> \n\
            <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"> \n\
            <title>分析报告</title> \n\
            </head>\n ";
        return true;
    }
    
    bool ReportBuilder::generateBody(const vector<string> exportedFiles)
    {
        mContent += "<body>\n<p><h1>分析报告</h1></p>\n";
        
        vector<string>::const_iterator iterator = exportedFiles.begin();
        while(iterator != exportedFiles.end())
        {
            string extraContent = "width=\"640\" height=\"480\"";
            
            if(has_suffix(*iterator,".html"))
            {
                mContent += "<iframe src=\""+*iterator+"\" > </iframe> <br/> <br/>\n";
            }
            else
               {
                   mContent += "<iframe src=\""+*iterator+"\" "+extraContent+"></iframe> <br/> <br/> \n";
               }
            ++iterator;
        }
        
        mContent += "</body>\n";
        return true;
    }
        
    bool ReportBuilder::writeToHTML()
    {
        mContent = "<!DOCTYPE html>\n <html>\n" + mContent + "</html>\n";
        
        FILE * fp = fopen(getFullPath(REPORT_FILE_NAME).c_str(),"w+");
        
        fprintf(fp,mContent.c_str());
        fclose(fp);
        
        return true;
    }
    
}//namespace DrRobot