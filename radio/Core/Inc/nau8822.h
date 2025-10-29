#pragma once
#include "main.h"
#include <stdint.h>
#include <math.h>

/* ---------- Device I2C Address ---------- */
#define NAU8822_ADDR (0x1A << 1)

/* ---------- Register Addresses (Datasheet Rev 3.3) ---------- */
typedef enum {
    NAU_RESET             = 0x00, // Software Reset
    NAU_MGMT1             = 0x01,
    NAU_MGMT2             = 0x02,
    NAU_MGMT3             = 0x03,

    NAU_AUDIO_IF          = 0x04,
    NAU_CLK_1             = 0x06,
    NAU_CLK_2             = 0x07,

    NAU_DAC_CTRL          = 0x0A,
    NAU_LDAC_VOL          = 0x0B,
    NAU_RDAC_VOL          = 0x0C,

    NAU_ADC_CTRL          = 0x0E,
    NAU_LADC_VOL          = 0x0F,
    NAU_RADC_VOL          = 0x10,

    NAU_NOISE_GATE        = 0x23,

    NAU_INPUT_CTRL        = 0x2C,
    NAU_LPGA_GAIN         = 0x2D,
    NAU_RPGA_GAIN         = 0x2E,
    NAU_LADC_BOOST        = 0x2F,
    NAU_RADC_BOOST        = 0x30,

    NAU_LMIX              = 0x32,
    NAU_RMIX              = 0x33,

    NAU_LHP_VOL           = 0x34,
    NAU_RHP_VOL           = 0x35,
    NAU_LSPK_VOL          = 0x36,
    NAU_RSPK_VOL          = 0x37,

    NAU_DEV_ID            = 0x3F,
} nau8822_reg_t;

/* ---------- Function Prototypes ---------- */

/**
 * @brief  Encodes a float volume percentage (0–100%) into 8-bit codec register format.
 * @param  volume_percent: Volume percentage from 0.0 to 100.0
 * @retval Encoded 8-bit value (0–255)
 */
uint8_t encode_vol(float volume_percent);

/**
 * @brief  Writes a 9-bit value to a NAU8822 register via I2C.
 * @param  reg: Register address
 * @param  val: 9-bit value (in lower bits of 16-bit)
 * @retval HAL status
 */
HAL_StatusTypeDef nau8822_write_reg(uint8_t reg, uint16_t val);

/**
 * @brief  Reads a 9-bit value from a NAU8822 register via I2C.
 * @param  reg: Register address
 * @param  val: Pointer to store read value
 * @retval HAL status
 */
HAL_StatusTypeDef nau8822_read_reg(uint8_t reg, uint16_t *val);

/**
 * @brief  Sets both headphone and optionally speaker volume.
 * @param  speaker: 0 = headphone only, 1 = include speaker
 * @param  volume:  Volume percentage (0–100%)
 * @retval HAL status
 */
HAL_StatusTypeDef set_speaker_volume(uint8_t speaker, float volume);

/**
 * @brief  Sets microphone ADC gain.
 * @param  volume: Volume percentage (0–100%)
 * @retval HAL status
 */
HAL_StatusTypeDef set_mic_volume(float volume);

/**
 * @brief  Reads and verifies NAU8822 device ID.
 * @retval HAL_OK if successful, HAL_ERROR if invalid ID
 */
HAL_StatusTypeDef test_read(void);

/**
 * @brief  Initializes the NAU8822 codec with default configuration.
 * @param  speaker: 0 = headphone output, 1 = speaker output enabled
 */
void nau8822_init(uint8_t speaker);

