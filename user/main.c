#include"pwm.h"
#include"delay.h"
int main(void)	
{
    u16 led0pwmval;	
	delay_init(72);
 	TIM2_PWM_Init(2000,719);	//100Khz的计数频率，计数到2000为20ms   

	  	for(led0pwmval=50;led0pwmval<150;led0pwmval++) 									 
		   {	    
		    TIM_SetCompare3(TIM2,led0pwmval);
	    	delay_ms(15);					 //延时多久很重要，自己一点点试。
		   }
  while(1);

}	
 /*
   while(1)
	{

		for(led0pwmval=100;led0pwmval<200;led0pwmval++) 									 
		   {	    
		    TIM_SetCompare3(TIM2,led0pwmval);
	    	delay_ms(10);					 //延时多久很重要，自己一点点试。
		   }
	   	for(led0pwmval=200;led0pwmval>=101;led0pwmval--) 									 
		   {
		    TIM_SetCompare3(TIM2,led0pwmval);
			delay_ms(10);
		   }
		 
	}
	*/	   

