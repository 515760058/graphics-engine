#include <shader_storage.hpp>
#include <shader_compiler.hpp>

using namespace GraphicsEngine;

bool GraphicsEngine::operator<(const ShaderKey& lhs, const ShaderKey& rhs) noexcept {
    return std::tie(lhs.material_type, lhs.model_type, lhs.material_index) < std::tie(rhs.material_type, rhs.model_type, rhs.material_index);
}

const std::shared_ptr<ShaderProgram>& ShaderStorage::get(const std::string& name) const {
    try {
        return shaders.at(name);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("No such shader " + name);
    }
}

const std::shared_ptr<ShaderProgram>& ShaderStorage::get(MaterialShaderType material_type, ModelShaderType model_type, uint64_t material_index) const {
    try {
        return material_shaders.at({material_type, model_type, material_index});
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("No such material shader");
    }
}

void ShaderStorage::add(std::string name, std::shared_ptr<ShaderProgram> program) noexcept {
    shaders.emplace(std::move(name), std::move(program));
}

void ShaderStorage::add(MaterialShaderType material_type, ModelShaderType model_type, uint64_t material_index, std::shared_ptr<ShaderProgram> program) noexcept {
    material_shaders.emplace(ShaderKey{material_type, model_type, material_index}, std::move(program));
}

bool ShaderStorage::isExist(MaterialShaderType material_type, ModelShaderType model_type, uint64_t material_index) const noexcept {
    return material_shaders.find({material_type, model_type, material_index}) != material_shaders.end();
}

const std::shared_ptr<ShaderProgram>& ShaderStorage::get(const UniqueSpriteEmitter &emitter_type) const {
    try {
        return sprite_emitter_shaders.at(emitter_type);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("No such sprite emitter shader");
    }
}

const std::shared_ptr<ShaderProgram>& ShaderStorage::get(const UniqueMeshEmitter &emitter_type) const {
    try {
        return mesh_emitter_shaders.at(emitter_type);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("No such mesh emitter shader");
    }
}

void ShaderStorage::add(const UniqueSpriteEmitter& emitter_type, std::shared_ptr<ShaderProgram> program) noexcept {
    sprite_emitter_shaders.emplace(emitter_type, std::move(program));
}

void ShaderStorage::add(const UniqueMeshEmitter& emitter_type, std::shared_ptr<ShaderProgram> program) noexcept {
    mesh_emitter_shaders.emplace(emitter_type, std::move(program));
}

void ShaderStorage::initialize() {
    add("blur", ShaderCompiler::compile(SHADER_DIR "postprocessing/blur"));
    add("brightness", ShaderCompiler::compile(SHADER_DIR "postprocessing/brightness"));
    add("postprocess", ShaderCompiler::compile(SHADER_DIR "postprocessing/postprocess"));
    add("skybox", ShaderCompiler::compile(SHADER_DIR "pipeline/skybox"));
}
