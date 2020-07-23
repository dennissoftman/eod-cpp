#include "include/basics.hpp"
#include "include/core.hpp"

Object2D::Object2D(const vec2 &_pos, const vec2 &_dim)
    : pos(_pos), dim(_dim),
      m_texture(nullptr)
{

}

void Object2D::draw()
{
    SDL_Rect trect;
    trect.x = pos.x();
    trect.y = pos.y();
    trect.w = dim.x();
    trect.h = dim.y();

    SDL_RenderCopy(GameWindow::sharedPtr->getRenderer(), m_texture, NULL, &trect);
}

void Object2D::setTexture(SDL_Texture *tex)
{
    m_texture = tex;
}

void Resource::draw()
{
    // for now
    Object2D::draw();
}
