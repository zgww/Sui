#include "MessageDialog.h"
#include "../Core/Window.h"
#include "../Core/App.h"
#include "../Layout/LayoutLinear.h"
#include "../View/EditText.h"
#include "../View/Button.h"
#include "../Core/NodeLib.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
static std::wstring utf8ToW(const char* s) {
	if (!s) return L"";
	int wlen = MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
	std::wstring ws(wlen > 0 ? wlen : 1, 0);
	if (wlen > 0) MultiByteToWideChar(CP_UTF8, 0, s, -1, &ws[0], wlen);
	return ws;
}
#endif

void MessageDialog_alert(const char* content, const char* title) {
#ifdef _WIN32
	MessageBoxW(nullptr, utf8ToW(content).c_str(), utf8ToW(title).c_str(), MB_OK | MB_ICONINFORMATION);
#endif
}

void MessageDialog_alert_error(const char* content, const char* title) {
#ifdef _WIN32
	MessageBoxW(nullptr, utf8ToW(content).c_str(), utf8ToW(title).c_str(), MB_OK | MB_ICONERROR);
#endif
}

void MessageDialog_alert_warn(const char* content, const char* title) {
#ifdef _WIN32
	MessageBoxW(nullptr, utf8ToW(content).c_str(), utf8ToW(title).c_str(), MB_OK | MB_ICONWARNING);
#endif
}

bool MessageDialog_confirm(const char* content, const char* title) {
#ifdef _WIN32
	int ret = MessageBoxW(nullptr, utf8ToW(content).c_str(), utf8ToW(title).c_str(), MB_YESNO | MB_ICONQUESTION);
	return ret == IDYES;
#else
	return false;
#endif
}

void MessageDialog_prompt(const char* value, const char* title, Ref<Closure<void(const std::string&)>> onNewValue) {
	Ref<Window> win{new Window()};
	win->initData();

	/*Ref<LayoutLinear> root{new LayoutLinear()};
	root->direction = "column";
	root->alignItems = "stretch";
	root->justifyContent = "center";
	root->padding.setAll(8);
	root->backgroundColor = 0xffffffff;
	win->setRootView(root.get());

	EditText* editText = gocEditText(root.get(), 0);
	if (editText) {
		editText->setValue(value);
	}

	LayoutLinear* btnRow = gocLayoutLinear(root.get(), 1);
	if (btnRow) {
		btnRow->justifyContent = "center";
		btnRow->margin.setVer(16);

		Button* okBtn = gocButton(btnRow, 0);
		if (okBtn) {
			okBtn->setLabel("OK");
			auto winRef = win;
			auto onNewValueRef = onNewValue;
			auto editTextRef = editText;
			okBtn->onClick = CLOSURE([=](MouseEvent*) {
				if (onNewValueRef.get() != nullptr && editTextRef) {
					onNewValueRef->invoke(editTextRef->value);
				}
				if (winRef.get() != nullptr) winRef->close();
			});
		}

		Button* cancelBtn = gocButton(btnRow, 1);
		if (cancelBtn) {
			cancelBtn->setLabel("Cancel");
			auto winRef = win;
			cancelBtn->onClick = CLOSURE([=](MouseEvent*) {
				if (winRef.get() != nullptr) winRef->close();
			});
		}
	}*/

	win->setTitle(title);
	win->setSize(300, 140);
	win->moveToCenter();
	win->show();
}
