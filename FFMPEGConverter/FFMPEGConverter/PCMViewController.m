//
//  PCMViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/1/31.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "PCMViewController.h"

@interface PCMViewController ()

@end

@implementation PCMViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    
    NSLog(@"%@", NSTemporaryDirectory());
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        simple_pcm16l2_split();
        simple_pcm16l2_halfvl();
        simple_pcm16l2_doublespeed();
        simple_pcm16l2_to_pcm8();
    });
}


void simple_pcm16l2_split()
{
    NSString *infile = [[NSBundle mainBundle] pathForResource:@"NocturneNo2inEflat_44.1k_s16le" ofType:@"pcm"];
    
    FILE *fp = fopen([infile UTF8String], "rb+");
    
    NSString *temp = NSTemporaryDirectory();
    
    
    
    FILE *fpl = fopen([[temp stringByAppendingString:@"output_l.pcm"] UTF8String], "wb+");
    FILE *fpr = fopen([[temp stringByAppendingString:@"output_r.pcm"] UTF8String], "wb+");
    
    unsigned char *sample = (unsigned char *)malloc(4);
    
    while (!feof(fp))
    {
        fread(sample, 4, 1, fp);
        
        fwrite(sample, 1, 2, fpl);
        fwrite(sample+2, 1, 2, fpr);
    }
    
    free(sample);
    
    fclose(fp);
    fclose(fpl);
    fclose(fpr);
    
}


void simple_pcm16l2_halfvl()
{
    NSString *infile = [[NSBundle mainBundle] pathForResource:@"NocturneNo2inEflat_44.1k_s16le" ofType:@"pcm"];
    
    FILE *fp = fopen([infile UTF8String], "rb+");
    
    NSString *temp = NSTemporaryDirectory();
    FILE *fpl = fopen([[temp stringByAppendingString:@"output_halfvl.pcm"] UTF8String], "wb+");
    
    unsigned char *sample = (unsigned char *)malloc(4);
    
    while (!feof(fp))
    {
        fread(sample, 4, 1, fp);
        unsigned short *s = (unsigned short *)sample;
        *s = *s/2;
        fwrite(sample, 1, 2, fpl);
        fwrite(sample+2, 1, 2, fpl);
    }
    
    free(sample);
    
    fclose(fp);
    fclose(fpl);
    
}

void simple_pcm16l2_to_pcm8()
{
    NSString *infile = [[NSBundle mainBundle] pathForResource:@"NocturneNo2inEflat_44.1k_s16le" ofType:@"pcm"];
    
    FILE *fp = fopen([infile UTF8String], "rb+");
    
    NSString *temp = NSTemporaryDirectory();
    FILE *fpl = fopen([[temp stringByAppendingString:@"output_8.pcm"] UTF8String], "wb+");
    
    unsigned char *sample = (unsigned char *)malloc(4);
    
    while(!feof(fp))
    {
        short *s16 = NULL;
        char s8 = 0;
        
        unsigned char s8_u = 0;
        
        fread(sample, 1, 4, fp);
        
        s16 = (short *)sample;
        s8 = *s16 >> 8;
        s8_u = s8 + 128;
        
        
        // L
        fwrite(&s8_u, 1, 1 , fpl);
        
        s16 = (short *)(sample+2);
        s8 = *s16 >> 8;
        s8_u = s8 + 128;
        
        // R
        fwrite(&s8_u, 1, 1 , fpl);
        
    }
    
    free(sample);
    
    fclose(fp);
    fclose(fpl);
}


void simple_pcm16l2_doublespeed()
{
    NSString *infile = [[NSBundle mainBundle] pathForResource:@"NocturneNo2inEflat_44.1k_s16le" ofType:@"pcm"];
    
    FILE *fp = fopen([infile UTF8String], "rb+");
    
    NSString *temp = NSTemporaryDirectory();
    FILE *fpl = fopen([[temp stringByAppendingString:@"output_speeddouble.pcm"] UTF8String], "wb+");
    
    unsigned char *sample = (unsigned char *)malloc(4);
    
    int count = 0;
    while (!feof(fp))
    {
        fread(sample, 1, 4, fp);
        if (count % 2 != 0) {
            fwrite(sample, 1, 4, fpl);
//            fwrite(sample+2, 1, 2, fpl);
        }
        count++;
        
    }
    
    free(sample);
    
    fclose(fp);
    fclose(fpl);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
