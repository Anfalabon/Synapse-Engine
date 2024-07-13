#pragma once

namespace Synapse
{


template<class T> class Ref
{
public:
    Ref(T& ref) : m_ref(ref){}

    T& Get() const {return m_ref;}

private:
    T& m_ref;
};



}