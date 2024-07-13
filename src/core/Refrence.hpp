#pragma once

namespace Synapse
{

template<class T>
class Ref
{
public:
    Ref() = default;
    ~Ref() = default;

    void SetValue(){}
    T &GetValue(){}

private:
    T &Ref;
};



}