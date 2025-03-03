#include "subghz_cli.h"

#include <furi.h>
#include <furi_hal.h>
#include <stream_buffer.h>

#include <lib/toolbox/args.h>
#include <lib/subghz/subghz_keystore.h>

#include <lib/subghz/receiver.h>
#include <lib/subghz/transmitter.h>
#include <lib/subghz/subghz_file_encoder_worker.h>

#include "helpers/subghz_chat.h"

#include <notification/notification_messages.h>
#include <flipper_format/flipper_format_i.h>

#define SUBGHZ_FREQUENCY_RANGE_STR \
    "299999755...348000000 or 386999938...464000000 or 778999847...928000000"

void subghz_cli_command_tx_carrier(Cli* cli, string_t args, void* context) {
    uint32_t frequency = 433920000;

    if(string_size(args)) {
        int ret = sscanf(string_get_cstr(args), "%lu", &frequency);
        if(ret != 1) {
            printf("sscanf returned %d, frequency: %lu\r\n", ret, frequency);
            cli_print_usage("subghz tx_carrier", "<Frequency: in Hz>", string_get_cstr(args));
            return;
        }
        if(!furi_hal_subghz_is_frequency_valid(frequency)) {
            printf(
                "Frequency must be in " SUBGHZ_FREQUENCY_RANGE_STR " range, not %lu\r\n",
                frequency);
            return;
        }
    }

    furi_hal_subghz_reset();
    furi_hal_subghz_load_preset(FuriHalSubGhzPresetOok650Async);
    frequency = furi_hal_subghz_set_frequency_and_path(frequency);

    furi_hal_gpio_init(&gpio_cc1101_g0, GpioModeOutputPushPull, GpioPullNo, GpioSpeedLow);
    furi_hal_gpio_write(&gpio_cc1101_g0, true);

    furi_hal_power_suppress_charge_enter();

    if(furi_hal_subghz_tx()) {
        printf("Transmitting at frequency %lu Hz\r\n", frequency);
        printf("Press CTRL+C to stop\r\n");
        while(!cli_cmd_interrupt_received(cli)) {
            osDelay(250);
        }
    } else {
        printf("This frequency can only be used for RX in your region\r\n");
    }

    furi_hal_subghz_set_path(FuriHalSubGhzPathIsolate);
    furi_hal_subghz_sleep();

    furi_hal_power_suppress_charge_exit();
}

void subghz_cli_command_rx_carrier(Cli* cli, string_t args, void* context) {
    uint32_t frequency = 433920000;

    if(string_size(args)) {
        int ret = sscanf(string_get_cstr(args), "%lu", &frequency);
        if(ret != 1) {
            printf("sscanf returned %d, frequency: %lu\r\n", ret, frequency);
            cli_print_usage("subghz rx_carrier", "<Frequency: in Hz>", string_get_cstr(args));
            return;
        }
        if(!furi_hal_subghz_is_frequency_valid(frequency)) {
            printf(
                "Frequency must be in " SUBGHZ_FREQUENCY_RANGE_STR " range, not %lu\r\n",
                frequency);
            return;
        }
    }

    furi_hal_subghz_reset();
    furi_hal_subghz_load_preset(FuriHalSubGhzPresetOok650Async);
    frequency = furi_hal_subghz_set_frequency_and_path(frequency);
    printf("Receiving at frequency %lu Hz\r\n", frequency);
    printf("Press CTRL+C to stop\r\n");

    furi_hal_power_suppress_charge_enter();

    furi_hal_subghz_rx();

    while(!cli_cmd_interrupt_received(cli)) {
        osDelay(250);
        printf("RSSI: %03.1fdbm\r", furi_hal_subghz_get_rssi());
        fflush(stdout);
    }

    furi_hal_power_suppress_charge_exit();

    furi_hal_subghz_set_path(FuriHalSubGhzPathIsolate);
    furi_hal_subghz_sleep();
}

void subghz_cli_command_tx(Cli* cli, string_t args, void* context) {
    uint32_t frequency = 433920000;
    uint32_t key = 0x0074BADE;
    uint32_t repeat = 10;

    if(string_size(args)) {
        int ret = sscanf(string_get_cstr(args), "%lx %lu %lu", &key, &frequency, &repeat);
        if(ret != 3) {
            printf(
                "sscanf returned %d, key: %lx, frequency: %lu, repeat: %lu\r\n",
                ret,
                key,
                frequency,
                repeat);
            cli_print_usage(
                "subghz tx",
                "<3 Byte Key: in hex> <Frequency: in Hz> <Repeat count>",
                string_get_cstr(args));
            return;
        }
        if(!furi_hal_subghz_is_frequency_valid(frequency)) {
            printf(
                "Frequency must be in " SUBGHZ_FREQUENCY_RANGE_STR " range, not %lu\r\n",
                frequency);
            return;
        }
    }

    printf(
        "Transmitting at %lu, key %lx, repeat %lu. Press CTRL+C to stop\r\n",
        frequency,
        key,
        repeat);

    string_t flipper_format_string;
    string_init_printf(
        flipper_format_string,
        "Protocol: Princeton\n"
        "Bit: 24\n"
        "Key: 00 00 00 00 00 %X %X %X\n"
        "TE: 403\n"
        "Repeat: %d\n",
        (uint8_t)((key >> 16) & 0xFF),
        (uint8_t)((key >> 8) & 0xFF),
        (uint8_t)(key & 0xFF),
        repeat);
    FlipperFormat* flipper_format = flipper_format_string_alloc();
    Stream* stream = flipper_format_get_raw_stream(flipper_format);
    stream_clean(stream);
    stream_write_cstring(stream, string_get_cstr(flipper_format_string));

    SubGhzEnvironment* environment = subghz_environment_alloc();

    SubGhzTransmitter* transmitter = subghz_transmitter_alloc_init(environment, "Princeton");
    subghz_transmitter_deserialize(transmitter, flipper_format);

    furi_hal_subghz_reset();
    furi_hal_subghz_load_preset(FuriHalSubGhzPresetOok650Async);
    frequency = furi_hal_subghz_set_frequency_and_path(frequency);

    furi_hal_power_suppress_charge_enter();

    furi_hal_subghz_start_async_tx(subghz_transmitter_yield, transmitter);

    while(!(furi_hal_subghz_is_async_tx_complete() || cli_cmd_interrupt_received(cli))) {
        printf(".");
        fflush(stdout);
        osDelay(333);
    }
    furi_hal_subghz_stop_async_tx();
    furi_hal_subghz_sleep();

    furi_hal_power_suppress_charge_exit();

    flipper_format_free(flipper_format);
    subghz_transmitter_free(transmitter);
    subghz_environment_free(environment);
}

typedef struct {
    volatile bool overrun;
    StreamBufferHandle_t stream;
    size_t packet_count;
} SubGhzCliCommandRx;

static void subghz_cli_command_rx_capture_callback(bool level, uint32_t duration, void* context) {
    SubGhzCliCommandRx* instance = context;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    LevelDuration level_duration = level_duration_make(level, duration);
    if(instance->overrun) {
        instance->overrun = false;
        level_duration = level_duration_reset();
    }
    size_t ret = xStreamBufferSendFromISR(
        instance->stream, &level_duration, sizeof(LevelDuration), &xHigherPriorityTaskWoken);
    if(sizeof(LevelDuration) != ret) instance->overrun = true;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void subghz_cli_command_rx_callback(
    SubGhzReceiver* receiver,
    SubGhzProtocolDecoderBase* decoder_base,
    void* context) {
    SubGhzCliCommandRx* instance = context;
    instance->packet_count++;

    string_t text;
    string_init(text);
    subghz_protocol_decoder_base_get_string(decoder_base, text);
    subghz_receiver_reset(receiver);
    printf("%s", string_get_cstr(text));
    string_clear(text);
}

void subghz_cli_command_rx(Cli* cli, string_t args, void* context) {
    uint32_t frequency = 433920000;

    if(string_size(args)) {
        int ret = sscanf(string_get_cstr(args), "%lu", &frequency);
        if(ret != 1) {
            printf("sscanf returned %d, frequency: %lu\r\n", ret, frequency);
            cli_print_usage("subghz rx", "<Frequency: in Hz>", string_get_cstr(args));
            return;
        }
        if(!furi_hal_subghz_is_frequency_valid(frequency)) {
            printf(
                "Frequency must be in " SUBGHZ_FREQUENCY_RANGE_STR " range, not %lu\r\n",
                frequency);
            return;
        }
    }

    // Allocate context and buffers
    SubGhzCliCommandRx* instance = malloc(sizeof(SubGhzCliCommandRx));
    instance->stream = xStreamBufferCreate(sizeof(LevelDuration) * 1024, sizeof(LevelDuration));
    furi_check(instance->stream);

    SubGhzEnvironment* environment = subghz_environment_alloc();
    subghz_environment_load_keystore(environment, "/ext/subghz/assets/keeloq_mfcodes");
    subghz_environment_set_came_atomo_rainbow_table_file_name(
        environment, "/ext/subghz/assets/came_atomo");
    subghz_environment_set_nice_flor_s_rainbow_table_file_name(
        environment, "/ext/subghz/assets/nice_flor_s");

    SubGhzReceiver* receiver = subghz_receiver_alloc_init(environment);
    subghz_receiver_set_filter(receiver, SubGhzProtocolFlag_Decodable);
    subghz_receiver_set_rx_callback(receiver, subghz_cli_command_rx_callback, instance);

    // Configure radio
    furi_hal_subghz_reset();
    furi_hal_subghz_load_preset(FuriHalSubGhzPresetOok650Async);
    frequency = furi_hal_subghz_set_frequency_and_path(frequency);
    furi_hal_gpio_init(&gpio_cc1101_g0, GpioModeInput, GpioPullNo, GpioSpeedLow);

    furi_hal_power_suppress_charge_enter();

    // Prepare and start RX
    furi_hal_subghz_start_async_rx(subghz_cli_command_rx_capture_callback, instance);

    // Wait for packets to arrive
    printf("Listening at %lu. Press CTRL+C to stop\r\n", frequency);
    LevelDuration level_duration;
    while(!cli_cmd_interrupt_received(cli)) {
        int ret =
            xStreamBufferReceive(instance->stream, &level_duration, sizeof(LevelDuration), 10);
        if(ret == sizeof(LevelDuration)) {
            if(level_duration_is_reset(level_duration)) {
                printf(".");
                subghz_receiver_reset(receiver);
            } else {
                bool level = level_duration_get_level(level_duration);
                uint32_t duration = level_duration_get_duration(level_duration);
                subghz_receiver_decode(receiver, level, duration);
            }
        }
    }

    // Shutdown radio
    furi_hal_subghz_stop_async_rx();
    furi_hal_subghz_sleep();

    furi_hal_power_suppress_charge_exit();

    printf("\r\nPackets recieved %u\r\n", instance->packet_count);

    // Cleanup
    subghz_receiver_free(receiver);
    subghz_environment_free(environment);
    vStreamBufferDelete(instance->stream);
    free(instance);
}

void subghz_cli_command_decode_raw(Cli* cli, string_t args, void* context) {
    string_t file_name;
    string_init(file_name);
    string_set(file_name, "/any/subghz/test.sub");

    Storage* storage = furi_record_open("storage");
    FlipperFormat* fff_data_file = flipper_format_file_alloc(storage);
    string_t temp_str;
    string_init(temp_str);
    uint32_t temp_data32;
    bool check_file = false;

    do {
        if(string_size(args)) {
            if(!args_read_string_and_trim(args, file_name)) {
                cli_print_usage(
                    "subghz decode_raw", "<file_name: path_RAW_file>", string_get_cstr(args));
                break;
            }
        }

        if(!flipper_format_file_open_existing(fff_data_file, string_get_cstr(file_name))) {
            printf(
                "subghz decode_raw \033[0;31mError open file\033[0m %s\r\n",
                string_get_cstr(file_name));
            break;
        }

        if(!flipper_format_read_header(fff_data_file, temp_str, &temp_data32)) {
            printf("subghz decode_raw \033[0;31mMissing or incorrect header\033[0m\r\n");
            break;
        }

        if(!strcmp(string_get_cstr(temp_str), SUBGHZ_RAW_FILE_TYPE) &&
           temp_data32 == SUBGHZ_KEY_FILE_VERSION) {
        } else {
            printf("subghz decode_raw \033[0;31mType or version mismatch\033[0m\r\n");
            break;
        }

        check_file = true;
    } while(false);

    string_clear(temp_str);
    flipper_format_free(fff_data_file);
    furi_record_close("storage");

    if(check_file) {
        // Allocate context
        SubGhzCliCommandRx* instance = malloc(sizeof(SubGhzCliCommandRx));

        SubGhzEnvironment* environment = subghz_environment_alloc();
        if(subghz_environment_load_keystore(environment, "/ext/subghz/assets/keeloq_mfcodes")) {
            printf("SubGhz test: Load_keystore \033[0;32mOK\033[0m\r\n");
        } else {
            printf("SubGhz test: Load_keystore \033[0;31mERROR\033[0m\r\n");
        }
        subghz_environment_set_came_atomo_rainbow_table_file_name(
            environment, "/ext/subghz/assets/came_atomo");
        subghz_environment_set_nice_flor_s_rainbow_table_file_name(
            environment, "/ext/subghz/assets/nice_flor_s");

        SubGhzReceiver* receiver = subghz_receiver_alloc_init(environment);
        subghz_receiver_set_filter(receiver, SubGhzProtocolFlag_Decodable);
        subghz_receiver_set_rx_callback(receiver, subghz_cli_command_rx_callback, instance);

        SubGhzFileEncoderWorker* file_worker_encoder = subghz_file_encoder_worker_alloc();
        if(subghz_file_encoder_worker_start(file_worker_encoder, string_get_cstr(file_name))) {
            //the worker needs a file in order to open and read part of the file
            osDelay(100);
        }

        printf(
            "Listening at \033[0;33m%s\033[0m.\r\n\r\nPress CTRL+C to stop\r\n\r\n",
            string_get_cstr(file_name));

        LevelDuration level_duration;
        while(!cli_cmd_interrupt_received(cli)) {
            furi_hal_delay_us(500); //you need to have time to read from the file from the SD card
            level_duration = subghz_file_encoder_worker_get_level_duration(file_worker_encoder);
            if(!level_duration_is_reset(level_duration)) {
                bool level = level_duration_get_level(level_duration);
                uint32_t duration = level_duration_get_duration(level_duration);
                subghz_receiver_decode(receiver, level, duration);
            } else {
                break;
            }
        }

        printf("\r\nPackets recieved \033[0;32m%u\033[0m\r\n", instance->packet_count);

        // Cleanup
        subghz_receiver_free(receiver);
        subghz_environment_free(environment);

        if(subghz_file_encoder_worker_is_running(file_worker_encoder)) {
            subghz_file_encoder_worker_stop(file_worker_encoder);
        }
        subghz_file_encoder_worker_free(file_worker_encoder);
        free(instance);
    }
    string_clear(file_name);
}

static void subghz_cli_command_print_usage() {
    printf("Usage:\r\n");
    printf("subghz <cmd> <args>\r\n");
    printf("Cmd list:\r\n");

    printf("\tchat <frequency:in Hz>\t - Chat with other Flippers\r\n");
    printf(
        "\ttx <3 byte Key: in hex> <frequency: in Hz> <repeat: count>\t - Transmitting key\r\n");
    printf("\trx <frequency:in Hz>\t - Reception key\r\n");
    printf("\tdecode_raw <file_name: path_RAW_file>\t - Testing\r\n");

    if(furi_hal_rtc_is_flag_set(FuriHalRtcFlagDebug)) {
        printf("\r\n");
        printf("  debug cmd:\r\n");
        printf("\ttx_carrier <frequency:in Hz>\t - Transmit carrier\r\n");
        printf("\trx_carrier <frequency:in Hz>\t - Receiv carrier\r\n");
        printf(
            "\tencrypt_keeloq <path_decrypted_file> <path_encrypted_file> <IV:16 bytes in hex>\t - Encrypt keeloq manufacture keys\r\n");
        printf(
            "\tencrypt_raw <path_decrypted_file> <path_encrypted_file> <IV:16 bytes in hex>\t - Encrypt RAW data\r\n");
    }
}

static void subghz_cli_command_encrypt_keeloq(Cli* cli, string_t args) {
    uint8_t iv[16];

    string_t source;
    string_t destination;
    string_init(source);
    string_init(destination);

    SubGhzKeystore* keystore = subghz_keystore_alloc();

    do {
        if(!args_read_string_and_trim(args, source)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!args_read_string_and_trim(args, destination)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!args_read_hex_bytes(args, iv, 16)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!subghz_keystore_load(keystore, string_get_cstr(source))) {
            printf("Failed to load Keystore");
            break;
        }

        if(!subghz_keystore_save(keystore, string_get_cstr(destination), iv)) {
            printf("Failed to save Keystore");
            break;
        }
    } while(false);

    subghz_keystore_free(keystore);
    string_clear(destination);
    string_clear(source);
}

static void subghz_cli_command_encrypt_raw(Cli* cli, string_t args) {
    uint8_t iv[16];

    string_t source;
    string_t destination;
    string_init(source);
    string_init(destination);

    do {
        if(!args_read_string_and_trim(args, source)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!args_read_string_and_trim(args, destination)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!args_read_hex_bytes(args, iv, 16)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(!subghz_keystore_raw_encrypted_save(
               string_get_cstr(source), string_get_cstr(destination), iv)) {
            printf("Failed to save Keystore");
            break;
        }

    } while(false);

    string_clear(destination);
    string_clear(source);
}

static void subghz_cli_command_chat(Cli* cli, string_t args) {
    uint32_t frequency = 433920000;

    if(string_size(args)) {
        int ret = sscanf(string_get_cstr(args), "%lu", &frequency);
        if(ret != 1) {
            printf("sscanf returned %d, frequency: %lu\r\n", ret, frequency);
            cli_print_usage("subghz chat", "<Frequency: in Hz>", string_get_cstr(args));
            return;
        }
        if(!furi_hal_subghz_is_frequency_valid(frequency)) {
            printf(
                "Frequency must be in " SUBGHZ_FREQUENCY_RANGE_STR " range, not %lu\r\n",
                frequency);
            return;
        }
    }
    if(!furi_hal_subghz_is_tx_allowed(frequency)) {
        printf(
            "In your region, only reception on this frequency (%lu) is allowed,\r\n"
            "the actual operation of the application is not possible\r\n ",
            frequency);
        return;
    }

    SubGhzChatWorker* subghz_chat = subghz_chat_worker_alloc(cli);
    if(!subghz_chat_worker_start(subghz_chat, frequency)) {
        printf("Startup error SubGhzChatWorker\r\n");

        if(subghz_chat_worker_is_running(subghz_chat)) {
            subghz_chat_worker_stop(subghz_chat);
            subghz_chat_worker_free(subghz_chat);
        }
        return;
    }

    printf("Receiving at frequency %lu Hz\r\n", frequency);
    printf("Press CTRL+C to stop\r\n");

    furi_hal_power_suppress_charge_enter();

    size_t message_max_len = 64;
    uint8_t message[64] = {0};
    string_t input;
    string_init(input);
    string_t name;
    string_init(name);
    string_t output;
    string_init(output);
    string_t sysmsg;
    string_init(sysmsg);
    bool exit = false;
    SubGhzChatEvent chat_event;

    NotificationApp* notification = furi_record_open("notification");

    string_printf(name, "\033[0;33m%s\033[0m: ", furi_hal_version_get_name_ptr());
    string_set(input, name);
    printf("%s", string_get_cstr(input));
    fflush(stdout);

    while(!exit) {
        chat_event = subghz_chat_worker_get_event_chat(subghz_chat);
        switch(chat_event.event) {
        case SubGhzChatEventInputData:
            if(chat_event.c == CliSymbolAsciiETX) {
                printf("\r\n");
                chat_event.event = SubGhzChatEventUserExit;
                subghz_chat_worker_put_event_chat(subghz_chat, &chat_event);
                break;
            } else if(
                (chat_event.c == CliSymbolAsciiBackspace) || (chat_event.c == CliSymbolAsciiDel)) {
                size_t len = string_length_u(input);
                if(len > string_length_u(name)) {
                    printf("%s", "\e[D\e[1P");
                    fflush(stdout);
                    //delete 1 char UTF
                    const char* str = string_get_cstr(input);
                    size_t size = 0;
                    m_str1ng_utf8_state_e s = M_STRING_UTF8_STARTING;
                    string_unicode_t u = 0;
                    string_reset(sysmsg);
                    while(*str) {
                        m_str1ng_utf8_decode(*str, &s, &u);
                        if((s == M_STRING_UTF8_ERROR) || s == M_STRING_UTF8_STARTING) {
                            string_push_u(sysmsg, u);
                            if(++size >= len - 1) break;
                            s = M_STRING_UTF8_STARTING;
                        }
                        str++;
                    }
                    string_set(input, sysmsg);
                }
            } else if(chat_event.c == CliSymbolAsciiCR) {
                printf("\r\n");
                string_push_back(input, '\r');
                string_push_back(input, '\n');
                while(!subghz_chat_worker_write(
                    subghz_chat,
                    (uint8_t*)string_get_cstr(input),
                    strlen(string_get_cstr(input)))) {
                    furi_hal_delay_ms(10);
                }

                string_printf(input, "%s", string_get_cstr(name));
                printf("%s", string_get_cstr(input));
                fflush(stdout);
            } else if(chat_event.c == CliSymbolAsciiLF) {
                //cut out the symbol \n
            } else {
                putc(chat_event.c, stdout);
                fflush(stdout);
                string_push_back(input, chat_event.c);
                break;
            case SubGhzChatEventRXData:
                do {
                    memset(message, 0x00, message_max_len);
                    size_t len = subghz_chat_worker_read(subghz_chat, message, message_max_len);
                    for(size_t i = 0; i < len; i++) {
                        string_push_back(output, message[i]);
                        if(message[i] == '\n') {
                            printf("\r");
                            for(uint8_t i = 0; i < 80; i++) {
                                printf(" ");
                            }
                            printf("\r %s", string_get_cstr(output));
                            printf("%s", string_get_cstr(input));
                            fflush(stdout);
                            string_reset(output);
                        }
                    }
                } while(subghz_chat_worker_available(subghz_chat));
                break;
            case SubGhzChatEventNewMessage:
                notification_message(notification, &sequence_single_vibro);
                break;
            case SubGhzChatEventUserEntrance:
                string_printf(
                    sysmsg,
                    "\033[0;34m%s joined chat.\033[0m\r\n",
                    furi_hal_version_get_name_ptr());
                subghz_chat_worker_write(
                    subghz_chat,
                    (uint8_t*)string_get_cstr(sysmsg),
                    strlen(string_get_cstr(sysmsg)));
                break;
            case SubGhzChatEventUserExit:
                string_printf(
                    sysmsg, "\033[0;31m%s left chat.\033[0m\r\n", furi_hal_version_get_name_ptr());
                subghz_chat_worker_write(
                    subghz_chat,
                    (uint8_t*)string_get_cstr(sysmsg),
                    strlen(string_get_cstr(sysmsg)));
                furi_hal_delay_ms(10);
                exit = true;
                break;
            default:
                FURI_LOG_W("SubGhzChat", "Error event");
                break;
            }
        }
    }

    string_clear(input);
    string_clear(name);
    string_clear(output);
    string_clear(sysmsg);
    furi_hal_power_suppress_charge_exit();
    furi_record_close("notification");

    if(subghz_chat_worker_is_running(subghz_chat)) {
        subghz_chat_worker_stop(subghz_chat);
        subghz_chat_worker_free(subghz_chat);
    }
    printf("\r\nExit chat\r\n");
}

static void subghz_cli_command(Cli* cli, string_t args, void* context) {
    string_t cmd;
    string_init(cmd);

    do {
        if(!args_read_string_and_trim(args, cmd)) {
            subghz_cli_command_print_usage();
            break;
        }

        if(string_cmp_str(cmd, "chat") == 0) {
            subghz_cli_command_chat(cli, args);
            break;
        }

        if(string_cmp_str(cmd, "tx") == 0) {
            subghz_cli_command_tx(cli, args, context);
            break;
        }

        if(string_cmp_str(cmd, "rx") == 0) {
            subghz_cli_command_rx(cli, args, context);
            break;
        }

        if(string_cmp_str(cmd, "decode_raw") == 0) {
            subghz_cli_command_decode_raw(cli, args, context);
            break;
        }

        if(furi_hal_rtc_is_flag_set(FuriHalRtcFlagDebug)) {
            if(string_cmp_str(cmd, "encrypt_keeloq") == 0) {
                subghz_cli_command_encrypt_keeloq(cli, args);
                break;
            }

            if(string_cmp_str(cmd, "encrypt_raw") == 0) {
                subghz_cli_command_encrypt_raw(cli, args);
                break;
            }

            if(string_cmp_str(cmd, "tx_carrier") == 0) {
                subghz_cli_command_tx_carrier(cli, args, context);
                break;
            }

            if(string_cmp_str(cmd, "rx_carrier") == 0) {
                subghz_cli_command_rx_carrier(cli, args, context);
                break;
            }
        }

        subghz_cli_command_print_usage();
    } while(false);

    string_clear(cmd);
}

void subghz_on_system_start() {
#ifdef SRV_CLI
    Cli* cli = furi_record_open("cli");

    cli_add_command(cli, "subghz", CliCommandFlagDefault, subghz_cli_command, NULL);

    furi_record_close("cli");
#else
    UNUSED(subghz_cli_command);
#endif
}
