//
//  OpenGLView.h
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface OpenGLView : UIView
{
@protected
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    
}

- (void)doInitGL;


@end
