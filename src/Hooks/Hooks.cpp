#include "Hooks/hooks.h"
#include "Hooks/Fixes/Fixes.h"

namespace Hooks {
	bool Install() {
		logger::info("Installing hooks..."sv);

		bool success = true;

		success &= Hooks::Fixes::InstallFixes();
		if (!success) {
			logger::error("Failed to install all hooks, aborting load..."sv);
			return false;
		}

		return true;
	}

}