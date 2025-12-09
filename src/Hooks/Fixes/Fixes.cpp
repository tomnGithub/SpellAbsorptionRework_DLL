#include "Fixes.h"

#include "RE/Offset.h"

namespace Hooks::Fixes
{
	bool Install() {
		logger::info("  >Installing fixes"sv);
		auto* listener = Listener::GetSingleton();
		if (!listener) {
			logger::critical("    >Failed to get Fixes Listener."sv);
			return false;
		}
		return listener->Install();
	}

	bool Listener::Install() {
	
		return Player::Install() && Character::Install();
	}

	bool Listener::IgnoreAbsorb(RE::MagicTarget* a_this,
		RE::Actor* a_actor,
		RE::MagicItem* a_magicItem,
		const RE::Effect* a_effect) {
		(void)a_effect;
		if (!a_magicItem ||
			a_magicItem->effects.empty() ||
			!a_actor ||
			!a_this ||
			!a_this->MagicTargetIsActor()) {
			return false;
		}
			return true;
	}

	// The repository's commonlib does NOT have these vtables specified. If you want to use
	// a different commonlib as a base, they may be defined.

	bool Listener::Character::Install() {
		REL::Relocation<std::uintptr_t> VTABLE{ RE::Offset::PlayerCharacter::VTABLE_PlayerCharacterMagicTarget };
		_func = VTABLE.write_vfunc(0xB, Thunk);
		logger::info("    >Installed Character Magic Target VFunc hook."sv);
		return true;
	}

	bool Listener::Character::Thunk(RE::MagicTarget* a_this,
		RE::Actor* a_actor,
		RE::MagicItem* a_magicItem,
		const RE::Effect* a_effect) {
		auto* listener = Listener::GetSingleton();
		if (!listener) {
			logger::warn("Somehow failed to get internal listener for the Character Absorb Listener."sv);
			return _func(a_this, a_actor, a_magicItem, a_effect);
		}

		if (listener->IgnoreAbsorb(a_this, a_actor, a_magicItem, a_effect)) {
			return false;
		}

		return _func(a_this, a_actor, a_magicItem, a_effect);
	}

	bool Listener::Player::Install() {
		REL::Relocation<std::uintptr_t> VTABLE{ RE::Offset::Character::VTABLE_CharacterMagicTarget };
		_func = VTABLE.write_vfunc(0xB, Thunk);
		logger::info("    >Installed Player Magic Target VFunc hook."sv);
		return true;
	}

	bool Listener::Player::Thunk(RE::MagicTarget* a_this,
		RE::Actor* a_actor,
		RE::MagicItem* a_magicItem,
		const RE::Effect* a_effect) {
		auto* listener = Listener::GetSingleton();
		if (!listener) {
			logger::warn("Somehow failed to get internal listener for the Player Absorb Listener."sv);
			return _func(a_this, a_actor, a_magicItem, a_effect);
		}

		if (listener->IgnoreAbsorb(a_this, a_actor, a_magicItem, a_effect)) {
			return false;
		}

		return _func(a_this, a_actor, a_magicItem, a_effect);
	}
}