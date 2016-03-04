//
//  Data.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/20/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef DataAnalyst_Data_h
#define DataAnalyst_Data_h
#include <string>
#include "RefCounted.h"
#include "RefPtr.h"

using namespace std;

namespace DrRobot{
    
    class Data:public RefCounted<Data>
    {
    public:
        Data():name(""),type(-1){}
        ~Data(){cout<<endl<<"\t *Freed:"<<name<<endl;}
        Data(const Data& _d):name(_d.name),type(_d.type)
        {
            cout<<endl<<"create:"<<name<<endl;
        }
        Data(const string& _name, int _type):name(_name),type(_type){}
        string name;
        int type;
        
        friend ostream& operator<<(ostream &out, Data c) 
        {
            out<<c.name<<"|"<<c.type;
            return out;
        }
        
        friend bool operator==(const Data& a, const Data& b)
        {
            return a.name == b.name;
        }
        
        friend bool operator==(const Data& a, const string& b)
        {
            return a.name == b;
        }
    };
    
}

#endif
