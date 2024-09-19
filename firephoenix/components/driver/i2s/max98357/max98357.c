#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"

static const char *TAG = "I2S_MAX98357";

#define EXAMPLE_STD_BCLK_IO1        GPIO_NUM_1      // I2S bit clock io number   I2S_BCLK
#define EXAMPLE_STD_WS_IO1          GPIO_NUM_4      // I2S word select io number    I2S_LRC
#define EXAMPLE_STD_DOUT_IO1        GPIO_NUM_2     // I2S data out io number    I2S_DOUT
#define EXAMPLE_STD_DIN_IO1         GPIO_NUM_NC    // I2S data in io number

static i2s_chan_handle_t tx_chan;        // I2S tx channel handler
#define SAMPLE_RATE 44100

void i2s_example_init_std_simplex(void) {

    i2s_chan_config_t tx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(1, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&tx_chan_cfg, &tx_chan, NULL));


    i2s_std_config_t tx_std_cfg = {
            .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
            .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT,
                                                        I2S_SLOT_MODE_MONO),

            .gpio_cfg = {
                    .mclk = I2S_GPIO_UNUSED,    // some codecs may require mclk signal, this example doesn't need it
                    .bclk = EXAMPLE_STD_BCLK_IO1,
                    .ws   = EXAMPLE_STD_WS_IO1,
                    .dout = EXAMPLE_STD_DOUT_IO1,
                    .din  = EXAMPLE_STD_DIN_IO1,
                    .invert_flags = {
                            .mclk_inv = false,
                            .bclk_inv = false,
                            .ws_inv   = false,
                    },
            },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_chan, &tx_std_cfg));
}