#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class FooterText
{
    const String _left;
    const String _center;
    const String _right;

public:
    FooterText(const String& left, const String& center, const String& right) : _left(left), _center(center), _right(right)
    {

    }

    const String& GetLeft() const
    {
        return _left;
    }

    const String& GetCenter() const
    {
        return _center;
    }

    const String& GetRight() const
    {
        return _right;
    }
};