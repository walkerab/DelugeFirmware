#include "CppUTest/TestHarness.h"
#include "gui/colour/palette.h"
#include "gui/views/arranger_audition_pad_colour.h"

TEST_GROUP(ArrangerAuditionPadColourTests){};

TEST(ArrangerAuditionPadColourTests, blackWhenNoOutput) {
	RGB result = computeArrangerAuditionPadIdleColour(false, 42);
	CHECK_EQUAL(deluge::gui::colours::black.r, result.r);
	CHECK_EQUAL(deluge::gui::colours::black.g, result.g);
	CHECK_EQUAL(deluge::gui::colours::black.b, result.b);
}

TEST(ArrangerAuditionPadColourTests, notBlackWhenOutputPresent) {
	RGB result = computeArrangerAuditionPadIdleColour(true, 0);
	bool anyChannelLit = result.r != 0 || result.g != 0 || result.b != 0;
	CHECK(anyChannelLit);
}

TEST(ArrangerAuditionPadColourTests, dimmerThanFullBrightnessHue) {
	RGB full = RGB::fromHue(24);
	RGB idle = computeArrangerAuditionPadIdleColour(true, 24);
	CHECK_COMPARE(idle.r, <=, full.r);
	CHECK_COMPARE(idle.g, <=, full.g);
	CHECK_COMPARE(idle.b, <=, full.b);
	bool anyChannelDimmed = idle.r < full.r || idle.g < full.g || idle.b < full.b;
	CHECK(anyChannelDimmed);
}

TEST(ArrangerAuditionPadColourTests, differentHuesProduceDifferentColours) {
	RGB colourA = computeArrangerAuditionPadIdleColour(true, 0);
	RGB colourB = computeArrangerAuditionPadIdleColour(true, 96);
	bool anyChannelDiffers = colourA.r != colourB.r || colourA.g != colourB.g || colourA.b != colourB.b;
	CHECK(anyChannelDiffers);
}

TEST(ArrangerAuditionPadColourTests, hueWraps192DegreesLikeFromHue) {
	RGB colourAtZero = computeArrangerAuditionPadIdleColour(true, 0);
	RGB colourAtWrap = computeArrangerAuditionPadIdleColour(true, 192);
	CHECK_EQUAL(colourAtZero.r, colourAtWrap.r);
	CHECK_EQUAL(colourAtZero.g, colourAtWrap.g);
	CHECK_EQUAL(colourAtZero.b, colourAtWrap.b);
}
