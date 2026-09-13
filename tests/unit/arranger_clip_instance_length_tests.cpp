#include "CppUTest/TestHarness.h"
#include "gui/views/arranger_clip_instance_length.h"

TEST_GROUP(ArrangerClipInstanceLengthTests){};

TEST(ArrangerClipInstanceLengthTests, preservesDesiredLengthWhenUnconstrained) {
	CHECK_EQUAL(32, clampClipInstanceLength(32, 0, false, 0, 10000));
}

TEST(ArrangerClipInstanceLengthTests, preservesDesiredLengthLongerThanOneLoop) {
	CHECK_EQUAL(16 * 96, clampClipInstanceLength(16 * 96, 0, false, 0, 10000));
}

TEST(ArrangerClipInstanceLengthTests, clampsToNextClipInstancePosition) {
	CHECK_EQUAL(16, clampClipInstanceLength(64, 0, true, 16, 10000));
}

TEST(ArrangerClipInstanceLengthTests, notClampedWhenWithinNextInstanceBound) {
	CHECK_EQUAL(8, clampClipInstanceLength(8, 0, true, 16, 10000));
}

TEST(ArrangerClipInstanceLengthTests, exactlyAtNextInstanceBoundIsNotClamped) {
	CHECK_EQUAL(16, clampClipInstanceLength(16, 0, true, 16, 10000));
}

TEST(ArrangerClipInstanceLengthTests, clampsToEndOfSequenceWithNoNextInstance) {
	CHECK_EQUAL(70, clampClipInstanceLength(100, 50, false, 0, 120));
}

TEST(ArrangerClipInstanceLengthTests, exactlyAtSequenceEndIsNotClamped) {
	CHECK_EQUAL(70, clampClipInstanceLength(70, 50, false, 0, 120));
}

TEST(ArrangerClipInstanceLengthTests, sequenceEndClampAppliesEvenAfterNextInstanceClamp) {
	CHECK_EQUAL(20, clampClipInstanceLength(100, 0, true, 30, 20));
}

TEST(ArrangerClipInstanceLengthTests, nextInstanceClampAppliesEvenWhenTighterThanSequenceEnd) {
	CHECK_EQUAL(10, clampClipInstanceLength(100, 0, true, 10, 500));
}
