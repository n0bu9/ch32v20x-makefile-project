#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <stdint.h>
#include <string.h>

#define MAX_BUTTON_NUM  1
#define BUTTON_DEBOUNCE_TICKS  10
#define LONG_PRESS_TICKS  300
#define RELASE_TIMEOUT_TICKS  60

typedef struct __button button_t;
typedef void (*button_cb_t)(uint8_t btn_evt);

typedef enum{
    BUTTON_EVENT_NONE = -1,
    // button event
    BUTTON_EVENT_PRESS = 0,
    BUTTON_EVENT_RELEASE,
    BUTTON_EVENT_LONG_PRESS,
    BUTTON_EVENT_CLICK_1,
    BUTTON_EVENT_CLICK_2,
    // BUTTON_EVENT_DOUBLE_CLICK,
    // BUTTON_EVENT_LONG_PRESS_START,
    // BUTTON_EVENT_LONG_PRESS_HOLD,
    // BUTTON_EVENT_LONG_PRESS_END,
    BUTTON_EVENT_MAX,
}BUTTON_EVENT_T;

typedef enum{
    BUTTON_STATUS_IDLE = 0,
    BUTTON_STATUS_PRESSED,
    BUTTON_STATUS_LONG_PRESSED,
    BUTTON_STATUS_RELEASED,
    BUTTON_STATUS_MAX,
}BUTTON_STATUS_T;

struct __button
{
    uint16_t id;	// 按钮ID编号
    uint16_t ticks;	// 扫描周期
    uint16_t debounce_ticks;	// 消抖周期
    uint8_t trigger_level;	// 按键（按下）触发电平
    uint8_t click_cnt;	// 点击次数
    uint8_t current_level;	// 当前电平
    uint8_t event;	// 状态机触发事件
    uint8_t status;  // 状态机当前状态
    int8_t (*hal_get_btn_level)(uint16_t id); // hal function to get button level
    button_cb_t cb;
};

// Function declarations
void button_init(button_t *btn, int8_t (*read_gpio_level)(uint16_t), uint8_t press_level, uint16_t button_id);
void button_action_attach(button_t *btn, button_cb_t cb);
int8_t button_is_pressed(button_t *btn);
void ticks(button_t *btn);

#endif
