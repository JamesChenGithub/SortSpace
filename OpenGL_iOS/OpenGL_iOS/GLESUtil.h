//
//  GLESUtil.h
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <OpenGLES/ES2/gl.h>

@interface GLESUtil : NSObject

+ (GLuint)loadShader:(GLenum)type withString:(NSString *)string;

+ (GLuint)loadShader:(GLenum)type withFilePath:(NSString *)path;



@end
