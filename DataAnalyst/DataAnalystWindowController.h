//
//  DataAnalystWindowController.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/18/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DataAnalystWindowController : NSWindowController{
    NSString* mSourceFile;
    
    IBOutlet NSTextField * sourceFile;
    
    IBOutlet NSPopUpButton *	filterButton1;
    IBOutlet NSPopUpButton *	filterButton2;
    IBOutlet NSPopUpButton *	plotterButton1;
    IBOutlet NSPopUpButton *	plotterButton2;
    
    IBOutlet NSPopUpButton *	fieldButton1;
    IBOutlet NSPopUpButton *	groupFieldButton1;
    IBOutlet NSPopUpButton *	fieldButton2;
    
    IBOutlet NSPopUpButton *	fieldButton3;
    IBOutlet NSPopUpButton *	groupFieldButton3;
    IBOutlet NSPopUpButton *	fieldButton4;
    
    IBOutlet NSPopUpButton *	plotterButton3;
    IBOutlet NSPopUpButton *	fieldButton5;
    IBOutlet NSPopUpButton *	labelField1;
    
    IBOutlet NSImageView *		backgroundImage;
    
    IBOutlet NSPopUpButton *    sourceSeperatorButton;
}

- (IBAction) buttonImportClicked:(id)sender;
- (IBAction) buttonRunClicked:(id)sender;
- (IBAction) buttonExportClicked:(id)sender;
- (IBAction) buttonSaveClicked:(id)sender;
- (IBAction) buttonLoadClicked:(id)sender;

- (IBAction) filterButton1Selected:(id)sender;
- (IBAction) filterButton2Selected:(id)sender;

- (bool) createDataFlowElements;
@end
