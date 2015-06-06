         /*
         * avr_cnc.c
         *
         * Created: 2015-04-01 6:13:58 AM
         *  Author: Alvi
         */ 


        #include <avr/io.h>    
        #include <stdio.h>
        #include <util/delay.h> 
        #include <avr/interrupt.h>  
        //axis bools

    //////////////////
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
    // DDR////////
        #define led_x_ddr DDRB  
        #define led_y_ddr DDRD 
        #define led_z_ddr DDRD
        #define F_CPU 16000000UL 
    ////////////////////////////////
    ////////////////// This is where the position commands are placed
        int axis[] = {1};
        int direction[] = {0};
        int steps[] = {30000};   
    ///////////////////////////////////////////////////////////////////
        int entries = sizeof(axis)/sizeof(int) - 1; // entries is the number of things in the array 
        int ab = 0; //general counter that goes through array 
    ////////////////////////////////// 
    ///Various counters and booleans for 3 axis and more
        static volatile unsigned long x_counter = 0; 
        static volatile int x_boolean = 1; 
        static volatile int y_counter = 0; 
        static volatile int y_boolean = 1;
        static volatile int z_counter = 0; 
        static volatile int z_boolean = 1;   
        static volatile int xy_boolean = 1; 
        static volatile int xy_counter = 0;  
        static volatile int xz_boolean = 1; 
        static volatile int xz_counter = 0; 
        static volatile int yz_boolean = 1; 
        static volatile int yz_counter = 0;
    ////////////////////////////////////////////////////////
    //////////Function Variables/////////////////////// 
        int direction_ab; 
        unsigned long steps_ab;  
    ///////////////////////////////// 
        

        int main(void)
        {  

        ////// DDR setups /////////////////////////////////////////////////
            led_x_ddr |= ((1 << stp_x_led) | (1 << dir_x_led));   
            led_y_ddr |= ((1 << stp_y_led) | (1 << dir_y_led)); 
            led_z_ddr |= ((1 << stp_z_led) | (1 << dir_z_led));
        /////////////////////////////////////////////////////////// 
            TCCR1B |= (1 << WGM12);  // configuring timer 1 for ctc mode
            OCR1A = 14.625;//Timer settings
            TIMSK1 |= (1 << OCIE1A); // enable ctc interrupt
            TCCR1B |= ((1 << CS12) | (1 << CS10)); //Start at 1024 prescaler 
            sei(); //Enable global interrupts
            while(1)  
            {    


            }          

        } //end of main loop


        ISR(TIMER1_COMPA_vect)
        {   
            ///////Define which stepper, direction and how many steps in this code
            stepper_protocol(axis[ab],steps[ab],direction[ab]);  

            ////////////////////////////////////////////////////////////////////
        }

         stepper_protocol(enable,steps_ab,direction_ab,sim_enable_ab){ 

        // checks if user enabled x-axis 
            if (ab <= entries){  
                if (enable == 1){ 
                    x_boolean = 1;
            //direction
                if (direction_ab == 1){ 
                    led_portx |= (1 << dir_x_led); 
                } 
                else if (direction_ab == 0){ 
                    led_portx &= ~ (1 << dir_x_led); 
                } 
            //stepper logic 
                led_portx ^= (1 << stp_x_led);
                   if (x_counter >= steps_ab){ 
                        led_portx &= ~ (1 << stp_x_led);   
                        led_portx &= ~ (1 << dir_x_led);
                        x_boolean = 0;  
                    }    
                    if (x_counter >= steps_ab){ 
                        x_counter = 0;
                        ab ++; 
                    }  
                    if (x_boolean == 1){
                        x_counter ++;
                    } 
                } 
            ///////////////////////////////
            
            // checks if user enabled y-axis 
                else if (enable == 2){ 
                y_boolean = 1;
            //directjion
                if (direction_ab == 1){ 
                    led_portyz |= (1 << dir_y_led); 
                } 
                else if (direction_ab == 0){ 
                    led_portyz &= ~ (1 << dir_y_led); 
                }  
            //stepper logic
                led_portyz ^= (1 << stp_y_led);
                    if (y_counter >= steps_ab){ 
                        led_portyz &= ~ (1 << stp_y_led);   
                        led_portyz &= ~ (1 << dir_y_led);  
                        y_boolean = 0;  
                    } 
                    if (y_counter >= steps_ab){ 
                        y_counter = 0;
                        ab ++; 
                    }
                if (y_boolean == 1){
                y_counter ++;
                    }   
                }  
            /////////////////////////////////
            
            // checks if user enabled z-axis 
                else if (enable == 3){ 
                z_boolean = 1;
            //direction
                if (direction_ab == 1){ 
                    led_portyz |= (1 << dir_z_led); 
                } 
                else if (direction_ab == 0){ 
                    led_portyz &= ~ (1 << dir_z_led); 
                } 
            //stepper logic
                led_portyz ^= (1 << stp_z_led);
                    if (z_counter >= steps_ab){ 
                        led_portyz &= ~ (1 << stp_z_led);   
                        led_portyz &= ~ (1 << dir_z_led);
                        z_boolean = 0; 
                    } 
                    if (z_counter >= steps_ab){ 
                        z_counter = 0;
                        ab ++; 
                    }      
                if (z_boolean == 1){
                z_counter ++;
                    }  
                }  
            
            //Checks is user enabled xz-axis     
                else if (enable = 4){  
                xy_boolean = 1; 
                //direction
                    if (direction_ab == 10){ 
                        led_portx |= (1 << dir_x_led); 
                        led_portyz &= ~ (1 << dir_z_led);
                    } 
                    else if (direction_ab == 11){ 
                        led_portx |= (1 << dir_x_led); 
                        led_portyz |= (1 << dir_z_led);
                    } 
                    else if (direction_ab == 01){ 
                        led_portx &= ~ (1 << dir_x_led); 
                        led_portyz |= (1 << dir_z_led);
                    } 
                    else if (direction_ab == 00){ 
                        led_portx &= ~ (1 << dir_x_led); 
                        led_portyz &= ~ (1 << dir_z_led);
                    }  
                //stepper logic 
                    led_portyz ^= (1 << stp_z_led); 
                    led_portx ^= (1 << stp_x_led);
                    if (xy_counter >= steps_ab){ 
                        led_portx &= ~ (1 << stp_x_led); 
                        led_portyz &= ~ (1 << stp_z_led);  
                        led_portx &= ~ (1 << dir_x_led);
                        led_portyz &= ~ (1 << dir_z_led);
                        xy_boolean = 0; 
                    } 
                    if (xy_counter >= steps_ab){ 
                        xy_counter = 0;
                        ab ++; 
                    }      
                    if (xy_boolean == 1){
                    xy_counter ++;
                    }  
                }  
            ////////////////////////////////////////////////////

            //Checks if user enables xy axis
                else if (enable = 5){  
                xy_boolean = 1; 
                //direction
                    if (direction_ab == 10){ 
                        led_portx |= (1 << dir_x_led); 
                        led_portyz &= ~ (1 << dir_y_led);
                    } 
                    else if (direction_ab == 11){ 
                        led_portx |= (1 << dir_x_led); 
                        led_portyz |= (1 << dir_y_led);
                    } 
                    else if (direction_ab == 01){ 
                        led_portx &= ~ (1 << dir_x_led); 
                        led_portyz |= (1 << dir_y_led);
                    } 
                    else if (direction_ab == 00){ 
                        led_portx &= ~ (1 << dir_x_led); 
                        led_portyz &= ~ (1 << dir_y_led);
                    }  
                //stepper logic 
                    led_portyz ^= (1 << stp_y_led); 
                    led_portx ^= (1 << stp_x_led);
                    if (xy_counter >= steps_ab){ 
                        led_portx &= ~ (1 << stp_x_led); 
                        led_portyz &= ~ (1 << stp_y_led);  
                        led_portx &= ~ (1 << dir_x_led);
                        led_portyz &= ~ (1 << dir_y_led);
                        xy_boolean = 0; 
                    } 
                    if (xy_counter >= steps_ab){ 
                        xy_counter = 0;
                        ab ++; 
                    }      
                    if (xy_boolean == 1){
                    xy_counter ++;
                    }  
                } 
                //////////////////////////////////////

            } 
            //return 0;
        }