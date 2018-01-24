//
//  FFConverter.cpp
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "FFConverter.hpp"


FFConverter::FFConverter(std::string fileUrl)
{
    if(!_mRegistAll)
    {
        av_register_all();
        _mRegistAll = true;
    }
    
    _mFileUrl = fileUrl;
    
    _mInitialized = false;
    _mPacket.data = 0;
}

FFConverter::~FFConverter()
{
    deinit();
}

bool FFConverter::init()
{
    if (_mInitialized)
    {
        return true;
    }
    
    if (!demuxInit())
    {
        return false;
    }
    
    _mAudioStream = -1;
    _mVideoFrame = -1;
    
    uint32_t numofstream = _mPContext->nb_streams;
    for (uint32_t i = 0; i < numofstream; i++)
    {
        AVStream *stream = _mPContext->streams[i];
        
        switch (stream->codec->codec_type)
        {
            case AVMEDIA_TYPE_AUDIO:
            {
                if(_mAudioStream != -1)
                {
                    continue;
                }
                
                _mAudioStream = i;
                _mAudioTimeBase = stream->time_base;
                _mAudioStartTime = stream->start_time;
                // TODO:获取格式信息
//                _mAudioFrameSize =
                
            }
                break;
                
            case AVMEDIA_TYPE_VIDEO:
                if (_mVideoStream != -1)
                {
                    continue;
                }
                
                if (stream->codec->codec_id != AV_CODEC_ID_H264)
                {
                    continue;
                }
                
                _mVideoStream = i;
                
            default:
                break;
        }
    }
    
    if (_mAudioStream == -1 && _mVideoStream == -1)
    {
        deinit();
        return false;
    }
    
    // TODO:设置格式相关
    
//    m_finished = false;
//    pframe = 0;
//    m_pframeData = 0;
//    m_frameAvail = 0;
//    m_audioFramesWritten = 0;
//    m_working = EWORKING_NONE;
//
//    if(m_observer) {
//        m_observer->init(m_audioOutputFormat);
//    }
//    m_initialized = true;
    
    _mFinished = false;
    _mPFrame = 0;
    _mPFrameData = 0;
    _mState = ENone;
    _mInitialized = true;
    return true;
}

bool FFConverter::deinit()
{
    _mInitialized = false;
    demuxDeinit();
    return true;
}

bool FFConverter::demuxDeinit()
{
    if(_mPacket.data) {
        av_free_packet(&_mPacket);
    }
    if(_mPContext) {
        avformat_close_input(&_mPContext);
        _mPContext = 0;
    }
    
    return true;
}

bool FFConverter::demuxInit()
{
    const char *url = _mFileUrl.c_str();
    int result = avformat_open_input(&_mPContext, url, 0, 0);
    if (result < 0)
    {
        char error[256];
        av_strerror(result, error, 256);
        return false;
    }
    result = avformat_find_stream_info(_mPContext, 0);
    if(result < 0)
    {
        char error[256];
        av_strerror(result, error, 256);
        return false;
    }

    av_dump_format(_mPContext, 0, url, 0);
    return true;
}

void FFConverter::startRead()
{
    _mReading = true;
    uint32_t numBytes = 32 * 1024;
    
    uint8_t *pdata = (uint8_t *)malloc(numBytes);
    uint8_t *pdst = pdata;
    
    while (!_mFinished)
    {
        if (_mReading)
        {
            memset(pdata, 0, numBytes);
            
            uint32_t availabel = numBytes;
            
            while (availabel > 0)
            {
                if (_mFrameAvail == 0)
                {
                    AVPacket *ppactket = demuxProcess();
                 
                    if (!ppactket)
                    {
                        _mFinished = true;
                        break;
                    }
                    
                    if (ppactket->stream_index == _mAudioStream)
                    {
                        // TODO:作音频转码
                    }
                    else if (ppactket->stream_index == _mVideoStream)
                    {
                        // TODO:作视频转码
                    }
                }
            }
        }
    }
}

AVPacket* FFConverter::demuxProcess()
{
    if(_mPacket.data) {
        av_free_packet(&_mPacket);
        _mPacket.data = 0;
    }
    
//    signal(SIGALRM, OnFCLibavStreamerBufferingTimeOut);
//    alarm(10);
    if(av_read_frame(_mPContext, &_mPacket) < 0) {
//        signal(SIGALRM, SIG_IGN);
//        printf("*** THAT'S ALL ***\n");
//        m_packet.data = 0;
        return 0;
    }
//    signal(SIGALRM, SIG_IGN);
    
    return &m_packet;
}
