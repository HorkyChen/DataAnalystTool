//
//  DrRobotWrapper.m
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#import "DrRobotWrapper.h"
#include "DrRobot.h"

@implementation DrRobotWrapper

+(NSArray *)getFilters{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    NSMutableArray *result = [[NSMutableArray alloc] initWithCapacity:drRobot->getFilterCount()];
    
    [result addObject:@"None"];
    
    for(int i=0;i<drRobot->getFilterCount();i++){
        [result addObject:[NSString stringWithUTF8String:drRobot->getFilterName(i)]];
    }
    
    return result;
}

+(NSArray *)getPlotters{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    NSMutableArray *result = [[NSMutableArray alloc] initWithCapacity:drRobot->getPlotterCount()];
    
    [result addObject:@"None"];
    
    for(int i=0;i<drRobot->getPlotterCount();i++){
        [result addObject:[NSString stringWithUTF8String:drRobot->getPlotterName(i)]];
    }
    return result;
}

+(NSArray *)getSourceFields{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    const std::vector<string>& list = drRobot->getSourceFields();
    
    NSMutableArray *result = [[NSMutableArray alloc] init];
    
    [result addObject:@"None"];
                              
    for(std::vector<string>::const_iterator iter=list.begin();iter!=list.end();iter++)
    {
        [result addObject:[NSString stringWithUTF8String:(*iter).c_str()]];
    }
    return result;
}

+(NSArray *)getOutputFieldsOfElement:(NSString*)elementName{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    std::vector<string> list;
    drRobot->getOutputFieldsOfElement([elementName cStringUsingEncoding:NSASCIIStringEncoding],list);
    
    NSMutableArray *result = [[NSMutableArray alloc] init];
    
    [result addObject:@"All"];
    
    for(std::vector<string>::const_iterator iter=list.begin();iter!=list.end();iter++)
    {
        [result addObject:[NSString stringWithUTF8String:(*iter).c_str()]];
    }
    return result;
}

+(bool)run{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    return drRobot->run();
}

+(bool)generateReport{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    if(drRobot->generateReport()){
        [[NSWorkspace sharedWorkspace] openFile:
            [NSString stringWithUTF8String:drRobot->getReportFilePath().c_str()]];
        return true;
    }
    return false;
}

+(void)createNewElement:(NSString *)srcElementName elementName:(NSString*)newElementName elementType:(int)nElementType{
    
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    
    drRobot->createNewElement([srcElementName cStringUsingEncoding:NSASCIIStringEncoding],
                              [newElementName cStringUsingEncoding:NSASCIIStringEncoding],
                              nElementType);
}

+(bool)setElementParameter:(NSString*)targetElement parameter:(NSArray*)parameters {
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    
    vector<string> paramsVector;
    for(int i=0;i<[parameters count];i++){
        paramsVector.push_back([[parameters objectAtIndex:i] cStringUsingEncoding:NSASCIIStringEncoding]);
    }
    
    return drRobot->setElementParameter([targetElement cStringUsingEncoding:NSASCIIStringEncoding],paramsVector);
}

+(bool)setElementParameter:(NSString*)targetElement key:(NSString*)parameter value:(NSString*)strValue{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    return drRobot->setElementParameter(
                        [targetElement cStringUsingEncoding:NSASCIIStringEncoding]
                        ,[parameter cStringUsingEncoding:NSASCIIStringEncoding]
                        ,[strValue cStringUsingEncoding:NSASCIIStringEncoding]);
}

+(bool)addElementParameter:(NSString*)targetElement parameter:(NSArray*)parameters {
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    
    vector<string> paramsVector;
    for(int i=0;i<[parameters count];i++){
        paramsVector.push_back([[parameters objectAtIndex:i] cStringUsingEncoding:NSASCIIStringEncoding]);
    }
    
    return drRobot->addElementParameter([targetElement cStringUsingEncoding:NSASCIIStringEncoding],paramsVector);
}

+(bool)clearElements{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    return drRobot->clearElements();
}

+(void)resetElementToUnExecuted:(NSString*)elementName{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    drRobot->resetElementToUnExecuted([elementName cStringUsingEncoding:NSASCIIStringEncoding]);
}

+(NSString *)getLastErrorString{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    NSString *result = [NSString stringWithUTF8String:drRobot->getLastErrorString().c_str()];
    return result;
}

+(bool)serializeToFile:(NSString*)filename{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    return drRobot->serializeToFile([filename cStringUsingEncoding:NSASCIIStringEncoding]);
}

+(bool)deserializeFromFile:(NSString*)filename{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    return drRobot->deserializeFromFile([filename cStringUsingEncoding:NSASCIIStringEncoding]);
}

+(void)setWorkingPath:(NSString *)path{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    drRobot->setWorkingPath([path cStringUsingEncoding:NSASCIIStringEncoding]);
}

+(void)setPlotFilePath:(NSString *)path{
    DrRobot::DrRobot* drRobot = DrRobot::getDrRobot();
    drRobot->setPlotFilePath([path cStringUsingEncoding:NSASCIIStringEncoding]);
}
@end
