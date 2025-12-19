#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <algorithm>
#include <cmath>

namespace YimMenu::Features
{
	class TractionControl : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		// How much sideways velocity we remove per tick (0.0 = none, 1.0 = remove all)
		// Start at ~0.80 for “very grippy”.
		static constexpr float k_LateralDamping = 0.80f;

		// Max change in forward speed per tick (limits sudden acceleration -> less wheelspin)
		static constexpr float k_MaxForwardDeltaPerTick = 2.0f;

		Vehicle m_LastHandle = 0;
		bool m_HasPrev = false;
		float m_PrevForwardSpeed = 0.0f;

		static float Dot2D(const Vector3& a, const Vector3& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		static Vector3 Normalize2D(Vector3 v)
		{
			const float len = std::sqrt(v.x * v.x + v.y * v.y);
			if (len > 0.0001f)
			{
				v.x /= len;
				v.y /= len;
			}
			return v;
		}

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
			{
				m_LastHandle = 0;
				m_HasPrev = false;
				m_PrevForwardSpeed = 0.0f;
				return;
			}

			const auto handle = veh.GetHandle();

			// Reset state when switching vehicles
			if (handle != m_LastHandle)
			{
				m_LastHandle = handle;
				m_HasPrev = false;
				m_PrevForwardSpeed = 0.0f;
			}

			// Forward direction (2D)
			Vector3 fwd = ENTITY::GET_ENTITY_FORWARD_VECTOR(handle);
			fwd.z = 0.0f;
			fwd = Normalize2D(fwd);

			// Current velocity
			const auto rawVel = veh.GetVelocity();          // rage::fvector3
			Vector3 vel(rawVel.x, rawVel.y, rawVel.z);

			// Split velocity into forward + lateral (2D)
			Vector3 vel2D(vel.x, vel.y, 0.0f);
			const float forwardSpeed = Dot2D(vel2D, fwd);

			float newForwardSpeed = forwardSpeed;

			// Clamp forward acceleration per tick (helps prevent “spin-up” feel)
			if (m_HasPrev)
			{
				const float delta = newForwardSpeed - m_PrevForwardSpeed;
				const float clampedDelta = std::clamp(delta, -k_MaxForwardDeltaPerTick, k_MaxForwardDeltaPerTick);
				newForwardSpeed = m_PrevForwardSpeed + clampedDelta;
			}
			else
			{
				m_HasPrev = true;
			}

			m_PrevForwardSpeed = newForwardSpeed;

			const Vector3 forwardVel2D = fwd * newForwardSpeed;
			const Vector3 lateralVel2D = vel2D - forwardVel2D;

			// Remove most sideways slip
			const Vector3 newVel2D = forwardVel2D + lateralVel2D * (1.0f - k_LateralDamping);

			// Keep original vertical velocity so bumps/jumps still work
			veh.SetVelocity(rage::fvector3(newVel2D.x, newVel2D.y, vel.z));
		}
	};

	static TractionControl _TractionControl{
		"tractioncontrol",
		"Traction Control",
		"Reduces wheelspin and sideways slip by damping lateral velocity"
	};
}
