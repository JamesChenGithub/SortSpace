//
//  FFTableViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/24.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "FFTableViewController.h"
#include "PlayAudioViewController.h"
#include "YUVViewController.h"
#include "ConstHeader.h"



@interface FFTableViewController ()

@end

@implementation FFTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return 4;
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
        text = @"本地mp3转pcm";
    }
    else if (indexPath.row == 2)
    {
        text = @"网络mp3转pcm";
    }
    else if (indexPath.row == 3)
    {
        text = @"YUV测试";
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
    else if (indexPath.row == 1)
    {
        [self localto48K];
    }
    else if (indexPath.row == 2)
    {
        [self nettopcm];
    }
    else if (indexPath.row == 3)
    {
        YUVViewController *vc = [[YUVViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
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
//    av_register_all();
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
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"left.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    
    path = [NSTemporaryDirectory() stringByAppendingString:@"right.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp2 = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    path = [NSTemporaryDirectory() stringByAppendingString:@"all.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp3 = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    
    AVPacket packet;
    av_init_packet(&packet);
    AVFrame *frame = NULL;
    
    
    uint8_t *bytes = (uint8_t *)malloc(5000);
    
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
            DebugLog(@"codeContext->channels = %d, %d, %d, %d, %p, %p, %p, %p", codeContext->channels, frame->nb_samples, data_size, frame->linesize[0], frame->extended_data[0], frame->data[1], frame->extended_data[0], frame->extended_data[0]);
            
            // codeContext->channels = 2, 1152, 4608, 2304, 0x7fa4ff01c000, 0x7fa4ff01ca00, 0x7fa4ff01c000, 0x7fa4ff01c000
            fwrite(frame->extended_data[0],1,frame->linesize[0],fp);
            fwrite(frame->extended_data[0],1,frame->linesize[0],fp2);
            
            int size = 0;
            int index = 0;
            while (size < frame->linesize[0]) {
                bytes[index++] = *(frame->extended_data[0] + size);
                bytes[index++] = *(frame->extended_data[0] + size);
                size++;
            }
            fwrite(bytes,1, index,fp3);
            
            fflush(fp);
            fflush(fp2);
            fflush(fp3);
            
            
        }
        av_frame_free(&frame);
        av_free_packet(&packet);
    }
    
    DebugLog(@"convert over");
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    avcodec_close(codeContext);
    avformat_close_input(&pFormatCtx);
}


#define MAX_AUDIO_FRAME_SIZE 192000

- (int)localto48K
{
    AVFormatContext         *pFormatCtx = NULL;
    AVCodecContext          *pCodecCtx = NULL;
    AVCodec                 *pCodec = NULL;
    AVFrame                 *pAudioFrame = NULL;
    AVPacket                packet;
    uint8_t                 *buffer = NULL;
    struct SwrContext       *audio_convert_ctx = NULL;
    int                     got_picture;
    int                     audioIndex;
    int                     index = 0;
    
    
    //    char filepath[1024] = "";
    //    printf("Usage: program.exe *.mp3\n");
    //    if (argc == 2)
    //    {
    //        strcpy(filepath, argv[1]);
    //    }
    //    else
    //    {
    //        printf("Could not find a audio file\n");
    //        return -1;
    //    }
    //
    //    FILE *fp_pcm = fopen("output.pcm", "wb+");
    //    if (fp_pcm == NULL)
    //    {
    //        printf("FILE open error");
    //        return -1;
    //    }
    
    
//    av_register_all();
    
    NSString *apath = [[NSBundle mainBundle] pathForResource:@"byebye" ofType:@"mp3"];
    const char *srcfile = [apath cStringUsingEncoding:NSASCIIStringEncoding];
    
    if (avformat_open_input(&pFormatCtx, srcfile, NULL, NULL) != 0){
        printf("Couldn't open an input stream.\n");
        return -1;
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0){
        printf("Couldn't find stream information.\n");
        return -1;
    }
    audioIndex = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioIndex = i;
            break;
        }
    }
    
    if (audioIndex == -1){
        printf("Couldn't find a audio stream.\n");
        return -1;
    }
    
    pCodecCtx = pFormatCtx->streams[audioIndex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL){
        printf("Codec not found.\n");
        return -1;
    }
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
        printf("Could not open codec.\n");
        return -1;
    }
    
    pAudioFrame = av_frame_alloc();
    if (pAudioFrame == NULL)
    {
        printf("Could not alloc AVFrame\n");
        return -1;
    }
    
    //音频输出参数
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;//声道格式
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;//采样格式
    int out_nb_samples = pCodecCtx->frame_size;//nb_samples: AAC-1024 MP3-1152
    int out_sample_rate = 48000;pCodecCtx->sample_rate;//采样率
    int out_nb_channels = av_get_channel_layout_nb_channels(out_channel_layout);//根据声道格式返回声道个数
    int out_buffer_size = av_samples_get_buffer_size(NULL, out_nb_channels, out_nb_samples, out_sample_fmt, 1);
    
    
    int64_t in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);//根据声道数返回默认输入声道格式
    
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"48k.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    
    /**
     * 函数声明：struct SwrContext *swr_alloc(void);
     * Allocate SwrContext.
     *
     * If you use this function you will need to set the parameters (manually or
     * with swr_alloc_set_opts()) before calling swr_init().
     *
     * @see swr_alloc_set_opts(), swr_init(), swr_free()
     * @return NULL on error, allocated context otherwise
     */
    
    audio_convert_ctx = swr_alloc();
    if (audio_convert_ctx == NULL)
    {
        printf("Could not allocate SwrContext\n");
        return -1;
    }
    
    /**
     * 函数声明：struct SwrContext *swr_alloc_set_opts(
     * struct SwrContext *s,int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
     * int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
     * int log_offset, void *log_ctx);
     *
     * Allocate SwrContext if needed and set/reset common parameters.
     *
     * This function does not require s to be allocated with swr_alloc(). On the
     * other hand, swr_alloc() can use swr_alloc_set_opts() to set the parameters
     * on the allocated context.
     *
     * @param s               existing Swr context if available, or NULL if not
     * @param out_ch_layout   output channel layout (AV_CH_LAYOUT_*)
     * @param out_sample_fmt  output sample format (AV_SAMPLE_FMT_*).
     * @param out_sample_rate output sample rate (frequency in Hz)
     * @param in_ch_layout    input channel layout (AV_CH_LAYOUT_*)
     * @param in_sample_fmt   input sample format (AV_SAMPLE_FMT_*).
     * @param in_sample_rate  input sample rate (frequency in Hz)
     * @param log_offset      logging level offset
     * @param log_ctx         parent logging context, can be NULL
     *
     * @see swr_init(), swr_free()
     * @return NULL on error, allocated context otherwise
     */
    audio_convert_ctx = swr_alloc_set_opts(audio_convert_ctx, out_channel_layout, out_sample_fmt,
                                           out_sample_rate, in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
    
    /**
     * 函数声明：int swr_init(struct SwrContext *s);
     * Initialize context after user parameters have been set.
     * @note The context must be configured using the AVOption API.
     *
     * @see av_opt_set_int()
     * @see av_opt_set_dict()
     *
     * @param[in,out]   s Swr context to initialize
     * @return AVERROR error code in case of failure.
     */
    swr_init(audio_convert_ctx);
    
    while (av_read_frame(pFormatCtx, &packet) >= 0)
    {
        if (packet.stream_index == audioIndex)
        {
            if (avcodec_decode_audio4(pCodecCtx, pAudioFrame, &got_picture, &packet) < 0)
            {
                printf("Error in decoding audio frame.\n");
                return -1;
            }
            if (got_picture)
            {
                /** Convert audio.
                 * 函数声明：int swr_convert(struct SwrContext *s, uint8_t **out, int out_count,
                 *                           const uint8_t **in, int in_count);
                 * in and in_count can be set to 0 to flush the last few samples out at the
                 * end.
                 *
                 * If more input is provided than output space, then the input will be buffered.
                 * You can avoid this buffering by using swr_get_out_samples() to retrieve an
                 * upper bound on the required number of output samples for the given number of
                 * input samples. Conversion will run directly without copying whenever possible.
                 *
                 * @param s         allocated Swr context, with parameters set
                 * @param out       output buffers, only the first one need be set in case of packed audio
                 * @param out_count amount of space available for output in samples per channel
                 * @param in        input buffers, only the first one need to be set in case of packed audio
                 * @param in_count  number of input samples available in one channel
                 *
                 * @return number of samples output per channel, negative value on error
                 */
                
                swr_convert(audio_convert_ctx, &buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pAudioFrame->data, pAudioFrame->nb_samples);
                printf("index:%5d\t pts:%lld\t packet size:%d\n", index, packet.pts, packet.size);
                //Write PCM
                fwrite(buffer, 1, out_buffer_size, fp);
                index++;
            }
        }
        av_free_packet(&packet);
    }
    
    fclose(fp);
    swr_free(&audio_convert_ctx);
    av_free(buffer);
    av_frame_free(&pAudioFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    
    return 0;
}

- (int)nettopcm
{
    AVFormatContext         *pFormatCtx = NULL;
    AVCodecContext          *pCodecCtx = NULL;
    AVCodec                 *pCodec = NULL;
    AVFrame                 *pAudioFrame = NULL;
    AVPacket                packet;
    uint8_t                 *buffer = NULL;
    struct SwrContext       *audio_convert_ctx = NULL;
    int                     got_picture;
    int                     audioIndex;
    int                     index = 0;
    
    
    //    char filepath[1024] = "";
    //    printf("Usage: program.exe *.mp3\n");
    //    if (argc == 2)
    //    {
    //        strcpy(filepath, argv[1]);
    //    }
    //    else
    //    {
    //        printf("Could not find a audio file\n");
    //        return -1;
    //    }
    //
    //    FILE *fp_pcm = fopen("output.pcm", "wb+");
    //    if (fp_pcm == NULL)
    //    {
    //        printf("FILE open error");
    //        return -1;
    //    }
    
    
//    av_register_all();
//    avformat_network_init();
    
    NSString *apath = kAudioTestURL;
    const char *srcfile = [apath cStringUsingEncoding:NSASCIIStringEncoding];
    
    if (avformat_open_input(&pFormatCtx, srcfile, NULL, NULL) != 0){
        printf("Couldn't open an input stream.\n");
        return -1;
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0){
        printf("Couldn't find stream information.\n");
        return -1;
    }
    audioIndex = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioIndex = i;
            break;
        }
    }
    
    if (audioIndex == -1){
        printf("Couldn't find a audio stream.\n");
        return -1;
    }
    
    pCodecCtx = pFormatCtx->streams[audioIndex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL){
        printf("Codec not found.\n");
        return -1;
    }
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
        printf("Could not open codec.\n");
        return -1;
    }
    
    pAudioFrame = av_frame_alloc();
    if (pAudioFrame == NULL)
    {
        printf("Could not alloc AVFrame\n");
        return -1;
    }
    
    //音频输出参数
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;//声道格式
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;//采样格式
    int out_nb_samples = pCodecCtx->frame_size;//nb_samples: AAC-1024 MP3-1152
    int out_sample_rate = pCodecCtx->sample_rate;//采样率
    int out_nb_channels = av_get_channel_layout_nb_channels(out_channel_layout);//根据声道格式返回声道个数
    int out_buffer_size = av_samples_get_buffer_size(NULL, out_nb_channels, out_nb_samples, out_sample_fmt, 1);
    
    
    int64_t in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);//根据声道数返回默认输入声道格式
    
    
    NSString *path = [NSTemporaryDirectory() stringByAppendingString:@"net48k.pcm"];
    DebugLog(@"%@",path);
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    
    FILE *fp = fopen([path cStringUsingEncoding:NSASCIIStringEncoding],"wb");
    
    buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    
    /**
     * 函数声明：struct SwrContext *swr_alloc(void);
     * Allocate SwrContext.
     *
     * If you use this function you will need to set the parameters (manually or
     * with swr_alloc_set_opts()) before calling swr_init().
     *
     * @see swr_alloc_set_opts(), swr_init(), swr_free()
     * @return NULL on error, allocated context otherwise
     */
    
    audio_convert_ctx = swr_alloc();
    if (audio_convert_ctx == NULL)
    {
        printf("Could not allocate SwrContext\n");
        return -1;
    }
    
    /**
     * 函数声明：struct SwrContext *swr_alloc_set_opts(
     * struct SwrContext *s,int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
     * int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
     * int log_offset, void *log_ctx);
     *
     * Allocate SwrContext if needed and set/reset common parameters.
     *
     * This function does not require s to be allocated with swr_alloc(). On the
     * other hand, swr_alloc() can use swr_alloc_set_opts() to set the parameters
     * on the allocated context.
     *
     * @param s               existing Swr context if available, or NULL if not
     * @param out_ch_layout   output channel layout (AV_CH_LAYOUT_*)
     * @param out_sample_fmt  output sample format (AV_SAMPLE_FMT_*).
     * @param out_sample_rate output sample rate (frequency in Hz)
     * @param in_ch_layout    input channel layout (AV_CH_LAYOUT_*)
     * @param in_sample_fmt   input sample format (AV_SAMPLE_FMT_*).
     * @param in_sample_rate  input sample rate (frequency in Hz)
     * @param log_offset      logging level offset
     * @param log_ctx         parent logging context, can be NULL
     *
     * @see swr_init(), swr_free()
     * @return NULL on error, allocated context otherwise
     */
    audio_convert_ctx = swr_alloc_set_opts(audio_convert_ctx, out_channel_layout, out_sample_fmt,
                                           out_sample_rate, in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
    
    /**
     * 函数声明：int swr_init(struct SwrContext *s);
     * Initialize context after user parameters have been set.
     * @note The context must be configured using the AVOption API.
     *
     * @see av_opt_set_int()
     * @see av_opt_set_dict()
     *
     * @param[in,out]   s Swr context to initialize
     * @return AVERROR error code in case of failure.
     */
    swr_init(audio_convert_ctx);
    
    while (av_read_frame(pFormatCtx, &packet) >= 0)
    {
        if (packet.stream_index == audioIndex)
        {
            if (avcodec_decode_audio4(pCodecCtx, pAudioFrame, &got_picture, &packet) < 0)
            {
                printf("Error in decoding audio frame.\n");
                return -1;
            }
            if (got_picture)
            {
                /** Convert audio.
                 * 函数声明：int swr_convert(struct SwrContext *s, uint8_t **out, int out_count,
                 *                           const uint8_t **in, int in_count);
                 * in and in_count can be set to 0 to flush the last few samples out at the
                 * end.
                 *
                 * If more input is provided than output space, then the input will be buffered.
                 * You can avoid this buffering by using swr_get_out_samples() to retrieve an
                 * upper bound on the required number of output samples for the given number of
                 * input samples. Conversion will run directly without copying whenever possible.
                 *
                 * @param s         allocated Swr context, with parameters set
                 * @param out       output buffers, only the first one need be set in case of packed audio
                 * @param out_count amount of space available for output in samples per channel
                 * @param in        input buffers, only the first one need to be set in case of packed audio
                 * @param in_count  number of input samples available in one channel
                 *
                 * @return number of samples output per channel, negative value on error
                 */
                
                swr_convert(audio_convert_ctx, &buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pAudioFrame->data, pAudioFrame->nb_samples);
                printf("index:%5d\t pts:%lld\t packet size:%d\n", index, packet.pts, packet.size);
                //Write PCM
                fwrite(buffer, 1, out_buffer_size, fp);
                index++;
            }
        }
        av_free_packet(&packet);
    }
    
    fclose(fp);
    swr_free(&audio_convert_ctx);
    av_free(buffer);
    av_frame_free(&pAudioFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    
    
    
    return 0;
}




@end
