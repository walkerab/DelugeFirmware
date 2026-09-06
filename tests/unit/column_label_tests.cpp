/*
 * Tests for truncateColumnLabelToFit() (column_label.h) - the label-truncation logic
 * HorizontalMenu::renderColumnLabel() uses to fit each column's text, independent of any
 * Canvas/font/hardware code (a fake fixed-width-per-character measurer stands in for the real
 * font metrics here).
 *
 * Background: the "modified from saved" indicator for these labels went through several designs
 * (a separately-positioned dot, then a "." appended to the string) before landing on underlining
 * the whole label - which doesn't touch the string at all, so it needed no dedicated tests here.
 * What's still worth pinning: the truncation itself never spins forever on a pathologically
 * narrow slot (the original inline version could, since size_t(0)-1 wraps rather than throws).
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

TEST_GROUP(TruncateColumnLabelToFit){};

TEST(TruncateColumnLabelToFit, shortNameIsUnchanged) {
    DEF_STACK_STRING_BUF(label, 32);
    label.append("PAN");
    truncateColumnLabelToFit(label, 32, fakeMeasure);
    STRCMP_EQUAL("PAN", label.c_str());
}

TEST(TruncateColumnLabelToFit, longNameIsTruncated) {
    // "SATURATION" (10 chars) doesn't fit a 32px slot at 6px/char (10*6+4=64 >= 32); truncates
    // down to the same 4-char "SATU" the real font produces for this exact real-world name.
    DEF_STACK_STRING_BUF(label, 32);
    label.append("SATURATION");
    truncateColumnLabelToFit(label, 32, fakeMeasure);
    STRCMP_EQUAL("SATU", label.c_str());
}

TEST(TruncateColumnLabelToFit, neverTruncatesBelowOneCharacter) {
    // Slot far too narrow for even one character plus padding - must not spin forever or
    // truncate to an empty string.
    DEF_STACK_STRING_BUF(label, 32);
    label.append("SATURATION");
    truncateColumnLabelToFit(label, 1, fakeMeasure);
    STRCMP_EQUAL("S", label.c_str());
}

TEST(TruncateColumnLabelToFit, emptyNameDoesNotCrashOrHang) {
    DEF_STACK_STRING_BUF(label, 32);
    truncateColumnLabelToFit(label, 8, fakeMeasure);
    STRCMP_EQUAL("", label.c_str());
}
