

bool MeasEnd = 0 , OVF = 0, edge = 0;
volatile int prevMeas = 0;
volatile uint16_t T1OVF_Counter = 0;
volatile int T1 = 0, T2 = 0, T = 0;
ICP_INIT(){
  Serial.begin(115200);
  DDRC &= ~ (1 << PC7); //Arduino Pin13 setup
  PORTC |= (0 << PC7);
  //Inicjalize TCCR3A and B register of timer3 
  TCCR3A = 0;           // Init Timer1A
  TCCR3B = 0;           // Init Timer1B
  //Noise reduction fo ICP OFF 0 ON 1
    TCCR3B |= (0<<ICNC3);   
  //Trigger with raising edge 
    TCCR3B |= (1<<ICES3);       
  //Set the prescaller for 1 / 16Mhz input
    TCCR3B |= (0<<CS32);
    TCCR3B |= (0<<CS31);        
    TCCR3B |= (1<<CS30);
    //  32  31  30
   // 0	0	0	 Clock Source Off
   // 0	0	1	 /1
   // 0	1	0	 /8
   // 0	1	1	 /64
   // 1	0	0	 /256
   // 1	0	1	 /1024
  //Inicjalize TIMSK3 register 
    TIMSK3 = 0;
   //ICP interrupt ON
    TIMSK3 |= (1<<ICIE3);  
  //OverFlow event interrupt ON
    TIMSK3 |= (1<<TOIE3);     
}
void ICP_OFF(){
   //ICP interrupt OFF
    TIMSK3 |= (0<<ICIE3); 
}
void ICP_ON(){
   //ICP interrupt ON
    TIMSK3 |= (1<<ICIE3); 
}
//Overflow Event
ISR(TIMER3_OVF_vect){
  //Increase value for each overflow event
  T1OVF_Counter++;
  //This is to work with 0% and 100% PWM signal
  if(T1OVF_Counter>2){
      T = !edge*4000;
    }
}

ISR(TIMER3_CAPT_vect){
//If this is first Edge:
  if(!MeasEnd) {
    //Get counter value
    T1 = ICR3;
    //Change flag for second measuere 
    MeasEnd = 1;
  }
  else {
    //If this is second measure
    //Capture caounter value
    T2 = ICR3;
    //If the counter overflow
    if(T1OVF_Counter) {
      //add its value to the value of T2
      T2 = T2 + (65536 * T1OVF_Counter) ; //16 bit long
      T=T2-T1;
    }
    else {
      T = T2 - T1;
    }
    
    T1OVF_Counter = 0;
    MeasEnd = 0;
  }
  //Change edge flag
  edge = !edge;
   TCCR3B ^= (1<<ICES3); //Change edge
}

