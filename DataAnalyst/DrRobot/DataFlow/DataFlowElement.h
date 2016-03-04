//
//  DataFlowElement.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/19/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DataFlow__
#define __DataAnalyst__DataFlow__

#include <string>
#include <algorithm>
#include <zenxml/xml.h>
#include "Collection.h"
#include "RefCounted.h"

#if defined(__DARWIN__) || defined(__APPLE__)
#include <ext/hash_map>
using namespace __gnu_cxx;
#elif defined(__GNUC__)
#include <ext/hash_map>
using namespace __gnu_cxx;
namespace __gnu_cxx {
    template<>
    struct hash<std::string>
    {
        hash<char*> h;
        size_t operator()(const std::string &s) const
        {
            return h(s.c_str());
        };
    };
}
#else
#include <hash_map>
using namespace std;
#endif

namespace DrRobot{
    
    class DataFlowElement:public RefCounted<DataFlowElement>
    {
    private:
        DataFlowElement(const DataFlowElement& _d){}
    public:
        enum Element_Type{ELEMENT_UNKNOWN=-1,ELEMENT_SOURCE=0,ELEMENT_FILTER,ELEMENT_PLOTTER};
    public:
        DataFlowElement()
        :mName("")
        ,mExecuted(false)
        ,mType(ELEMENT_UNKNOWN)
        ,mTargetHandle(NULL)
        ,mSuccessed(true)
        ,mSourceElement(NULL)
        {
        }
        
        DataFlowElement(const string& _name, int _type)
        :mName(_name)
        ,mType(_type)
        ,mExecuted(false)
        ,mTargetHandle(NULL)
        ,mSourceElement(NULL)
        ,mSuccessed(true)
        {
        }
        
        ~DataFlowElement()
        {
            reset();
        }
        
        friend ostream& operator<<(ostream &out, DataFlowElement& c) 
        {
            out<<c.name()<<"|"<<c.type();
            return out;
        }
        
        friend bool operator==(const DataFlowElement& a, const DataFlowElement& b)
        {
            return a.name() == b.name();
        }
        
        friend bool operator==(const DataFlowElement& a, const string& b)
        {
            return a.name() == b;
        }
        
        bool executed(){return mExecuted;};
        void resetToUnexecuted(){ mExecuted = false; mSuccessed=true;};
        void * targetHandle(){return mTargetHandle;};
        
        virtual bool run();
        virtual bool reset();
        virtual bool exportTo();
        virtual string getTargetFileName(){return "";};
        
        bool successed() {return mSuccessed;};
        
        Collection* getResult(const vector<string>& fields);
        virtual const char* getDBTableName();
        
        void setParameters(const vector<string>& values);
        void addParameters(const vector<string>& values);
        
        void setParameter(const string key, const string value);
        const string parameter(const string key);
        bool hasParameter(const string key){return mParameters.find(key) != mParameters.end();};
        
        void setSourceElement(DataFlowElement* element){mSourceElement = element;};
        
        const string& name()const{return mName;}
        int type()const{return mType;}
        
        virtual void getColumns(vector<string>& list){};
        virtual bool serialize(zen::XmlOut& outXML, const string name);
        bool deserialize(zen::XmlIn& inXML);
    protected:
        virtual void* getTargetHandle();
        virtual void initAvailableParameters(){};
        
        bool mExecuted;
        bool mSuccessed;
        string mTargetTable;
        
        void * mTargetHandle;
        hash_map<string,string> mParameters;
        vector<string> mAvailableParameters;
        
        DataFlowElement* mSourceElement;
        
        string mName;
        int mType;
    private:
        void addParameterImpl(const vector<string>& values);
    };
    
}
#endif /* defined(__DataAnalyst__DataFlow__) */
