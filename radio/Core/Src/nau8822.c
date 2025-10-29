#include "main.h"
#include "nau8822.h"

HAL_StatusTypeDef nau8822_write_reg(uint8_t reg, uint16_t val) {
    uint8_t data[3];

    data[0] = (reg << 1) | ((val >> 8) & 0x01);
    data[1] = val & 0xFF;

    return HAL_I2C_Master_Transmit(&hi2c2, NAU8822_ADDR, data, 2, HAL_MAX_DELAY);
}

void nau8822_init(uint8_t speaker) {
    // Resets all registers to default values
    nau8822_write_reg(NAU_RESET, 0x000);
    HAL_Delay(10);

    // Power Management 1:
    // Enable MICBIASEN, ABIASEN, IOBUFEN, REFIMP=3k ohm
    nau8822_write_reg(NAU_MGMT1, 0x1F);

    // Power Management 2:
    // Enable (RHPEN, LHPEN) if not speaker, RPGAEN, LPGAEN, RADCEN, LADCEN
    nau8822_write_reg(NAU_MGMT2, speaker==1 ? 0xF : 0x18F);

    // Power Management 3:
    // Enable (LSPKEN, RSPKEN) if speaker, RMIXEN, LMIXEN, RDACEN, LDACEN
    nau8822_write_reg(NAU_MGMT3, speaker==1 ? 0x6F : 0xF);

    // Audio Interface:
    // I2S, 24-bit
    nau8822_write_reg(NAU_AUDIO_IF, 0x50);

    // Clock Control 1:
    // CLKM = 0, MCLKSEL = divide by 1
    nau8822_write_reg(NAU_CLK_1, 0x00);

    // Clock Control 2:
    // SMPLR=48kHz, Enable SCLKEN
    nau8822_write_reg(NAU_CLK_2, 0x01);

    // Left DAC Volume
    // LDACGAIN = -20 dB
    nau8822_write_reg(NAU_LDAC_VOL, 0xD7);

    // Right DAC Volume
    // RDACGAIN = -20 dB
    nau8822_write_reg(NAU_RDAC_VOL, 0xD7);

    // Left ADC Volume
    // LADCGAIN = 0 dB (no change)

    // Right ADC Volume
    // RADCGAIN = 0 dB (no change)

    // Noise Gate
    // Enable ALCNEN
    nau8822_write_reg(NAU_NOISE_GATE, 0x08);

    // TODO: Input control

    // Left PGA Gain
    // Enable LPGAZC, Gain = 24 dB
    nau8822_write_reg(NAU_LPGA_GAIN, 0xB0);

    // Right PGA Gain
    // Enable RPGAZC, Gain = 24 dB
    nau8822_write_reg(NAU_RPGA_GAIN, 0xB0);

    // Left Mixer
    // Enable LDACCLMX
    nau8822_write_reg(NAU_LMIX, 0x01);

    // Right Mixer
    // Enable RDACCRMX
    nau8822_write_reg(NAU_RMIX, 0x01);

    // Left Headphone Volume
    // Enable LHPZC, LHPGAIN=-18 dB
    nau8822_write_reg(NAU_LHP_VOL, 0xA7);

    // Right Headphone Volume
    // Enable RHPZC, RHPGAIN=-18 dB
    nau8822_write_reg(NAU_RHP_VOL, 0xA7);

    if (speaker == 1) {
        // Left Speaker Volume
        // Enable LSPKZC, LSPKGAIN=-18 dB
        nau8822_write_reg(NAU_LSPK_VOL, 0xA7);

        // Right Speaker Volume
        // Enable RSPKZC, RSPKGAIN=-18 dB
        nau8822_write_reg(NAU_RSPK_VOL, 0xA7);
    }
}