/*
 * Tests for the "modified from saved" comparison (param_value_comparison.h).
 *
 * Background: the OLED sound-editor menu shows a small dot next to a parameter's name when
 * its live value differs from what's saved on disk. valueDiffersFromSaved() is the single,
 * pure comparison this is built on - exact equality only, no epsilon/tolerance, since
 * parameter values are integers with well-defined semantics. This pins that intent so
 * nobody "improves" it into a fuzzy comparison later.
 */

#include "CppUTest/TestHarness.h"
#include "modulation/automation/param_value_comparison.h"

TEST_GROUP(ValueDiffersFromSaved){};

TEST(ValueDiffersFromSaved, equalValuesAreNotDifferent) {
    CHECK_FALSE(valueDiffersFromSaved(0, 0));
    CHECK_FALSE(valueDiffersFromSaved(42, 42));
    CHECK_FALSE(valueDiffersFromSaved(-1000, -1000));
}

TEST(ValueDiffersFromSaved, offByOneEitherDirectionIsDifferent) {
    CHECK_TRUE(valueDiffersFromSaved(1, 0));
    CHECK_TRUE(valueDiffersFromSaved(0, 1));
}

TEST(ValueDiffersFromSaved, negativeValuesAreComparedExactly) {
    CHECK_TRUE(valueDiffersFromSaved(-5, 5));
    CHECK_FALSE(valueDiffersFromSaved(-5, -5));
}

TEST(ValueDiffersFromSaved, zeroVersusNonZero) {
    CHECK_TRUE(valueDiffersFromSaved(0, 1));
    CHECK_TRUE(valueDiffersFromSaved(1, 0));
    CHECK_FALSE(valueDiffersFromSaved(0, 0));
}
