#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "rotation.h"

namespace SokubaiPos
{
    class LCDBase
    {
    protected:
        TFT_eSPI* _tft;

    public:
        LCDBase(TFT_eSPI* tft) : _tft(tft)
        {

        }

        LCDBase() : _tft(&M5.Lcd)
        {

        }

        Rotation GetRotation()
        {
            return static_cast<Rotation>(_tft->getRotation());
        }

        void SetRotation(const Rotation rotation)
        {
            _tft->setRotation(static_cast<uint8_t>(rotation));
        }

        void InvertDisplay()
        {
            _tft->invertDisplay(true);
        }

        void NotInvertDisplay()
        {
            _tft->invertDisplay(false);
        }
    };
}