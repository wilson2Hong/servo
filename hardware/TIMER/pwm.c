#include"pwm.h"

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器3时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );// 不开AFIO也可以
    //设置该引脚为复用输出功能,输出TIM2 CH3的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH3（通道3就是PA2）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出。这句好关键啊。。。。
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = arr;   //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	//初始化TIM2 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能，使能PWM输出到端口。
//	TIM_OCInitStructure.TIM_Pulse=127;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性:TIM输出比较极性
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
 	TIM_ARRPreloadConfig(TIM2, ENABLE);                //使能TIMx在ARR上的预装载寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIM3总开关
}
