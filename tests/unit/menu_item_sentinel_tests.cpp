#include "CppUTest/TestHarness.h"
#include "gui/menu_item/menu_item.h"

TEST_GROUP(MenuItemSentinelTests){};

TEST(MenuItemSentinelTests, plainMenuItemSurvivesAllCallsUsedOnClosedSentinel) {
	MenuItem item;
	CHECK_FALSE(item.isSubmenu());
	CHECK_TRUE(item.getParamKind() == deluge::modulation::params::Kind::NONE);
	CHECK_EQUAL(255, item.getParamIndex());
	CHECK_FALSE(item.usesAffectEntire());
	CHECK_FALSE(item.allowsLearnMode());
	CHECK_FALSE(item.isRangeDependent());
	item.readValueAgain(); // must not crash
}
