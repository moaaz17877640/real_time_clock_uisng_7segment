/*
 * File: application.c
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:21 PM
 */
#include "application.h"
volatile uint8 tmr1_counter = 0 ;


 pin_config_t seg1_en1s = {
    .port = PORTD_INDEX,
    .pin = PIN0,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
  pin_config_t seg1_en2s = {
    .port = PORTD_INDEX,
    .pin = PIN1,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
   pin_config_t seg1_en3m = {
    .port = PORTD_INDEX,
    .pin = PIN2,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
   pin_config_t seg1_en4m = {
    .port = PORTD_INDEX,
    .pin = PIN3,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
    pin_config_t seg1_en5h = {
    .port = PORTD_INDEX,
    .pin = PIN4,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
     pin_config_t seg1_en6h = {
    .port = PORTD_INDEX,
    .pin = PIN5,
    .direction = OUTPUT,
    .logic = LOGIC_LOW
};
     Segment_t seg_s = {
    .seg__pins[0].pin = PIN0,
    .seg__pins[0].port = PORTA_INDEX,
    .seg__pins[0].direction = OUTPUT,
    .seg__pins[0].logic = LOGIC_LOW,
    .seg__pins[1].pin = PIN1,
    .seg__pins[1].port = PORTA_INDEX,
    .seg__pins[1].direction = OUTPUT,
    .seg__pins[1].logic = LOGIC_LOW,
    .seg__pins[2].pin = PIN2,
    .seg__pins[2].port = PORTA_INDEX,
    .seg__pins[2].direction = OUTPUT,
    .seg__pins[2].logic = LOGIC_LOW,
    .seg__pins[3].pin = PIN3,
    .seg__pins[3].port = PORTA_INDEX,
    .seg__pins[3].direction = OUTPUT,
    .seg__pins[3].logic = LOGIC_LOW,
    .type = COMMON_ANODE
};
      Segment_t seg_m = {
    .seg__pins[0].pin = PIN4,
    .seg__pins[0].port = PORTC_INDEX,
    .seg__pins[0].direction = OUTPUT,
    .seg__pins[0].logic = LOGIC_LOW,
    .seg__pins[1].pin = PIN5,
    .seg__pins[1].port = PORTC_INDEX,
    .seg__pins[1].direction = OUTPUT,
    .seg__pins[1].logic = LOGIC_LOW,
    .seg__pins[2].pin = PIN6,
    .seg__pins[2].port = PORTC_INDEX,
    .seg__pins[2].direction = OUTPUT,
    .seg__pins[2].logic = LOGIC_LOW,
    .seg__pins[3].pin = PIN7,
    .seg__pins[3].port = PORTC_INDEX,
    .seg__pins[3].direction = OUTPUT,
    .seg__pins[3].logic = LOGIC_LOW,
    .type = COMMON_ANODE
};
       Segment_t seg_h = {
    .seg__pins[0].pin = PIN0,
    .seg__pins[0].port = PORTC_INDEX,
    .seg__pins[0].direction = OUTPUT,
    .seg__pins[0].logic = LOGIC_LOW,
    .seg__pins[1].pin = PIN1,
    .seg__pins[1].port = PORTC_INDEX,
    .seg__pins[1].direction = OUTPUT,
    .seg__pins[1].logic = LOGIC_LOW,
    .seg__pins[2].pin = PIN2,
    .seg__pins[2].port = PORTC_INDEX,
    .seg__pins[2].direction = OUTPUT,
    .seg__pins[2].logic = LOGIC_LOW,
    .seg__pins[3].pin = PIN3,
    .seg__pins[3].port = PORTC_INDEX,
    .seg__pins[3].direction = OUTPUT,
    .seg__pins[3].logic = LOGIC_LOW,
    .type = COMMON_ANODE
};
     
   
void TMR_Isr(void){
    tmr1_counter++;
  //  led_toggle(&led_2);
}

void app_initialize(void);
Timer1_t int1 ;
void interrupt_init1(void){
int1.Prescaler_value = TIMER1_PRESCALER_DIV_8 ;
int1.TIMER1_INTERRUPT_HANDLER = TMR_Isr ;
//int1.counter_mode =TIMER1_SYNCHRONOUS_mode ;
int1.timer1_mode =  TIMER1_TIMER_MODE_CFG ;
int1.timer1_osc_cfg = TIMER1_Disable_osc_cfg ;
int1.timer1_preload_value = 13036 ;
int1.timer1_register_size = TIMER1_16_RW_reg ;
TMR1_Init(&int1);
}

Std_ReturnType ret = E_NOT_OK;
uint8 second_num= 0;
uint8 minute_num = 0;
uint8 hour_num = 0 ;

int main() {
     app_initialize();
   interrupt_init1();
   
    while(1){
        if(tmr1_counter  == 4){
           second_num++;
           tmr1_counter = 0;
        }
        Segment_Write_number(&seg_s,(uint8)(second_num % 10));
           gpio_pin_write_logic(&seg1_en2s, LOGIC_HIGH);
              __delay_us(50); 
            gpio_pin_write_logic(&seg1_en2s, LOGIC_LOW);
                Segment_Write_number(&seg_s,(uint8)( second_num / 10));
                gpio_pin_write_logic(&seg1_en1s, LOGIC_HIGH);
               __delay_us(50);
             gpio_pin_write_logic(&seg1_en1s, LOGIC_LOW);
             
            Segment_Write_number(&seg_m,(uint8)(minute_num % 10));
           gpio_pin_write_logic(&seg1_en4m, LOGIC_HIGH);
            __delay_us(50);
            gpio_pin_write_logic(&seg1_en4m, LOGIC_LOW);
             Segment_Write_number(&seg_m,(uint8)( minute_num / 10));
                gpio_pin_write_logic(&seg1_en3m, LOGIC_HIGH);
               __delay_us(50);
             gpio_pin_write_logic(&seg1_en3m, LOGIC_LOW);
              
            Segment_Write_number(&seg_h,(uint8)(hour_num % 10));
           gpio_pin_write_logic(&seg1_en6h, LOGIC_HIGH);
             __delay_us(50);
            gpio_pin_write_logic(&seg1_en6h, LOGIC_LOW);
             Segment_Write_number(&seg_h,(uint8)( hour_num / 10));
                gpio_pin_write_logic(&seg1_en5h, LOGIC_HIGH);
               __delay_us(50);
             gpio_pin_write_logic(&seg1_en5h, LOGIC_LOW);
             
             if(second_num == 60){
                 second_num= 0;
             minute_num++;
             }
              if(minute_num == 60){
                  minute_num = 0;
             hour_num++;
             }
       
        
        
        
        
     
    }
   
     return (EXIT_SUCCESS);
}

void  app_initialize(void) {
  
  Segment_initalize(&seg_s);
  Segment_initalize(&seg_m);
  Segment_initalize(&seg_h);
  gpio_pin_intialize(&seg1_en1s);
  gpio_pin_intialize(&seg1_en2s);
  gpio_pin_intialize(&seg1_en3m);
  gpio_pin_intialize(&seg1_en4m);
  gpio_pin_intialize(&seg1_en5h);
  gpio_pin_intialize(&seg1_en6h);
  
}