#pragma once

#include "types.h"
#include "../common/buffer.h"

/**
 * Deserialize raw transaction in structure.
 *
 * @param[in, out] buf
 *   Pointer to buffer with serialized transaction.
 * @param[out]     tx
 *   Pointer to transaction structure.
 *
 * @return PARSING_OK if success, error status otherwise.
 *
 */
parser_status_e transaction_deserialize(buffer_t *buf, transaction_t *tx);

// PEN: CUSTOM TRANSACTION FORMAT FUNCTIONS
parser_status_e transaction_deserialize_1(buffer_t *buf, transaction_t *tx);
parser_status_e transaction_deserialize_2(buffer_t *buf, transaction_t *tx);