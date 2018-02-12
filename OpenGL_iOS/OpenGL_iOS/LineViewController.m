//
//  ViewController.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "LineViewController.h"
#include "DrawBaseView.h"

@implementation DrawLineView

//- (void)render
//{
//    for (DrawItem *item in _drawItems)
//    {
//        if (item) {
//            <#statements#>
//        }
//
//
//        glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, item.vetexs);
//
//        glEnableVertexAttribArray(_positionSlot);
//
//        glDrawArrays(item.drawMode, 0, item.vetexcount);
//
//        glDisableVertexAttribArray(_positionSlot);
//    }
//
//
//
//    [_context presentRenderbuffer:GL_RENDERBUFFER];
//}

@end


@interface LineViewController ()

@end

@implementation LineViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    DrawLineView *glView = (DrawLineView *)[self.view viewWithTag:100];
    glView.backgroundColor = [UIColor colorWithRed:1 green:1 blue:1 alpha:1];
    
    {
        GLfloat vert1[] ={
            -0.9, 0.9, 0,
            -0.1, 0.9, 0
        };
        
        int count = sizeof(vert1)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert1 mode:GL_LINES vetexCount:count];
        [glView drawItem:item];
    }
    
    {
        GLfloat vert2[] ={
            -0.8, 0.8, 0,
            -0.1, 0.1, 0,
            -0.8, 0.1, 0
        };
        
        int count = sizeof(vert2)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert2 mode:GL_LINE_STRIP vetexCount:count];
        [glView drawItem:item];
    }
    
    
    {
        GLfloat vert2[] ={
            -0.7, 0.7, 0,
            -0.1, 0.1, 0,
            -0.7, 0.1, 0,
            -0.1, 0.7, 0,
        };
        
        int count = sizeof(vert2)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert2 mode:GL_LINE_STRIP vetexCount:count];
        [glView drawItem:item];
    }
    
    {
        GLfloat vert2[] ={
            -0.6, 0.6, 0,
            -0.3, 0.1, 0,
            -0.6, 0.1, 0,
            -0.3, 0.6, 0,
        };
        
        int count = sizeof(vert2)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert2 mode:GL_LINE_LOOP vetexCount:count];
        [glView drawItem:item];
    }
    
    
    {
        GLfloat vert2[] ={
            0.9, 0.9, 0,
            0.9, 0.1, 0,
            0.1, 0.1, 0,
            0.1, 0.9, 0,
        };
        
        int count = sizeof(vert2)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert2 mode:GL_LINE_LOOP vetexCount:count];
        [glView drawItem:item];
    }
    
    {
        GLfloat vert2[] ={
            -0.9, -0.9, 0,
            -0.7, -0.1, 0,
            -0.5, -0.9, 0,
            -0.3, -0.1, 0,
            -0.1, -0.9, 0,
        };
        
        int count = sizeof(vert2)/(3 * sizeof(GLfloat));
        DrawItem *item = [DrawItem draw:vert2 mode:GL_LINE_STRIP vetexCount:count];
        [glView drawItem:item];
    }
    
    
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
