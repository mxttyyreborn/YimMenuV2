#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features::Self
{
    struct VehiclePool
    {
        int capacity;          // MUST be set before call
        int vehicles[1023];    // handles returned here
    };

    class OpenGunVan final : public Command
    {
        using Command::Command;

        void OnCall() override
        {
            auto ped = ::YimMenu::Self::GetPed();
            if (!ped)
                return;

            const int pedHandle = ped.GetHandle();

            const Hash gunVanModel = MISC::GET_HASH_KEY("weapontruck");

            VehiclePool pool{};
            pool.capacity = 1023;

            const int count = VEHICLE::GET_ALL_VEHICLES(&pool);
            if (count <= 0)
            {
                Notifications::Show("Gun Van", "No vehicles found (pool empty).", NotificationType::Error);
                return;
            }

            for (int i = 0; i < count && i < pool.capacity; ++i)
            {
                const int veh = pool.vehicles[i];
                if (!ENTITY::DOES_ENTITY_EXIST(veh))
                    continue;

                if (ENTITY::GET_ENTITY_MODEL(veh) != gunVanModel)
                    continue;

                const Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, false);

                ENTITY::SET_ENTITY_COORDS(
                    pedHandle,
                    pos.x,
                    pos.y,
                    pos.z + 1.0f,
                    false,
                    false,
                    false,
                    true
                );

                Notifications::Show("Gun Van", "Teleported to Gun Van.");
                return;
            }

            Notifications::Show("Gun Van", "Gun Van vehicle not found in this session.", NotificationType::Error);
        }
    };

    static OpenGunVan _OpenGunVan{
        "opengunvan",
        "Goto Gun Van",
        "Teleport to the current Gun Van location"
    };
}
