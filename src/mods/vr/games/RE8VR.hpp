// Even though this is called RE8VR, it also affects RE7.
#pragma once

#include <sdk/REMath.hpp>

#include "../../../Mod.hpp"

class RE8VR : public Mod {
public:
    static std::shared_ptr<RE8VR>& get();

    std::string_view get_name() const override {
        return "RE8VR";
    }

    std::optional<std::string> on_initialize() override;
    void on_lua_state_created(sol::state& lua) override;
    void on_lua_state_destroyed(sol::state& lua) override;

    void set_hand_joints_to_tpose(::REManagedObject* hand_ik);
    void update_hand_ik();
    void update_body_ik(glm::quat* camera_rotation, Vector4f* camera_pos);

private:
    union {
        ::REGameObject* m_player{nullptr};
        ::REManagedObject* m_player_downcast;
    };

    ::REManagedObject* m_left_hand_ik{nullptr};
    ::REManagedObject* m_right_hand_ik{nullptr};
    ::RETransform* m_left_hand_ik_transform{nullptr};
    ::RETransform* m_right_hand_ik_transform{nullptr};
    ::REManagedObject* m_left_hand_ik_object{nullptr};
    ::REManagedObject* m_right_hand_ik_object{nullptr};

    Vector4f m_left_hand_position_offset{};
    Vector4f m_right_hand_position_offset{};
    glm::quat m_left_hand_rotation_offset{};
    glm::quat m_right_hand_rotation_offset{};

    Vector4f m_last_right_hand_position{};
    glm::quat m_last_right_hand_rotation{};
    Vector4f m_last_left_hand_position{};
    glm::quat m_last_left_hand_rotation{};

    bool m_was_gripping_weapon{false};
    bool m_is_holding_left_grip{false};
    bool m_is_in_cutscene{false};
    bool m_is_grapple_aim{false};
    bool m_is_reloading{false};
    bool m_can_use_hands{true};
};