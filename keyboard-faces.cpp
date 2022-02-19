#include "keyboard-faces.h"

void KeyboardFaces::ReceiveKeyCode(uint8_t code)
{
    switch (code)
    {
        case h_code:
            if (on_left_pressed == nullptr)
            {
                break;
            }
            on_left_pressed();
            break;
        case j_code:
            if (on_down_pressed == nullptr)
            {
                break;
            }
            on_down_pressed();
            break;
        case k_code:
            if (on_up_pressed == nullptr)
            {
                break;
            }
            on_up_pressed();
            break;
        case l_code:
            if (on_right_pressed == nullptr)
            {
                break;
            }
            on_right_pressed();
            break;
        case space_code:
            if (on_a_pressed == nullptr)
            {
                break;
            }
            on_a_pressed();
            break;
        case bs_code:
            if (on_b_pressed == nullptr)
            {
                break;
            }
            on_b_pressed();
            break;
        case enter_code:
            if (on_start_pressed == nullptr)
            {
                break;
            }
            on_start_pressed();
            break;
        case del_code:
            if (on_select_pressed == nullptr)
            {
                break;
            }
            on_select_pressed();
            break;
    }
}