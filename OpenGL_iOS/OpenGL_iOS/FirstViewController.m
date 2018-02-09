//
//  FirstViewController.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "FirstViewController.h"
#include "OpenGLView.h"

@interface FirstViewController ()

@end

@implementation FirstViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self.glView setBackgroundColor:[UIColor colorWithRed:0.4 green:0.5 blue:0.6 alpha:0.7]];
    
    OpenGLView *view = [[OpenGLView alloc] init];
    
    [self.view addSubview:view];
    
    [UIView animateWithDuration:3 animations:^{
       
        view.frame = CGRectMake(100, 100, 100, 100);
        view.backgroundColor = [UIColor colorWithRed:0.6 green:0.7 blue:0.1 alpha:1];
    }];

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
