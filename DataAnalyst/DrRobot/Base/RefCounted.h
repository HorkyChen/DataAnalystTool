/*
 * Copyright (C) 2006, 2007, 2008, 2009, 2010 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */
//
//  RefCounted.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef DataAnalyst_RefCounted_h
#define DataAnalyst_RefCounted_h

#include "Assertions.h"

namespace DrRobot{

class RefCountedBase {
public:
    void ref()
    {
        ++m_refCount;
    }
    
    bool hasOneRef() const
    {
        return m_refCount == 1;
    }
    
    int refCount() const
    {
        return m_refCount;
    }
        
protected:
    RefCountedBase()
    : m_refCount(1)
    {
    }
    
    ~RefCountedBase()
    {
    }
    
    // Returns whether the pointer should be freed or not.
    bool derefBase()
    {
        ASSERT(m_refCount > 0);
        if (m_refCount == 1) {
            return true;
        }
        
        --m_refCount;
        return false;
    }
    
    
private:
    int m_refCount;
};


template<typename T> class RefCounted : public RefCountedBase {
private: 
    RefCounted(const RefCounted&);
    RefCounted& operator=(const RefCounted&);
public:
    void deref()
    {
        if (derefBase())
            delete static_cast<T*>(this);
    }
    
protected:
    RefCounted() { }
    ~RefCounted()
    {
    }
};

} 

using DrRobot::RefCounted;

#endif
