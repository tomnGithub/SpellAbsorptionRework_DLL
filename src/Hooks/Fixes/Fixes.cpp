#include "Fixes.h"

#include "RE/Offset.h"


#include <xbyak.h>

namespace
{
	bool AllowAbsorb(RE::MagicTarget* a_this,
		RE::Actor* a_actor,
		RE::MagicItem* a_magicItem,
		const RE::Effect* a_effect)
	{
		(void)a_effect;
		if (!a_magicItem ||
			a_magicItem->effects.empty() ||
			!a_actor ||
			!a_this ||
			!a_this->MagicTargetIsActor()) {
			return true;
		}

		return false;
	}
}

namespace Hooks {
	namespace Fixes {
		bool InstallFixes() {
			bool success = true;
			success &= Character::InstallCharacterFixes();
			success &= Player::InstallPlayerFixes();
		
			return success;
		}

		bool Character::InstallCharacterFixes() {
			REL::Relocation<std::uintptr_t> VTABLE{ RE::Character::VTABLE[4] };
			_func = VTABLE.write_vfunc(0xB, CharacterThunk);
			logger::info("    >Installed Character Magic Target VFunc hook."sv);
			return true;
		}

		bool Player::InstallPlayerFixes() {
			REL::Relocation<std::uintptr_t> VTABLE{ RE::PlayerCharacter::VTABLE[4] };
			_func = VTABLE.write_vfunc(0xB, PlayerThunk);
			logger::info("    >Installed Player Character Magic Target VFunc hook."sv);
			return true;
		}

		bool Player::PlayerThunk(RE::MagicTarget* a_this,
			RE::Actor* a_actor,
			RE::MagicItem* a_magicItem,
			const RE::Effect* a_effect)
		{
			return AllowAbsorb(a_this, a_actor, a_magicItem, a_effect) &&
				_func(a_this, a_actor, a_magicItem, a_effect);
		}

		bool Character::CharacterThunk(RE::MagicTarget* a_this,
			RE::Actor* a_actor,
			RE::MagicItem* a_magicItem,
			const RE::Effect* a_effect)
		{
			return AllowAbsorb(a_this, a_actor, a_magicItem, a_effect) &&
				_func(a_this, a_actor, a_magicItem, a_effect);
		}

	}
}