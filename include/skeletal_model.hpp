#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <model.hpp>
#include <skinned_mesh.hpp>
#include <tree.hpp>

namespace GraphicsEngine {
    template <typename T>
    struct KeyFrame {
        T data;
        double time;

        KeyFrame(T data, double time) noexcept
            : data{std::move(data)}, time(time) { }
    };

    struct AnimationNode {
        std::vector<KeyFrame<glm::vec3>> positions;
        std::vector<KeyFrame<glm::fquat>> rotations;
        std::vector<KeyFrame<glm::vec3>> scales;
        Bone &bone;

        AnimationNode(decltype(positions) positions, decltype(rotations) rotations, decltype(scales) scales, Bone &bone) noexcept;

        [[nodiscard]] auto findPositionKeyframe(double anim_time) const;
        [[nodiscard]] auto findRotationKeyframe(double anim_time) const;
        [[nodiscard]] auto findScalingKeyframe(double anim_time) const;
        [[nodiscard]] auto positionLerp(double anim_time) const;
        [[nodiscard]] glm::fquat rotationLerp(double anim_time) const;
        [[nodiscard]] auto scalingLerp(double anim_time) const;
    };

    struct Animation {
        std::string name;
        double duration;
        double tps;
        std::vector<AnimationNode> nodes;

        Animation(std::string name, double duration, double tps, decltype(nodes) nodes) noexcept
            : name(std::move(name)), duration(duration), tps(tps), nodes(std::move(nodes)) {}
    };

    class SkeletalModel : public Model {
    protected:
        std::vector<Bone> bones;
        std::unordered_map<std::string, uint32_t> bone_map;
        std::vector<Animation> animations;
        Tree<uint32_t> skeleton;

        glm::mat4 global_inverse;
    public:
        SkeletalModel(decltype(meshes)&& meshes, decltype(materials)&& materials, decltype(bones)&& bones, decltype(bone_map)&& bone_map, decltype(skeleton)&& skeleton, decltype(animations)&& a, const glm::mat4& global_matrix) noexcept;
        ~SkeletalModel() override = default;

        auto& getAnimations() const noexcept { return animations; }
        const auto& getBones() const noexcept { return bones; }
        const auto& getGlobalInverseMatrix() const noexcept { return global_inverse; }
        const auto& getSkeletonTree() const noexcept { return skeleton; }

        SkeletalModel(const SkeletalModel&) = delete;
        SkeletalModel& operator=(const SkeletalModel&) = delete;
    };
}