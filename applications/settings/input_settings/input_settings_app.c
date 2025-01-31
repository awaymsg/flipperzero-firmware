#include <stdint.h>
#include "input_settings_app.h"

#define VIBRO_TOUCH_LEVEL_COUNT 10
// vibro touch human readable levels
const char* const vibro_touch_level_text[VIBRO_TOUCH_LEVEL_COUNT] = {
    "OFF",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
};
// vibro touch levels tick valies delay
const uint32_t vibro_touch_level_value[VIBRO_TOUCH_LEVEL_COUNT] =
    {0,13,16,19,21,24,27,30,33,36};

input_settings_start_vibro_touch_level_changed (){
    
}

InputSettingsApp* input_settings_alloc (void) {
    InputSettingsApp* app = malloc(sizeof(InputSettingsApp));

    app->gui = furi_record_open (RECORD_GUI);
    app->view_dispatcher = view_dispatcher_alloc ();

    VariableItem* item;
    app->var_item_list = variable_item_list_alloc();
    
    item = variable_item_list_add(
        variable_item_list,
        "Vibro touch level",
        VIBRO_TOUCH_LEVEL_COUNT,
        input_settings_start_vibro_touch_level_changed,
        app);

    value_index = value_index_uint32(
        app->settings.vibro_touch_level, vibro_touch_level_value, VIBRO_TOUCH_LEVEL_COUNT);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, vibro_touch_level_text[value_index]);

    
return app;
}


// Enter point 
int32_t input_settings_app (void* p) {
    UNUSED (p);
    
    //take memory
    InputSettingsApp* app = input_settings_alloc ();

    //start view_dispatcher 
    view_dispatcher_run(app->view_dispatcher);

    //free memory
    Input_settings_free (app);
    
    //exit with 0 code
    return 0;
};