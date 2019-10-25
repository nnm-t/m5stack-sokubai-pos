#pragma once

class StateBase
{
public:
    virtual void Begin() = 0;

    virtual void Loop() = 0;

    virtual void Draw() = 0;
};