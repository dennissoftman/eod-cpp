#ifndef CORE_HPP
#define CORE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "config.hpp"
#include "basics.hpp"

#define GAME_ERROR(s_a, s_t) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, s_a, s_t, NULL)

class EventProcessor;

class GameWindow
{
public:
    GameWindow();

    void init();
    int run();
    void draw();
    void quit();

    void cleanup();
    void bindEvents();
    void load_configs();
    void load_resources();

    // helper functions
    SDL_Renderer *getRenderer() const;
    //

    // event binded functions
    static void quit_event(SDL_Event *qev);
    //

    static GameWindow *sharedPtr;
private:
    uint16_t m_scrwidth, m_scrheight;
    SDL_Window *m_sdlwindow;
    SDL_Renderer *m_sdlrend;
    bool m_quit;

    EventProcessor *m_processor;

    //
    SDL_Texture *m_bgtex;
    std::vector<Object2D*> m_game_objs;
};

#endif
