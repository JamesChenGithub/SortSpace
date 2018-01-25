//
//  FFTableViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "FFTableViewController.h"
#include "PlayAudioViewController.h"

#include "ConstHeader.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/audio_fifo.h>
    
#ifdef __cplusplus
};
#endif

@interface FFTableViewController ()

@end

@implementation FFTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    av_register_all();
//    avcodec_register_all();
//    avformat_network_init();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return  2;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"reuseIdentifier"];
    
    if (!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"reuseIdentifier"];
    }
    
    NSString *text = nil;
    
    if (indexPath.row == 0)
    {
        text = @"本地mp3转pcm";
    }
    else if (indexPath.row == 1)
    {
        text = @"网络mp3转pcm";
    }
    
    cell.textLabel.text = text;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row == 0)
    {
        [self localtoPCMSucc1];
        return;
//        [self local_mp3_to_pcm];
        
        PlayAudioViewController *pavc =[[PlayAudioViewController alloc] init];
        [self.navigationController pushViewController:pavc animated:YES];
    }
}

- (void)local_mp3_to_pcm
{
    NSString *apath = [[NSBundle mainBundle] pathForResource:@"byebye" ofType:@"mp3"];
    
    AVFormatContext *pFormatContext = NULL;
    int ret = avformat_open_input(&pFormatContext, [apath UTF8String], NULL, NULL);
    
    if (ret != 0) {
        NSLog(@"打开文件失败");
        return;
    }
    
    ret = avformat_find_stream_info(pFormatContext, NULL);
    if (ret != 0)
    {
        NSLog(@"未找到流信息");
        return;
    }
    
    
    int audioStream = -1;
    
    
    for(int index = 0; index < pFormatContext->nb_streams; index++)
    {
        AVStream *stream = pFormatContext->streams[index];
        AVCodecContext *codec = stream->codec;
        if (codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioStream = index;
            break;
        }
    }
    
    
    if (audioStream == -1)
    {
        NSLog(@"未找到音频流信息");
        return;
    }
    AVCodecContext *inputCodecCtx = pFormatContext->streams[audioStream]->codec;
    
    AVCodec *pCodec = avcodec_find_decoder(inputCodecCtx->codec_id);
    
    ret = avcodec_open2(inputCodecCtx, pCodec, NULL);
    
    if (ret < 0)
    {
        NSLog(@"打开音频解码器失败");
        return;
    }
    
    AVCodec *pcmCodec = avcodec_find_decoder(AV_CODEC_ID_PCM_S16LE);
    if(!pcmCodec)
    {
        NSLog(@"不能找到encoder");
        return;
    }
    
    AVCodecContext *pcmCodecContext = avcodec_alloc_context3(pcmCodec);
    pcmCodecContext->sample_fmt = pcmCodec->sample_fmts[0];
    pcmCodecContext->sample_rate = 48000;
    pcmCodecContext->channel_layout = av_get_default_channel_layout(2);
    pcmCodecContext->channels = inputCodecCtx->channels;
    pcmCodecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
    
    AVDictionary *opts = NULL;
    ret = avcodec_open2(pcmCodecContext, pcmCodec, &opts);
    if(ret < 0)
    {
        NSLog(@"failure open code");
        return;
    }
    
    int output_frame_size = pcmCodecContext->frame_size;
    AVAudioFifo *fifo = av_audio_fifo_alloc(AV_SAMPLE_FMT_S16, pcmCodecContext->channels, output_frame_size);
    
    SwrContext *resampleContext = swr_alloc();
    // 初始化重采样上下文
    resampleContext = swr_alloc_set_opts(resampleContext, pcmCodecContext->channels, pcmCodecContext->sample_fmt, pcmCodecContext->sample_rate, inputCodecCtx->channels, inputCodecCtx->sample_fmt, inputCodecCtx->sample_rate, 0, NULL);
    
    bool finished = false;
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"test.pcm"];
    
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    FILE *pcmFile = fopen([path UTF8String], "wb");
    
    
    path = [NSTemporaryDirectory() stringByAppendingString:@"raw.pcm"];
    
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    FILE *rawFile = fopen([path UTF8String], "wb");
    
    while (!finished)
    {
        while (av_audio_fifo_size(fifo) < output_frame_size)
        {
            if(finished)
            {
                break;
            }
            
            AVFrame *audioFrame = av_frame_alloc();
            AVPacket packet;
            packet.data = NULL;
            packet.size = 0;
            
            int data_present = 0;
            
            finished = (av_read_frame(pFormatContext, &packet) == AVERROR_EOF);
            
            if (packet.stream_index != audioStream)
            {
                continue;
            }
            
            if(avcodec_decode_audio4(inputCodecCtx, audioFrame, &data_present, &packet) < 0)
            {
                NSLog(@"解码失败");
                return;
            }
            
            if (data_present)
            {
                for(int i = 0; i < audioFrame->channels; i++)
                {
                    fwrite(audioFrame->data[i], 1, audioFrame->linesize[0], rawFile);
                }
            }
            
            
//            uint8_t **converted_input_samples = NULL;
//            if (init_conve)
            
            
        }
    }
}



- (void)localtoPCMSucc1
{
    NSString *apath = [[NSBundle mainBundle] pathForResource:@"byebye" ofType:@"mp3"];
    const char *srcfile = [apath cStringUsingEncoding:NSASCIIStringEncoding];
    av_register_all();
    AVFormatContext *pFormatCtx = NULL;
    if(avformat_open_input(&pFormatCtx, srcfile, NULL, 0) != 0)
        DebugLog(@"open file error");
    
    
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        DebugLog(@"av_find_stream_info");
    
    av_dump_format(pFormatCtx, 0, srcfile, false);
    
    int i = -1;
    int index = -1;
    int nbstr = pFormatCtx->nb_streams;
    for(i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            index = i;
            break;
        }
    }
    
//    for(i = 0; i < pFormatCtx->nb_streams; i++)
//    {
//        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
//        {
//            DebugLog(@"pFormatCtx->streams[%d] is Audio", i);
//        }
//    }
    
    if (index == -1)
    {
        DebugLog(@"there is not any audio stream in [%s]",srcfile);
        return;
    }
    
    AVCodecContext *codeContext = pFormatCtx->streams[i]->codec;
    AVCodec *codec = avcodec_find_decoder(codeContext->codec_id);
    if (!codec)
    {
        DebugLog(@"find codec for codec_id[%d] fail, file[%s]", pFormatCtx->audio_codec_id, srcfile);
        return;
    }
    
    int ret = avcodec_open2(codeContext, codec, NULL);
    if (ret >= 0)
    {
        DebugLog(@"open codec[name:%s] for stream [id:%d] of file [%s]\n",codec->name,index,srcfile);
    }
    
    codeContext->sample_fmt; // AV_SAMPLE_FMT_S16P
    codeContext->sample_rate;
    codeContext->channels;
    codeContext->channel_layout;
//    6,  44100,  2 , 3
    DebugLog(@"%d,  %d,  %d , %d", codeContext->sample_fmt, codeContext->sample_rate, codeContext->channels, codeContext->channel_layout);
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"test2.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    
    AVPacket packet;
    av_init_packet(&packet);
    AVFrame *frame = NULL;
    
    while(av_read_frame(pFormatCtx,&packet) >= 0)
    {
        DebugLog(@"av_read_frame");
        int got_frame = 0;
        
        frame = av_frame_alloc();
        ret = avcodec_decode_audio4(codeContext, frame, &got_frame, &packet);
        if (ret < 0 )
        {
            DebugLog("decode error \n");
            break;
        }
        
        if (got_frame)
        {
            int data_size = av_samples_get_buffer_size(NULL, codeContext->channels, frame->nb_samples, codeContext->sample_fmt, 1);
            DebugLog(@"codeContext->channels = %d, %d, %d, %d, %p, %p", codeContext->channels, frame->nb_samples, data_size, frame->linesize[0], frame->extended_data[0], frame->data[0]);
            fwrite(frame->extended_data[0],1,frame->linesize[0],fp);
            fflush(fp);
            
            
        }
        av_frame_free(&frame);
        av_free_packet(&packet);
    }
    
    DebugLog(@"convert over");
    fclose(fp);
    avcodec_close(codeContext);
    avformat_close_input(&pFormatCtx);
}




@end
