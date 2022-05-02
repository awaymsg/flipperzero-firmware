#pragma once

#include <gui/view.h>
#include "../helpers/subghz_custom_event.h"

typedef struct SubGhzOpenSesame SubGhzOpenSesame;

typedef void (*SubGhzOpenSesameCallback)(SubGhzCustomEvent event, void* context);

void subghz_opensesame_set_callback(
    SubGhzOpenSesame* subghz_opensesame,
    SubGhzOpenSesameCallback callback,
    void* context);

void subghz_opensesame_add_data_statusbar(
    SubGhzOpenSesame* instance,
    const char* frequency_str,
    const char* preset_str,
    uint8_t codelength);

void subghz_opensesame_stop_send(SubGhzOpenSesame* instance);

SubGhzOpenSesame* subghz_opensesame_alloc();

void subghz_opensesame_free(SubGhzOpenSesame* subghz_opensesame);

View* subghz_opensesame_get_view(SubGhzOpenSesame* subghz_opensesame);
