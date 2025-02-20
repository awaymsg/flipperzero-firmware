<h3 align="center">
    <a href="https://github.com/DarkFlippers/unleashed-firmware">
        <img src="https://github.com/user-attachments/assets/466c40d5-f6a1-444d-a235-d9026f7cd0ff" align="center" alt="Unleashed Firmware Logo" border="0">  
    </a>
</h3>

<div align="center" id="badges">
    <a href="https://t.me/flipperzero_unofficial">
       <img src="https://img.shields.io/endpoint?color=neon&style=flat&url=https%3A%2F%2Ftg.sumanjay.workers.dev%2Fflipperzero_unofficial" alt="English Telegram Chat"/>  
    </a>
    <a href="https://t.me/flipperzero_unofficial_ru">
       <img src="https://img.shields.io/endpoint?color=neon&style=flat&url=https%3A%2F%2Ftg.sumanjay.workers.dev%2Fflipperzero_unofficial_ru" alt="Russian Telegram Chat"/>  
    </a>
    <a href="https://t.me/flipperzero_unofficial_ua">
       <img src="https://img.shields.io/endpoint?color=neon&style=flat&url=https%3A%2F%2Ftg.sumanjay.workers.dev%2Fflipperzero_unofficial_ua" alt="Ukraine Telegram Chat"/>  
    </a>
    <br>
    <a href="https://discord.unleashedflip.com">
       <img src="https://img.shields.io/discord/937479784148115456?style=flat&logo=discord&label=Discord&color=%237289DA&link=https%3A%2F%2Fdiscord.unleashedflip.com%2F" alt="Discord server"/>  
    </a>
</div>

# Flipper Zero Unleashed Firmware
This firmware is a fork of the original (OFW) version of [flipperdevices/flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware) and represents the **most stable** custom build, incorporating **new features** and **improvements** to the original components while remaining **fully compatible** with the API and applications of the original firmware.

> [!WARNING]
> This software is intended solely for experimental purposes and is not meant for any illegal activities.
> We do not condone unlawful behavior and strongly encourage you to use it only within the bounds of the law.
>
> This project is developed independently and is not affiliated with Flipper Devices.

<br/>

## 🚀 Usage

Before getting started:
- **Review the Official Documentation:** [docs.flipper.net](https://docs.flipper.net)

- **Installation Guide & Version Info:**  
  How to install the firmware by following the [Installation Guide](/documentation/HowToInstall.md) and check the [version information](/CHANGELOG.md#recommended-update-option---web-updater) (`r`, `e`, ` `, `c`)

- **FAQ:**  
  Find answers to common questions in the [FAQ](/documentation/FAQ.md)


## 📦 Releases

### Release builds (stable)
- <img src="https://github.com/badges/shields/assets/10694593/c5c5acc3-f434-4a8d-a834-6d94a7ffb45a" alt="Telegram" title="Telegram" width="14" height="14"> Telegram: <a href="https://t.me/unleashed_fw">t.me/unleashed_fw</a>
- <a href="https://github.com/DarkFlippers/unleashed-firmware/releases"> <img src="https://cdn.simpleicons.org/github/black/white" alt="GitHub" title="" width="14" height="14"> GitHub Releases</a>

### Dev builds (unstable)
> [!NOTE]
> Built automatically from dev branch

- Web site: https://dev.unleashedflip.com
- <img src="https://github.com/badges/shields/assets/10694593/c5c5acc3-f434-4a8d-a834-6d94a7ffb45a" alt="Telegram" title="Telegram" width="14" height="16"> Telegram: <a href="https://t.me/kotnehleb">t.me/kotnehleb</a>


## 🆕 What's New

> <details>
> <summary><strong>Sub‑GHz Library & HAL</strong></summary>
> <br/>
>
> - Regional TX restrictions removed
> - Extra Sub-GHz frequencies added
> - Frequency range can be extended in settings file (Warning: It can damage Flipper's hardware)
> - Many rolling code [protocols](#current-modified-and-new-sub-ghz-protocols-list) now have the ability to save & send captured signals  
> - FAAC SLH (Spa) & BFT Mitto (keeloq secure with seed) manual creation
> - External CC1101 module support [(by quen0n)](https://github.com/DarkFlippers/unleashed-firmware/pull/307)
> </details>

> <details>
> <summary><strong>Sub‑GHz Main App</strong></summary>
> <br/>
> 
> - Save last used settings [(by derskythe)](https://github.com/DarkFlippers/unleashed-firmware/pull/77)
> - New frequency analyzer [(by ClusterM)](https://github.com/DarkFlippers/unleashed-firmware/pull/43)
> - Press OK in frequency analyzer to use detected frequency in Read modes [(by derskythe)](https://github.com/DarkFlippers/unleashed-firmware/pull/77)  
> - Long press OK button in Sub-GHz Frequency analyzer to switch to Read menu [(by derskythe)](https://github.com/DarkFlippers/unleashed-firmware/pull/79)  
> - New option to use timestamps + protocol name when you saving file, instead of random name or timestamp only - Enable in `Radio Settings -> Protocol Names = ON`  
> - Read mode UI improvements (shows time when signal was received) (by @wosk)
> - External CC1101 module support (Hardware SPI used)
> - External CC1101 module amplifier control (or LED control) support (enabled by default)
> - **Hold right in received signal list to delete selected signal**
>- **Custom buttons for Keeloq / Alutech AT4N / Nice Flor S / Somfy Telis / Security+ 2.0 / CAME Atomo** - now you can use arrow buttons to send signal with different button code  
> - `Add manually` menu extended with new protocols
> - FAAC SLH, BFT Mitto / Somfy Telis / Nice Flor S / CAME Atomo, etc. manual creation with programming new remote into receiver (use button 0xF for BFT Mitto, 0x8 (Prog) on Somfy Telis, (right arrow button for other protocols))  
> - Debug mode counter increase settings (+1 -> +5, +10, default: +1)
> - Debug PIN output settings for protocol development
> </details>

> <details>
> <summary><strong>Sub‑GHz Apps (by Unleashed Team)</strong></summary>
> <br/>
> 
> - Sub-GHz Bruteforce - static code brute-force plugin
> - Time delay (between signals) setting (hold Up in main screen (says Up to Save)) + configure repeats in protocols list by pressing right button on selected protocol  
> - Load your own file and select bytes you want to bruteforce or use preconfigured options in protocols list  
> - Sub-GHz Remote - remote control for 5 sub-ghz files | bind one file for each button  
> - use the built-in constructor or make config file by following this [instruction](/documentation/SubGHzRemotePlugin.md)  
> </details>

> <details>
> <summary><strong>Infrared (IR)</strong></summary>
> <br/>
> 
> - Recompiled IR TV Universal Remote for ALL buttons
> - Universal remotes for Projectors, Fans, A/Cs and Audio(soundbars, etc.) -> Also always updated and verified by our team  
> - Infrared -> `RCA` Protocol
> - Infrared -> External IR modules support (with autodetect by OFW)
> </details>

> <details>
> <summary><strong>NFC/RFID/iButton</strong></summary>
> <br/>
> 
> - LFRFID and iButton Fuzzer plugins
> - Add DEZ 8 display form for EM4100 (by @korden32)
> - Extra Mifare Classic keys in system dict
> - EMV Protocol + Public data parser (by @Leptopt1los and @wosk)
> - NFC `Add manually` -> Mifare Classic with custom UID
> - NFC parsers: Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow Social Card, Troika (reworked) and [many others](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards) (by @Leptopt1los and @assasinfil)
> </details>

> <details>
> <summary><strong>Quality of Life & Other Features</strong></summary>
> <br/>
> 
> - Customizable Flipper name **Update! Now can be changed in Settings->Desktop** (by @xMasterX and @Willy-JL)
> - Text Input UI element -> Cursor feature (by @Willy-JL)
> - Byte Input Mini editor -> **Press UP** multiple times until the nibble editor appears (by @gid9798)
> - Clock on Desktop -> `Settings -> Desktop -> Show Clock` (by @gid9798)
> - Battery percentage display with different styles `Settings -> Desktop -> Battery View`
> - More games in Dummy Mode -> click or hold any of arrow buttons
> - Lock device with pin (or regular lock if pin not set) by holding UP button on main screen [(by an4tur0r)](https://github.com/DarkFlippers/unleashed-firmware/pull/107)  
> - **BadKB** plugin [(by Willy-JL, ClaraCrazy, XFW contributors)](https://github.com/Flipper-XFW/Xtreme-Firmware/tree/dev/applications/main/bad_kb) - (See in Applications->Tools) - (aka BadUSB via Bluetooth)  
> - BadUSB -> Keyboard layouts [(by rien > dummy-decoy)](https://github.com/dummy-decoy/flipperzero-firmware/tree/dummy_decoy/bad_usb_keyboard_layout)  
> - Custom community plugins and games added + all known working apps can be downloaded in extra pack in every release  
> - Other small fixes and changes throughout
> - See other changes in readme below
> </details>

Also check the [changelog in releases](https://github.com/DarkFlippers/unleashed-firmware/releases) for latest updates!

### Current modified and new Sub-GHz protocols list:
Thanks to Official team (to their SubGHz Developer, Skorp) for implementing support (decoder + encoder / or decode only) for these protocols in OFW.  

> [!NOTE]
> Not ALL Keeloq systems are supported for decoding or emulation!
> <details>
> <summary><strong>Supported manufacturers include</strong></summary>
> <br/>
>
> ```
> DoorHan, Alligator, Stilmatic, Mongoose, SL_A6-A9/Tomahawk_9010, Pantera, SL_A2-A4, Cenmax_St-5, SL_B6,B9_dop, Harpoon, Tomahawk_TZ-9030, Tomahawk_Z,X_3-5, Cenmax_St-7, Sheriff, Pantera_CLK, Cenmax, Alligator_S-275, Guard_RF-311A, Partisan_RX, APS-1100_APS-2550, Pantera_XS/Jaguar, NICE_Smilo, NICE_MHOUSE, Dea_Mio, Genius_Bravo, FAAC_RC,XT, FAAC_SLH, BFT, Came_Space, DTM_Neo, GSN, Beninca, Elmes_Poland, IronLogic, Comunello, Sommer(fsk476), Normstahl, KEY, JCM_Tech, EcoStar, Gibidi, Aprimatic, Kingates_Stylo4k, Centurion, KGB/Subaru, Magic_1, Magic_2, Magic_3, Magic_4, Teco, Mutanco_Mutancode, Leopard, Faraon, Reff, ZX-730-750-1055
> ```
</details>

<br/>

<details>
<summary><code><strong>Decoders/Encoders or emulation (+ programming mode) support made by @xMasterX</strong></code></summary>
<br/>

- Marantec24 (static 24 bit) with add manually support
- GangQi (static 34 bit) with button parsing and add manually support (thanks to @mishamyte for captures and testing, thanks @Skorpionm for help)  
- Hollarm (static 42 bit) with button parsing and add manually support (thanks to @mishamyte for captures, thanks @Skorpionm for help)  
- Hay21 (dynamic 21 bit) with button parsing
- Nero Radio 57bit (+ 56bit support)
- CAME 12bit/24bit encoder fixes (Fixes are now merged in OFW)
- Keeloq: Dea Mio, Genius Bravo, GSN, HCS101, AN-Motors, JCM Tech, MHouse, Nice Smilo, DTM Neo, FAAC RC,XT, Mutancode, Normstahl, Beninca + Allmatic, Stilmatic, CAME Space, Aprimatic (model TR and similar), Centurion Nova (thanks Carlos !), Hormann EcoStar, Novoferm, Sommer, Monarch (thanks @ashphx !)
</details>

<details>
<summary><code><strong>Protocols support made by Skorp (original implementation) and @xMasterX (current version)</strong></code></summary>
<br/>

- CAME Atomo -> Update! check out new [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- Nice Flor S -> How to create new remote - [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- FAAC SLH (Spa) -> Update!!! (Programming mode!) Check out new [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- Keeloq: BFT Mitto -> Update! Check out new [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- Star Line
- Security+ v1 & v2
</details>

<details>
<summary><code><strong>Encoders made by @assasinfil and @xMasterX</strong></code></summary>
<br/>

- Somfy Telis -> How to create new remote - [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- Somfy Keytis
- KingGates Stylo 4k
- Alutech AT-4N -> How to create new remote - [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- Nice ON2E (Nice One) -> How to create new remote - [instructions](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)
</details>


## ❤️ Please support development of the project

The majority of this project is developed and maintained by me, @xMasterX.
Our team is small and the guys are working on this project as much as they can solely based on the enthusiasm they have for this project and the community.  
- @Leptopt1los - NFC, RFID, Plugins, and many other things
- @gid9798 - SubGHz, Plugins, many other things - currently offline :( 
- @assasinfil - SubGHz protocols, NFC parsers
- @Svaarich - UI design and animations
- @amec0e - Infrared assets
- Community moderators in Telegram, Discord, and Reddit
- And of course our GitHub community. Your PRs are a very important part of this firmware and open-source development.

The amount of work done on this project is huge and we need your support, no matter how large or small. Even if you just say, "Thank you Unleashed firmware developers!" somewhere. Doing so will help us continue our work and will help drive us to make the firmware better every time.
Also, regarding our releases, every build has and always will be free and open-source. There will be no paywall releases or closed-source apps within the firmware. As long as I am working on this project it will never happen.  
You can support us by using links or addresses below:
|Service|Remark|QR Code|Link/Wallet|
|-|-|-|-|
|**Patreon**||<div align="center"><a href="https://github.com/user-attachments/assets/a88a90a5-28c3-40b4-864a-0c0b79494a42"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|https://patreon.com/mmxdev|
|**Boosty**|patreon alternative|<div align="center"><a href="https://github.com/user-attachments/assets/893c0760-f738-42c1-acaa-916019a7bdf8"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|https://boosty.to/mmxdev|
|cloudtips|only RU payments accepted|<div align="center"><a href="https://github.com/user-attachments/assets/5de31d6a-ef24-4d30-bd8e-c06af815332a"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|https://pay.cloudtips.ru/p/7b3e9d65|
|YooMoney|only RU payments accepted|<div align="center"><a href="https://github.com/user-attachments/assets/33454f79-074b-4349-b453-f94fdadc3c68"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|https://yoomoney.ru/fundraise/XA49mgQLPA0.221209|
|USDT|(TRC20)|<div align="center"><a href="https://github.com/user-attachments/assets/0500498d-18ed-412d-a1a4-8a66d0b6f057"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`TSXcitMSnWXUFqiUfEXrTVpVewXy2cYhrs`|
|ETH|(BSC/ERC20-Tokens)|<div align="center"><a href="https://github.com/user-attachments/assets/0f323e98-c524-4f41-abb2-f4f1cec83ab6"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`0xFebF1bBc8229418FF2408C07AF6Afa49152fEc6a`|
|BTC||<div align="center"><a href="https://github.com/user-attachments/assets/5a904d45-947e-4b92-9f0f-7fbaaa7b37f8"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`bc1q0np836jk9jwr4dd7p6qv66d04vamtqkxrecck9`|
|SOL|(Solana/Tokens)|<div align="center"><a href="https://github.com/user-attachments/assets/ab33c5e0-dd59-497b-9c91-ceb89c36b34d"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`DSgwouAEgu8iP5yr7EHHDqMNYWZxAqXWsTEeqCAXGLj8`|
|DOGE||<div align="center"><a href="https://github.com/user-attachments/assets/2937edd0-5c85-4465-a444-14d4edb481c0"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`D6R6gYgBn5LwTNmPyvAQR6bZ9EtGgFCpvv`|
|LTC||<div align="center"><a href="https://github.com/user-attachments/assets/441985fe-f028-4400-83c1-c215760c1e74"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`ltc1q3ex4ejkl0xpx3znwrmth4lyuadr5qgv8tmq8z9`|
|BCH||<div align="center"><a href="https://github.com/user-attachments/assets/7f365976-19a3-4777-b17e-4bfba5f69eff"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`qquxfyzntuqufy2dx0hrfr4sndp0tucvky4sw8qyu3`|
|XMR|(Monero)|<div align="center"><a href="https://github.com/user-attachments/assets/96186c06-61e7-4b4d-b716-6eaf1779bfd8"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`41xUz92suUu1u5Mu4qkrcs52gtfpu9rnZRdBpCJ244KRHf6xXSvVFevdf2cnjS7RAeYr5hn9MsEfxKoFDRSctFjG5fv1Mhn`|
|TON||<div align="center"><a href="https://github.com/user-attachments/assets/92a57e57-7462-42b7-a342-6f22c6e600c1"><img src="https://github.com/user-attachments/assets/da3a864d-d1c7-42cc-8a86-6fcaf26663ec" alt="QR image"/></a></div>|`UQCOqcnYkvzOZUV_9bPE_8oTbOrOF03MnF-VcJyjisTZmsxa`|


## 📱 Community Apps

Enhance your Flipper Zero with apps and plugins created by the community:

- **Extra Plugins & Packs:**  
  Check out the latest extra plugins and plugin packs (Extra Pack and Base Pack) on [GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).

- **Source Code & Full List:**  
  Find the complete list and source code at [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).

- **Official Apps Catalog:**  
  Browse the official Flipper Zero Apps Catalog on the [web](https://lab.flipper.net/apps) or via the [mobile app](https://flipperzero.one/downloads).


## 📁 Where I can find IR, Sub-GHz, ... files, DBs, and other stuff?
- [UberGuidoZ Playground - Large collection of files - Github](https://github.com/UberGuidoZ/Flipper) 
- [Awesome Flipper Zero - Github](https://github.com/djsime1/awesome-flipperzero)


## 📘 Instructions

### Firmware & main Apps feature

- System: [How to change Flipper name](/documentation/CustomFlipperName.md)
- BadUSB: [How to add new keyboard layouts](https://github.com/dummy-decoy/flipperzero_badusb_kl)
- Infrared: [How to make captures to add them into Universal IR remotes](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md)  

### Sub-GHz

- [How to use Flipper as new remote (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors, etc..)](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md)  
- External Radio: [How to connect CC1101 module](https://github.com/quen0n/flipperzero-ext-cc1101)  
- Transmission is blocked? [How to extend Sub-GHz frequency range](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md)
- [How to add extra Sub-GHz frequencies](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md)
- [~~Configure Sub-GHz Remote App~~](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md) ⚠️ Not recommended, please use embedded configurator

### Plugins 

- TOTP (Authenticator): [config description](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) 
- Barcode Generator: [How to use](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BarcodeGenerator.md)
- Multi Converter: [How to use](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MultiConverter.md)
- WAV Player: [sample files & how to convert](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme)  
- Sub-GHz playlist: [generator script](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py)

### **Plugins that works with external hardware** [GPIO] 

- Unitemp - Temperature sensors reader: [How to use & supported sensors](https://github.com/quen0n/unitemp-flipperzero#readme)
- [NMEA] GPS: [How to use](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md)  
- i2c Tools [How to use](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md)  
- [NRF24] plugins: [How to use](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md)  
- [WiFi] Scanner: [How to use](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) | [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/)
- [ESP8266] Deauther: [How to use](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) | [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/)
- [ESP32] WiFi Marauder: [How to use](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard)<sub> docs by UberGuidoZ</sub> | [Marauder repo](https://github.com/justcallmekoko/ESP32Marauder)
- [ESP32-CAM] Camera Suite: [How to use](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite)
- How to Upload `.bin` to ESP32/ESP8266: [Windows](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32) | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher)
- [GPIO] SentrySafe plugin: [How to use](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md)


## 👨‍💻 Firmware & Development

- **Developer Documentation** - [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen)  
- **[How to build](/documentation/HowToBuild.md#how-to-build-by-yourself) | [Project-structure](#project-structure)**
- **CLion IDE** - How to setup workspace for flipper firmware development [by Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- **"Hello world!"** - plugin tutorial [English<sub> by DroomOne</sub> ](https://github.com/DroomOne/Flipper-Plugin-Tutorial) | [Russian<sub> by Pavel Yakovlev</sub>](https://yakovlev.me/hello-flipper-zero)
- [How to write your own app](https://flipper.atmanos.com/docs/overview/intro).

### Project structure

- `applications`    - Applications and services used in firmware
- `assets`          - Assets used by applications and services
- `furi`            - Furi Core: OS-level primitives and helpers
- `debug`           - Debug tool: GDB-plugins, SVD-file and etc
- `documentation`   - Documentation generation system configs and input files
- `firmware`        - Firmware source code
- `lib`             - Our and 3rd party libraries, drivers and etc...
- `site_scons`      - Build helpers
- `scripts`         - Supplementary scripts and python libraries home

Also, pay attention to the `ReadMe.md` files inside those directories.**


## 🔗 Links
- **Unleashed web page:** [flipperunleashed.com](https://flipperunleashed.com)
- **Unleashed update server, direct .tgz update links for web updater or direct download:** [unleashedflip.com](https://unleashedflip.com)

- Official Docs: [docs.flipper.net](https://docs.flipper.net)
- Official Forum: [forum.flipperzero.one](https://forum.flipperzero.one)
- Update! Developer Documentation [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen)
