//
//  Collection.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 5/6/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "Collection.h"
#include <algorithm>
#include <stdarg.h>
#include "Assertions.h"
#include "ReportError.h"

namespace DrRobot{    
    bool Collection::appendField(string name, Node_Type type)
    {
        headers.push_back(name);
        Node node(name,type);
        fields.push_back(node);
        return true;
    }
    
    bool Collection::append(const Node& field)
    {
        headers.push_back(field.name());
        fields.push_back(field);
        return true;
    }
    
    long Collection::rowCount() const
    {
        if(length()>0)
        {
            return fields[0].size();
        }
        return 0;
    }
    
    bool Collection::deleteField(const string name)
    {
        long index = indexOf(name);
        if(index >= 0){
            removeValueFromVectorByIndex(&fields,index);
            removeValuesFromVector(&headers,index,index);
        }
        return true;
    }
    
    short Collection::getValueType(const string name)
    {
        long index = indexOf(name);
        
        if(index >= 0)
        {
            return fields[index].type();
        }
        
        return UNKNOWN;
    }
    
    Node* Collection::getField(const string name)
    {
        long index = indexOf(name);
        if(index >= 0){
            return &fields[index];
        }
        
        return NULL;
    }
    
    Node* Collection::getField(long index)
    {
        if(index<0 || index>=length()){
            return NULL;
        }
        
        return &fields[index];
    }
    
    const string Collection::getFieldName(unsigned int index)
    {
        if(index<headers.size())
        {
            return headers[index];
        }
        return NULL;
    }
    
    Collection* Collection::getRow(unsigned short index)
    {
        return NULL;
    }
    
    Collection* Collection::getRows(int start,int end)
    {
        return NULL;
    }
    
    bool Collection::hasField(const string name)
    {
        return (indexOf(name) != -1);
    }
    
    long Collection::indexOf(const string name) const
    {
        if(name.length()==0)
            return -1;
        
        std::vector<string>::const_iterator it = find (headers.begin(), headers.end(), name);
        if(it != headers.end())
        {
            return it-headers.begin();
        }
        else
        {
            return -1;
        }
    }
    
    int Collection::addRow(char* items[], int count)
    {
        if(!items)
        {
            return -1;
        }
        
        for(int i=0;i<count;i++)
        {
            fields[i].addValue(items[i]);
        }
        
        return 0;
    }
    
    int Collection::addRow(int count, ...)
    {
        va_list arg_ptr;
        
        va_start(arg_ptr,count);
        
        char *value = NULL;
        int index = 0;
        do
        {
            value = va_arg(arg_ptr,char *);
            fields[index].addValue(value);
            ++index;
        } while(index<count);
        
        return 0;
    }
    
    int Collection::addRow(const vector<string>& values)
    {
        vector<string>::const_iterator iterator = values.begin();
        int index = 0;
        while(iterator != values.end())
        {
            fields[index].addValue(*iterator);
            ++iterator;
            ++index;
        }
        return 0;
    }
    
    void Collection::clear()
    {
        fields.clear();
        headers.clear();
    }
    
    void Collection::multiply(float x)
    {
        for(std::vector<Node>::iterator i=fields.begin();i!=fields.end();++i)
        {
            (*i).multiply(x);
        }
    }
    
    void Collection::divide(float x)
    {
        for(std::vector<Node>::iterator i=fields.begin();i!=fields.end();++i)
        {
            (*i).divide(x);
        }
    }
    
    void Collection::plus(float x)
    {
        for(std::vector<Node>::iterator i=fields.begin();i!=fields.end();++i)
        {
            (*i).plus(x);
        }
    }
    
    void Collection::minus(float x)
    {
        for(std::vector<Node>::iterator i=fields.begin();i!=fields.end();++i)
        {
            (*i).minus(x);
        }
    }
    
    void Collection::dump() const
    {
        std::cout<<"Number of fields:"<<length()<<std::endl;
        for(std::vector<Node>::const_iterator i=fields.begin();i!=fields.end();++i)
        {
            (*i).dump();
        }
    }
    
    bool Collection::writeToFile(const string filename) const
    {
        ASSERT(filename.length()>0);
        ASSERT(rowCount()>0);
        
        FILE*   tmpfd = fopen(filename.c_str(),"w+");
        if(!tmpfd){
            setError("Failed to open file while saving the collection.");
            return false;
        }
        
        string strLine;
        for(int i=0;i<length();++i)
        {
            strLine += headers[i]+" ";
        }
        fprintf(tmpfd,"%s\n",strLine.c_str());
        
        for(int i=0;i<rowCount();++i)
        {
            strLine = "";
            for(int j=0;j<length();++j){
                strLine += fields[j].getValue(i) + " ";
            }
            fprintf(tmpfd,"%s\n",strLine.c_str());
        }
        
        fclose(tmpfd);
        return true;
    }
}
