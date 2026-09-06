/*
 * Copyright (c) 2024 Sean Ditny
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

#pragma once

#include "gui/menu_item/menu_item.h"
#include <cstdint>

class ParamSet;
class ModelStackWithAutoParam;

namespace deluge::gui::menu_item {

// Note that this does *not* inherit from MenuItem actually!
class Automation {
public:
	MenuItem* selectButtonPress();
	ActionResult buttonAction(deluge::hid::Button b, bool on, bool inCardRoutine);
	virtual ModelStackWithAutoParam* getModelStackWithParam(void* memory) = 0;
	virtual PatchSource getPatchSource() { return PatchSource::NONE; }
	void selectAutomationViewParameter(bool clipMinder);
	bool isValueModifiedFromSaved();

	/// Most menu items round-trip their AutoParam's raw value through a coarse UI display scale
	/// (e.g. "standard" scaling collapses the whole int32_t range down to just 51 discrete grid
	/// points - see value_scaling.h) every time they're read/written via the menu. A saved raw
	/// value essentially never lands exactly on one of those grid points to begin with (it wasn't
	/// necessarily set via this same UI), so touching the knob at all and dialing back to the same
	/// displayed number can leave the raw value permanently, harmlessly different from savedValue -
	/// the naive exact comparison would then never clear the "modified" dot even though nothing the
	/// user can perceive has changed. Override this to apply the same scale the class's own
	/// readCurrentValue()/getFinalValue() use, so "modified" means "the displayed value differs",
	/// not "the raw bytes differ". Defaults to identity (exact raw comparison) for anything that
	/// doesn't override it.
	virtual int32_t quantizeValueForModifiedComparison(int32_t rawValue) { return rawValue; }
};
} // namespace deluge::gui::menu_item
