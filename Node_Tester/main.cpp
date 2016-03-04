//
//  main.cpp
//  Node_Tester
//
//  Created by Chen Hao on 6/21/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "Collection.h"

using namespace DrRobot;

void simpleTestCaseString()
{
    Node aNode("string_data",STRING);
    aNode.appendValue("0.3");
    aNode.appendValue("0.4");
    aNode.appendValue("0.5");
    aNode.appendValue("0.6");
    
    std::cout << " Var name is "<<aNode.name()<<std::endl;
    
    vector<string> *values = (vector<string> *)aNode.getValues();
    std::cout << "Value[0]"<<(*values)[0]<<std::endl;
    std::cout << "Value[2]"<<(*values)[2]<<std::endl;
    aNode.remove(1);
    std::cout << "Value[1]"<<(*values)[1]<<std::endl;
}

void simpleTestCaseFloat()
{
    Node aNode("data",NUMERIC);
    aNode.appendValue(0.3f);
    aNode.appendValue(0.4f);
    aNode.appendValue(0.5f);
    aNode.appendValue(0.6f);
    
    std::cout << " Var name is "<<aNode.name()<<std::endl;
    vector<float> *values = (vector<float> *)aNode.getValues();
    std::cout << "Value[0]"<<(*values)[0]<<std::endl;
    std::cout << "Value[2]"<<(*values)[2]<<std::endl;
    
    aNode.remove(1);
    
    std::cout << "Value[1]"<<(*values)[1]<<std::endl;
}

void simpleTestCaseInt()
{
    Node aNode("int_data",INTEGER);
    aNode.appendValue(3);
    aNode.appendValue(4);
    aNode.appendValue(5);
    aNode.appendValue(6);
    
    std::cout << " Var name is "<<aNode.name()<<std::endl;
    
    vector<int> *values = (vector<int> *)aNode.getValues();
    std::cout << "Value[0]"<<(*values)[0]<<std::endl;
    std::cout << "Value[2]"<<(*values)[2]<<std::endl;
    aNode.remove(1);
    std::cout << "Value[1]"<<(*values)[1]<<std::endl;
}

void simpleTestCollection()
{
    Collection collection;
    collection.appendField("name",STRING);
    collection.appendField("address",STRING);
    collection.appendField("age",INTEGER);
    char* values[3]={"HaHa","CHINA","25"};
    collection.addRow(values,3);
    
    collection.addRow(3, "PaPa","US","30");
    
    collection.dump();
}

int main(int argc, const char * argv[])
{
    simpleTestCaseFloat();
    simpleTestCaseInt();
    simpleTestCaseString();
    
    simpleTestCollection();
    return 0;
}
