//
//  ConstHeader.h
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef ConstHeader_h
#define ConstHeader_h


#define kVideoTestURL @"http://dldir1.qq.com/hudongzhibo/TCShow/video.mp4"

#define kAudioTestURL @"http://dldir1.qq.com/hudongzhibo/TCShow/byebye.mp3"

#define DebugLog(fmt, ...) NSLog((@"[%s Line %d]" fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif /* ConstHeader_h */
