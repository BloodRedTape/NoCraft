#ifndef LAYERS_HPP
#define LAYERS_HPP

#include "platform/events.hpp"
#include "core/push_array.hpp"

using namespace StraitX;


struct Layer{
    Layer **Storage = nullptr;    

    virtual ~Layer(){
        (void)0;
    }

    void PopSelf(){
        Assert(Storage);
        *Storage = nullptr;
    }

    virtual void OnUpdate(float dt){
        (void)dt;
    }

    virtual void OnRender(){
        (void)0;
    }
    //true means handled
    virtual bool OnEvent(const Event &e){
        (void)e;
        return false;
    }
};


#endif//LAYERS_HPP