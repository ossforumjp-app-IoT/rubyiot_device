/*---------------------------------------------*/
/*                    main.c                   */
/*---------------------------------------------*/
/*                                             */
/*---------------------------------------------*/

#include "FM3_type2.h"
#include "integer.h"

#include "mruby.h"
#include "mruby/irep.h"

/* Control onboard LED */
#define LED_ON()	DDRF |= 0x0008	/* PF3 Low */
#define LED_OFF()	DDRF &= ~0x0008	/* PF3 Hi-Z */

volatile UINT Timer;		/* Performance counter (1kHz increment) */

/* mruby bytecode */
extern const uint8_t mrbprcs[];

/*---------------------------------------------*/
/* 1kHz timer process                          */
/*---------------------------------------------*/
 
void SysTick_Handler (void)
{
	static UINT led;
 
	STCTRL;		/* Clear IRQ */
 
	Timer++;	/* Increment performance counter */
 
	led++;		/* LED blinking timer */
	if ((led & 0x40) && (led & 0x680) == 0)
	{
		LED_OFF();
	}
	else
	{
		LED_ON();
	}
}

UINT gap(time)
{
	if ( Timer >= time )
	{
		return (Timer - time);
	}
	else
	{
		return (0xffffffff - time + Timer);
	}
}

void msleep(UINT ms)
{
	UINT start;
	start = Timer;
	while(gap(start) < ms);
}

/*---------------------------------------------*/
/* main function                               */
/*---------------------------------------------*/
 
int main (void)
{
	mrb_state *mrb = NULL;
	mrb_value app;
	int ai;
	uint8_t i;
 
	/* Configure WDT (disable) */
	WDG_LCK = 0; WDG_LCK = 0x1ACCE551; WDG_LCK = ~0x1ACCE551;
	WDG_CTL = 0;
	
	/* Configure I/O port */
	ADE = 0;	/* Disable all analog inputs */
 
	/* Enable SysTick timer in interval of 1 ms */
	STRELOAD = 144000000 / 1000 - 1;
	STCTRL = 0x07;
	
	/* mruby VM  */
	mrb = mrb_open();
	 
	if(mrb)
	{
		/* Load bytecode */
		mrb_load_irep(mrb, mrbprcs);
	
		/* Create instance from App Class(Initialize) */
		app = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "App"));
		
		/* Main process */
		for(;;)
		{
			ai = mrb_gc_arena_save(mrb);
			mrb_funcall(mrb, app, "get_message", 0);	/* message polling */
			mrb_gc_arena_restore(mrb, ai);
			i++;
			if(i >= 18)
			{
				ai = mrb_gc_arena_save(mrb);
				mrb_funcall(mrb, app, "main", 0);	/* main */
				mrb_gc_arena_restore(mrb, ai);
				i = 0;
			}
			msleep(50);			/* polling interval */
		}
	}
}

