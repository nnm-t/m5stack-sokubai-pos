#include "m5-button.h"

void M5Button::Begin()
{

}

void M5Button::Update()
{
    if (M5.BtnA.wasPressed())
    {
        if (on_button_a_pressed != nullptr)
        {
            on_button_a_pressed();
        }
    }

    if (M5.BtnB.wasPressed())
    {
        if (on_button_b_pressed != nullptr)
        {
            on_button_b_pressed();
        }
    }

    if (M5.BtnC.wasPressed())
    {
        if (on_button_c_pressed != nullptr)
        {
            on_button_c_pressed();
        }
    }
}