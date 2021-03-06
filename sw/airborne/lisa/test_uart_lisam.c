/*
 * Copyright (C) 2009 Antoine Drouin <poinix@gmail.com>
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

//#include <libopencm3/stm32/rcc.h>
//#include <libopencm3/stm32/gpio.h>

//#include <libopencm3/stm32/flash.h>

//#include <libopencm3/cm3/common.h>

#include BOARD_CONFIG
#include "mcu.h"
#include "mcu_periph/uart.h"
#include "mcu_periph/sys_time.h"
#include "led.h"

static inline void main_init( void );
static inline void main_periodic( void );

int main(void) {

  main_init();

  while (1) {
    if (sys_time_check_and_ack_timer(0))
      main_periodic();
  }

  return 0;
}

static inline void main_init( void ) {
  mcu_init();
  sys_time_register_timer((1./PERIODIC_FREQUENCY), NULL);
}

static inline void main_periodic( void ) {
  char ch;

  uart_transmit(&uart1, 'a');
  uart_transmit(&uart2, 'b');
  uart_transmit(&uart3, 'c');
  uart_transmit(&uart5, 'd');

  LED_OFF(1);
  LED_OFF(2);

  if (uart_char_available(&uart1)) {
    ch = uart_getch(&uart1);
    if (ch == 'a') {
      LED_ON(1);
    } else {
      LED_ON(2);
    }
  }

  if (uart_char_available(&uart2)) {
    ch =  uart_getch(&uart2);
    if (ch == 'b') {
      LED_ON(1);
    } else {
      LED_ON(2);
    }
  }

  if (uart_char_available(&uart3)) {
    ch =  uart_getch(&uart3);
    if (ch == 'c') {
      LED_ON(1);
    } else {
      LED_ON(2);
    }
  }

  if (uart_char_available(&uart5)) {
    ch =  uart_getch(&uart5);
    if (ch == 'd') {
      LED_ON(1);
    } else {
      LED_ON(2);
    }
  }
}
