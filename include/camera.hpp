#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GraphicsEngine {
    enum class CameraMovement { Forward, Backward, Left, Right, Up, Down };
    enum class CameraMode { Free, Panning };

    class Camera {
    private:
        glm::vec3 position;
        glm::vec3 front, up, right, world_up;

        glm::mat4 projection, view;

        CameraMode mode { CameraMode::Free };

        float pitch;
        float yaw;

        float fov {90}; // degrees
        float near_distance {0.01f};
        float far_distance {1000.0f};

        float move_speed {2.0f};
        float mouse_sence {0.5f};
    public:
        explicit Camera(glm::uvec2 window_size) noexcept;

        [[nodiscard]] const auto& getProjection() const noexcept { return projection; }
        [[nodiscard]] const auto& getPosition() const noexcept { return position; }
        [[nodiscard]] const auto& getFront() const noexcept { return front; }
        [[nodiscard]] const auto& getUp() const noexcept { return up; }
        [[nodiscard]] const auto& getRight() const noexcept { return right; }
        [[nodiscard]] const auto& getView() const noexcept { return view; }
        [[nodiscard]] const auto& getNear() const noexcept { return near_distance; }
        [[nodiscard]] const auto& getFar() const noexcept { return far_distance; }
        [[nodiscard]] const auto& getFov() const noexcept { return fov; }

        [[nodiscard]] auto& getMoveSpeed() const noexcept { return move_speed; }
        [[nodiscard]] auto& getMouseSence() const noexcept { return mouse_sence; }

        void setPosition(const glm::vec3& position) noexcept;
        void setFront(const glm::vec3& front) noexcept;

        void mouseMove(glm::dvec2 offset) noexcept;
        void mouseScroll(float yoffset) noexcept;
        void movement(CameraMovement move, float delta) noexcept;

        void updateView() noexcept;
        void updateProjection(glm::uvec2 size) noexcept;
    };
}