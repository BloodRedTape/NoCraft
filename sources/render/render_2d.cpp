#include "render_2d.hpp"
#include "graphics/renderer_2d.hpp"
#include "servers/display_server.hpp"

static Renderer2D *s_Impl;

Vector2f (&Render2D::DefaultTextureCoords)[4] = s_Impl->s_DefaultTextureCoords;

void Render2D::Init(){
    s_Impl = new Renderer2D(DisplayServer::Window.Pass());
}

void Render2D::Begin(){
    s_Impl->BeginScene(DisplayServer::Window.CurrentFramebuffer());
}

void Render2D::End(){
    s_Impl->EndScene();
}

void Render2D::Flush(){
    End();
    Begin();
}

void Render2D::Clear(Color color, float depth){
    DisplayServer::Window.ClearColorBuffer(color);
    DisplayServer::Window.ClearDepthBuffer(depth);
}

void Render2D::SwapBuffers(){
    DisplayServer::Window.SwapBuffers();
}

void Render2D::DrawRect(Vector2i position, Vector2i size, const Color &color, const Texture &texture, Vector2f (&texture_coords)[4]){
    s_Impl->DrawRect(position, size, color, texture, texture_coords);
}

void Render2D::DrawRect(Vector2i position, Vector2i size, const Color &color){
    s_Impl->DrawRect(position, size, color);
}

void Render2D::DrawRect(Vector2i position, Vector2i size, const Texture &texture, Vector2f (&texture_coords)[4]){
    s_Impl->DrawRect(position, size, texture, texture_coords);
}
    
