#include "CppUTest/TestHarness.h"
#include "gui/menu_item/menu_item.h"

TEST_GROUP(MenuItemSentinelTests){};

TEST(MenuItemSentinelTests, plainMenuItemSurvivesAllCallsUsedOnClosedSentinel) {
	MenuItem item;
	CHECK_FALSE(item.isSubmenu());
	CHECK_TRUE(item.getParamKind() == deluge::modulation::params::Kind::NONE);
	// 255 here is MenuItem::getParamIndex()'s own "not a patched param" sentinel (menu_item.h) -
	// a separate, narrower convention from kNoParamID (param.h, 0xFFFFFFFF) used elsewhere.
	CHECK_EQUAL(255, item.getParamIndex());
	CHECK_FALSE(item.usesAffectEntire());
	CHECK_FALSE(item.allowsLearnMode());
	CHECK_FALSE(item.isRangeDependent());
	item.readValueAgain(); // must not crash
}
