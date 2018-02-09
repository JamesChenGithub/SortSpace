//
//  YUVShowViewController.m
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/2/7.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "YUVShowViewController.h"

#include "YUVView.h"

@interface YUVShowViewController ()

@end

@implementation YUVShowViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    YUVView *view = [[YUVView alloc] initWithFrame:CGRectMake(20, 100, 256, 256)];
    view.backgroundColor = [UIColor redColor];
    
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"lena_256x256_yuv420p" ofType:@"yuv"];
    NSData *data = [NSData dataWithContentsOfFile:path];
    
    [self.view addSubview:view];
    
    [view displayYUV420pData:data.bytes width:256 height:256];
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
