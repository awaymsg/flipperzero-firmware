#pragma once
#include "ibutton_scene_generic.h"

class iButtonSceneSavedKeyMenu : public iButtonScene {
public:
    void on_enter(iButtonApp* app) final;
    bool on_event(iButtonApp* app, iButtonEvent* event) final;
    void on_exit(iButtonApp* app) final;

private:
    uint32_t submenu_item_selected = 0;
};