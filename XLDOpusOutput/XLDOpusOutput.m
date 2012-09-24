//
//  XLDOpusOutput.m
//  XLDOpusOutput
//
//  Created by tmkk on 12/08/09.
//  Copyright 2012 tmkk. All rights reserved.
//

#import "XLDOpusOutput.h"
#import "XLDOpusOutputTask.h"

@implementation XLDOpusOutput

+ (NSString *)pluginName
{
	return @"Opus";
}

+ (BOOL)canLoadThisBundle
{
	return YES;
}

- (id)init
{
	[super init];
	[NSBundle loadNibNamed:@"XLDOpusOutput" owner:self];
	srand(time(NULL));
	return self;
}

- (NSView *)prefPane
{
	return o_prefPane;
}

- (int)bitrate
{
	int bitrate = [o_bitrate intValue] * 1000;
	if(bitrate < 6000) bitrate = 6000;
	return bitrate;
}

- (void)savePrefs
{
	NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
	[pref setInteger:[o_bitrate intValue] forKey:@"XLDOpusOutput_Bitrate"];
	[pref setInteger:[o_frameSize indexOfSelectedItem] forKey:@"XLDOpusOutput_FrameSize"];
	[pref setInteger:[o_encoderMode indexOfSelectedItem] forKey:@"XLDOpusOutput_EncoderMode"];
	[pref synchronize];
}

- (void)loadPrefs
{
	NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
	[self loadConfigurations:pref];
}

- (id)createTaskForOutput
{
	return [[XLDOpusOutputTask alloc] initWithConfigurations:[self configurations]];
}

- (id)createTaskForOutputWithConfigurations:(NSDictionary *)cfg
{
	return [[XLDOpusOutputTask alloc] initWithConfigurations:cfg];
}

- (NSMutableDictionary *)configurations
{
	NSMutableDictionary *cfg = [[NSMutableDictionary alloc] init];
	/* for GUI */
	[cfg setObject:[NSNumber numberWithInt:[o_bitrate intValue]] forKey:@"XLDOpusOutput_Bitrate"];
	[cfg setObject:[NSNumber numberWithInt:[o_frameSize indexOfSelectedItem]] forKey:@"XLDOpusOutput_FrameSize"];
	[cfg setObject:[NSNumber numberWithInt:[o_encoderMode indexOfSelectedItem]] forKey:@"XLDOpusOutput_EncoderMode"];
	/* for task */
	[cfg setObject:[NSNumber numberWithInt:[self bitrate]] forKey:@"Bitrate"];
	[cfg setObject:[NSNumber numberWithInt:[[o_frameSize selectedItem] tag]] forKey:@"FrameSize"];
	[cfg setObject:[NSNumber numberWithInt:[[o_encoderMode selectedItem] tag]] forKey:@"EncoderMode"];
	/* desc */
	switch([[o_encoderMode selectedItem] tag]) {
		case 0:
			[cfg setObject:[NSString stringWithFormat:@"VBR, %d kbps",[self bitrate]] forKey:@"ShortDesc"];
		case 1:
			[cfg setObject:[NSString stringWithFormat:@"Constrained VBR, %d kbps",[self bitrate]] forKey:@"ShortDesc"];
		case 2:
			[cfg setObject:[NSString stringWithFormat:@"CBR, %d kbps",[self bitrate]] forKey:@"ShortDesc"];
	}
	return [cfg autorelease];
}

- (void)loadConfigurations:(id)cfg
{
	id obj;
	if(obj=[cfg objectForKey:@"XLDOpusOutput_Bitrate"]) {
		[o_bitrate setIntValue:[obj intValue]];
	}
	if(obj=[cfg objectForKey:@"XLDOpusOutput_FrameSize"]) {
		if([obj intValue] < [o_frameSize numberOfItems]) [o_frameSize selectItemAtIndex:[obj intValue]];
	}
	if(obj=[cfg objectForKey:@"XLDOpusOutput_EncoderMode"]) {
		if([obj intValue] < [o_encoderMode numberOfItems]) [o_encoderMode selectItemAtIndex:[obj intValue]];
	}
}

@end
