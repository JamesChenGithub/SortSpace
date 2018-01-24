//
//  PlayAudioViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "PlayAudioViewController.h"


#ifdef __cplusplus
extern "C"
{
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
    
#ifdef __cplusplus
};
#endif

#include "ConstHeader.h"

@interface PlayAudioViewController ()
{
    AVFormatContext *_pFormatContext;
    AVCodecContext *_pCodecContext;
    AVCodec *_pCodec;
    
    AVPacket    *_avPacket;
    
    FILE    *_pcmFile;
    FILE    *_rawFile;
    
    struct SwrContext *_auConvertContext;
}

@end

@implementation PlayAudioViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#define MAX_AUDIO_FRAME_SIZE 96000 // 1 second of 48khz 32bit audio

- (IBAction)registAll:(UIButton *)sender
{
    av_register_all();
    avformat_network_init();
    
    _pFormatContext = avformat_alloc_context();
    
    NSString *mp3url = kAudioTestURL;
    const char *url = [mp3url UTF8String];
    
    AVInputFormat format;
    AVDictionary *dic = NULL;
    
    if(avformat_open_input(&_pFormatContext, url, NULL, NULL))
    {
        NSLog(@"could't open input stream");
        return;
    }
    
    AVDictionary *opdic = NULL;
    
    if (avformat_find_stream_info(_pFormatContext, &opdic) < 0)
    {
        NSLog(@"could't find stream information");
        return;
    }
    
    av_dump_format(_pFormatContext, 0, url, false);
    
    
    int audiostream = -1;
    for (int i = 0; i < _pFormatContext->nb_streams; i++)
    {
        if(_pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audiostream = i;
            break;
        }
    }
    
    if (audiostream == -1)
    {
        NSLog(@"Couldn't find audio stream");
        return;
    }
    
    _pCodecContext = _pFormatContext->streams[audiostream]->codec;
    
    _pCodec = avcodec_find_decoder(_pCodecContext->codec_id);
    if(_pCodec == NULL)
    {
        NSLog(@"codec couldn't find");
        return;
    }
    
    AVDictionary *op = NULL;
    if(avcodec_open2(_pCodecContext, _pCodec, &op))
    {
        NSLog(@"could open codec");
        return;
    }
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"test.pcm"];
    
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    _pcmFile = fopen([path UTF8String], "wb");
    
    
    path = [NSTemporaryDirectory() stringByAppendingString:@"raw.pcm"];
    
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    _rawFile = fopen([path UTF8String], "wb");
    
    
    
    _avPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
    
    av_init_packet(_avPacket);
    
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
    int out_nb_samples = _pCodecContext->frame_size;
    
    enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    
    int out_sample_rate = 48000;
    int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    
    uint8_t *out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    AVFrame *pFrame = av_frame_alloc();
    
    int64_t in_channel_layout = av_get_default_channel_layout(_pCodecContext->channels);
    enum AVSampleFormat in_sample_fmt = _pCodecContext->sample_fmt;
    int in_sample_rate = _pCodecContext->sample_rate;
    
    int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
    
    _auConvertContext = swr_alloc();
    
//    struct SwrContext *swr_alloc_set_opts(struct SwrContext *s,
//                                          int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
//                                          int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
//                                          int log_offset, void *log_ctx);

    
    _auConvertContext = swr_alloc_set_opts(_auConvertContext, out_channels, out_sample_fmt, out_sample_rate,
                                           in_channel_layout, in_sample_fmt, in_sample_rate,
                                           0, NULL);
    swr_init(_auConvertContext);
    
    int got_picture;
    int index = 0;
    while (av_read_frame(_pFormatContext, _avPacket) >= 0)
    {
        if(_avPacket->stream_index == audiostream)
        {
            int ret = avcodec_decode_audio4(_pCodecContext, pFrame, &got_picture, _avPacket);
            if (ret < 0)
            {
                NSLog(@"error in decoding audio frame");
                break;
            }
            
            if (got_picture > 0)
            {
                
                fwrite(pFrame->data[0], 1, pFrame->linesize[0], _rawFile);
                
                swr_convert(_auConvertContext, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pFrame->data, pFrame->nb_samples);
                NSLog(@"index:%5d\t pts:%lld\t packet size:%d\n",index,_avPacket->pts,_avPacket->size);
                
                fwrite(out_buffer, 1, out_buffer_size, _pcmFile);
                
                index++;
            }
            
           // TODO：播数据
        }
        
        av_packet_unref(_avPacket);
        
        
        
        
    }
    
    swr_free(&_auConvertContext);
    
    fclose(_pcmFile);
    
    fclose(_rawFile);
    
    av_free(out_buffer);
    
    avcodec_close(_pCodecContext);
    avformat_close_input(&_pFormatContext);
    
    [sender setTitle:@"Over" forState:UIControlStateNormal];
}

- (IBAction)unregistAll:(UIButton *)sender
{
    
}

@end
