/*
 * Copyright © 2014-2023 Synthstrom Audible Limited
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

#include "definitions_cxx.hpp"
#include "model/sync.h"

#include <cstdint>

class Song;

class SideChain {
public:
	SideChain();
	void cloneFrom(SideChain* other);

	EnvelopeStage status;
	uint32_t pos;
	int32_t lastValue;
	int32_t pendingHitStrength;

	int32_t envelopeOffset;
	int32_t envelopeHeight;

	int32_t attack;
	int32_t release;

	SyncType syncType;
	SyncLevel syncLevel; // Basically, 0 is off, max value is 9. Higher numbers are shorter intervals (higher speed).

	int32_t render(uint16_t numSamples, int32_t shapeValue);
	void registerHit(int32_t strength);
	void registerHitRetrospectively(int32_t strength, uint32_t numSamplesAgo);

	/// "Modified from saved" baseline for attack/sync, same concept as AutoParam::savedValue -
	/// attack/release/syncType/syncLevel are plain fields, not AutoParams, so they need their own
	/// shadow copy (same pattern as ModControllableAudio::modFXType_saved_).
	inline void refreshSavedBaseline() {
		attack_saved_ = attack;
		syncType_saved_ = syncType;
		syncLevel_saved_ = syncLevel;
	}
	inline bool isAttackModifiedFromSaved() const { return attack != attack_saved_; }
	inline bool isSyncModifiedFromSaved() const { return syncType != syncType_saved_ || syncLevel != syncLevel_saved_; }

	/// The reverse of refreshSavedBaseline(): reset attack/sync back to their saved baseline
	/// ("Reset clip to saved").
	inline void resetToSavedBaseline() {
		attack = attack_saved_;
		syncType = syncType_saved_;
		syncLevel = syncLevel_saved_;
	}

private:
	int32_t getActualAttackRate();
	int32_t getActualReleaseRate();

	int32_t attack_saved_{0};
	SyncType syncType_saved_{SYNC_TYPE_EVEN};
	SyncLevel syncLevel_saved_{SYNC_LEVEL_NONE};
};
