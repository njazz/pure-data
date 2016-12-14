//
//  tl_cue2.h
//  pd_ext
//
//  Created by Alex on 13/12/16.
//
//

#ifndef tl_cue2_h
#define tl_cue2_h

#include "ceammc_gui.cpp"
#include "tl_lib.hpp"

#include <stdlib.h>
//#include <m_pd.h>

//#define HIDE __attribute__ ((visibility ("hidden")))
//#define HIDE

//alias

class tl_cue2 : public ceammc_gui
{
public:
    //     void pd_setup(t_object* obj);
    
} ;





class tl_cue2_object : public ceammc_gui_object
{
public:
    virtual void ui_property_init();
    
    virtual long size(){return sizeof(tl_cue2_object);}
    
    //    void w_getrect(t_gobj *z, t_glist *glist, int *x1, int *y1, int *x2, int *y2) ;
    
    virtual void w_displace(t_gobj *z, t_glist *glist, int dx, int dy) ;
    
    //virtual  void w_delete(t_gobj *z, t_glist *glist) ;
    virtual  void w_draw(t_gobj *z, t_glist *glist);
    virtual  void w_erase(t_gobj *z, t_glist *glist);
    //int w_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit);
    virtual void w_select(t_gobj *z, t_glist *glist, int selected);
    
    virtual void pd_instance_init();
    
    
};

#endif /* tl_cue2_h */