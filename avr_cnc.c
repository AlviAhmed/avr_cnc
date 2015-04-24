/*
             * avr_cnc.c
             *
             * Created: 2015-04-01 6:13:58 AM
             *  Author: Alvi
             */ 


            #include <avr/io.h>   
            #include <util/delay.h> 
            #include <avr/interrupt.h> 
            #define stp_led PB0 
            #define dir_led PB1
            #define led_port PORTB
            #define led_ddr DDRB
            #define F_CPU 16000000UL 
            int x_counter = 0; 
            int x_boolean = 1; 
            int y_counter = 0; 
            int y_boolean = 1; 
            int z_counter = 0; 
            int z_boolean = 1;


            int main(void)
            {  
                //volatile int x = 0;
                ///////////////////////////////////////////////////////
                led_ddr |= (1 << stp_led); //enable led as an output pin  
                led_ddr |= (1 << dir_led);   
                //led_port |= (1<<stp_led);   
                led_port |= (1<<dir_led); 
                ///////////////////////////////////////////////////////
                TCCR1B |= (1 << WGM12);  // configuring timer 1 for ctc mode
                OCR1A = 4678;
                TIMSK1 |= (1 << OCIE1A); // enable ctc interrupt

                TCCR1B |= ((1 << CS12) | (1<< CS10)); //Start at 1024 prescaler 

                sei(); //Enable global interrupts

                 //Sets ctc compare value to 1hz at 1mhz AVR clock, with prescaler of 64




             while(1)  
                {  

                } 
            } //end of while loop 


            ISR(TIMER1_COMPA_vect)
            {   

                x_stepper (10, 1);

            }

            void x_stepper (stp,dir){  
                //direction
                if (dir == 1){ 
                    led_port |= (1 << dir_led);} 
                else if (dir == 0){ 
                    led_port &= ~ (1 << dir_led);} 
                //stepper logic
                    led_port ^= (1 << stp_led);
                    if (x_counter >= stp){ 
                        led_port &= ~ (1 << stp_led);  
                            x_boolean = 0;}      
                if (x_boolean == 1){
                x_counter ++;
                 }
            } 


               
            

            
