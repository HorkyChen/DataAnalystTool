//
//  Collection.h
//  DataAnalyst
//
//  Created by Chen Hao on 5/6/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__Collection__
#define __DataAnalyst__Collection__

#include "Node.h"
#include <vector>

using namespace std;

namespace DrRobot{

class Collection{
private:
    std::vector<Node> fields;
    std::vector<string> headers;
    std::string mName;
public:
    bool appendField(string name, Node_Type type);
    bool append(const Node& field);
    
    bool deleteField(const string name);
    
    short getValueType(const string name);
    
    Node* getField(const string name);
    Node* getField(long index);
    const string getFieldName(unsigned int index);
    
    Collection* getRow(unsigned short index);
    Collection* getRows(int start,int end);
    
    int addRow(char* items[], int count);
    int addRow(int count, ...);
    int addRow(const vector<string>& values);
    
    bool hasField(const string name);
    long indexOf(const string name) const;
    
    long length()const{return headers.size();};
    long columnCount()const{ return length();};
    long rowCount()const;
    
    void clear();
    
    void setName(const string& name){ mName = name; };
    
    //Mathmatic operators
    void multiply(float x);
    void divide(float x);
    void plus(float x);
    void minus(float x);

    void dump() const;
    bool writeToFile(const string filename) const;
};

}
#endif /* defined(__DataAnalyst__Collection__) */
