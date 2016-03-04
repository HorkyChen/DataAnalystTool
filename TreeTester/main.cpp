//
//  main.cpp
//  TreeTester
//
//  Created by Chen Hao on 8/20/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#include "tree.hh"
#include "tree_util.hh"
#include "RefPtr.h"
#include "RefCounted.h"
#include <string>

using namespace std;
using namespace DrRobot;

void testTreeWithData()
{
	tree<RefPtr<Data>> tr;
    
    
    
	tr.insert(tr.begin(), adoptRef(new Data("A",0)));
	tree<RefPtr<Data>>::iterator i2 = tr.insert(tr.end(), adoptRef(new Data("F1",1)));
	tree<RefPtr<Data>>::iterator i3 = tr.insert(tr.end(), adoptRef(new Data("F2",1)));
	tr.append_child(i2, adoptRef(new Data("P1",2)));
	tr.append_child(i2, adoptRef(new Data("P2",2)));
	tree<RefPtr<Data>>::iterator i4 = tr.insert(tr.end(), adoptRef(new Data("F3",2)));
    
    tree<RefPtr<Data>>::iterator iter = find(tr.begin(), tr.end(), "F2");
    tr.append_child(iter, adoptRef(new Data("P1",2)));
    
    kptree::print_tree_bracketed(tr, std::cout);
    cout<<endl<<endl;
    
    //Test erasing
    tree<RefPtr<Data>>::iterator iter2 = find(tr.begin(), tr.end(), "F2");
    cout<<"F2 Pointer:"<<&(*iter2)<<endl;
    tr.erase(iter2);
    
    cout<<"After erasing F2."<<endl;
    kptree::print_tree_bracketed(tr, std::cout);
    
	std::cout << std::endl;	
}


int main(int, char **)
{
    testTreeWithData();
}

