//
//  DrRobotWrapper.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DrRobotWrapper : NSObject{
}
+(NSArray *)getFilters;
+(NSArray *)getPlotters;
+(NSArray *)getSourceFields;
+(NSArray *)getOutputFieldsOfElement:(NSString*)elementName;

+(bool)run;
+(bool)generateReport;

+(void)createNewElement:(NSString *)srcElementName elementName:(NSString*)newElementName elementType:(int)nElementType;
+(bool)setElementParameter:(NSString*)targetElement parameter:(NSArray*)parameters;
+(bool)setElementParameter:(NSString*)targetElement key:(NSString*)parameter value:(NSString*)strValue;
+(bool)addElementParameter:(NSString*)targetElement parameter:(NSArray*)parameters;
+(bool)clearElements;
+(void)resetElementToUnExecuted:(NSString*)elementName;
+(NSString *)getLastErrorString;
+(bool)serializeToFile:(NSString*)filename;
+(bool)deserializeFromFile:(NSString*)filename;

+(void)setWorkingPath:(NSString *)path;
+(void)setPlotFilePath:(NSString *)path;
@end
