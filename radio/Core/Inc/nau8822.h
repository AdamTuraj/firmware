#pragma once
#include <stdint.h>

const uint8_t NAU8822_ADDR = 0x1A << 1;

/* ---------- Register addresses (Datasheet Rev 3.3) ---------- */
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