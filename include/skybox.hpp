#pragma once

#include <texture.hpp>
#include <filesystem.hpp>
#include <context.hpp>

namespace GraphicsEngine {
    class Skybox {
    private:
        std::shared_ptr<Texture> cubemap;
    public:
        explicit Skybox(const fs::path& path);
        virtual ~Skybox() = default;

        virtual void draw(Context& context);
    };
}