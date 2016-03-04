//
//  ReportError.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/29/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__ReportError__
#define __DataAnalyst__ReportError__

#include <string>
namespace DrRobot{
class ReportEorr{
public:
    void setError(const char *message){mErrorString = message;}
    const std::string getLastError(){return mErrorString;}
    void clearError(){mErrorString="";};
private:
    std::string mErrorString;
};

extern void setError(const char * message);
extern const std::string getLastError();
extern void clearError();

}//end of namespace

#endif /* defined(__DataAnalyst__ReportError__) */
