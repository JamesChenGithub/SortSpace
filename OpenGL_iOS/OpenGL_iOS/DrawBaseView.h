//
//  DrawBaseView.h
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "OpenGLView2.h"

@interface DrawItem : NSObject
{
    GLfloat *_vetexs;
    GLuint _vetexcount;
    GLenum _drawMode;
}

@property (nonatomic, readonly) GLfloat *vetexs;
@property (nonatomic, readonly) GLuint vetexcount;
@property (nonatomic, readonly) GLenum drawMode;

//+ (instancetype)draw:(GLfloat *)vs mode:(GLenum)mode;
+ (instancetype)draw:(GLfloat *)vs mode:(GLenum)mode vetexCount:(GLuint)count;

@end

@interface DrawBaseView : OpenGLView2


@property (nonatomic, strong) NSMutableArray *drawItems;

- (void)draw:(GLfloat *)vs mode:(GLenum)mode vetexCount:(GLuint)count;

- (void)drawItem:(DrawItem *)item;
- (void)drawItems:(NSArray *)items;

@end
