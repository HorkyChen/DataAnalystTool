//
//  main.cpp
//  FilterTester
//
//  Created by Chen Hao on 8/13/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <iostream>
#include "Collection.h"
#include "FiveNumberFilter.h"
#include "TextOutput.h"

int main(int argc, const char * argv[])
{
    FiveNumberFilter myFilter("_data","Price","Make","_view01");
    myFilter.execute();
    DrRobot::Collection* result = myFilter.getData();
    result->dump();
    
    DrRobot::TextOutput textOutput;
    textOutput.plot(result);
}

