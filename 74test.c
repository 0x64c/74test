#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/*    CONSTANTS   */
#define blink_delay_long 1000
#define blink_delay_short 250

/*    BITMASKS    */
#define t7406pinmask_l 0b01010101
#define t7406pinmask_h 0b00000101
#define t7408pinmask_l 0b11011011
#define t7408pinmask_h 0b00000110

/*    I/O PINS  */
#define LED_DIR     DDRB
#define LED_PORT    PORTB
#define LED_BIT     0b10000000

#define SW_DIR      DDRB
#define SW_PIN      PINB
#define SW_BIT      0b01000000

#define DIP_SEL     PINF
#define DIP_DIR     DDRF
#define DIP_BIT     0b11111111

#define DIPL_PIN  PINA
#define DIPL_PORT PORTA
#define DIPL_DIR  DDRA

#define DIPH_PIN  PINC
#define DIPH_PORT PORTC
#define DIPH_DIR  DDRC

#define DIPG_PIN  PIND
#define DIPG_PORT PORTD
#define DIPG_DIR  DDRD

/*    MACROS    */
#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)
#define check_pin(a,b) ((a)&(b)==0)?1:0
#define t_d8w(a,b,c,d,e,f)\
  DIPL_PORT=(a)&(c);\
  DIPH_PORT=(b)&(d);\
  _NOP();\
  if(\
    (DIPL_PIN&(~c)!=(e)&(~(c)))||\
    (DIPH_PIN&(~d)!=(f)&(~(d)))\
  ){return 1;}

/*    DISPLAY FUNCTIONS   */
void blink(int times){
  int i;
  LED_PORT&=~(LED_BIT);
  for(i=0;i<times;i++){
    LED_PORT|=(LED_BIT);
    _delay_ms(blink_delay_short);
    LED_PORT&=~(LED_BIT);
    _delay_ms(blink_delay_short);
  }
  LED_PORT&=~(LED_BIT);
}

void blinker(int a){
  switch(a){
    case 2:blink(2);break; //ready
    case 1:blink(4);break; //fail
    case 0:blink(1);break; //pass
  }
  _delay_ms(blink_delay_long);
}

/*    TEST FUNCTIONS    */

/*
DIP14 PIN CONFIGURATION
  l0  1| v |14  vcc
  l1  2|   |13  l6
  l2  3|   |12  l7
  l3  4|   |11  h0
  l4  5|   |10  h1
  l5  6|   |9   h2
  gnd 7|   |8   h3
*/

int test_7406(void){
  DIPL_DIR= t7406pinmask_l;
  DIPH_DIR= t7406pinmask_h;
  t_d8w(0b00000000,0b00000000,t7406pinmask_l,t7406pinmask_h,0b11111111,0b11111111);
  t_d8w(0b11111111,0b11111111,t7406pinmask_l,t7406pinmask_h,0b00000000,0b00000000);
  return 0;
}

int test_7408(void){
  DIPL_DIR= t7408pinmask_l;
  DIPH_DIR= t7408pinmask_h;
  t_d8w(0b00000000,0b00000000,t7408pinmask_l,t7408pinmask_h,0b00000000,0b00000000);
  t_d8w(0b01001001,0b00000010,t7408pinmask_l,t7408pinmask_h,0b00000000,0b00000000);
  t_d8w(0b10010010,0b00000100,t7408pinmask_l,t7408pinmask_h,0b00000000,0b00000000);
  t_d8w(0b11011011,0b00000110,t7408pinmask_l,t7408pinmask_h,0b11111111,0b11111111);
  return 0;
}

/*
DIP16 PIN CONFIGURATION
  l0  1| v |16  vcc
  l1  2|   |15  l6
  l2  3|   |14  l7
  l3  4|   |13  h0
  l4  5|   |12  h1
  l5  6|   |11  h2
  h5  7|   |10  h3
  gnd 8|   |9   h4
*/



/*
DIP20 PIN CONFIGURATION
  l0  1 | v |20 vcc
  l1  2 |   |19 l6
  l2  3 |   |18 l7
  l3  4 |   |17 h0
  l4  5 |   |16 h1
  l5  6 |   |15 h2
  h5  7 |   |14 h3
  h6  8 |   |13 h4
  h7  9 |   |12 g0
  gnd 10|   |11 g1
*/

/*    PROGRAM    */
void init(void){
  DIP_DIR&=~(DIP_BIT);
  LED_DIR|=(LED_BIT);
  SW_DIR&=~(SW_BIT);
}

int main(void){
  init();
  
  int res=0;
  while(check_pin(SW_PIN,SW_BIT)){
    blinker(2);
  }
  
  switch(DIP_SEL){
    case 0:
      res=test_7406();
      break;
    case 1:
      res=test_7408();
      break;
    case 2:
      break;
    case 4:
      break;
    case 8:
      break;
    case 16:
      break;
    case 32:
      break;
  }
  
  while(check_pin(SW_PIN,SW_BIT)){
    blinker(res);
  }
}
