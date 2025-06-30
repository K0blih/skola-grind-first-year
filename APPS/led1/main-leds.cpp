// **************************************************************************
//
//               Demo program for APPS labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 02/2025
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LEDs
//
// **************************************************************************

/**
 * @file    main-leds.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <functional>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_mrt.h"

#include "mcxn-kit.h"

// **************************************************************************
//! System initialization. Do not modify it!!!
void _mcu_initialization() __attribute__(( constructor( 0x100 ) ));

void _mcu_initialization()
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    CLOCK_EnableClock( kCLOCK_Gpio0 );
    CLOCK_EnableClock( kCLOCK_Gpio1 );
    CLOCK_EnableClock( kCLOCK_Gpio2 );
    CLOCK_EnableClock( kCLOCK_Gpio3 );
    CLOCK_EnableClock( kCLOCK_Gpio4 );
}
// **************************************************************************

//! Global data

//! LEDs on MCXN-KIT - instances of class DigitalOut
DigitalOut g_led_P3_16( P3_16 );
DigitalOut g_led_P3_17( P3_17 );

//! Button on MCXN-KIT - instance of class DigitalIn
DigitalIn g_but_P3_18( P3_18 );
DigitalIn g_but_P3_19( P3_19 );
DigitalIn g_but_P3_20( P3_20 );
DigitalIn g_but_P3_21( P3_21 );

#define T 100

class PWMLed
{
public:
    DigitalOut m_led;
    Ticker m_ticker;
    uint32_t m_T1;

    PWMLed( pin_name_t t_pin ) : m_led( t_pin )
    {
        /// inicializace
        /// m_ticker.attach( připojit vlastní pwm_control );
    	m_T1 = T;
    	m_ticker.attach(&PWMLed::pwm_control, this , 1);
    }

    void nastav_jas( uint8_t t_level )
    {
        m_T1 = (t_level * T) / 255;
    }

protected:
//    uint32_t _m_ticks;

    void pwm_control()
    {
    /// řízení jasu dle m_T1

    		static int l_ticks = 0;

    		int32_t l_periode = T;
    		int32_t onOff = this->m_T1;

//    		if ( g_but_P3_18.read() == 0 )				// check button
//    		{
//    			l_periode /= 10;						// increase speed of blinking
//    		}

    		if ( l_ticks < onOff )				// time to switch on or off?
    		{
    			this->m_led.write( 1 );					// LED Off
    		}
    		else
    		{
    			this->m_led.write( 0 );					// LED On
    		}

    		l_ticks++;									// milliseconds counter
    		if ( l_ticks >= l_periode )					// end of time period?
    		{
    			l_ticks = 0;							// start time period again
    		}

//        _m_ticks++;
//        if ( _m_ticks >= T )
//        {
//            _m_ticks = 0;
//        }
    }

};

PWMLed g_leds[] = { P3_16, P3_17 };
PWMLed g_red_leds[] = {P4_00, P4_01, P4_02, P4_03, P4_12, P4_13, P4_16, P4_20};

int main()
{
    PRINTF( "LED demo program started...\n" );

    g_leds[ 0 ].nastav_jas( 128 );
    g_leds[ 1 ].nastav_jas( 13 );

//    for (int i = 0; i < 8; i++) {
//    	g_red_leds[i].nastav_jas(i * 16);
//    }

    if (g_but_P3_18.read() == 0) {
    	while(1) {
    		for (int i = 0; i < 8; i++) {
    		    	g_red_leds[i].nastav_jas(0);
    		    }
    		if (g_but_P3_19.read() == 0) {
    			break;
    		}
    	}
    }

    int i = 0;
    while (1) {
        	if (g_but_P3_18.read() == 0) {
        	    		for (int i = 0; i < 8; i++) {
        	    		    	g_red_leds[i].nastav_jas(0);
        	    		    }
        	    }
        	if (g_but_P3_19.read() == 0) {
        		for (int i = 0; i < 8; i++) {
        		    	g_red_leds[i].nastav_jas(i * 16);
        		    }
        	}


        	if (g_but_P3_20.read() == 0 && i < 8) {
        		i++;
        		for (int i = 0; i < 8; i++) {
        		    	g_red_leds[i].nastav_jas(0);
        		    }
        		g_red_leds[i].nastav_jas(128);
        		delay_ms(500);
        	}
        	if (g_but_P3_20.read() == 1 && i > 0) {
        	    i--;
        	    for (int i = 0; i < 8; i++) {
        	        	g_red_leds[i].nastav_jas(0);
        	        }
        	    g_red_leds[i].nastav_jas(128);
        	    delay_ms(500);
        	}
        }

    while ( 1 ) __WFI();
}
//! Callback function for LED control
//void control_from_ticker()
//{
//	static int l_ticks = 0;
//
//	int32_t l_periode = 500;					// T = 0.5 second
//
//	if ( g_but_P3_18.read() == 0 )				// check button
//	{
//		l_periode /= 10;						// increase speed of blinking
//	}
//
//	if ( l_ticks < l_periode / 2 )				// time to switch on or off?
//	{
//		g_led_P3_16.write( 0 );					// LED Off
//	}
//	else
//	{
//		g_led_P3_16.write( 1 );					// LED On
//	}
//
//	l_ticks++;									// milliseconds counter
//	if ( l_ticks >= l_periode )					// end of time period?
//	{
//		l_ticks = 0;							// start time period again
//	}
//}
//
//int main()
//{
//	PRINTF( "LED demo program started...\n" );
//
//#if 0
//	// modern approach with timer (and interrupt)
//	Ticker l_ticker;
//
//	l_ticker.attach( control_from_ticker, 1 );		// attach callback function
//
//	while ( 1 )
//	{ // infinite loop
//	}
//
//#else
//
//	// lazy (conservative) approach
//	while ( 1 )
//	{
//		int32_t l_periode = 500;				// T = 500 ms = 0.5 sec
//
//		if ( g_but_P3_18.read() == 0 )			// button pressed?
//		{
//			l_periode /= 10;					// speed up blinking
//		}
//
//		g_led_P3_16.write( 0 );					// LED off
//
//		delay_ms( l_periode / 2 );
//
//		g_led_P3_16.write( 1 );					// LED on
//
//		delay_ms( l_periode / 2 );
//	}
//
//#endif
//
//}

