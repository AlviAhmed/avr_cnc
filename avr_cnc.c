 /*
             * avr_cnc.c
             *
             * Created: 2015-04-01 6:13:58 AM
             *  Author: Alvi
             */ 


            #include <avr/io.h>   
            #include <util/delay.h> 
            #include <avr/interrupt.h> 
            // x-axis
            #define stp_x_led PB0
            #define dir_x_led PB1  
           
            ////////////// 
            // y-axis
            #define stp_y_led PD6
            #define dir_y_led PD7 
             
            ////////////  
            // z-zxis  
            #define stp_z_led PD4 
            #define dir_z_led PD5
            
            // PORTB 
            #define led_portx PORTB
            //////////// 
            /// PORTD
            #define led_portyz PORTD 
            ///////////  
            // PORTC 
            //#define led_portz PORTC 
            // DDR////////
            #define led_x_ddr DDRB  
            #define led_y_ddr DDRD 
            #define led_z_ddr DDRD
            #define F_CPU 16000000UL 
           
             
            int x_counter = 0; 
            int x_boolean = 1; 
            int y_counter = 0; 
            int y_boolean = 1;
            int z_counter = 0; 
            int z_boolean = 1;
            
            int main(void)
            {  
                
                ////// DDR setups /////////////////////////////////////////////////
                led_x_ddr |= ((1 << stp_x_led) | (1 << dir_x_led));   
                led_y_ddr |= ((1 << stp_y_led) | (1 << dir_y_led)); 
                led_z_ddr |= ((1 << stp_z_led) | (1 << dir_z_led));
                ////////// PORT setups /////////////////////////////////////// 
                //led_portx |= ((1 << stp_x_led) | (1 << dir_x_led)); 
                //led_porty |= ((1 << stp_y_led) | (1 << dir_y_led)); 
                //led_portz |= ((1 << stp_z_led) | (1 << dir_z_led));
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

                x_stepper(10, 1);  
                y_stepper(20,1); 
                z_stepper(30,1); 
            }

            void x_stepper (stp_x,dir_x){  
                //direction
                if (dir_x == 1){ 
                    led_portx |= (1 << dir_x_led); 
                } 
                else if (dir_x == 0){ 
                    led_portx &= ~ (1 << dir_x_led); 
                } 
                ///////////////////////////////
                //stepper logic
                    led_portx ^= (1 << stp_x_led);
                    if (x_counter >= stp_x){ 
                        led_portx &= ~ (1 << stp_x_led);  
                        x_boolean = 0; 
                    }      
                    if (x_boolean == 1){
                    x_counter ++;
                    }   
                //////////////////////////////
            }  

            void y_stepper (stp_y,dir_y){  
                //direction
                if (dir_y == 1){ 
                    led_portyz |= (1 << dir_y_led); 
                } 
                else if (dir_y == 0){ 
                    led_portyz &= ~ (1 << dir_y_led); 
                }  
                ///////////////////////////////
                //stepper logic
                    led_portyz ^= (1 << stp_y_led);
                    if (y_counter >= stp_y){ 
                        led_portyz &= ~ (1 << stp_y_led);  
                        y_boolean = 0; 
                    }      
                    if (y_boolean == 1){
                    y_counter ++;
                    }   
                //////////////////////////////
            } 

             void z_stepper (stp_z,dir_z){  
                //direction
                if (dir_z == 1){ 
                    led_portyz |= (1 << dir_z_led); 
                } 
                else if (dir_z == 0){ 
                    led_portyz &= ~ (1 << dir_z_led); 
                } 
                ///////////////////////////////
                //stepper logic
                    led_portyz ^= (1 << stp_z_led);
                    if (z_counter >= stp_z){ 
                        led_portyz &= ~ (1 << stp_z_led);  
                        z_boolean = 0; 
                    }      
                    if (z_boolean == 1){
                    z_counter ++;
                    }   
                //////////////////////////////
            }
            