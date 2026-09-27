// Trivial stand-ins for MenuItem's out-of-line virtuals, so a plain MenuItem's vtable links in host
// tests without pulling in menu_item.cpp's real OLED/SoundEditor-rendering methods (and their large
// unrelated dependency chain - Canvas, OLED display state, l10n string tables, etc). None of these
// bodies are exercised by menu_item_sentinel_tests.cpp - a vtable just needs every slot resolved to
// something, even slots the test never calls.
#include "gui/menu_item/menu_item.h"

MenuPermission MenuItem::checkPermissionToBeginSession(ModControllableAudio*, int32_t, MultiRange**) {
	return MenuPermission::YES;
}

void MenuItem::endSession() {
}
void MenuItem::learnCC(MIDICable&, int32_t, int32_t, int32_t) {
}
void MenuItem::renderOLED() {
}
void MenuItem::drawName() {
}
void MenuItem::renderSubmenuItemTypeForOled(int32_t) {
}
void MenuItem::updatePadLights() {
}

namespace deluge::l10n {
std::string_view getView(String) {
	return "";
}
} // namespace deluge::l10n
