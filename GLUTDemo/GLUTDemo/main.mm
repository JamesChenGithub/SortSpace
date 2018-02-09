////
////  main.m
////  GLUTDemo
////
////  Created by AlexiChen on 2018/2/7.
////  Copyright © 2018年 AlexiChen. All rights reserved.
////
//
//#import <Cocoa/Cocoa.h>
//#include <iostream>
//#include <GLUT/GLUT.h>
//#include <OpenGL/gl.h>
//
//void RenderScene(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glShadeModel(GL_SMOOTH);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    glBegin(GL_TRIANGLES);
//    glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
//    glVertex3f(-100, 200, 0);
//
//    glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
//    glVertex3f(200, 200, 0);
//
//    glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
//    glVertex3f(-200, -70, 0);
//
//    glEnd();
//    glutSwapBuffers();
//}
//
//void SetupRC(void) {
//    glClearColor(1, 1, 0, 0.5);
//}
//
//void changeSize(int w, int h) {
//    GLfloat windowHeight, windowWidth;
//
//    if (h == 0) {
//        h = 1;
//    }
//
//    glViewport(0, 0, w, h);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    windowHeight = windowWidth = 200;
//
//    glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, -1, 1);
//}
//
//int main(int argc, char * argv[]) {
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(600, 600);
//
//    glutCreateWindow("Simple");
//
//    const GLubyte * info = glGetString(GL_VERSION);
//    std::cout << ( const char *)info << std::endl;
//
//    glutReshapeFunc(changeSize);
//    glutDisplayFunc(RenderScene);
//    SetupRC();
//
//    glutMainLoop();
//
//    return 0;
//}

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <thread>
#include <unistd.h>

GLuint createShader(GLenum type, const char * shaderSrc) {
    GLuint shader;
    GLint compiled;
    
    shader = glCreateShader(type);
    
    if (shader == 0) {
        return 0;
    }
    
    glShaderSource(shader, 1, &shaderSrc, NULL);
    
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char * infoLog = (char *)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            
            std::cout << "Error compiling shader: " << infoLog << std::endl;
            
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

GLuint programObject;

bool init() {
    //todo 读文件
    char * vShaderStr =
    "attribute vec4 vPositon;  \n"
    "attribute vec4 aColor;    \n"
    "varying vec4 vertexColor; \n"
    "void main() {             \n"
    "   gl_Position = gl_ModelViewProjectionMatrix * vPositon; \n"
    "   vertexColor = aColor; \n"
    "}"
    ;
    
    char * fShaderStr =
    "varying vec4 vertexColor;"
    "void main() {"
    "   gl_FragColor = vertexColor;"
    "}"
    ;
    
    GLuint vertexShader;
    GLuint fragmentShader;
    
    GLint linked;
    
    vertexShader = createShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = createShader(GL_FRAGMENT_SHADER, fShaderStr);
    
    programObject = glCreateProgram();
    
    if (programObject == 0) {
        return false;
    }
    
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    
    glLinkProgram(programObject);
    
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1) {
            char * infoLog =(char *)malloc(sizeof(char) * infoLen);
            
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            
            std::cout << "Error linking program: " << infoLog << std::endl;
            free(infoLog);
        }
        glDeleteProgram(programObject);
        return false;
    }
    glClearColor(0, 0, 0, 0);
    
    return true;
}

void RenderScene(void) {
    GLfloat vVerties[] = {
        0, 200, 0,
        200, -70, 0,
        -200, -70, 0
    };
    
    GLfloat vertexColor[] = {
        1,0,0,1,
        0,1,0,1,
        0,0,1,1
    };
    
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programObject);
    
    GLint attributePos = glGetAttribLocation(programObject, "vPositon");
    glVertexAttribPointer(attributePos, 3, GL_FLOAT, GL_FALSE, 0, vVerties);
    glEnableVertexAttribArray(attributePos);
    
    GLint colorPos = glGetAttribLocation(programObject, "aColor");
    glVertexAttribPointer(colorPos, 4, GL_FLOAT, GL_FALSE, 0, vertexColor);
    glEnableVertexAttribArray(colorPos);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glutSwapBuffers();
}

void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat windowHeight, windowWidth;
    
    windowHeight = windowWidth = 250;
    glOrtho(-windowHeight, windowHeight, -windowWidth, windowWidth, -1, 1);
    
}

int main(int argc, char * argv[]) {
//
//
//        printf("ffplay adev0.mp4\n");
//        system("ffplay adev0.mp4");
//
//
////    sleep(61);
//
//    std::thread([](){
//        printf("ffplay adev1.mp4\n");
//        system("ffplay adev1.mp4");
//    }).detach();
//
//    int a;
//    std::cin >> a ;
//
//    return 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("Simple");
    
    glutReshapeFunc(changeSize);
    glutDisplayFunc(RenderScene);
    
    init();
    
    glutMainLoop();
    
    return 0;
}

