#pragma once

#include <stdint.h>

// PEN: CHANGED FROM "ux.h" BUT DID NOT HELP cmocka UNABLE TO FIND FILE

// IO_SEPROSYHAL_BUFFER_SIZE_B SPECIFIC TO NANOS ONLY, OTHERWISE 300
#ifdef CMOCKA_TEST
#define IO_SEPROXYHAL_BUFFER_SIZE_B 128  
#include "/app/unit-tests/utils/ux.h"
#else
#include "ux.h"
#endif


#include "io.h"
#include "types.h"
#include "constants.h"

/**
 * Global buffer for interactions between SE and MCU.
 */
extern uint8_t G_io_seproxyhal_spi_buffer[IO_SEPROXYHAL_BUFFER_SIZE_B];

/**
 * Global variable with the lenght of APDU response to send back.
 */
extern uint32_t G_output_len;

/**
 * Global structure to perform asynchronous UX aside IO operations.
 */
extern ux_state_t G_ux;

/**
 * Global structure with the parameters to exchange with the BOLOS UX application.
 */
extern bolos_ux_params_t G_ux_params;

/**
 * Global enumeration with the state of IO (READY, RECEIVING, WAITING).
 */
extern io_state_e G_io_state;

/**
 * Global context for user requests.
 */
extern global_ctx_t G_context;
