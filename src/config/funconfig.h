#ifndef SIMPLE_FUNCONFIG_H
#define SIMPLE_FUNCONFIG_H

#define CH32V003 1
#define FUNCONF_SYSTEM_CORE_CLOCK 48000000
// #define FUNCONF_SYSTEM_CORE_CLOCK 24000000

// TINYVECTOR now saves like another 120 bytes of space.
// #define FUNCONF_TINYVECTOR       1
// #define FUNCONF_SYSTICK_USE_HCLK 1
// I don't use virtual functions and fancy inheritance
// so the macro is not needed.

// #define CPLUSPLUS                 1
#define FUNCONF_USE_HSE 0 // external crystal on PA1 PA2
#define FUNCONF_USE_HSI 1 // internal 24MHz clock oscillator
#define FUNCONF_USE_PLL 1 // use PLL x2
// bypass the HSE when using an external clock source, which requires HSE enabled
#define FUNCONF_HSE_BYPASS  0
#define FUNCONF_USE_CLK_SEC 1 // clock security system
#define SYSTEM_CORE_CLOCK   FUNCONF_SYSTEM_CORE_CLOCK
#define APB_CLOCK           SYSTEM_CORE_CLOCK

#endif // SIMPLE_FUNCONFIG_H
