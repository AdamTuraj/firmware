/* Owen Brake - May 2021
 * This is what all non driver C files should include to interface with the LTC chips
 * This has the user facing functions
 * */
#ifndef LTC_CHIP_H

#define LTC_CHIP_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f7xx_hal.h"
#include "bmu_can.h"

/** @defgroup AccumulatorConfig
 *
 * These defines change based upon the battery box layout.
 *
 * @{
 */

// TODO: Update these to 2021 values
extern uint32_t delay_US;
extern uint32_t delay_MS;
/// Number of AMS boards in system
#define NUM_BOARDS                  14
/// Number of valid cells per board, starting from the most negative terminal
#define CELLS_PER_BOARD             10
/// Number of thermistors attached to each AMS, starting from A0
#define THERMISTORS_PER_BOARD       16

// This specifies which chip architecture we are using
// 6812/6804
// Ex. if 6812 is selected: then ltc6812.c is used
#define LTC_CHIP_6812 1
#define LTC_CHIP_6804 2

#define LTC_CHIP LTC_CHIP_6804

#if LTC_CHIP == LTC_CHIP_6804
#define NUM_LTC_CHIPS_PER_BOARD 1
#elif LTC_CHIP == LTC_CHIP_6812
#define NUM_LTC_CHIPS_PER_BOARD 1
#else
#error "No LTC Chip specified, please specify one"
#endif

// Number of Voltage Cells per LTC6812/6804/6811 chip
#define CELLS_PER_CHIP (CELLS_PER_BOARD / NUM_LTC_CHIPS_PER_BOARD) 

// Average 4 readings for both pullup and pulldown in open wire test
#define NUM_OPEN_WIRE_TEST_VOLTAGE_READINGS 2
#define NUM_THERMISTOR_MEASUREMENTS_PER_CYCLE 2

#define NUM_PEC_MISMATCH_CONSECUTIVE_FAILS_ERROR (3)
#define NUM_PEC_MISMATCH_CONSECUTIVE_FAILS_WARNING (2)
#define PRINT_ALL_PEC_ERRORS (0)

// Public defines
#define NUM_VOLTAGE_CELLS           (NUM_BOARDS*CELLS_PER_BOARD)
#define NUM_TEMP_CELLS              (NUM_BOARDS*THERMISTORS_PER_BOARD)

#if NUM_VOLTAGE_CELLS > VOLTAGECELL_COUNT
#error "DBC file has less voltage cells defined then they are in the system"
#endif

#if NUM_TEMP_CELLS > TEMPCHANNEL_COUNT
#error "DBC file has less temp cells defined then they are in the system"
#endif

#define LTC_T_WAKE_MAX_US  300          // TYP=100us. Regulator Start-Up Time aka time to get VREG Generated from Drive Pin. This happens during transition from SLEEP to STANDBY states in core LTC state machine
#define LTC_T_READY_US 10               // If the core state machine is in standby wait this amount of time, if core state machine is in sleep then wait for T_WAKE. 
                                        /* When isoSPI port A receives a WAKEUP signal, the isoSPI enters the READY state. This transition happens quickly (within t_READY) if the Core is in the STANDBY state because the DRIVE and VREG pins are already biased up. If the Core is in the SLEEP state when the isoSPI receives a WAKEUP signal, then it transitions to the READY state within t_WAKE. */

#if LTC_CHIP == LTC_CHIP_6804
// We set this to 3 as the last 3 cell connections are actually CELL7 which is on the 2nd chip
// If this changes in the future VOLTAGE_BLOCKS_PER_CHIP should be 4
#define VOLTAGE_BLOCKS_PER_CHIP    4   // Number of voltage blocks per AMS board
#elif LTC_CHIP == LTC_CHIP_6812
#define VOLTAGE_BLOCKS_PER_CHIP    5   // Number of voltage blocks per AMS board
#endif

/** @} */

typedef enum DischargeTimerLength {
    DT_OFF = 0,
    DT_30_SEC,
    DT_1_MIN,
    DT_2_MIN,
    DT_3_MIN,
    DT_4_MIN,
    DT_5_MIN,
    DT_10_MIN,
    DT_15_MIN,
    DT_20_MIN,
    INVALID_DT_TIME, // There is longer times, but we won't need it for now
} DischargeTimerLength;

/* Public Functions */
HAL_StatusTypeDef batt_read_cell_voltages_and_temps(float *cell_voltage_array, float *cell_temp_array);


HAL_StatusTypeDef batt_balance_cell(int cell);
HAL_StatusTypeDef batt_stop_balance_cell(int cell);
bool batt_is_cell_balancing(int cell);
HAL_StatusTypeDef batt_unset_balancing_all_cells();
HAL_StatusTypeDef batt_write_balancing_config();
HAL_StatusTypeDef checkForOpenCircuit();
HAL_StatusTypeDef batt_start_ADC_conversion(void);
HAL_StatusTypeDef batt_set_disharge_timer(DischargeTimerLength length);

HAL_StatusTypeDef batt_init();
HAL_StatusTypeDef balanceTest();

#endif /* end of include guard: LTC6811_H */
