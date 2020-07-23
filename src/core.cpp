#include "include/core.hpp"
#include "include/events.hpp"
#include <yaml-cpp/yaml.h>

GameWindow *GameWindow::sharedPtr = nullptr;

GameWindow::GameWindow()
    : m_scrwidth(GAME_WIDTH), m_scrheight(GAME_HEIGHT),
      m_sdlwindow(nullptr), m_sdlrend(nullptr), m_quit(false)
{
    sharedPtr = this;
}

void GameWindow::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
    {
        GAME_ERROR("SDL error", "Failed to init SDL! Check your drivers!");
        exit(-1);
    }

    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        GAME_ERROR("SDL_image error", "Failed to init SDL_image!");
        exit(-1);
    }

//    m_sdlwindow = SDL_CreateWindow(GAME_TITLE,
//                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//                                   m_scrwidth, m_scrheight,
//                                   SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
//    if(m_sdlwindow == nullptr)
    m_sdlwindow = SDL_CreateWindow(GAME_TITLE,
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   m_scrwidth, m_scrheight,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(m_sdlwindow == nullptr)
    {
        GAME_ERROR("SDL error", "Failed to create SDL window! Check your drivers!");
        exit(-1);
    }

    m_sdlrend = SDL_CreateRenderer(m_sdlwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_sdlrend == nullptr)
    {
        fprintf(stdout, "{W} SDL error: %s\n", SDL_GetError());
        fprintf(stdout, "{W} Fallback to SW renderer\n");
        m_sdlrend = SDL_CreateRenderer(m_sdlwindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    }
    if(m_sdlrend == nullptr)
    {
        GAME_ERROR("SDL error", "Failed to create SDL renderer! Check your drivers!");
        exit(-1);
    }
    SDL_GL_SetSwapInterval(1);

    //

    m_processor = new EventProcessor;

    bindEvents();

    load_resources();
}

int GameWindow::run()
{
    SDL_SetRenderDrawColor(m_sdlrend, 0, 0, 0, 0xff);
    do
    {
        m_processor->update();
        draw();
    } while(!m_quit);

    cleanup();
    return 0;
}

void GameWindow::draw()
{
    SDL_RenderClear(m_sdlrend);

    SDL_RenderCopy(m_sdlrend, m_bgtex, nullptr, nullptr);

    for(Object2D *obj : m_game_objs)
        obj->draw();

    SDL_RenderPresent(m_sdlrend);
}

void GameWindow::quit()
{
    m_quit = true;
}

void GameWindow::cleanup()
{
    delete m_processor;

    SDL_DestroyRenderer(m_sdlrend);
    SDL_DestroyWindow(m_sdlwindow);

    IMG_Quit();
    SDL_Quit();
}

void GameWindow::bindEvents()
{
    m_processor->bindEvent(SDL_QUIT, GameWindow::quit_event);
}

void GameWindow::load_configs()
{
    // collectibles
    YAML::Node root = YAML::LoadFile("cfg/res.yml");

    try
    {
        for(auto it = root.begin(); it != root.end(); it++)
        {
            std::string r_type = (*it)["type"].as<std::string>();
            std::string r_name = (*it)["name"].as<std::string>();
        }
    } catch(YAML::ParserException &e)
    {
        fprintf(stderr, "YAML Error: %s\n", e.what());
    }
    //
}

void GameWindow::load_resources()
{
    load_configs();

    // Background
    SDL_Texture *grass_texs[4];
    char tex_str[32];
    for(int i=0; i < 3; i++)
    {
        sprintf(tex_str, "img/grass_%d.png", i);
        grass_texs[i] = IMG_LoadTexture(m_sdlrend, tex_str);
    }
    m_bgtex = SDL_CreateTexture(m_sdlrend,
                                SDL_PIXELFORMAT_RGB888,
                                SDL_TEXTUREACCESS_TARGET,
                                m_scrwidth, m_scrheight);
    if(m_bgtex == nullptr)
        exit(-1);

    SDL_Rect target_rect;
    target_rect.w = 76;
    target_rect.h = 38;

    SDL_SetRenderTarget(m_sdlrend, m_bgtex);
    for(int i=0; i < 39; i++)
    {
        for(int j=0; j < 18; j++)
        {
            target_rect.x = j * 76 + (76 >> 1) * (i % 2 - 1);
            target_rect.y = (38>>1) * (i - 1);
            SDL_RenderCopy(m_sdlrend, grass_texs[rand() % 3], nullptr, &target_rect);
        }
    }
    SDL_SetRenderTarget(m_sdlrend, nullptr);

    for(int i=0; i < 3; i++)
        SDL_DestroyTexture(grass_texs[i]);
    // =========================================================================================

    Object2D *obj = new Object2D(vec2(100, 100), vec2(96, 96));
    obj->setTexture(IMG_LoadTexture(m_sdlrend, "img/camp_0.png"));
    m_game_objs.push_back(obj);
}

SDL_Renderer *GameWindow::getRenderer() const
{
    return m_sdlrend;
}

void GameWindow::quit_event(SDL_Event *qev)
{
    E_UNUSED(qev);
    GameWindow::sharedPtr->quit();
}

