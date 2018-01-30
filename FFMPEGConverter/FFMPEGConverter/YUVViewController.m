//
//  YUVViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/30.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "YUVViewController.h"
#include "OpenGLView20.h"

@interface YUVViewController ()

@end

@implementation YUVViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    // Do any additional setup after loading the view.
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        
        NSString *lena_yuv420p_path = [[NSBundle mainBundle] pathForResource:@"lena_256x256_yuv420p" ofType:@"yuv"];
        NSLog(@"%@",lena_yuv420p_path);
        simplest_yuv420_split([lena_yuv420p_path UTF8String], 256, 256, 1);
        
        
        NSString *lena_yuv444p_path = [[NSBundle mainBundle] pathForResource:@"lena_256x256_yuv444p" ofType:@"yuv"];
        NSLog(@"%@",lena_yuv420p_path);
        simplest_yuv444_split([lena_yuv420p_path UTF8String], 256, 256, 1);
        
        
        simple_yuv420_gray([lena_yuv420p_path UTF8String], 256, 256, 1);
        
        simple_yuv420_halfy([lena_yuv420p_path UTF8String], 256, 256, 1);
        
        simple_yuv420_border([lena_yuv420p_path UTF8String], 256, 256, 16, 1);
        
        NSString *temp = NSTemporaryDirectory();
        simple_yuv420_graybar(640 , 480, 0, 255, 10, [[temp stringByAppendingString:@"output_graybar.yuv"] UTF8String]);
    });
    
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

int simplest_yuv420_split(char *url, int w, int h,int num){
    FILE *fp=fopen(url,"rb+");
    
    NSString *temp = NSTemporaryDirectory();
    NSLog(@"%@", temp);
    FILE *fp1=fopen([[temp stringByAppendingString:@"output_420_y.yuv"] UTF8String],"wb+");
    FILE *fp2=fopen([[temp stringByAppendingString:@"output_420_u.yuv"] UTF8String],"wb+");
    FILE *fp3=fopen([[temp stringByAppendingString:@"output_420_v.yuv"] UTF8String],"wb+");
    
    int size = w*h*3/2;
    unsigned char *pic=(unsigned char *)malloc(size);
    
    for(int i=0;i<num;i++){
        
        fread(pic,1,size,fp);
        fwrite(pic, w*h, 1, fp1);
        fwrite(pic+w*h, w*h/4, 1, fp2);
        fwrite(pic+w*h*5/4, w*h/4, 1, fp3);
    }
    
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    
    return 0;
}

int simplest_yuv444_split(char *url, int w, int h,int num){
    FILE *fp=fopen(url,"rb+");
    
    NSString *temp = NSTemporaryDirectory();
    NSLog(@"%@", temp);
    FILE *fp1=fopen([[temp stringByAppendingString:@"output_444_y.yuv"] UTF8String],"wb+");
    FILE *fp2=fopen([[temp stringByAppendingString:@"output_444_u.yuv"] UTF8String],"wb+");
    FILE *fp3=fopen([[temp stringByAppendingString:@"output_444_v.yuv"] UTF8String],"wb+");
    
    int size = w*h*3;
    unsigned char *pic=(unsigned char *)malloc(size);
    
    for(int i=0;i<num;i++){
        
        fread(pic,1,size,fp);
        
        fwrite(pic, w*h, 1, fp1);
        fwrite(pic+w*h, w*h, 1, fp2);
        fwrite(pic+w*h*2, w*h, 1, fp3);
        //Y
        //        fwrite(pic,1,w*h,fp1);
        //        //U
        //        fwrite(pic+w*h,1,w*h/4,fp2);
        //        //V
        //        fwrite(pic+w*h*5/4,1,w*h/4,fp3);
    }
    
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    
    return 0;
}

int simple_yuv420_gray(char *url, int w, int h, int num)
{
    FILE *fp = fopen(url, "rb+");
    NSString *temp = NSTemporaryDirectory();
    NSLog(@"%@", temp);
    FILE *fp2 = fopen([[temp stringByAppendingString:@"output_gray.yuv"] UTF8String], "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0; i < num; i++)
    {
        fread(pic, w*h*3/2, 1, fp);
        memset(pic + w*h, 64, w*h/2);
        fwrite(pic, w*h*3/2, 1, fp2);
    }
    
    free(pic);
    fclose(fp2);
    fclose(fp);
    return 0;
    
}

int simple_yuv420_halfy(char *url, int w, int h, int num)
{
    FILE *fp = fopen(url, "rb+");
    NSString *temp = NSTemporaryDirectory();
    NSLog(@"%@", temp);
    FILE *fp2 = fopen([[temp stringByAppendingString:@"output_halfy.yuv"] UTF8String], "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0; i < num; i++)
    {
        fread(pic, w*h*3/2, 1, fp);
        
        
        for (int j = 0; j < w*h; j++)
        {
            pic[j] /=2;
        }
        
        fwrite(pic, w*h*3/2, 1, fp2);
    }
    
    free(pic);
    fclose(fp2);
    fclose(fp);
    return 0;
    
}

int simple_yuv420_border(char *url, int w, int h, int border,int num)
{
    FILE *fp = fopen(url, "rb+");
    NSString *temp = NSTemporaryDirectory();
    NSLog(@"%@", temp);
    FILE *fp2 = fopen([[temp stringByAppendingString:@"output_border.yuv"] UTF8String], "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0; i < num; i++)
    {
        fread(pic, w*h*3/2, 1, fp);
        
        
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < w; k++)
            {
                if (k < border || k > (w - border) || j < border || j > (h - border)) {
                    pic[j*w + k] = 255;
                }
            }
            
        }
        
        fwrite(pic, w*h*3/2, 1, fp2);
    }
    
    free(pic);
    fclose(fp2);
    fclose(fp);
    return 0;
    
}

int simple_yuv420_graybar(int width, int height, int ymin, int ymax, int barnum, char *outurl)
{
    int barwidth;
    float lum_inc;
    
    unsigned char lum_temp;
    int uv_width, uv_height;
    
    FILE *fp = NULL;
    unsigned char *data_y = NULL;
    unsigned char *data_u = NULL;
    unsigned char *data_v = NULL;
    
    int i=0, j = 0, k = 0, t = 0;
    
    barwidth = width/barnum;
    lum_inc = ((float)(ymax - ymin))/((float)(barnum - 1));
    
    uv_width = width/2;
    uv_height = height/2;
    
    
    data_y = (unsigned char *)malloc(width * height);
    data_u = (unsigned char *)malloc(uv_width * uv_height);
    data_v = (unsigned char *)malloc(uv_width * uv_height);
    
    memset(data_u, 128, uv_width * uv_height);
    memset(data_v, 128, uv_width * uv_height);
    
    if ((fp = fopen(outurl, "wb+")) == NULL)
    {
        return -1;
    }
    
    printf("y,u,v value from picture's left to right\n");
    
    for (t = 0; t < barnum; t++)
    {
        lum_temp = ymin+(unsigned char)(t * lum_inc);
        printf("%3d, 128, 128\n", lum_temp);
    }
    
    // Gen Data
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            t = i/barwidth;
            lum_temp = ymin+(unsigned char)(t * lum_inc);
            data_y[j * width + i] = lum_temp;
        }
    }
    
    fwrite(data_y, width * height, 1, fp);
    fwrite(data_u, uv_width * uv_height, 1, fp);
    fwrite(data_v, uv_width * uv_height, 1, fp);
    
    fclose(fp);
    
    free(data_y);
    free(data_u);
    free(data_v);
    
    return 0;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
