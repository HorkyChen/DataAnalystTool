//
//  main.cpp
//  Node_Tester
//  PlotTester
//
//  Created by Chen Hao on 6/21/14.
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "Collection.h"
#include "GNUPlotter.h"

using namespace DrRobot;

int main(int argc, const char * argv[])
{
    Collection collection;
    collection.appendField("count",INTEGER);
    collection.addRow(1, "1005");
    collection.addRow(1, "982");
    collection.addRow(1, "1025");
    collection.addRow(1, "861");
    collection.addRow(1, "940");
    collection.addRow(1, "1078");
    collection.addRow(1, "1506");
    
    collection.dump();
    
    GNUPlotter plot;
    plot.plot(&collection);
    
    Collection collection2;
    collection2.appendField("size",INTEGER);
    collection2.appendField("rate",NUMERIC);
    collection2.addRow(2, "1","3.5");
    collection2.addRow(2, "9","7.5");
    collection2.addRow(2, "5","5.79");
    collection2.addRow(2, "3","1.2");
    collection2.addRow(2, "2","8.5");
    
    GNUPlotter plot2("","lines");
    plot2.plot(&collection2);
    
    Collection collection3;
    collection3.appendField("size2",NUMERIC);
    collection3.addRow(1, "6.005");
    collection3.addRow(1, "7.82");
    collection3.addRow(1, "3.025");
    collection3.addRow(1, "5.861");
    collection3.addRow(1, "3.940");
    
    GNUPlotter plot3("","boxes",plot2);
    plot3.plot(&collection3);
    plot2.plot(&collection3);
    
    collection3.multiply(100);
    plot.plot(&collection3);
    
    int x;
    std::cin>>x;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

