#include <stdio.h>

#include "os_sdmmc.h"
#include "max98357.h"

void app_main(void)
{
    os_sdmmc_init();
    i2s_example_init_std_simplex();
}
