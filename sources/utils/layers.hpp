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

    virtual void OnBecomeTop(){
        (void)0;
    }

    virtual void OnStopBeingTop(){
        (void)0;
    }
};

class LayerStack{
private:
    PushArray<Layer *, 16> m_Layers;
public:
    void PushLayer(Layer *layer){
        if(Size())
            m_Layers[Size()-1]->OnStopBeingTop();
        m_Layers.Push(layer);
        layer->OnBecomeTop();
    }

    Layer *PopLayer(){
        Layer *layer = m_Layers[m_Layers.Size() - 1];
        m_Layers.Pop();
        if(Size())
            m_Layers[Size()-1]->OnBecomeTop();
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
    size_t Size(){
        return m_Layers.Size();
    }
};

#endif//LAYERS_HPP