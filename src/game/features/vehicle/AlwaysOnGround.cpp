#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

#include <algorithm>

namespace YimMenu::Features
{
    class AlwaysOnGround : public LoopedCommand
    {
        using LoopedCommand::LoopedCommand;

        void OnTick() override
        {
            if (auto vehicle = Self::GetVehicle())
            {
                auto handle = vehicle.GetHandle();

                // Get vehicle speed
                float speed = ENTITY::GET_ENTITY_SPEED(handle);

                // Scale downforce with speed
                float downforce = std::clamp(speed * 12.0f, 50.0f, 300.0f);

                ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
                    handle,
                    1,          // Force type
                    0.0f,       // X
                    0.0f,       // Y
                    -downforce, // Z (downwards)
                    false,
                    true,
                    true,
                    false
                );
            }
        }
    };

    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Applies downward force to keep vehicle wheels on the ground"
    };
}
