/*
 * Copyright © 2026 Synthstrom Audible Limited
 *
 * This file is part of The Synthstrom Audible Deluge Firmware.
 *
 * The Synthstrom Audible Deluge Firmware is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

// A handful of SoundEditor's methods live in this file, separate from the rest of sound_editor.cpp,
// specifically so they can be linked into a host unit test without pulling in the whole menu tree
// sound_editor.cpp otherwise wires together (hundreds of concrete menu-item singletons across dozens of
// files, cascading into DSP code that isn't host-buildable at all). Everything here only needs the
// SoundEditor class layout itself (sound_editor.h) - nothing else - which is what makes that possible.
#include "gui/ui/sound_editor.h"
#include <cstring>

namespace {
// A plain, un-overridden MenuItem whose virtual methods all fall back to their harmless base-class
// defaults (isSubmenu() -> false, getParamKind() -> Kind::NONE, buttonAction() -> NOT_DEALT_WITH, etc.).
// Returned by getCurrentMenuItem() instead of null once the sound editor has closed
// (menuItemNavigationRecord[navigationDepth] is nulled in exitCompletely()), so callers can keep
// treating the result as a normal MenuItem* without every call site needing its own null check.
// Not const: getCurrentMenuItem() returns a plain MenuItem* everywhere, and real call sites invoke
// non-const methods on the result (beginSession(), endSession(), selectEncoderAction(), etc.), so this
// can't be const-qualified without changing that return type across the whole class. Nothing is ever
// meant to actually mutate it - it's conceptually fixed, just not literally, hence no k prefix.
MenuItem closedMenuItem;
} // namespace

MenuItem* SoundEditor::getCurrentMenuItem() {
	MenuItem* item = menuItemNavigationRecord[navigationDepth];
	return item ? item : &closedMenuItem;
}

SoundEditor::SoundEditor() {
	currentParamShortcutX = kNoSelection;
	timeLastAttemptedAutomatedParamEdit = 0;
	shouldGoUpOneLevelOnBegin = false;
	setupKitGlobalFXMenu = false;
	selectedNoteRow = false;
	resetSourceBlinks();
}

void SoundEditor::resetSourceBlinks() {
	memset(sourceShortcutBlinkFrequencies, 255, sizeof(sourceShortcutBlinkFrequencies));
	memset(sourceShortcutBlinkColours, 0, sizeof(sourceShortcutBlinkColours));
}
