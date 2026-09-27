#include "CppUTest/TestHarness.h"
#include "gui/ui/sound_editor.h"

TEST_GROUP(SoundEditorGetCurrentMenuItemTests){};

TEST(SoundEditorGetCurrentMenuItemTests, neverReturnsNullWhenSlotIsNull) {
	SoundEditor testEditor;
	testEditor.navigationDepth = 0;
	testEditor.menuItemNavigationRecord[0] = nullptr;
	CHECK_TRUE(testEditor.getCurrentMenuItem() != nullptr);
}

TEST(SoundEditorGetCurrentMenuItemTests, returnsTheStoredItemWhenPresent) {
	SoundEditor testEditor;
	MenuItem item;
	testEditor.navigationDepth = 0;
	testEditor.menuItemNavigationRecord[0] = &item;
	CHECK_EQUAL(&item, testEditor.getCurrentMenuItem());
}
