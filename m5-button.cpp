#include "m5-button.h"

void M5Button::Begin()
{

}

void M5Button::Update()
{
    if (M5.BtnA.isPressed())
    {
        if (on_button_a_pressed != nullptr)
        {
            on_button_a_pressed();
        }
    }

    if (M5.BtnB.isPressed())
    {
        if (on_button_b_pressed != nullptr)
        {
            on_button_b_pressed();
        }
    }

    if (M5.BtnC.isPressed())
    {
        if (on_button_c_pressed != nullptr)
        {
            on_button_c_pressed();
        }
    }
}