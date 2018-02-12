//
//  ThirdViewController.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "ThirdViewController.h"
#include "DrawBaseView.h"

@interface ThirdViewController ()

@end

@implementation ThirdViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    DrawBaseView *glView = (DrawBaseView *)self.view;
    
    GLfloat vertexs[] = {
        0,0.5,0,
        0.5,0,0,
        
    };
    
    [glView draw:vertexs mode:GL_LINES vetexCount:sizeof(vertexs)/ (sizeof(GLfloat)*3)];
    
    
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
