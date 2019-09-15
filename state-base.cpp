#include "state-base.h"

namespace SokubaiPos
{
    void StateBase::Loop()
    {
        _button_a.Loop();
        _button_b.Loop();
        _button_c.Loop();
    }

    void StateBase::OnButtonAPressed()
    {

    }

    void StateBase::OnButtonBPressed()
    {

    }

    void StateBase::OnButtonCPressed()
    {

    }
}