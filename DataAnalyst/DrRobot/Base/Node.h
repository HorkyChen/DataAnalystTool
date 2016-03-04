//
//  Node.h
//  DataAnalyst
//
//  Created by Chen Hao on 5/5/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__Node__
#define __DataAnalyst__Node__

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

namespace DrRobot{

    template <typename T> void clearVector(vector<T>* targetVector)
    {
        targetVector->clear();
    }
    
    /*
     template <typename T>   bool removeValueFromVector(vector<T>* targetVector, T value)
     {
     typedef typename vector<T>::iterator iterator;
     iterator first=targetVector->begin(), last=targetVector->end();
     iterator foundNode = find(first,last,value);
     
     if(foundNode!=last){
     targetVector->erase(foundNode);
     return true;
     }        
     return false;
     } */
    
    template<typename T> void printEachData(vector<T>* targetVector)
    {
        typedef typename vector<T>::const_iterator iterator;
        int maxCount = 20;
        for(iterator i= targetVector->begin(); i != targetVector->end()&&maxCount>0; ++i)
        {
            std::cout<<"\t"<<*i<<std::endl;
            --maxCount;
        }
    }
    
    template<typename T> void vectorMultiplyOperator(vector<T>* sourceVector,vector<T>* targetVector,float x)
    {
        typedef typename vector<T>::const_iterator iterator;
        for(iterator i= sourceVector->begin(); i != sourceVector->end(); ++i)
        {
            targetVector->push_back(*i * x);
        }
    }
    
    template<typename T> void vectorPlusOperator(vector<T>* sourceVector,vector<T>* targetVector,float x)
    {
        typedef typename vector<T>::const_iterator iterator;
        for(iterator i= sourceVector->begin(); i != sourceVector->end(); ++i)
        {
            targetVector->push_back(*i + x);
        }
    }
    
    template<typename T> bool removeValueFromVectorByIndex(vector<T>* targetVector, long index)
    {
        return removeValuesFromVector(targetVector,index,index);
    }
    
    template<typename T> bool removeValuesFromVector(vector<T>* targetVector, long begin, long end)
    {
        typedef typename vector<T>::iterator iterator;
        
        iterator it1,it2;
        it1 = it2 = targetVector->begin();
        
        if(begin<0 || end==targetVector->size()){
            return false;
        }
        
        advance(it1,begin);
        advance(it2,end+1);
        
        targetVector->erase(it1,it2);
        
        return true;
    }
    
    enum Node_Type{UNKNOWN=-1,NUMERIC=0,INTEGER,STRING};
    
    class Node{
    public:
        static Node& convertNodeType(const Node& orgNode, Node_Type newType)
        {
            Node* newNode = new Node(orgNode.name(),newType);
            newNode->copyAndConvertValues(orgNode);
            return *newNode;
        }

        static Node* convertNodeType(const Node* orgNode, Node_Type newType)
        {
            Node* newNode = new Node(orgNode->name(),newType);
            newNode->copyAndConvertValues(*orgNode);
            return newNode;
        }
        
    private:
        union {
            vector<int> * intValues;
            vector<float> * numValues;
            vector<string> * stringValues;
        } mData;
        short mType;
        string mName;
    private:
        void createValues();
        void freeValues();
        void copyValues(const Node& node);
        void copyAndConvertValues(const Node& node);
    private:
        Node(){}
    public:   
        Node(string name, Node_Type type)
            :mType(type)
            ,mName(name)
        {
            createValues();
        }
        
        Node(const char * name, Node_Type type)
            :mType(type)
            ,mName(name)
        {
            createValues();
        }
        
        Node(const Node& node)
            :mType(node.type())
            ,mName(node.name())
        {
            createValues();
            
            copyValues(node);
        }
        
        ~Node(){
            clear();
            freeValues();
        }
        
        short type()const{return mType;};
        string name() const{ return mName;};
        bool appendValue(int node);        
        bool appendValue(float node);
        bool appendValue(const string node);
        
        /*
         bool removeValue(int node);
         bool removeValue(float node);         
         bool removeValue(string node);
         */
        
        bool remove(int index){
            return remove(index,index);
        }
        
        bool remove(int start,int end);
        bool clear();
        
        string getValue(int index)const;
        void * getValues() const;        
        int addValue(const string value);
        int addValue(char *value);
        unsigned long size()const;
        
        //Mathmatic operators
        void multiply(float x);
        void divide(float x){ multiply(1/x); }
        void plus(float x);
        void minus(float x) {plus(-1*x);};
        
        void dump() const;
        
        friend class Node;
    };
}
#endif /* defined(__DataAnalyst__Node__) */
