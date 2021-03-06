//
//  OpenGLView.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "OpenGLView.h"

@implementation OpenGLView

- (void)dealloc
{
    [self destoryGL];
    NSLog(@"%@ Dealloc", [self class]);
}

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)setupLayer
{
    [self setContentScaleFactor:[UIScreen mainScreen].scale];
    _eaglLayer = (CAEAGLLayer *)self.layer;
    _eaglLayer.opaque = YES;
    
    _eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                     [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    [self destoryGL];
    
    [self setupRenderBuffer];
    
    [self setupFrameBuffer];
    
    [self doRender];
}

- (void)setupContext
{
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context)
    {
        NSLog(@"Failed to initialize opengl es2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context])
    {
        NSLog(@"Failed to set current context");
        exit(1);
    }
}

- (void)setupRenderBuffer
{
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)destoryGL
{
    glDeleteFramebuffers(1, &_frameBuffer);
    _frameBuffer = 0;
    
    glDeleteRenderbuffers(1, &_colorRenderBuffer);
    _colorRenderBuffer = 0;
}

- (void)setBackgroundColor:(UIColor *)backgroundColor
{
    [super setBackgroundColor:backgroundColor];
    [self doRender];
}

- (void)doRender
{
    [self preRender];
    [self render];
}

- (void)render
{
     [_context presentRenderbuffer:GL_RENDERBUFFER];
}
- (void)preRender
{
    int numComponents = CGColorGetNumberOfComponents(self.backgroundColor.CGColor);
    if (numComponents == 4)
    {
        const CGFloat *com =  CGColorGetComponents(self.backgroundColor.CGColor);
        CGFloat R = com[0];
        CGFloat G = com[1];
        CGFloat B = com[2];
        CGFloat A = com[3];
        glClearColor(R, G, B, A);
    }
    else
    {
        glClearColor(0.2, 0.2, 0.2, 0.3);
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    CGFloat scale  = [UIScreen mainScreen].scale;
    glViewport(0, 0, self.bounds.size.width * scale , self.bounds.size.height * scale);
    
   
    
}

- (void)setupFrameBuffer
{
    glGenRenderbuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
}

- (void)doInitGL
{
    [self setupLayer];
    [self setupContext];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame])
    {
        [self doInitGL];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    if (self = [super initWithCoder:aDecoder])
    {
        [self doInitGL];
    }
    return self;
}
@end
