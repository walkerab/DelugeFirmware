// Trivial stand-ins for SoundEditor's out-of-line UI overrides (and UI's own constructor), so a plain
// SoundEditor's vtable links in host tests without pulling in the rest of sound_editor.cpp's real
// UI/rendering bodies (and the whole menu tree they wire together - hundreds of concrete menu-item
// singletons across dozens of files, cascading into DSP code that isn't host-buildable at all). None
// of these bodies are exercised by sound_editor_get_current_menu_item_tests.cpp - a vtable just needs
// every slot resolved to something, even slots the test never calls.
#include "gui/ui/sound_editor.h"

UI::UI() {
}
void UI::graphicsRoutine() {
}
void UI::modButtonAction(uint8_t, bool) {
}
// UI's key function - the first non-inline virtual UI declares itself - anchors UI's vtable/typeinfo
// to whichever TU defines it, even though SoundEditor overrides it below with its own definition.
void UI::modEncoderAction(int32_t, int32_t) {
}
// SoundEditor::SoundEditor() briefly runs with the UI base subobject's own vtable in effect (standard
// construction-order semantics), so all of UI's own virtual slots need real definitions too - not just
// SoundEditor's overrides below - even though nothing here ever calls through a plain UI*.
void UI::modEncoderButtonAction(uint8_t, bool) {
}
void UI::displayOrLanguageChanged() {
}

ActionResult SoundEditor::exitCompletely() {
	return ActionResult::DEALT_WITH;
}

bool SoundEditor::opened() {
	return true;
}
void SoundEditor::focusRegained() {
}
void SoundEditor::displayOrLanguageChanged() {
}
bool SoundEditor::getGreyoutColsAndRows(uint32_t*, uint32_t*) {
	return false;
}
ActionResult SoundEditor::buttonAction(deluge::hid::Button, bool, bool) {
	return ActionResult::NOT_DEALT_WITH;
}
ActionResult SoundEditor::padAction(int32_t, int32_t, int32_t) {
	return ActionResult::NOT_DEALT_WITH;
}
ActionResult SoundEditor::verticalEncoderAction(int32_t, bool) {
	return ActionResult::NOT_DEALT_WITH;
}
void SoundEditor::modEncoderAction(int32_t, int32_t) {
}
void SoundEditor::modEncoderButtonAction(uint8_t, bool) {
}
ActionResult SoundEditor::horizontalEncoderAction(int32_t) {
	return ActionResult::NOT_DEALT_WITH;
}
void SoundEditor::scrollFinished() {
}
bool SoundEditor::renderMainPads(uint32_t, RGB[kDisplayHeight][kDisplayWidth + kSideBarWidth],
                                 uint8_t[kDisplayHeight][kDisplayWidth + kSideBarWidth], bool) {
	return true;
}
ActionResult SoundEditor::timerCallback() {
	return ActionResult::DEALT_WITH;
}
void SoundEditor::selectEncoderAction(int8_t) {
}
bool SoundEditor::pcReceivedForMidiLearn(MIDICable&, int32_t, int32_t) {
	return false;
}
bool SoundEditor::noteOnReceivedForMidiLearn(MIDICable&, int32_t, int32_t, int32_t) {
	return false;
}
void SoundEditor::renderOLED(deluge::hid::display::oled_canvas::Canvas&) {
}
