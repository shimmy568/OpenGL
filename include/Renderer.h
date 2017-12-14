#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <Drawable.h>

class Renderer
{
  public:
    Renderer();
    ~Renderer();
    void drawObject(Drawable d);
};

#endif