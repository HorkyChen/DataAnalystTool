//
//  BaseUtilities.cpp
//  DataAnalyst
//
//  Created by Chen Hao on 9/10/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "BaseUtilities.h"

namespace DrRobot{
    
    bool has_suffix(const std::string &str, const std::string &suffix)
    {
        return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
    
} //namespace DrRobot