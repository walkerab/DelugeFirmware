#include "CppUTest/TestHarness.h"
#include "gui/ui/menu_param_change.h"

using deluge::modulation::params::Kind;

TEST_GROUP(MenuParamChangeTests){};

TEST(MenuParamChangeTests, noItemIsNeverAParamMenu) {
	// currentItem/previousItem are null after backing all the way out of the menu
	// (SoundEditor::goUpOneLevel() -> exitCompletely()) - must not crash, must read as "not a param menu".
	CHECK_FALSE(isParamMenu(false, false, false, Kind::PATCHED));
	CHECK_FALSE(isParamMenu(false, true, true, Kind::PATCHED));
}

TEST(MenuParamChangeTests, nonHorizontalMenuIgnoresSubmenuFlag) {
	CHECK_TRUE(isParamMenu(true, false, true, Kind::PATCHED));
	CHECK_TRUE(isParamMenu(true, false, false, Kind::PATCHED));
}

TEST(MenuParamChangeTests, horizontalMenuSubmenuIsNeverAParamMenu) {
	CHECK_FALSE(isParamMenu(true, true, true, Kind::PATCHED));
}

TEST(MenuParamChangeTests, horizontalMenuNonSubmenuChecksParamKind) {
	CHECK_TRUE(isParamMenu(true, true, false, Kind::PATCHED));
	CHECK_FALSE(isParamMenu(true, true, false, Kind::NONE));
}

TEST(MenuParamChangeTests, noneKindIsNeverAParamMenu) {
	CHECK_FALSE(isParamMenu(true, false, false, Kind::NONE));
}
