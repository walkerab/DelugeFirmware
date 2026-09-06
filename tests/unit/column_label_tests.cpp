/*
 * Tests for buildColumnLabel() (column_label.h) - the marker-append-and-truncate logic
 * HorizontalMenu::renderColumnLabel() uses to build each column's text, independent of any
 * Canvas/font/hardware code (a fake fixed-width-per-character measurer stands in for the real
 * font metrics here).
 *
 * Background: the "modified from saved" indicator for these labels went through several designs
 * - a separately-positioned dot (drifted for variable-width labels, or overlapped/corrupted a
 * tight-fitting one), then an underline (couldn't be nudged away from the text without exiting
 * the label's own row and the selection-highlight box) - before landing on appending a marker
 * character ("+") to the string itself, so it rides the same centering/truncation/highlight
 * logic as the label text. These tests exist so that logic (which name gets truncated, and that
 * the marker itself is never silently dropped by truncation) can be verified in a fraction of a
 * second, without a build+flash+emulator cycle each time it's touched.
 */

#include "CppUTest/TestHarness.h"
#include "gui/menu_item/column_label.h"
#include <cstring>

namespace {
constexpr int32_t kCharWidthPx = 6;

int32_t fakeMeasure(const char* s) {
    return static_cast<int32_t>(strlen(s)) * kCharWidthPx;
}
} // namespace

TEST_GROUP(BuildColumnLabel){};

TEST(BuildColumnLabel, shortNameUnmodifiedIsUnchanged) {
    DEF_STACK_STRING_BUF(label, 32);
    label.append("PAN");
    buildColumnLabel(label, false, '+', 32, fakeMeasure);
    STRCMP_EQUAL("PAN", label.c_str());
}

TEST(BuildColumnLabel, shortNameModifiedGetsMarkerAppended) {
    DEF_STACK_STRING_BUF(label, 32);
    label.append("PAN");
    buildColumnLabel(label, true, '+', 32, fakeMeasure);
    STRCMP_EQUAL("PAN+", label.c_str());
}

TEST(BuildColumnLabel, longNameUnmodifiedIsTruncated) {
    // "SATURATION" (10 chars) doesn't fit a 32px slot at 6px/char (10*6+4=64 >= 32); truncates
    // down to the same 4-char "SATU" the real font produces for this exact real-world name.
    DEF_STACK_STRING_BUF(label, 32);
    label.append("SATURATION");
    buildColumnLabel(label, false, '+', 32, fakeMeasure);
    STRCMP_EQUAL("SATU", label.c_str());
}

TEST(BuildColumnLabel, longNameModifiedTruncatesNameNotMarker) {
    // Reserving room for "+" up front means the name gives up one more character than the
    // unmodified case (3 instead of 4) so the marker always survives, rather than the naive
    // "append then truncate from the end" approach silently chopping it off first for exactly
    // the labels tightest on space - which is what actually broke on real hardware with ".".
    DEF_STACK_STRING_BUF(label, 32);
    label.append("SATURATION");
    buildColumnLabel(label, true, '+', 32, fakeMeasure);
    STRCMP_EQUAL("SAT+", label.c_str());
}

TEST(BuildColumnLabel, modifiedMarkerSurvivesEvenWhenNameShrinksToOneChar) {
    // Slot only wide enough for one name character plus the marker (6 + 6 + 4 = 16 < 20).
    DEF_STACK_STRING_BUF(label, 32);
    label.append("SATURATION");
    buildColumnLabel(label, true, '+', 20, fakeMeasure);
    STRCMP_EQUAL("S+", label.c_str());
}

TEST(BuildColumnLabel, variableWidthLabelStillGetsMarkerAppended) {
    // Mirrors sidechain SYNC, whose "label" is the current note-length value itself
    // ("1/16-T", "OFF", ...) rather than a fixed short tag - the marker still just appends.
    DEF_STACK_STRING_BUF(label, 32);
    label.append("1/16-T");
    buildColumnLabel(label, true, '+', 64, fakeMeasure);
    STRCMP_EQUAL("1/16-T+", label.c_str());
}

TEST(BuildColumnLabel, emptyNameDoesNotCrashOrHang) {
    DEF_STACK_STRING_BUF(label, 32);
    buildColumnLabel(label, true, '+', 8, fakeMeasure);
    STRCMP_EQUAL("+", label.c_str());
}
