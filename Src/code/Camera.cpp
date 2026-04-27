#include "Camera.hpp"
#include <algorithm> // for std::clamp

namespace Render {

    // =====================
    // Movement
    // =====================
    void Camera::Move(float dx, float dy, float dz) {
        position.x += dx;
        position.y += dy;
        position.z += dz;
    }

    // =====================
    // Rotation
    // =====================
    void Camera::Rotate(float dyaw, float dpitch) {
        yaw   += dyaw;
        pitch += dpitch;

        // Ограничиваем pitch (чтобы не переворачиваться)
        const float limit = 1.5f; // ~85 градусов
        pitch = std::clamp(pitch, -limit, limit);
    }

    // =====================
    // Projection pipeline
    // =====================
    Vec2 Camera::Project(const Vec3& point) const {
        // 1. World → Camera
        Vec3 p = WorldToCamera(point);

        // 2. Rotation
        p = ApplyRotation(p);

        // 3. Orthographic projection
        Vec2 result;
        result.x = p.x * scale;
        result.y = p.y * scale;

        return result;
    }

    // =====================
    // World → Camera space
    // =====================
    Vec3 Camera::WorldToCamera(const Vec3& p) const {
        return {
            p.x - position.x,
            p.y - position.y,
            p.z - position.z
        };
    }

    // =====================
    // Rotation (Yaw + Pitch)
    // =====================
    Vec3 Camera::ApplyRotation(const Vec3& p) const {
        // --- Yaw (Z axis) ---
        float cos_y = std::cos(yaw);
        float sin_y = std::sin(yaw);

        float x1 = p.x * cos_y - p.y * sin_y;
        float y1 = p.x * sin_y + p.y * cos_y;
        float z1 = p.z;

        // --- Pitch (X axis) ---
        float cos_p = std::cos(pitch);
        float sin_p = std::sin(pitch);

        float y2 = y1 * cos_p - z1 * sin_p;
        float z2 = y1 * sin_p + z1 * cos_p;

        return {x1, y2, z2};
    }

} // namespace Render
