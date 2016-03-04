//
//  Node.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 8/17/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "Node.h"
#include "Assertions.h"
#include <math.h>
#include <stdlib.h>

namespace DrRobot{
    
    void Node::createValues(){
        switch(mType){
            case INTEGER:
                mData.intValues = new vector<int>;
                break;
            case NUMERIC:
                mData.numValues = new vector<float>;
                break;
            case STRING:
                mData.stringValues = new vector<string>;
                break;
        }
    };
    
    void Node::freeValues(){
        switch(mType){
            case INTEGER:
                delete mData.intValues;
                break;
            case NUMERIC:
                delete mData.numValues;
                break;
            case STRING:
                delete mData.stringValues;
                break;
        }
        mData.stringValues = NULL;
    };
    
    void Node::copyAndConvertValues(const Node& node){
        switch(node.type()){
            case INTEGER:{
                    vector<int> *Values = (vector<int> *)(node.getValues());
                    vector<int>::iterator iter = Values->begin();
                    while(iter != Values->end()){
                        appendValue(*iter);
                        iter++;
                    }
                }
                break;
            case NUMERIC:{
                    vector<float> *Values = (vector<float> *)(node.getValues());
                    vector<float>::iterator iter = Values->begin();
                    while(iter != Values->end()){
                        appendValue(*iter);
                        iter++;
                    }
                }
                break;
            case STRING:{
                    vector<string> *Values = (vector<string> *)(node.getValues());
                    vector<string>::iterator iter = Values->begin();
                    while(iter != Values->end()){
                        appendValue(*iter);
                        iter++;
                    }
                }
                break;
        }
    }
        
    void Node::copyValues(const Node& node){
        ASSERT(node.type()==mType);
        
        switch(mType){
            case INTEGER:
                mData.intValues = new vector<int>(*(vector<int> *)node.getValues());
                break;
            case NUMERIC:
                mData.numValues = new vector<float>(*(vector<float> *)node.getValues());
                break;
            case STRING:
                mData.stringValues = new vector<string>(*(vector<string> *)node.getValues());
                break;
        }
    }
    
    bool Node::appendValue(int value){
        switch(mType)
        {
            case INTEGER:
                mData.intValues->push_back(value);
                break;
            case NUMERIC:
                mData.numValues->push_back(0.0+value);
                break;
            case STRING:
                char sBuffer[64] = {0};
                sprintf(sBuffer,"%d",value);
                mData.stringValues->push_back(sBuffer);
                break;
        }        
        return true;
    }
    
    bool Node::appendValue(float value){
        switch(mType)
        {
            case INTEGER:
                mData.intValues->push_back(floor(value));
                break;
            case NUMERIC:
                mData.numValues->push_back(value);
                break;
            case STRING:
                char sBuffer[64] = {0};
                sprintf(sBuffer,"%f",value);
                mData.stringValues->push_back(sBuffer);
                break;
        }
        
        return true;
    }
    
    bool Node::appendValue(const string value){
        switch(mType)
        {
            case INTEGER:
                mData.intValues->push_back(atoi(value.c_str()));
                break;
            case NUMERIC:
                mData.numValues->push_back(atof(value.c_str()));
                break;
            case STRING:
                mData.stringValues->push_back(value);
                break;
        }
        
        return false;
    }
    
    bool Node::remove(int start,int end){
        switch(mType){
            case INTEGER:
                return removeValuesFromVector(mData.intValues,start,end);
            case NUMERIC:
                return removeValuesFromVector(mData.numValues,start,end);
            case STRING:
                return removeValuesFromVector(mData.stringValues,start,end);
        }
        return false;
    }
    
    bool Node::clear(){
        switch(mType){
            case INTEGER:
                mData.intValues->clear();
                break;
            case NUMERIC:
                mData.numValues->clear();
                break;
            case STRING:
                mData.stringValues->clear();
                break;
            default:
                return false;
        }
        return true;
    }
    
    string Node::getValue(int index) const{
        char buffer [33];
        switch(mType){
            case INTEGER:
                sprintf(buffer,"%d",(*(mData.intValues))[index]);
                return string(buffer);
            case NUMERIC:
                sprintf(buffer,"%f",(*(mData.numValues))[index]);
                return string(buffer);
            case STRING:
                return (*(mData.stringValues))[index];
            default:
                return "";
        }
    }
    
    void * Node::getValues() const{
        switch(mType){
            case INTEGER:
                return (void*)mData.intValues;
            case NUMERIC:
                return (void*)mData.numValues;
            case STRING:
                return (void*)mData.stringValues;
            default:
                return NULL;
        }
    }
    
    int Node::addValue(const string value)
    {
        switch(mType){
            case INTEGER:
                appendValue(atoi(value.c_str()));
                break;
            case NUMERIC:
                appendValue((float)atof(value.c_str()));
                break;
            case STRING:
                appendValue(value);
                break;
            default:
                return -2;
        }
        return 0;
    }
    
    int Node::addValue(char *value)
    {
        switch(mType){
            case INTEGER:
                appendValue(atoi(value));
                break;
            case NUMERIC:
                appendValue((float)atof(value));
                break;
            case STRING:
                appendValue(string(value));
                break;
            default:
                return -2;
        }
        return 0;
    }
    
    unsigned long Node::size()const{
        switch(mType){
            case INTEGER:
                return mData.intValues->size();
            case NUMERIC:
                return mData.numValues->size();
            case STRING:
                return mData.stringValues->size();
            default:
                return 0;
        }
    }
    
    void Node::multiply(float x)
    {
        switch(mType){
            case INTEGER:
            {
                vector<int>* newData = new vector<int>;
                vector<int>* oldValues = mData.intValues;
                vectorMultiplyOperator(oldValues,newData,x);
                mData.intValues = newData;
                delete oldValues;
            }
                break;
            case NUMERIC:
            {
                vector<float>* newData = new vector<float>;
                vector<float>* oldValues = mData.numValues;
                vectorMultiplyOperator(oldValues,newData,x);
                mData.numValues = newData;
                delete oldValues;
            }
                break;
        }
    }
    
    void Node::plus(float x)
    {
        switch(mType){
            case INTEGER:
            {
                vector<int>* newData = new vector<int>;
                vector<int>* oldValues = mData.intValues;
                vectorPlusOperator(oldValues,newData,x);
                mData.intValues = newData;
                delete oldValues;
            }
                break;
            case NUMERIC:
            {
                vector<float>* newData = new vector<float>;
                vector<float>* oldValues = mData.numValues;
                vectorPlusOperator(oldValues,newData,x);
                mData.numValues = newData;
                delete oldValues;
            }
                break;
        }
    }
    
    void Node::dump() const
    {
        std::cout<<"Node, name:"<< mName <<std::endl;
        std::cout<<"Node, type:"<< mType <<std::endl;
        std::cout<<"Node, size:"<< size() <<std::endl;
        
        switch(mType){
            case INTEGER:
                printEachData(mData.intValues);
                break;
            case NUMERIC:
                printEachData(mData.numValues);
                break;
            case STRING:
                printEachData(mData.stringValues);
                break;
        }            
    }
    
    /*
     bool Node::removeValue(int node){
     if(mType == INTEGER){
     removeValueFromVector(mData.intValues, node);
     }
     return false;
     }
     
     bool Node::removeValue(float node){
     if(mType == NUMERIC){
     removeValueFromVector(mData.numValues, node);
     }
     return false;
     }
     
     bool Node::removeValue(string node){
     if(mType == STRING){
     removeValueFromVector(mData.stringValues, node);
     }
     return false;
     }
     */
    
} //end of namespace
