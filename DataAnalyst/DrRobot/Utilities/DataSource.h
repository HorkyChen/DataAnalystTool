//
//  DataSource.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/11/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef __DataAnalyst__DataSource__
#define __DataAnalyst__DataSource__
#include "BaseConfig.h"
#ifdef USE_OWN_DATA_BACKEND
#include <iostream>
#include "Collection.h"

namespace DrRobot{
class DataSource
{
public:
    Collection* getData(){return &mCollection;}
protected:
    Collection mCollection;
};
}
#endif
#endif /* defined(__DataAnalyst__DataSource__) */
