#include "../subghz_i.h"
#include "../views/subghz_opensesame.h"

static void subghz_scene_opensesame_update_statusbar(void* context) {
    furi_assert(context);
    SubGhz* subghz = context;

    string_t frequency_str;
    string_t modulation_str;

    string_init(frequency_str);
    string_init(modulation_str);

    subghz_get_frequency_modulation(subghz, frequency_str, modulation_str);
    subghz_opensesame_add_data_statusbar(
        subghz->subghz_opensesame, string_get_cstr(frequency_str), string_get_cstr(modulation_str));

    string_clear(frequency_str);
    string_clear(modulation_str);
}

void subghz_scene_opensesame_callback(SubGhzCustomEvent event, void* context) {
    furi_assert(context);
    SubGhz* subghz = context;
    view_dispatcher_send_custom_event(subghz->view_dispatcher, event);
}

void subghz_scene_opensesame_on_enter(void* context) {
    SubGhz* subghz = context;

    subghz_scene_opensesame_update_statusbar(subghz);
    subghz_opensesame_set_callback(
        subghz->subghz_opensesame, subghz_scene_opensesame_callback, subghz);
    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdOpenSesame);
}

bool subghz_scene_opensesame_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;
    if(event.type == SceneManagerEventTypeCustom) {
        // event callbacks
        switch(event.event) {
        case SubGhzCustomEventViewOpenSesameConfig:
            scene_manager_set_scene_state(
                subghz->scene_manager, SubGhzSceneOpenSesame, SubGhzCustomEventManagerSet);
            scene_manager_next_scene(subghz->scene_manager, SubGhzSceneReceiverConfig);
            return true;
            break;
        case SubGhzCustomEventViewOpenSesameTxStart:
            //return true;
            break;
        case SubGhzCustomEventViewOpenSesameTxStop:
            //Stop TX
            if(subghz->txrx->txrx_state == SubGhzTxRxStateTx) {
                subghz_tx_stop(subghz);
                subghz_sleep(subghz);
            }
            subghz->state_notifications = SubGhzNotificationStateIDLE;
            break;
        case SubGhzCustomEventViewOpenSesameBack:
            //Stop TX
            if(subghz->txrx->txrx_state == SubGhzTxRxStateTx) {
                subghz_tx_stop(subghz);
                subghz_sleep(subghz);
            }
            subghz->state_notifications = SubGhzNotificationStateIDLE;

            //Restore default setting
            subghz->txrx->frequency = subghz_setting_get_default_frequency(subghz->setting);
            subghz->txrx->preset = FuriHalSubGhzPresetOok650Async;

            //Return to previous scene
            if(!scene_manager_search_and_switch_to_previous_scene(
                   subghz->scene_manager, SubGhzSceneSaved)) {
                if(!scene_manager_search_and_switch_to_previous_scene(
                    subghz->scene_manager, SubGhzSceneStart)) {
                    scene_manager_stop(subghz->scene_manager);
                    view_dispatcher_stop(subghz->view_dispatcher);
                }
            }
            return true;
            break;
        default:
            break;
        }
    }
    return false;
}

void subghz_scene_opensesame_on_exit(void* context) {
    SubGhz* subghz = context;

    //Stop CC1101
    if(subghz->txrx->txrx_state == SubGhzTxRxStateRx) {
        subghz_rx_end(subghz);
        subghz_sleep(subghz);
    };
    subghz->state_notifications = SubGhzNotificationStateIDLE;

    //filter restoration
    subghz_receiver_set_filter(subghz->txrx->receiver, SubGhzProtocolFlag_Decodable);
}