#include "ceammc_factory.h"
#include "ceammc_format.h"
#include "ceammc_object.h"

using namespace ceammc;

class TestProp : public BaseObject {
public:
    TestProp(const PdArgs& pd)
        : BaseObject(pd)
    {
        createOutlet();
        createOutlet();
        createInlet();
        createInlet();
        createProperty(new FloatProperty("@a", 0));
        createProperty(new ListProperty("@b"));

        parseArguments();
    }

    void processInlet(size_t n, const AtomList& lst)
    {
        post("data to inlet: %s", to_string(lst).c_str());
    }

    void testMethod(t_symbol* s, const AtomList& lst)
    {
        post("hi!!! from: %s - %s", s->s_name, to_string(lst).c_str());
    }
    void testMethod2(t_symbol* s, const AtomList& lst)
    {
        post("hi2!!! from: %s - %s", s->s_name, to_string(lst).c_str());
    }
};

extern "C" void setup_test0x2eprop()
{
    ObjectFactory<TestProp> t("test.prop");
    t.addMethod("help", &TestProp::testMethod);
    t.addMethod("help2", &TestProp::testMethod2);
}
