#include "my_button.h"

void button_init(button_t *btn, int8_t (*read_gpio_level)(uint16_t), uint8_t press_level, uint16_t button_id)
{
    btn->id = button_id;
    btn->status = BUTTON_STATUS_IDLE;
    btn->event = BUTTON_EVENT_NONE;
    btn->ticks = 0;
    btn->debounce_ticks = 0;
    btn->trigger_level = press_level;
    btn->current_level = !press_level;
    btn->hal_get_btn_level = read_gpio_level;
}

void button_action_attach(button_t *btn, button_cb_t cb)
{
        btn->cb = cb;
}

int8_t button_is_pressed(button_t *btn)
{
    if (btn == NULL)
        return -1;
    return btn->current_level == btn->trigger_level ? 1 : 0;
}

static void button_process(button_t *btn)
{
    uint8_t update_level = btn->hal_get_btn_level(btn->id);

    if (btn->status > BUTTON_STATUS_IDLE)
        btn->ticks++;

    if (btn->current_level != update_level){
        btn->debounce_ticks++;
        if (btn->debounce_ticks > BUTTON_DEBOUNCE_TICKS){
            btn->current_level = update_level;
            btn->debounce_ticks = 0;
        }
    }else{
        btn->debounce_ticks = 0;
    }

    switch (btn->status){
    case BUTTON_STATUS_IDLE:
        if (btn->current_level == btn->trigger_level)
        {
            btn->event = BUTTON_EVENT_PRESS;
            // current_status + event -> next_status
            btn->status = BUTTON_STATUS_PRESSED;
            // triggle atcion
            if (btn->cb != NULL)
                btn->cb(btn->event);
        }else{
            btn->event = BUTTON_EVENT_NONE;
        }
        break;

    case BUTTON_STATUS_PRESSED:
        if (btn->current_level != btn->trigger_level)
        {
            btn->ticks = 0;
            btn->event = BUTTON_EVENT_RELEASE;
            // current_status + event -> next_status
            btn->status = BUTTON_STATUS_RELEASED;
            // triggle atcion
            if (btn->cb != NULL)
                btn->cb(btn->event);
        }else{
            if (btn->ticks > LONG_PRESS_TICKS){
                btn->ticks = 0;
                btn->event = BUTTON_EVENT_LONG_PRESS;
                // current_status + event -> next_status
                btn->status = BUTTON_STATUS_LONG_PRESSED;
                // triggle atcion
                if (btn->cb != NULL)
                    btn->cb(btn->event);
            }
        }
        break;

    case BUTTON_STATUS_RELEASED:
        if (btn->current_level == btn->trigger_level)   // click again
        {
            btn->event = BUTTON_EVENT_PRESS;
            // current_status + event -> next_status
            btn->status = BUTTON_STATUS_PRESSED;
            // click cnt + 1
            btn->click_cnt++;
            // triggle atcion
            if (btn->cb != NULL)
                btn->cb(btn->event);
        }else{
            if (btn->ticks > RELASE_TIMEOUT_TICKS){
                // current_status + event -> next_status
                btn->status = BUTTON_STATUS_IDLE;
                // triggle atcion
                if (btn->click_cnt == 0){
                    btn->event = BUTTON_EVENT_CLICK_1;
                    if (btn->cb != NULL)
                        btn->cb(btn->event);
                }else{
                    btn->event = BUTTON_EVENT_CLICK_2;
                    if (btn->cb != NULL)
                        btn->cb(btn->event);
                }
                // clear click cnt
                btn->click_cnt = 0;
            }
        }
        break;

    case BUTTON_STATUS_LONG_PRESSED:
        if (btn->current_level != btn->trigger_level)
        {
            btn->ticks = 0;
            btn->event = BUTTON_EVENT_RELEASE;
            // current_status + event -> next_status
            btn->status = BUTTON_STATUS_IDLE;
            // triggle atcion
            if (btn->cb != NULL)
                btn->cb(btn->event);
        }
        break;

    default:
        break;
    }
}


void ticks(button_t *btn)
{
    for (int i = 0; i < MAX_BUTTON_NUM; i++)
    {
        button_process(&btn[i]);
    }
}
