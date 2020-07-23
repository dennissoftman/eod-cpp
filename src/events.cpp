#include "include/events.hpp"

EventProcessor::EventProcessor()
{
    mouseclick_binds.clear();
    keyup_binds.clear();
    keydown_binds.clear();
}

void EventProcessor::update()
{
    while(SDL_PollEvent(&last_event))
    {
        uint8_t mbtn = (last_event.button.button % 5);
        uint8_t key = (last_event.key.keysym.scancode % 256);

        if(last_event.type == SDL_QUIT)
        {
            if(bound_functions.find(last_event.type) == bound_functions.end())
                continue;

            for(event_fptr ptr : bound_functions[last_event.type])
                ptr(&last_event);
        }
        else if(last_event.type == SDL_MOUSEBUTTONDOWN)
        {
            mouse_btns[mbtn] = true;
            for(event_fptr ptr : mouseclick_binds)
                ptr(&last_event);
        }
        else if(last_event.type == SDL_MOUSEBUTTONUP)
        {
            mouse_btns[mbtn] = false;
        }
        else if(last_event.type == SDL_KEYDOWN)
        {
            kbd_keys[key] = true;
            if(keydown_binds.find(key) == keydown_binds.end())
                continue;

            for(event_fptr ptr : keydown_binds[key])
                ptr(&last_event);
        }
        else if(last_event.type == SDL_KEYUP)
        {
            kbd_keys[key] = false;
            if(keyup_binds.find(key) == keyup_binds.end())
                continue;

            for(event_fptr ptr : keyup_binds[key])
                ptr(&last_event);
        }
    }
}

bool EventProcessor::keyUp(int key) const
{
    return !keyDown(key);
}

bool EventProcessor::keyDown(int key) const
{
    return kbd_keys[key % 256];
}

bool EventProcessor::mouseUp(int btn) const
{
    return !mouseDown(btn);
}

bool EventProcessor::mouseDown(int btn) const
{
    return mouse_btns[btn % 5];
}

void EventProcessor::bindEvent(int ev_type, event_fptr fptr)
{
    bound_functions[ev_type].push_back(fptr);
}

void EventProcessor::bindKey(int key, event_fptr fptr, bool keyup)
{
    if(keyup)
        keyup_binds[key].push_back(fptr);
    else
        keydown_binds[key].push_back(fptr);
}

void EventProcessor::bindMouseClick(event_fptr fptr)
{
    mouseclick_binds.push_back(fptr);
}
