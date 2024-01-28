#include "brightness.h"

void Brightness::Begin()
{
    LCD::SetBrightness(_value);
}

void Brightness::Up()
{
    if (max - _step < _value)
    {
        _value = max;
    }
    else
    {
        _value += _step;
    }

    LCD::SetBrightness(_value);
}

void Brightness::Down()
{
    if (_value < _step)
    {
        _value = min;
    }
    else
    {
        _value -= _step;
    }

    LCD::SetBrightness(_value);
}