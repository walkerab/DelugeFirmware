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

#pragma once

#include "util/d_stringbuf.h"
#include <cstdint>
#include <functional>

/// Builds the text HorizontalMenu::renderColumnLabel() draws for a single column: the item's
/// name, with `marker` appended if it's modified from saved (baked directly into the string
/// rather than drawn or positioned separately - an underline and a couple of standalone-dot
/// designs were each tried and each had a real drawback, see horizontal_menu.cpp), truncated
/// from the end to fit within `slotWidthPx` (matching the 4px padding renderColumnLabel() has
/// always left).
///
/// `marker` is reserved for and appended *after* truncation, not before - so it's the last thing
/// to disappear under space pressure, not the first. A label that's merely tight for space should
/// still show its modified-indicator; only a slot too narrow for even one name character plus the
/// marker loses it entirely.
///
/// `measureWidthPx` abstracts the actual font-metric lookup (Canvas::getStringWidthInPixels) so
/// this can be unit tested without pulling in font/display/hardware code - see
/// tests/unit/column_label_tests.cpp.
void buildColumnLabel(StringBuf& label, bool isModified, char marker, int32_t slotWidthPx,
                      const std::function<int32_t(const char*)>& measureWidthPx);
