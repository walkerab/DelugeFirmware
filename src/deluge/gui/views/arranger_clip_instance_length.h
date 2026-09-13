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

#include <cstdint>

/// Clamps a candidate length for an Arranger clip instance to the two hard limits every instance is
/// subject to: it can't run into the next instance on the same row, and it can't run past the end of
/// the sequence.
int32_t clampClipInstanceLength(int32_t desiredLength, int32_t clipInstancePos, bool hasNextClipInstance,
                                int32_t nextClipInstancePos, int32_t maxSequenceLength);
