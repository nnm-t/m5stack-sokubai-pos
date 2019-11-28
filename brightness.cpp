#include "brightness.h"

void Brightness::Begin()
{
    LCD::SetBrightness(_value);
}

void Brightness::Up()
{
    _value += _step;

    LCD::SetBrightness(_value);
}

void Brightness::Down()
{
    _value -= _step;

    LCD::SetBrightness(_value);
}