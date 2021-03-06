#pragma once

#include <model.hpp>
#include <texture_loader.hpp>
#include <model_loader.hpp>
#include <skybox.hpp>

#define ASSETS_DIR "../assets/"

namespace GraphicsEngine {
    template<typename T>
    class ResourceContainer {
    private:
        std::unordered_map<std::string, std::shared_ptr<T>> resource;
    public:
        const auto& get(const std::string& name) const {
            try {
                return resource.at(name);
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("No such resource called " + name);
            }
        }

        void add(const std::string& name, std::shared_ptr<T> res) {
            auto result = resource.emplace(name, std::move(res));
            if (!result.second) {
                throw std::runtime_error("Failed to add resource " + std::string(typeid(T).name()) + name + ", already exists.");
            }
        }

        [[nodiscard]] bool isExist(const std::string& name) const noexcept {
            return resource.find(name) != resource.end();
        }
    };

    struct Assets {
        ResourceContainer<AbstractModel> models;
        ResourceContainer<AbstractMesh> meshes;
        ResourceContainer<Texture> textures;
        ResourceContainer<Material> materials;
        ResourceContainer<Skybox> skyboxes;

        void load();
    };

    inline Assets assets;
}