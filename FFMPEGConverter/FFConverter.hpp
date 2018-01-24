//
//  FFConverter.hpp
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef FFConverter_hpp
#define FFConverter_hpp

#include <stdio.h>
#include <string>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
    
#ifdef __cplusplus
}
#endif

class FFConverter
{
private:
    enum FFWork{
        ENone,
        EAudio,
        EVideo,
        EAll,
    };
    
private:
    static bool _mRegistAll;
    bool _mInitialized;
    bool _mFinished;
    FFWork _mState;
    std::string _mFileUrl;
    
private:
    
    bool _mReading;
    pthread_t _mCachingThread;
    pthread_t _mStreamThread;
    
private:
    AVFormatContext *_mPContext;
    AVPacket        _mPacket;

private:
    // Audio Processing
    int _mAudioStream;
    AVRational _mAudioTimeBase;
    uint64_t _mAudioStartTime;
    uint64_t _mAudioFramesWritten;
    uint32_t _mAudioFrameSize;
    
    // Video Processing
    int _mVideoStream;
    AVRational _mVideoTimebase;
    uint64_t _mVideoStartTime;
    uint64_t _mVideoFrame;
    
    // demuxer
    
    AVFrame* _mPFrame;
    const uint8_t* _mPFrameData;
    uint32_t _mFrameAvail;
    
public:
    FFConverter(const std::string fileURL);
    ~FFConverter();
    
    bool init();
    bool deinit();
    
    
    void startRead();
    void pauseRead();
    void resumeRead();
    void stopRead();
    
private:
    bool demuxInit();
    bool demuxDeinit();
    AVPacket* demuxProcess();
};

bool FFConverter::_mRegistAll = false;

#endif /* FFConverter_hpp */
