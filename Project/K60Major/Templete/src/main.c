#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "adc.h"
#include "pit.h"

#include "LQ_OLED.h"
#include "DataScope_DP.h"
#include "8700_2100.h"

#include "counter.h"
#include "filter.h"
#include "timer.h"

#define LED_ON PEout(26) = 0
#define LED_OFF PEout(26) = 1

uint32_t uart_instance;
    
extern uint32_t ChlValue[2];

Data fin;


// Turn = Gyro_y;
// Balance = Gyro_x, accel_y
    
int main(void)
{   
    DelayInit();

    GPIO_QuickInit(HW_GPIOE, 26, kGPIO_Mode_OPP);   

    uart_instance = UART_QuickInit(UART4_RX_PE25_TX_PE24, 115200);
    
    LCD_Init();
    LCD_Print(20, 2, "Big Brother");
    
//    LED_ON;  // 查看初始化时间
//
//    LED_ON;   // 
    
    GyroAccel_Init();
    
    CounterInit();
    Timer_Init();
    
    while(1)
    {

//        printf("[CH%d]:%4dHz [CH%d]:%4dHz\r\n", 0, ChlValue[0], 1, ChlValue[1]);

        DataScope(uart_instance, scope_buf);
#if 0
    float gyroaccel[6];
    
    GyroAccel_Read(gyroaccel);
        
    scope_buf[0] = gyroaccel[0];
    scope_buf[1] = gyroaccel[1];
    scope_buf[2] = gyroaccel[2];
    scope_buf[3] = gyroaccel[3];
    scope_buf[4] = gyroaccel[4];
    scope_buf[5] = gyroaccel[5];
 
//    scope_buf[6] = yi;
 
    scope_buf[7] = Kalman_Filter(gyroaccel[5], gyroaccel[1]);	
    scope_buf[8] = Complementary_Filter(gyroaccel[5], gyroaccel[1]);
    scope_buf[9] = Complementary_Filter2(gyroaccel[5], gyroaccel[1]);
        
    
    DataScope(uart_instance, scope_buf);

#endif

    }
}


