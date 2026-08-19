#pragma once

#include "../Core/Predef.h"
#include <string>

void MessageDialog_alert(const char* content, const char* title);
void MessageDialog_alert_error(const char* content, const char* title);
void MessageDialog_alert_warn(const char* content, const char* title);
bool MessageDialog_confirm(const char* content, const char* title);
void MessageDialog_prompt(const char* value, const char* title, Ref<Closure<void(const std::string&)>> onNewValue);
