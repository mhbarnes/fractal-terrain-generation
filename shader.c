#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "vecmath.h"
#include "shader.h"

// Loads shaders as text files
char* loadTextFile(const char* filename) {
    printf("loading files\n");
    fflush(stdout);

    FILE* file = fopen(filename, "r");
    long size;
    char* text;
  
    fseek(file, 0, SEEK_END);
    size = ftell(file); 
    text = (char*) malloc(size);
    rewind(file);

    if (fread(text, sizeof(char), size, file) == 0) {
        fprintf(stderr, "cannot load file\n");
        exit(1);
    }

    text[size] = '\0';

    char* ch;
    while ((ch = strchr(text, '\r'))) {
        text[ch-text+1] = ' ';
    }

    fclose(file);

    return text;
}

// Prints program log to print any errors or successes
void printProgramLog(shaderprogram program) {
    int length, written;
    char* log;

    glGetProgramiv(program.prog, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        log = (char *) malloc(length+1);
        log[length] = '\0';
        glGetProgramInfoLog(program.prog, length, &written, log);
        printf("%s\n", log);
        free(log);
    }
}

// Prints shader log as it gets compiled
void printShaderLog(GLuint shader) {
    int length, written;
    char* log;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        log = (char *) malloc(length+1);
        log[length] = '\0';
        glGetShaderInfoLog(shader, length, &written, log);
        printf("%s\n", log);
        free(log);
    }
}

// Loads shaders into program
void loadShaders(shaderprogram *program, const char* vname, const char* fname) {
    char *vs=NULL, *fs=NULL;
    const char *cvs, *cfs;
    
    printf("making a shader\n");
    fflush(stdout);

    program->vert = glCreateShader(GL_VERTEX_SHADER);
    program->frag = glCreateShader(GL_FRAGMENT_SHADER);

    printf("loading the files\n");
    fflush(stdout);

    vs = loadTextFile(vname);
    fs = loadTextFile(fname);

    cvs = vs, cfs = fs;

    printf("starting compile\n");
    fflush(stdout);

    glShaderSource(program->vert, 1, &cvs, NULL);
    glShaderSource(program->frag, 1, &cfs, NULL);

    glCompileShader(program->vert);
    glCompileShader(program->frag);

    printShaderLog(program->vert);
    printShaderLog(program->frag);
    

    printf("compiled\n");
    fflush(stdout);

    program->prog = glCreateProgram();
    glAttachShader(program->prog, program->vert);
    glAttachShader(program->prog, program->frag);

    printf("linking\n");
    glLinkProgram(program->prog);
}

// Loads mandelbrot variables into shaders
void loadMandelbulbVars(shaderprogram program, vec3f fov, vec3f camerapos,
    vec3f color, float step, int bail, float power, float phi, float theta, 
	vec2f resolution, int multisampling, vec3f lightpos, float intensity,
	vec3f horizontalAxis, vec3f verticalAxis, vec3f depthAxis, float wVar,
	int orbittrap) {
    
	GLint fov_loc, camerapos_loc, color_loc, step_loc, bail_loc, power_loc,
		phi_loc, theta_loc, resolution_loc, multisampling_loc, lightpos_loc,
		intensity_loc, horizontalAxis_loc, verticalAxis_loc, depthAxis_loc,
		wVar_loc, orbittrap_loc;

    fov_loc = glGetUniformLocation(program.prog, "FOV");
    camerapos_loc = glGetUniformLocation(program.prog, "camerapos");
    color_loc = glGetUniformLocation(program.prog, "color");
    step_loc = glGetUniformLocation(program.prog, "step");
    bail_loc = glGetUniformLocation(program.prog, "bail");
    power_loc = glGetUniformLocation(program.prog, "power");
    phi_loc = glGetUniformLocation(program.prog, "phi");
    theta_loc = glGetUniformLocation(program.prog, "theta");
    resolution_loc = glGetUniformLocation(program.prog, "resolution");
    multisampling_loc = glGetUniformLocation(program.prog, "multisampling");
    lightpos_loc = glGetUniformLocation(program.prog, "lightpos");
    intensity_loc = glGetUniformLocation(program.prog, "intensity");
	horizontalAxis_loc = glGetUniformLocation(program.prog, "horizontalAxis");
	verticalAxis_loc = glGetUniformLocation(program.prog, "verticalAxis");
	depthAxis_loc = glGetUniformLocation(program.prog, "depthAxis");
	wVar_loc = glGetUniformLocation(program.prog, "wVar");
	orbittrap_loc = glGetUniformLocation(program.prog, "orbittrap");

    //printf("************ %f, %f, %f", fov.x, fov.y, fov.z);

    glUniform3f(fov_loc, fov.x, fov.y, fov.z);
    glUniform3f(camerapos_loc, camerapos.x, camerapos.y, camerapos.z);
    glUniform3f(color_loc, color.x, color.y, color.z);
    glUniform1f(step_loc, step);
    glUniform1i(bail_loc, bail);
    glUniform1f(power_loc, power);
    glUniform1f(phi_loc, phi);
    glUniform1f(theta_loc, theta);
    glUniform2f(resolution_loc, resolution.x, resolution.y);
    glUniform1i(multisampling_loc, multisampling);
    glUniform3f(lightpos_loc, lightpos.x, lightpos.y, lightpos.z);
    glUniform1f(intensity_loc, intensity);
	glUniform3f(horizontalAxis_loc, horizontalAxis.x, horizontalAxis.y, horizontalAxis.z);
	glUniform3f(verticalAxis_loc, verticalAxis.x, verticalAxis.y, verticalAxis.z);
	glUniform3f(depthAxis_loc, depthAxis.x, depthAxis.y, depthAxis.z);
	glUniform1f(wVar_loc, wVar);
	glUniform1i(orbittrap_loc, orbittrap);
}

// Loads program to output mandelbrot to viewing window
void loadMandelbulbProgram(shaderprogram* program, vec3f fov, vec3f camerapos,
    vec3f color, float step, int bail, float power, float phi, float theta,
	vec2f resolution, int multisampling, vec3f lightpos, float intensity,
	vec3f horizontalAxis, vec3f verticalAxis, vec3f depthAxis, float wVar,
	int orbittrap) {

    //loadShaders(program, "shaders/mandelbulb_shader.vert", "shaders/quaternion_shader.frag");
	loadShaders(program, "shaders/mandelbulb_shader.vert", "shaders/mandelbulb_shader.frag");

    glUseProgram(program->prog);

    loadMandelbulbVars(*program, fov, camerapos, color, step, bail, power, phi,
		theta, resolution, multisampling, lightpos, intensity, horizontalAxis,
		verticalAxis, depthAxis, wVar, orbittrap);
}

//Load the display texture shader
void loadTextureProgram(shaderprogram* program, GLuint texture, GLuint *sampler) {
    loadShaders(program, "shaders/texture_shader.vert", "shaders/texture_shader.frag");
    
    glUseProgram(program->prog);
    
    //glGenSamplers(1, sampler);

    loadTextureVars(*program, texture, *sampler);
}

//Load the texture to the display texture shader
void loadTextureVars(shaderprogram program, GLuint texture, GLuint sampler) {
    GLint texture_loc;

    texture_loc = glGetUniformLocation(program.prog, "drawtexture");

    glUniform1i(texture_loc, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glBindSampler(0, sampler);

}
