#pragma once

#include <cmath>

namespace Render {

    // =====================
    // Basic math structs
    // =====================
    struct Vec2 {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct Vec3 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    // =====================
    // Camera
    // =====================
    class Camera {
    public:
        // Position
        Vec3 position{0.f, 0.f, 0.f};

        // Rotation (Euler angles)
        float yaw   = 0.0f; // вращение вокруг Z
        float pitch = 0.0f; // наклон

        // Projection
        float scale = 2.0f;

    public:
        Camera() = default;

        // --- Movement ---
        void Move(float dx, float dy, float dz);

        // --- Rotation ---
        void Rotate(float dyaw, float dpitch);

        // --- Projection ---
        Vec2 Project(const Vec3& point) const;

    private:
        Vec3 WorldToCamera(const Vec3& p) const;
        Vec3 ApplyRotation(const Vec3& p) const;
    };

} // namespace Render
