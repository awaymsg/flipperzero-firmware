#include "subghz_opensesame.h"
#include "../subghz_i.h"

#include <input/input.h>
#include <gui/elements.h>

struct SubGhzOpenSesame {
    View* view;
    SubGhzOpenSesameCallback callback;
    void* context;
};

typedef enum {
    SubGhzOpenSesameModelStatusIdle,
    SubGhzOpenSesameModelStatusTx,
} SubGhzOpenSesameModelStatus;

typedef struct {
    string_t frequency_str;
    string_t preset_str;
    SubGhzOpenSesameModelStatus status;
} SubGhzOpenSesameModel;

void subghz_opensesame_set_callback(
    SubGhzOpenSesame* subghz_opensesame,
    SubGhzOpenSesameCallback callback,
    void* context) {
    furi_assert(subghz_opensesame);
    furi_assert(callback);
    subghz_opensesame->callback = callback;
    subghz_opensesame->context = context;
}

void subghz_opensesame_add_data_statusbar(
    SubGhzOpenSesame* instance,
    const char* frequency_str,
    const char* preset_str) {
    furi_assert(instance);
    with_view_model(
        instance->view, (SubGhzOpenSesameModel* model) {
            string_set(model->frequency_str, frequency_str);
            string_set(model->preset_str, preset_str);
            return true;
        });
}

void subghz_opensesame_stop_send(SubGhzOpenSesame* instance) {
    furi_assert(instance);

    with_view_model(
        instance->view, (SubGhzOpenSesameModel* model) {
            model->status = SubGhzOpenSesameModelStatusIdle;
            return true;
        });
}

void subghz_opensesame_draw(Canvas* canvas, SubGhzOpenSesameModel* model) {
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 60, 8, "OpenSesame");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 5, 8, string_get_cstr(model->frequency_str));
    canvas_draw_str(canvas, 40, 8, string_get_cstr(model->preset_str));
    
    canvas_draw_line(canvas, 0, 14, 115, 14);
    canvas_draw_line(canvas, 0, 48, 115, 48);
    canvas_draw_line(canvas, 115, 14, 115, 48);

    switch(model->status) {
    case SubGhzOpenSesameModelStatusIdle:
        elements_button_left(canvas, "Config");
        elements_button_center(canvas, "Send");
        break;
    case SubGhzOpenSesameModelStatusTx:
        elements_text_box(
            canvas,
            4,
            20,
            110,
            30,
            AlignCenter,
            AlignCenter,
            "Transmitting",
            true);
        elements_button_center(canvas, "Stop");
        break;
    }
}

bool subghz_opensesame_input(InputEvent* event, void* context) {
    furi_assert(context);
    SubGhzOpenSesame* instance = context;

    if(event->key == InputKeyBack || event->type != InputTypeShort) {
        return false;
    } else if(event->key == InputKeyLeft && event->type == InputTypeShort) {
        with_view_model(
            instance->view, (SubGhzOpenSesameModel* model) {
                if(model->status == SubGhzOpenSesameModelStatusIdle) {
                    //Config
                    instance->callback(SubGhzCustomEventViewOpenSesameConfig, instance->context);
                }
                return true;
            });
    } else if(event->key == InputKeyBack && event->type == InputTypeShort) {
        with_view_model(
            instance->view, (SubGhzOpenSesameModel* model) {
                //Exit
                model->status = SubGhzOpenSesameModelStatusIdle;
                instance->callback(SubGhzCustomEventViewOpenSesameBack, instance->context);
                return true;
            });
    } else if(event->key == InputKeyOk && event->type == InputTypeShort) {
        with_view_model(
            instance->view, (SubGhzOpenSesameModel* model) {
                if(model->status == SubGhzOpenSesameModelStatusIdle) {
                    //Send
                    instance->callback(SubGhzCustomEventViewOpenSesameTxStart, instance->context);
                    model->status = SubGhzOpenSesameModelStatusTx;
                } else if(model->status == SubGhzOpenSesameModelStatusTx) {
                    //Send
                    instance->callback(SubGhzCustomEventViewOpenSesameTxStop, instance->context);
                    model->status = SubGhzOpenSesameModelStatusIdle;
                }
                return true;
            });
    }

    return true;
}

void subghz_opensesame_enter(void* context) {
    furi_assert(context);
}

void subghz_opensesame_exit(void* context) {
    furi_assert(context);
}

SubGhzOpenSesame* subghz_opensesame_alloc() {
    SubGhzOpenSesame* subghz_opensesame = malloc(sizeof(SubGhzOpenSesame));

    // View allocation and configuration
    subghz_opensesame->view = view_alloc();
    view_allocate_model(
        subghz_opensesame->view, ViewModelTypeLocking, sizeof(SubGhzOpenSesameModel));
    view_set_context(subghz_opensesame->view, subghz_opensesame);
    view_set_draw_callback(
        subghz_opensesame->view, (ViewDrawCallback)subghz_opensesame_draw);
    view_set_input_callback(subghz_opensesame->view, subghz_opensesame_input);
    view_set_enter_callback(subghz_opensesame->view, subghz_opensesame_enter);
    view_set_exit_callback(subghz_opensesame->view, subghz_opensesame_exit);

    with_view_model(
        subghz_opensesame->view, (SubGhzOpenSesameModel* model) {
            string_init(model->frequency_str);
            string_init(model->preset_str);
            return true;
        });

    return subghz_opensesame;
}

void subghz_opensesame_free(SubGhzOpenSesame* subghz_opensesame) {
    furi_assert(subghz_opensesame);
    with_view_model(
        subghz_opensesame->view, (SubGhzOpenSesameModel* model) {
            string_clear(model->frequency_str);
            string_clear(model->preset_str);
            return true;
        });
    view_free(subghz_opensesame->view);
    free(subghz_opensesame);
}

View* subghz_opensesame_get_view(SubGhzOpenSesame* subghz_opensesame) {
    furi_assert(subghz_opensesame);
    return subghz_opensesame->view;
}