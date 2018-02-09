//
//  GLESUtil.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "GLESUtil.h"

@implementation GLESUtil
+ (GLuint)loadShader:(GLenum)type withString:(NSString *)string
{
    GLuint shader = glCreateShader(type);
    if (shader == 0)
    {
        NSLog(@"Error : failed to create shader.");
        return 0;
    }
    
    const char *shaderStr = [string UTF8String];
    
    glShaderSource(shader, 1, &shaderStr, NULL);
    
    glCompileShader(shader);
    
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 0)
        {
            char *infoLog = (char *)malloc(sizeof(char) * (infoLen + 10));
            memset(infoLog, 0, infoLen + 10);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            
            NSLog(@"Error compiling shader : %s", infoLog);
            free(infoLog);
        }
        
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

+ (GLuint)loadShader:(GLenum)type withFilePath:(NSString *)path
{
    NSError *error = NULL;
    
    NSString *shaderStirng = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
    
    if(!shaderStirng)
    {
        NSLog(@"Error : loading shader file: %@  Error: %@", path, error);
        return 0;
    }
    return [self loadShader:type withString:shaderStirng];
}
@end
