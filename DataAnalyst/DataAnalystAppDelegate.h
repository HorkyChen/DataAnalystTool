//
//  DataAnalystAppDelegate.h
//  DataAnalyst
//
//  Created by Chen Hao on 4/29/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DataAnalystAppDelegate : NSObject <NSApplicationDelegate>{
}

@property (assign) IBOutlet NSWindow *window;

@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;

@end
