/*=============================================================================

Copyright (c) 2013 Ville Ruusutie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

=============================================================================*/
#include "unitos/unitos.h"
#if 0
#include "reflectos_lua.h"

namespace r = reflectos;
//----------------------------------------------------------------------------

namespace {

void* allocate(void* userdata, void* ptr, size_t oldSize, size_t newSize)
{
    userdata;
    oldSize;
    if(newSize == 0) {
        ::free(ptr);
        return nullptr;
    }
    return ::realloc(ptr, newSize);
}

}
//----------------------------------------------------------------------------

class LuaClass
{
public:
    LuaClass() : m_data(3) {}

    void setData(int i) { m_data = i; }
    int getData() const { return m_data; }
    int one() const { return 1; }

private:
    int m_data;

    REFLECT_CLASS(LuaClass)
        REFLECT_FIELD(m_data)
        REFLECT_FUNCTION(setData)
        REFLECT_FUNCTION(getData)
        REFLECT_FUNCTION(one)
    REFLECT_END()
};

REGISTER_CLASS(LuaClass)
//----------------------------------------------------------------------------

struct LuaFixture : public unitos::SuiteTest
{
    LuaFixture()
    {
        L = lua_newstate(::allocate, nullptr);
        r::LuaBinder luaBinder(L);
        luaBinder.visitClass<LuaClass>();
    }

    virtual ~LuaFixture()
    {
        lua_close(L);
    }

    lua_State* L;
};

TEST_SUITE(Lua)
{
    TEST_FIXTURE(LuaFixture,GetData)
    {
        
    }
}
#endif
