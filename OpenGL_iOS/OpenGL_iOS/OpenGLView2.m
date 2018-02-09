//
//  OpenGLView2.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "OpenGLView2.h"

#include "GLESUtil.h"

@implementation OpenGLView2


- (void)dealloc
{
    glDeleteProgram(_programHandle);
    _programHandle = 0;
}
- (void)setupProgram
{
    
    _programHandle = glCreateProgram();
    
    if (!_programHandle)
    {
        NSLog(@"Failed to create program");
        exit(1);
    }
    
    NSString *vp = [[NSBundle mainBundle] pathForResource:@"VertexShader" ofType:@"glsl"];
    NSString *fp = [[NSBundle mainBundle] pathForResource:@"FragmentShader" ofType:@"glsl"];
    
    GLuint vs = [GLESUtil loadShader:GL_VERTEX_SHADER withFilePath:vp];
    GLuint fs = [GLESUtil loadShader:GL_FRAGMENT_SHADER withFilePath:fp];
    
    
    glAttachShader(_programHandle, vs);
    glAttachShader(_programHandle, fs);
    
    
    glLinkProgram(_programHandle);
    
    GLint linked = 0;
    
    glGetProgramiv(_programHandle, GL_LINK_STATUS, &linked);
    
    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 0)
        {
            char *infoLog = (char *)malloc(sizeof(char) * (infoLen + 10));
            memset(infoLog, 0, infoLen + 10);
            glGetProgramInfoLog(_programHandle, infoLen, NULL, infoLog);
            
            NSLog(@"Error compiling shader : %s", infoLog);
            free(infoLog);
        }
        
        glDeleteProgram(_programHandle);
        _programHandle = 0;
        return;
    }
    
    
    glUseProgram(_programHandle);
    
    _positionSlot = glGetAttribLocation(_programHandle, "vPosition");
    
    
}

- (void)render
{
    const CGFloat *com =  CGColorGetComponents(self.backgroundColor.CGColor);
    CGFloat R = com[0];
    CGFloat G = com[1];
    CGFloat B = com[2];
    CGFloat A = com[3];
    glClearColor(R, G, B, A);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    CGFloat scale  = [UIScreen mainScreen].scale;
    glViewport(0, 0, self.bounds.size.width * scale , self.bounds.size.height * scale);
    
//    GLfloat vertics[] = {
//        0.5, 0, 0,
//        0, 0.5, 0,
//        -0.5, 0, 0
//    };
    
    GLfloat vertics[] = {
        0.25, 0.5, 0,
        0, 0.75, 0,
        -0.25, 0.5, 0
    };
    
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, vertics);
    
    glEnableVertexAttribArray(_positionSlot);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(_positionSlot);
    
    
    
    GLfloat vertics2[] = {
        0.25, 0, 0,
        0, 0.25, 0,
        -0.25, 0, 0,
        0.25, 0, 0,
    };
    
    
    
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, vertics2);
    
    glEnableVertexAttribArray(_positionSlot);
    
    
    glLineWidth(scale * 2);
    
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 1, 2);
    glDrawArrays(GL_LINES, 2, 2);
    
    glDisableVertexAttribArray(_positionSlot);
    
    
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    
}

- (void)doInitGL
{
    [super doInitGL];
    [self setupProgram];
}
@end
