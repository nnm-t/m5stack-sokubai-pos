#pragma once

class IState
{
public:
    virtual void Begin() = 0;

    virtual void Loop() = 0;

    virtual void Draw() = 0;

    virtual void Up() = 0;

    virtual void Down() = 0;

    virtual void Left() = 0;

    virtual void Right() = 0;

    virtual void Select() = 0;

    virtual void Start() = 0;

    virtual void ButtonA() = 0;

    virtual void ButtonB() = 0;

    virtual void ButtonC() = 0;
};