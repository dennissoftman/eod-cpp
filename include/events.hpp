#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SDL2/SDL.h>
#include <map>
#include <vector>

typedef void (*event_fptr)(SDL_Event *ev);

class EventProcessor
{
public:
    EventProcessor();
    void update();

    bool keyUp(int key) const;
    bool keyDown(int key) const;

    bool mouseUp(int btn) const;
    bool mouseDown(int btn) const;

    void bindEvent(int ev_type, event_fptr fptr);
    void bindKey(int key, event_fptr fptr, bool keyup=false);
    void bindMouseClick(event_fptr fptr);

private:
    SDL_Event last_event;

    bool kbd_keys[256];
    bool mouse_btns[4];

    std::map<int, std::vector<event_fptr>> bound_functions;
    std::vector<event_fptr> mouseclick_binds;
    std::map<int, std::vector<event_fptr>> keydown_binds;
    std::map<int, std::vector<event_fptr>> keyup_binds;
};

#endif
