//
//  XLDAacOutputTask.h
//  XLDAacOutput
//
//  Created by tmkk on 06/09/08.
//  Copyright 2006 tmkk. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "XLDOutputTask.h"
#import <CoreAudio/CoreAudioTypes.h>
#import <AudioToolbox/AudioToolbox.h>

#define XLD_METADATA_TITLE		@"Title"
#define XLD_METADATA_ARTIST		@"Artist"
#define XLD_METADATA_ALBUM		@"Album"
#define XLD_METADATA_GENRE		@"Genre"
#define XLD_METADATA_TRACK		@"Track"
#define XLD_METADATA_DISC		@"Disc"
#define XLD_METADATA_YEAR		@"Year"
#define XLD_METADATA_DATE		@"Date"
#define XLD_METADATA_COMPOSER	@"Composer"
#define XLD_METADATA_CUESHEET	@"Cuesheet"
#define XLD_METADATA_COMMENT	@"Comment"
#define XLD_METADATA_TOTALTRACKS	@"Totaltracks"
#define XLD_METADATA_TOTALDISCS	@"Totaldiscs"
#define XLD_METADATA_LYRICS		@"Lyrics"
#define XLD_METADATA_COVER		@"Cover"
#define XLD_METADATA_ALBUMARTIST	@"AlbumArtist"
#define XLD_METADATA_COMPILATION	@"Compilation"
#define XLD_METADATA_GROUP		@"Group"
#define XLD_METADATA_GRACENOTE		@"Gracenote"
#define XLD_METADATA_GRACENOTE2		@"Gracenote2"
#define XLD_METADATA_BPM		@"BPM"
#define XLD_METADATA_COPYRIGHT	@"Copyright"
#define XLD_METADATA_GAPLESSALBUM	@"GaplessAlbum"
#define XLD_METADATA_TITLESORT	@"TitleSort"
#define XLD_METADATA_ARTISTSORT	@"ArtistSort"
#define XLD_METADATA_ALBUMSORT	@"AlbumSort"
#define XLD_METADATA_ALBUMARTISTSORT	@"AlbumArtistSort"
#define XLD_METADATA_COMPOSERSORT	@"ComposerSort"
#define XLD_METADATA_MB_TRACKID		@"MusicBrainz_TrackID"
#define XLD_METADATA_MB_ALBUMID	@"MusicBrainz_AlbumID"
#define XLD_METADATA_MB_ARTISTID	@"MusicBrainz_ArtistID"
#define XLD_METADATA_MB_ALBUMARTISTID	@"MusicBrainz_AlbumArtistID"
#define XLD_METADATA_MB_DISCID	@"MusicBrainz_DiscID"
#define XLD_METADATA_PUID		@"MusicIP_PUID"
#define XLD_METADATA_MB_ALBUMSTATUS	@"MusicBrainz_AlbumStatus"
#define XLD_METADATA_MB_ALBUMTYPE	@"MusicBrainz_AlbumType"
#define XLD_METADATA_MB_RELEASECOUNTRY	@"MusicBrainz_ReleaseCountry"
#define XLD_METADATA_MB_RELEASEGROUPID	@"MusicBrainz_ReleaseGroupID"
#define XLD_METADATA_MB_WORKID	@"MusicBrainz_WorkID"
#define XLD_METADATA_TOTALSAMPLES	@"TotalSamples"
#define XLD_METADATA_TRACKLIST	@"XLDTrackList"
#define XLD_METADATA_SMPTE_TIMECODE_START	@"SMTPE Timecode Start"
#define XLD_METADATA_SMPTE_TIMECODE_DURATION	@"SMTPE Timecode Duration"
#define XLD_METADATA_MEDIA_FPS	@"Media FPS"

@interface XLDAacOutput2Task : NSObject <XLDOutputTask> {
	XLDFormat format;
	ExtAudioFileRef file;
	AudioBufferList fillBufList;
	AudioStreamBasicDescription inputFormat,outputFormat;
	BOOL addTag;
	BOOL addGaplessInfo;
	NSMutableData *tagData;
	NSString *path;
	int64_t totalFrames;
	NSRange gaplessDataRange;
	NSRange bitrateDataRange;
	BOOL sbrEnabled;
	NSDictionary *configurations;
	NSData *chapterMdat;
	BOOL embedChapter;
}

- (BOOL)setOutputFormat:(XLDFormat)fmt;
- (BOOL)openFileForOutput:(NSString *)str withTrackData:(id)track;
- (NSString *)extensionStr;
- (BOOL)writeBuffer:(int *)buffer frames:(int)counts;
- (void)finalize;
- (void)closeFile;
- (void)setEnableAddTag:(BOOL)flag;

- (id)initWithConfigurations:(NSDictionary *)cfg;

@end
