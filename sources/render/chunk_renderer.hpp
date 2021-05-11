#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include "core/math/vector3.hpp"
#include "graphics/api/graphics_pipeline.hpp"
#include "graphics/render_window.hpp"
#include "graphics/color.hpp"
#include "mesh.hpp"
#include "texture_atlas.hpp"
#include "camera.hpp"

using namespace StraitX;

struct Vertex{
    Vector3f a_Position;
    Vector2f a_TexCoord;

    static VertexAttribute s_Attributes[];
};

struct Uniform{
    Matrix4f u_Projection;
    Matrix4f u_View;
};

class ChunkRenderer{
private:
    RenderWindow &m_Window;
    Vector2u m_WindowSize;

    Shader *m_Shaders[2] = {};
    GraphicsPipeline *m_Pipeline = nullptr;

    CPUBuffer m_StagingUniform;
    GPUBuffer m_UniformBuffer;
public:
    ChunkRenderer();

    ~ChunkRenderer();

    void BeginScene(const Camera &camera);

    void EndScene();

    void Draw(const Mesh &mesh);
};

#endif//CHUNK_RENDERER_HPP