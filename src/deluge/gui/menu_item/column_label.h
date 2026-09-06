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

/// Truncates `label` from the end, in place, until it fits within `slotWidthPx` (leaving 4px of
/// padding, matching how HorizontalMenu::renderColumnLabel() has always fit labels into their
/// column). Never truncates below one character, so a pathologically narrow slot can't spin here
/// forever.
///
/// `measureWidthPx` abstracts the actual font-metric lookup (Canvas::getStringWidthInPixels) so
/// this can be unit tested without pulling in font/display/hardware code - see
/// tests/unit/column_label_tests.cpp.
void truncateColumnLabelToFit(StringBuf& label, int32_t slotWidthPx,
                              const std::function<int32_t(const char*)>& measureWidthPx);
