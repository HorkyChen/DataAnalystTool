//
//  main.cpp
//  ExportingTester
//
//  Created by Chen Hao on 9/12/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <iostream>
#include <zenxml/xml.h>
#include "DataFlowSourceElement.h"

using namespace std;

void testWriting()
{
    DrRobot::DataFlowSourceElement srcElement;
    zen::XmlDoc doc; 
    zen::XmlOut out(doc); 
    out["Element0"]["name"]("Source1"); 
    out["Element0"]["type"]("source"); 
    out["Element0"]["parameters"]["filepath"]("/Volumes");
    out["Element0"]["parameters"]["seperator"](","); 
    try
    {
        zen::save(doc, "file.xml"); //throw zen::XmlFileError
    }
    catch (const zen::XmlFileError& e) { /* handle error */ }
}

void testParsering()
{
    size_t a = 0;
    double b = 0.0;
    int    c = 0;
    
    zen::XmlDoc doc; //empty XML document
    try
    {
        doc = zen::load("file.xml"); //throw XmlFileError, XmlParsingError
    }
    catch (const zen::XmlError& e) { /* handle error */ }
    zen::XmlIn in(doc); //the simplest way to read the document is to use a data input proxy
    in["elem1"](a); //
    in["elem2"](b); //map XML elements into user data
    in["elem3"](c); //
    //check for mapping errors, i.e. missing elements or conversion errors: you may consider these as warnings only
    if (in.errorsOccured())
    {
        std::vector<std::wstring> failedElements = in.getErrorsAs<std::wstring>();
        /* generate error message showing the XML element names that failed to convert */
    }
}

int main(int argc, const char * argv[])
{
    testWriting();
    
   // testParsering();
    
    return 0;
}

