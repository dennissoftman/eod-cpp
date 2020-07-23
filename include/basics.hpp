#ifndef BASICS_HPP
#define BASICS_HPP

#include <SDL2/SDL.h>
#include "primitives.hpp"

class GameWindow;

class Object2D
{
public:
    Object2D(const vec2 &_pos=vec2(), const vec2 &_dim=vec2());

    virtual void draw();

    virtual void setTexture(SDL_Texture *tex);

private:
    vec2 pos, dim;

    SDL_Texture *m_texture;
};

class Resource : public Object2D
{
    void draw() override;
};

#endif
