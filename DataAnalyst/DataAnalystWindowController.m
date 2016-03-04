//
//  DataAnalystWindowController.m
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#import "DataAnalystWindowController.h"
#import "DrRobotWrapper.h"

@interface DataAnalystWindowController ()

@end

@implementation DataAnalystWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)awakeFromNib
{
    [sourceFile setStringValue:@""];
    
    [filterButton1 removeAllItems];
    [filterButton2 removeAllItems];
    [plotterButton1 removeAllItems];
    [plotterButton2 removeAllItems];
    [plotterButton3 removeAllItems];
    
    [fieldButton1 removeAllItems];
    [groupFieldButton1 removeAllItems];
    [fieldButton3 removeAllItems];
    [groupFieldButton3 removeAllItems];
    [fieldButton2 removeAllItems];
    [fieldButton4 removeAllItems];
    
    [filterButton1 addItemsWithTitles:[DrRobotWrapper getFilters]];
    [filterButton2 addItemsWithTitles:[DrRobotWrapper getFilters]];
    
    [plotterButton1 addItemsWithTitles:[DrRobotWrapper getPlotters]];
    [plotterButton2 addItemsWithTitles:[DrRobotWrapper getPlotters]];
    [plotterButton3 addItemsWithTitles:[DrRobotWrapper getPlotters]];
    
    [fieldButton5 removeAllItems];
    [labelField1 removeAllItems];
    
    [backgroundImage setImage:[NSImage imageNamed: @"Background.png"]];
    
    //set Working path
    NSBundle * bundle = [NSBundle mainBundle];    
    [DrRobotWrapper setWorkingPath:[[bundle bundlePath] stringByDeletingLastPathComponent]];
    [DrRobotWrapper setPlotFilePath:[bundle resourcePath]];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (IBAction) buttonImportClicked:(id)sender{
    NSArray * fileTypes = [NSArray arrayWithObjects: @"csv",@"txt",nil];
	NSOpenPanel * oPanel = [NSOpenPanel openPanel];
	
	[oPanel setAllowsMultipleSelection: NO];
	[oPanel setTitle: @"Choose a source file"];
	
	if([oPanel runModalForTypes:fileTypes] == NSOKButton){
        [fieldButton1 removeAllItems];
        [groupFieldButton1 removeAllItems];
        [fieldButton3 removeAllItems];
        [groupFieldButton3 removeAllItems];
        [fieldButton2 removeAllItems];
        [fieldButton4 removeAllItems];
        [labelField1 removeAllItems];
        [fieldButton5 removeAllItems];
        
        NSLog(@"%@",[oPanel filename]);
        mSourceFile = [[NSString alloc] initWithString: [oPanel filename]];
        [sourceFile setStringValue:[mSourceFile lastPathComponent]];
        
        /*Rebuild the total element tree*/
        [DrRobotWrapper clearElements];
        
        [DrRobotWrapper createNewElement:@"" elementName:@"Source_1" elementType:0];
        [DrRobotWrapper setElementParameter:@"Source_1" 
                                  parameter:[[NSArray alloc] initWithObjects:mSourceFile, nil]];
        
        switch([sourceSeperatorButton indexOfItem:[sourceSeperatorButton selectedItem]]){
            case 0:
                [DrRobotWrapper addElementParameter:@"Source_1" 
                                          parameter:[[NSArray alloc] initWithObjects:@"\t", nil]];
                break;
            case 1:
                [DrRobotWrapper addElementParameter:@"Source_1" 
                                          parameter:[[NSArray alloc] initWithObjects:@",", nil]];
                break;
            case 2:
            default:
                [DrRobotWrapper addElementParameter:@"Source_1" 
                                          parameter:[[NSArray alloc] initWithObjects:@" ", nil]];
                break;
        }
        
        NSArray* sourceFields = [DrRobotWrapper getSourceFields];

        [fieldButton1 removeAllItems];
        [groupFieldButton1 removeAllItems];
        [fieldButton3 removeAllItems];
        [groupFieldButton3 removeAllItems];
        
        [fieldButton1 addItemsWithTitles:sourceFields];
        [groupFieldButton1 addItemsWithTitles:sourceFields];
        [fieldButton3 addItemsWithTitles:sourceFields];
        [groupFieldButton3 addItemsWithTitles:sourceFields];
        [fieldButton5 addItemsWithTitles:sourceFields];
        [labelField1 addItemsWithTitles:sourceFields];
    }
}

- (IBAction) filterButton1Selected:(id)sender{
    if([filterButton1 indexOfItem:[filterButton1 selectedItem]]>0){
        [DrRobotWrapper createNewElement:@"Source_1" elementName:@"Filter_1" elementType:1];
        [DrRobotWrapper setElementParameter:@"Filter_1" 
                                  parameter:[[NSArray alloc] initWithObjects:[filterButton1 titleOfSelectedItem], nil]];
        
        [fieldButton2 removeAllItems];
        [fieldButton2 addItemsWithTitles:[DrRobotWrapper getOutputFieldsOfElement:@"Filter_1"]];
    }
}

- (IBAction) filterButton2Selected:(id)sender{
    if([filterButton2 indexOfItem:[filterButton2 selectedItem]]>0){
        [DrRobotWrapper createNewElement:@"Source_1" elementName:@"Filter_2" elementType:1];
        
        [DrRobotWrapper setElementParameter:@"Filter_2" 
                                  parameter:[[NSArray alloc] initWithObjects:[filterButton2 titleOfSelectedItem], nil]];
        
        [fieldButton4 removeAllItems];
        [fieldButton4 addItemsWithTitles:[DrRobotWrapper getOutputFieldsOfElement:@"Filter_2"]];
    }
}

- (IBAction) buttonRunClicked:(id)sender{
    if(![self createDataFlowElements])
        return;
    
    if(![DrRobotWrapper run]){
        NSRunAlertPanel( @"Error", 
                        [DrRobotWrapper getLastErrorString], 
                        @"OK", 
                        nil, 
                        nil
                        );
    }
    else {
        NSRunAlertPanel( @"Success", 
                        @"Successed to run the analysis!", 
                        @"OK", 
                        nil, 
                        nil
                        );
    }
}


- (IBAction) buttonExportClicked:(id)sender
{
    if(![self createDataFlowElements])
        return;
    
    if(![DrRobotWrapper generateReport]){
        NSRunAlertPanel( @"Error", 
                        [DrRobotWrapper getLastErrorString], 
                        @"OK", 
                        nil, 
                        nil
                        );
    }
}

- (bool) createDataFlowElements 
{
    if(!mSourceFile)
    {
        NSRunAlertPanel( @"Error", 
                        @"Not specify Source element.", 
                        @"OK", 
                        nil, 
                        nil);
        return false;
    }
    
    if([filterButton1 indexOfItem:[filterButton1 selectedItem]]>0){
        NSString * field = [[NSString alloc] init];
        NSString * grpField = [[NSString alloc] init];
        if([fieldButton1 indexOfItem:[fieldButton1 selectedItem]]>0)
        {
            field = [fieldButton1 titleOfSelectedItem];
        }
        else
        {
            return false;
        }
        
        if([groupFieldButton1 indexOfItem:[groupFieldButton1 selectedItem]]>0)
        {
            grpField = [groupFieldButton1 titleOfSelectedItem];
        }
        
        [DrRobotWrapper setElementParameter:@"Filter_1" 
                                  parameter:[[NSArray alloc] initWithObjects:[filterButton1 titleOfSelectedItem],field,grpField, nil]];
    }
    
    if([filterButton2 indexOfItem:[filterButton2 selectedItem]]>0){
        NSString * field = [[NSString alloc] init];
        NSString * grpField = [[NSString alloc] init];
        if([fieldButton3 indexOfItem:[fieldButton3 selectedItem]]>0)
        {
            field = [fieldButton3 titleOfSelectedItem];
        }
        else{
            return false;
        }
        
        if([groupFieldButton3 indexOfItem:[groupFieldButton3 selectedItem]]>0)
        {
            grpField = [groupFieldButton3 titleOfSelectedItem];
        }
        
        [DrRobotWrapper setElementParameter:@"Filter_2" 
                                  parameter:[[NSArray alloc] initWithObjects:[filterButton2 titleOfSelectedItem],field,grpField, nil]];
    }
    
    if([plotterButton1 indexOfItem:[plotterButton1 selectedItem]]>0){
        [DrRobotWrapper resetElementToUnExecuted:@"Filter_1"];
        
        [DrRobotWrapper createNewElement:@"Filter_1" elementName:@"Plotter_1" elementType:2];
        [DrRobotWrapper setElementParameter:@"Plotter_1" 
                                  parameter:[[NSArray alloc] initWithObjects:[plotterButton1 titleOfSelectedItem], nil]];
        if([fieldButton2 indexOfItem:[fieldButton2 selectedItem]]>0)
        {
            [DrRobotWrapper addElementParameter:@"Plotter_1" 
                                      parameter:[[NSArray alloc] initWithObjects:[fieldButton2 titleOfSelectedItem],@"",[fieldButton2 titleOfSelectedItem], nil]];
        }
    }
    
    if([plotterButton2 indexOfItem:[plotterButton2 selectedItem]]>0){
        [DrRobotWrapper resetElementToUnExecuted:@"Filter_2"];
        
        [DrRobotWrapper createNewElement:@"Filter_2" elementName:@"Plotter_2" elementType:2];
        [DrRobotWrapper setElementParameter:@"Plotter_2" 
                                  parameter:[[NSArray alloc] initWithObjects:[plotterButton2 titleOfSelectedItem], nil]];
        if([fieldButton4 indexOfItem:[fieldButton4 selectedItem]]>0)
        {
            [DrRobotWrapper addElementParameter:@"Plotter_2" 
                                      parameter:[[NSArray alloc] initWithObjects:[fieldButton4 titleOfSelectedItem],
                                          @"",
                                          [fieldButton4 titleOfSelectedItem], nil]];
        }
    }
    
    if([plotterButton3 indexOfItem:[plotterButton3 selectedItem]]>0){
        
        [DrRobotWrapper createNewElement:@"Source_1" elementName:@"Plotter_3" elementType:2];
        [DrRobotWrapper setElementParameter:@"Plotter_3" 
                                  parameter:[[NSArray alloc] initWithObjects:[plotterButton3 titleOfSelectedItem],@"", nil]];
        
        if([labelField1 indexOfItem:[labelField1 selectedItem]]>0)
        {
            [DrRobotWrapper setElementParameter:@"Plotter_3" 
                                      key:@"xticlabelfield"
                                          value:[labelField1 titleOfSelectedItem]];
        }
        
        if([fieldButton5 indexOfItem:[fieldButton5 selectedItem]]>0)
        {
            [DrRobotWrapper setElementParameter:@"Plotter_3" 
                                      key:@"targetfield1"
                                          value:[fieldButton5 titleOfSelectedItem]];
        }
        else //draw all columns here
        {
            for(int i=1;i<[fieldButton5 numberOfItems];i++)
                [DrRobotWrapper setElementParameter:@"Plotter_3" 
                                                key:[NSString stringWithFormat:@"targetfield%d",i]
                                              value:[fieldButton5 itemTitleAtIndex:i]];
        }
        
    }
    return true;
}

- (IBAction) buttonSaveClicked:(id)sender
{
    NSArray * fileTypes = [NSArray arrayWithObjects: @"cln",nil];
	NSSavePanel * oPanel = [NSSavePanel savePanel];
	
	[oPanel setTitle: @"Choose a exporting file"];
	[oPanel setAllowedFileTypes:fileTypes];
	if([oPanel runModal] == NSOKButton)
    {
        if(![self createDataFlowElements])
            return;
        
        if([DrRobotWrapper serializeToFile:[oPanel filename]])
        {
            NSRunAlertPanel( @"Success", 
                            @"Successed to export to a file.", 
                            @"OK", 
                            nil, 
                            nil
                            );
        }
        else
        {
            NSRunAlertPanel( @"Error", 
                            [DrRobotWrapper getLastErrorString], 
                            @"OK", 
                            nil, 
                            nil
                            );
        }
    }
}

- (IBAction) buttonLoadClicked:(id)sender
{
    NSArray * fileTypes = [NSArray arrayWithObjects: @"cln",nil];
	NSOpenPanel * oPanel = [NSOpenPanel openPanel];
	
	[oPanel setAllowsMultipleSelection: NO];
	[oPanel setTitle: @"Choose a collection file"];
	
	if([oPanel runModalForTypes:fileTypes] == NSOKButton){
        if([DrRobotWrapper deserializeFromFile:[oPanel filename]])
        {
            if(![DrRobotWrapper run]){
                NSRunAlertPanel( @"Error", 
                                [DrRobotWrapper getLastErrorString], 
                                @"OK", 
                                nil, 
                                nil
                                );
            }
        }
    }
}
@end
