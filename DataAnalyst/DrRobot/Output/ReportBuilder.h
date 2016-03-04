//
//  ReportBuilder.h
//  DataAnalyst
//
//  Created by Chen Hao on 9/10/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//
//  To generate HTML report involve all exported files.
//

#ifndef __DataAnalyst__ReportBuilder__
#define __DataAnalyst__ReportBuilder__

#include <string>
#include <vector>
using namespace std;

namespace DrRobot{
    
#define REPORT_FILE_NAME "Report.html"
    
    class ReportBuilder{
    public:
        bool generateReport(const vector<string> exportedFiles);
        static const char* getReportFileName(){return REPORT_FILE_NAME;};
    private:
        string mContent;
    private:
        bool generateHeader();
        bool generateBody(const vector<string> exportedFiles);
        bool writeToHTML();
    };
}//namespace DrRobot

#endif /* defined(__DataAnalyst__ReportBuilder__) */
