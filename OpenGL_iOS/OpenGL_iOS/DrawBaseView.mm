//
//  DrawBaseView.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "DrawBaseView.h"

@implementation DrawItem

- (void)dealloc
{
    delete [] _vetexs;
    _vetexs = NULL;
}

+ (instancetype)draw:(GLfloat *)vs mode:(GLenum)mode vetexCount:(GLuint)count
{
    
    if (vs)
    {
        DrawItem *item = [[DrawItem alloc] init];
        item->_vetexs =  new GLfloat[3 * count];
        memcpy(item->_vetexs, vs, sizeof(GLfloat) * count * 3);
        item->_vetexcount = count;
        item->_drawMode = mode;
        return item;
        
    }
    return nil;
}

- (NSString *)description
{
    NSMutableString *str = [NSMutableString string];
    
    [str appendFormat:@"vetexcount = %d, drawMode = %d , vetexs = {\n", _vetexcount, _drawMode];
    
    for (int i = 0 ; i < sizeof(GLfloat) * 3 * _vetexcount; i++)
    {
        [str appendFormat:@"%0.3f, ", (GLfloat)_vetexs[i]];
    }
    [str appendString:@"}"];
    return str;
}

@end

@implementation DrawBaseView



- (void)draw:(GLfloat *)vs mode:(GLenum)mode vetexCount:(GLuint)count
{
    DrawItem *item = [DrawItem draw:vs mode:mode vetexCount:count];
    
    [self drawItem:item];
}

- (void)drawItem:(DrawItem *)item
{
    if (item)
    {
        if (!_drawItems)
        {
            _drawItems = [NSMutableArray array];
        }
        
        [_drawItems addObject:item];
    }
    
    [self doRender];
}

- (void)drawItems:(NSArray *)items
{
    if (items.count > 0)
    {
        if (!_drawItems)
        {
            _drawItems = [NSMutableArray array];
        }
        
        [_drawItems addObjectsFromArray:items];
    }
    
    [self doRender];
}

- (void)render
{
    
    for (DrawItem *item in _drawItems)
    {
        glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, item.vetexs);
        
        glEnableVertexAttribArray(_positionSlot);
        
        glDrawArrays(item.drawMode, 0, item.vetexcount);
        
        glDisableVertexAttribArray(_positionSlot);
    }
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    
}


@end
