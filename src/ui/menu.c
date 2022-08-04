/*****************************************************************************
 *   Ledger App Boilerplate.
 *   (c) 2020 Ledger SAS.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#include "os.h"
#include "ux.h"
#include "glyphs.h"

#include "../globals.h"
#include "menu.h"

// PEN: EXTRA INCLUDES, MAY NOT ALL BE NECESSARY
#pragma GCC diagnostic ignored "-Wformat-invalid-specifier" // snprintf
#pragma GCC diagnostic ignored "-Wformat-extra-args"        // snprintf
#include "../crypto.h"
#include "../types.h"
#include "../sw.h"
#include "../common/buffer.h"
#include "../ui/display.h"
#include "../common/bip32.h"
#include "../common/format.h"
#include "../transaction/types.h"
#include "../io.h"
#include "display.h"
#include "constants.h"
#include "../address.h"
#include "action/validate.h"

UX_STEP_NOCB(ux_menu_ready_step, pnn, {&C_boilerplate_logo, "Tree", "is ready"});
UX_STEP_NOCB(ux_menu_version_step, bn, {"Version", APPVERSION});

// PEN: EXTRA STEPS
UX_STEP_CB(ux_menu_show_hot_pub_key_step, bn, ui_menu_show_hot_pub_key(), {"Show hot pub key", "m/44'/632'/0'"});
UX_STEP_CB(ux_menu_show_cold_pub_key_step, bn, ui_menu_show_cold_pub_key(), {"Show cold pub key", "m/44'/632'/1'"});

UX_STEP_CB(ux_menu_about_step, pb, ui_menu_about(), {&C_icon_certificate, "About"});
UX_STEP_VALID(ux_menu_exit_step, pb, os_sched_exit(-1), {&C_icon_dashboard_x, "Quit"});

// FLOW for the main menu:
// #1 screen: ready
// #2 screen: version of the app
// #3 screen: show hot public key    // PEN: EXTRA STEP
// #4 screen: show cold public key   // PEN: EXTRA STEP
// #5 screen: about submenu
// #6 screen: quit
UX_FLOW(ux_menu_main_flow,
        &ux_menu_ready_step,
        &ux_menu_version_step,
        &ux_menu_show_hot_pub_key_step,    // PEN: EXTRA STEP
        &ux_menu_show_cold_pub_key_step,   // PEN: EXTRA STEP
        &ux_menu_about_step,
        &ux_menu_exit_step,
        FLOW_LOOP);

void ui_menu_main() {
    if (G_ux.stack_count == 0) {
        ux_stack_push();
    }

    ux_flow_init(0, ux_menu_main_flow, NULL);
}

UX_STEP_NOCB(ux_menu_info_step, bn, {"Tree App", "(c) 2022 The Pen"});
UX_STEP_CB(ux_menu_back_step, pb, ui_menu_main(), {&C_icon_back, "Back"});

// FLOW for the about submenu:
// #1 screen: app info
// #2 screen: back button to main menu
UX_FLOW(ux_menu_about_flow, &ux_menu_info_step, &ux_menu_back_step, FLOW_LOOP);

void ui_menu_about() {
    ux_flow_init(0, ux_menu_about_flow, NULL);
}


/////////////////////////////////
//  PEN: EXTRA MENU FUNCTIONS  //
/////////////////////////////////

    pubkey_ctx_t pubkey_ctx_0;  // LOCAL GLOBALS
    static char pubkey_0_chars[67];
    pubkey_ctx_t pubkey_ctx_1;
    static char pubkey_1_chars[67];

UX_STEP_NOCB(ux_menu_show_hot_pub_key_step2, bnnn_paging, 
            {
                .title = "Hot pub key:", 
                .text = pubkey_0_chars,
            });

UX_FLOW(ux_menu_show_hot_pub_key_flow2, &ux_menu_show_hot_pub_key_step2, &ux_menu_back_step, FLOW_LOOP);

void ui_menu_show_hot_pub_key() {

// CALCULATE HOT KEY HERE, SO IT CAN BE SHOWN IN NEXT STEP

    cx_ecfp_private_key_t private_key_0 = {0};
    cx_ecfp_public_key_t public_key_0 = {0};
  
    uint8_t bip32_path_len_0 = 3;
    uint32_t bip32_path_0[3] = {0x8000002c, 0x80000278, 0x80000000};

    crypto_derive_private_key(&private_key_0,
                              pubkey_ctx_0.chain_code,
                              bip32_path_0,
                              bip32_path_len_0);

    crypto_init_public_key(&private_key_0, &public_key_0, pubkey_ctx_0.raw_public_key);

    explicit_bzero(&private_key_0, sizeof(private_key_0));

    snprintf(pubkey_0_chars, sizeof(pubkey_0_chars), "0x%.*H", \
            sizeof(pubkey_ctx_0.raw_public_key), pubkey_ctx_0.raw_public_key);

    pubkey_0_chars[66] = 0x00;

// CONVERT PUBLIC KEY TO LOWER CASE
    unsigned int ci;
    char cU;
    for (ci=0; ci< sizeof(pubkey_0_chars); ci++) {
        cU = pubkey_0_chars[ci];
        if ((cU > 0x40) && (cU < 0x47)) {
            pubkey_0_chars[ci] = cU + 0x20;
        }
    }

    ux_flow_init(0, ux_menu_show_hot_pub_key_flow2, NULL);

}

UX_STEP_NOCB(ux_menu_show_cold_pub_key_step2, bnnn_paging, 
            {
                .title = "Cold pub key:", 
                .text = pubkey_1_chars,
            });

UX_FLOW(ux_menu_show_cold_pub_key_flow2, &ux_menu_show_cold_pub_key_step2, &ux_menu_back_step, FLOW_LOOP);

void ui_menu_show_cold_pub_key() {

// CALCULATE COLD KEY HERE, SO IT CAN BE SHOWN IN NEXT STEP

    cx_ecfp_private_key_t private_key_1 = {0};
    cx_ecfp_public_key_t public_key_1 = {0};
  
    uint8_t bip32_path_len_1 = 3;
    uint32_t bip32_path_1[3] = {0x8000002c, 0x80000278, 0x80000001};

    crypto_derive_private_key(&private_key_1,
                              pubkey_ctx_1.chain_code,
                              bip32_path_1,
                              bip32_path_len_1);

    crypto_init_public_key(&private_key_1, &public_key_1, pubkey_ctx_1.raw_public_key);

    explicit_bzero(&private_key_1, sizeof(private_key_1));

    snprintf(pubkey_1_chars, sizeof(pubkey_1_chars), "0x%.*H", \
            sizeof(pubkey_ctx_1.raw_public_key), pubkey_ctx_1.raw_public_key);

    pubkey_1_chars[66] = 0x00;

// CONVERT PUBLIC KEY TO LOWER CASE
    unsigned int ci;
    char cU;
    for (ci=0; ci< sizeof(pubkey_1_chars); ci++) {
        cU = pubkey_1_chars[ci];
        if ((cU > 0x40) && (cU < 0x47)) {
            pubkey_1_chars[ci] = cU + 0x20;
        }
    }

    ux_flow_init(0, ux_menu_show_cold_pub_key_flow2, NULL);

}


