//
//  TextOutput.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/15/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "TextOutput.h"
#include <stdio.h>
#include <string>
#include "ReportError.h"

using namespace std;

extern const std::string getFullPath(const char *path);

namespace DrRobot{
    bool TextOutput::generateTextFile(Collection * collection,const string xticLabelColumn, const string fileName)
    {
        if(!collection){
            setError("No valid data for plotting.");
            return false;
        }
        
        FILE*   tmpfd = fopen(getFullPath(fileName.c_str()).c_str(),"w+");
        
        fprintf(tmpfd,"<!DOCTYPE html> \
                <html>  \
                <head>  \
                <style> \
                #customers {    \
                width: 100%%; \
                border-collapse: collapse; \
                }\
                #customers td, #customers th { \
                font-size: 1em; \
                border: 1px solid #98bf21; \
                padding: 3px 7px 2px 7px; \
                } \
                #customers th { \
                font-size: 1.1em;\
                text-align: left;\
                padding-top: 5px;\
                padding-bottom: 4px;\
                background-color: #A7C942;\
                color: #ffffff;\
                }\
                #customers tr.alt td { \
                color: #000000; \
                background-color: #EAF2D3;\
                }\
                </style>\
                </head>\
                <body>\
                <table id=\"customers\">");
        
        fprintf(tmpfd,"<tr>");
        for(int i=0;i<collection->length();++i)
        {
            fprintf(tmpfd,"<th>%s</th>\n",collection->getFieldName(i).c_str());
        }
        fprintf(tmpfd,"</tr>\n");
        
        for(int i=0;i<collection->rowCount();++i)
        {
            if(i%2==0){
                fprintf(tmpfd,"<tr>");
            }
            else
            {
                fprintf(tmpfd,"<tr class=\"alt\">\n");
            }
            
            for(int j=0;j<collection->length();++j){
                fprintf(tmpfd,"<td>%s</td>\n",collection->getField(j)->getValue(i).c_str());
            }
            fprintf(tmpfd,"</tr>\n");
        }
        
        fprintf(tmpfd,"</table></body></html>");
        
        fclose(tmpfd);
        return true;
    }
    
    bool TextOutput::plot(Collection * collection, const string& xticLabelColumn)
    {
        return generateTextFile(collection, xticLabelColumn, "./TextOutput.html");
    }
    
    bool TextOutput::exportToFile(Collection * collection, const string& xticLabelColumn, const string& fileName) 
    {
        return generateTextFile(collection, xticLabelColumn, fileName);
    }
    
}