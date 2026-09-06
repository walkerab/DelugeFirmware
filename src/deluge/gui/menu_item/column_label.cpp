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

#include "column_label.h"

void buildColumnLabel(StringBuf& label, bool isModified, char marker, int32_t slotWidthPx,
                      const std::function<int32_t(const char*)>& measureWidthPx) {
	char markerStr[2] = {marker, '\0'};
	int32_t markerWidthPx = isModified ? measureWidthPx(markerStr) : 0;

	// If the name fits as-is, we'll squeeze it in. Otherwise, we chop off letters until
	// we have some padding between columns - but never chop below one character, so a
	// pathologically narrow slot can't spin here forever.
	while (label.size() > 1 && measureWidthPx(label.c_str()) + markerWidthPx + 4 >= slotWidthPx) {
		label.truncate(label.size() - 1);
	}

	if (isModified) {
		label.append(marker);
	}
}
