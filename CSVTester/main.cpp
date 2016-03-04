//
//  main.cpp
//  CSVTester
//
//  Created by Chen Hao on 8/11/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <iostream>
#include "CSVparser.hpp"
#include "Collection.h"

int main(int argc, char **argv)
{
    try
    {
        DrRobot::CSVParser file = DrRobot::CSVParser("./files/simple_spc.csv",DrRobot::eFILE);
        
        file.parseContent();
        
        //Print headers
        for(int j=0;j<file.columnCount();j++){
            std::cout << file.getHeaderElement(j) << "\t\t";
        }
        std::cout<<std::endl;
        
        for(int i=0;i<file.rowCount();i++) {
            for(int j=0;j<file.columnCount();j++){
                std::cout << file[i][j] << "\t\t";
            }
            std::cout<<std::endl;
        }
        
        DrRobot::Collection* output = file.getData();
        output->dump();
        
    }
    catch (DrRobot::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

