/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *USART Print debugging routine:
 *USART1_Tx(PA9).
 *This example demonstrates using USART1(PA9) as a print debug port output.
 *
 */

#include "debug.h"
#include "my_button.h"

/* Global typedef */

/* Global define */
#define LED_PORT GPIOC
#define LED_PIN  GPIO_Pin_13
#define BTN_PORT GPIOA
#define BTN_PIN  GPIO_Pin_0


/* Global Variable */
button_t b_test[2];
uint8_t led_state = 0;

void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void GPIO_LED_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = BTN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BTN_PORT, &GPIO_InitStructure);
}

int8_t get_button_level(uint16_t id)
{
    int8_t level = 0;

    switch (id) {
    case 1:
        level = GPIO_ReadInputDataBit(BTN_PORT, BTN_PIN);
        break;
    
    default:
        break;
    }
    return level;
}

void test_btn(void)
{
    static uint8_t flag = 0;
    uint8_t level = GPIO_ReadInputDataBit(BTN_PORT, BTN_PIN);

    if (!flag && level){
        flag = 1;
    }else if (flag && !level){
        flag = 0;
        printf("User Test\r\n");
    }
}

void btn1_callback(uint8_t btn_evt)
{
    switch (btn_evt) {
    case BUTTON_EVENT_PRESS:
        printf("press\r\n");
        break;

    case BUTTON_EVENT_RELEASE:
        printf("release\r\n");
        break;
    
    case BUTTON_EVENT_CLICK_1:
        printf("click 1\r\n");
        break;

    case BUTTON_EVENT_CLICK_2:
        printf("click 2\r\n");
        break;
    
    case BUTTON_EVENT_LONG_PRESS:
        printf("long press\r\n");
        break;

    default:
        break;
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    // hardware init
    GPIO_Toggle_INIT();
    GPIO_LED_INIT();
    // user init
    button_init(&b_test[0], get_button_level, 1, 1);
    button_action_attach(&b_test[0], btn1_callback);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    printf("This is printf example\r\n");

    while(1)
    {
        // test_btn();
        ticks(b_test);
        Delay_Ms(5);
    }
}
