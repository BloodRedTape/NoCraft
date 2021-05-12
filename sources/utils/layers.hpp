#ifndef LAYERS_HPP
#define LAYERS_HPP

#include "platform/events.hpp"
#include "core/push_array.hpp"

using namespace StraitX;

struct Layer{
    virtual ~Layer(){
        (void)0;
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

class LayerStack{
private:
    PushArray<Layer *, 16> m_Layers;
public:
    void PushLayer(Layer *layer){
        m_Layers.Push(layer);
    }

    Layer *PopLayer(){
        Layer *layer = m_Layers[m_Layers.Size() - 1];
        m_Layers.Pop();
        return layer;
    }

    void OnEvent(const Event &e){
        for(int i = m_Layers.Size() - 1; i>=0; i--)
            if(m_Layers[i]->OnEvent(e))return;
    }

    void OnRender(){
        for(Layer *layer: m_Layers)
            layer->OnRender();
    }

    void OnUpdate(float dt){
        if(m_Layers.Size())
            m_Layers[m_Layers.Size()-1]->OnUpdate(dt);
    }
};

#endif//LAYERS_HPP