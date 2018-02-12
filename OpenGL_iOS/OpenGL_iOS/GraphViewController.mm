//
//  GraphViewController.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "GraphViewController.h"
#include <math.h>


@implementation DrawGraphView


- (void)drawItems:(NSArray *)items
{
    [self.drawItems removeAllObjects];
    [super drawItems];
}

- (void)drawItem:(DrawItem *)item
{
    [self.drawItems removeAllObjects];
    
    [super drawItem:item];
}

@end

@interface GraphViewController ()

@end

@implementation GraphViewController
static int kVertCount = 3;
const double kPI = 3.1415926;
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
     self.view.backgroundColor = [UIColor colorWithRed:1 green:1 blue:1 alpha:1];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self draw];
    });
    
}

- (void)draw
{
    CGFloat w = 0.8;
    CGFloat h = self.view.bounds.size.width / self.view.bounds.size.height * w;
    
    GLfloat *verts = new GLfloat[kVertCount * 3];
    
    const double delta = 2 * kPI / kVertCount;
    for (int i = 0; i < kVertCount; i++) {
        verts[i*3] = cos(delta*i + delta/2) * w;
        verts[i*3 + 1] = sin(delta*i + delta/2) * h;
        verts[i*3 + 2] = 0;
    }
    
    DrawItem *item = [DrawItem draw:verts mode:GL_LINE_LOOP vetexCount:kVertCount];
    DrawGraphView *glview = (DrawGraphView *) self.view;
    [glview drawItem:item];
    
    kVertCount++;
    
    delete [] verts;
    
    
    if (kVertCount < 20)
    {
    
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self draw];
        });
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
