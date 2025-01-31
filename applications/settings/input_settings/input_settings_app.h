#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/variable_item_list.h>
#include "input/input_settings.h"

// app stucture
typedef struct {
InputSettings* settings;
Input* input;
Gui* gui;
ViewDispatcher* view_dispatcher;
VariableItemList* variable_item_list;
} InputSettingsApp;

// list of menu views for view dispatcher
typedef enum {
    InputSettingsViewVariableItemList,
} InputSettingsView;