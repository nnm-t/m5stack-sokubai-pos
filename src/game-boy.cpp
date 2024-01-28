#include "game-boy.h"

void GameBoy::ReceiveKeyCode(const uint8_t code)
{
    switch (code)
    {
        case up_code:
            if (on_up_pressed == nullptr)
            {
                break;
            }

            on_up_pressed();
            break;
        case down_code:
            if (on_down_pressed == nullptr)
            {
                break;
            }

            on_down_pressed();
            break;
        case left_code:
            if (on_left_pressed == nullptr)
            {
                break;
            }

            on_left_pressed();
            break;
        case right_code:
            if (on_right_pressed == nullptr)
            {
                break;
            }

            on_right_pressed();
            break;
        case a_code:
            if (on_a_pressed == nullptr)
            {
                break;
            }

            on_a_pressed();
            break;
        case b_code:
            if (on_b_pressed == nullptr)
            {
                break;
            }

            on_b_pressed();
            break;
        case start_code:
            if (on_start_pressed == nullptr)
            {
                break;
            }

            on_start_pressed();
            break;
        case select_code:
            if (on_select_pressed == nullptr)
            {
                break;
            }

            on_select_pressed();
            break;
        case release_code:
            if (on_released == nullptr)
            {
                break;
            }

            on_released();
            break;
    }
}