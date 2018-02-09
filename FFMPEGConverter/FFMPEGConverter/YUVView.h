//
//  YUVView.h
//  FFMPEGConverter
//
//  Created by AlexiChen on 2018/2/7.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/EAGL.h>

@interface YUVView : UIView
{
    
    EAGLContext  *_glContext; // 上下文
    GLuint       _frameBuffer;
    GLuint       _renderBuffer;
    
    GLuint       _program;
    GLuint       _textureYUV[3];
    
    GLuint       _videoW;
    GLuint       _videoH;
    
    GLsizei     _viewScale;
    
}

-(void)displayYUV420pData:(void *)data width:(NSInteger)w height:(NSInteger)h;
@end
