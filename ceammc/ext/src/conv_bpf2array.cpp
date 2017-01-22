//
//  2bpflist.cpp
//  bpf2list
//
//  Created by Alex Nadzharov on 06/01/17.
//
//

#include "ceammc.hpp"
#include "ceammc_factory.h"
//#include "ceammc_fn_list.h"
#include "ceammc_log.h"
#include "ceammc_object.h"

#include "ceammc_bpf.h"

using namespace ceammc;

class Bpf2List : public BaseObject
{
    AtomList out_list_;
    
    SymbolEnumProperty* method_;
    Atom size_;
    
    t_symbol *arrayname;
    int array_size;
    
public:
    Bpf2List(const PdArgs& a)
    : BaseObject(a)
    , size_(16)
    
    {
        createOutlet();
        
        initProperties();
        // parse creation arguments and properties
        parseArguments();
    }
    
    void onBang()
    {
        int i, vecsize;
        t_garray *a;
        t_word *vec;
        
        if (!(a = (t_garray *)pd_findbyclass(this->arrayname, garray_class)))
            pd_error(this->owner(), "%s: no such array", this->arrayname->s_name);
        else if (!garray_getfloatwords(a, &vecsize, &vec))
            pd_error(this->owner(), "%s: bad template for tabwrite", this->arrayname->s_name);
        else
        {
            for ( i=0;i<vecsize; i++)
            {
                vec[i].w_float = out_list_.at(i).asFloat();
            }
            garray_redraw(a);
        }
    }
    
    void onList(const AtomList& l)
    {
        int vecsize;
        t_garray *a;
        t_word *vec;
        
        if (!(a = (t_garray *)pd_findbyclass(this->arrayname, garray_class)))
            pd_error(this->owner(), "%s: no such array", this->arrayname->s_name);
        else if (!garray_getfloatwords(a, &vecsize, &vec))
            pd_error(this->owner(), "%s: bad template for tabwrite", this->arrayname->s_name);
        else
        {
            this->size_ = Atom(vecsize);
            
            BPF func;
            func.empty();
            //temporary
            func.initRange();
            
            func.setBPFList(l);
            
            this->out_list_ = func.getVector(this->size_.asInt());
            
            onBang();
        }
        
        
    }
    
    void initProperties()
    {
        
    }
    
};

extern "C" void setup_conv0x2ebpf2array()
{
    ObjectFactory<Bpf2List> obj("conv.bpf2array");
}
