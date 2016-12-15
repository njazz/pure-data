//
//  ceammc_gui.hpp
//  pd_ext
//
//  Created by Alex on 12/12/16.
//
//

#ifndef ceammc_gui_hpp
#define ceammc_gui_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>


#include <m_pd.h>
#include <g_canvas.h>


class ceammc_gui_object;

//typedef t_class*(ceammc_gui_get_pd_class_p)();

class w_proxy{
public:

    //
    static t_widgetbehavior w_widget;
    
    //TEMP
    static t_object *ceammc_gui_pd_object;     //name
    
    //static void pd_instance_init(t_object *obj);
    static t_object *ceammc_gui_pd_instance;
    
};


typedef std::map<std::string,t_atom> gui_properties;
class ceammc_gui{
    
private:
    
    
    //pd class
    //t_class *pd_class;
    
    static void pd_class_free(ceammc_gui_object *x);
    static void pd_class_save(t_gobj *z, t_binbuf *b);
    
    //TEMP
    static t_object *ceammc_gui_pd_object;     //name
    static t_class* ceammc_gui_pd_class;
    
public:
    //test
    static void *pd_class_new1(t_symbol *s, int argc, t_atom *argv);
    static void *pd_class_new_common(t_class *c, t_object* prototype, t_symbol *s, int argc, t_atom *argv);
    
    static void pd_class_free1(t_object *x);
    static void pd_class_free_common(t_object *x);
    
    
    //log
    static void e_error(std::string err);
    static void e_properties(t_object *obj);
    static void e_atoms(t_atom *obj, int count);
    
    virtual t_class*  pd_setup(t_object *gui_class, std::string class_name,  t_class *pd_class);
    
    static gui_properties *default_properties;
    
    virtual t_class* get_pd_class();
    virtual void set_pd_class(t_class* c1);

    
};


//typedef void (drawfunc)(t_gobj, t_glist);

class ceammc_gui_object  {
private:
    //widget
    t_canvas *w_canvas;
    t_object *w_obj;
    
    //prototype
    t_class *proto_class;
    
public:
    //pd
    t_object            x_obj;
    t_glist             *x_glist;
    
    //
    virtual long size(){return sizeof(ceammc_gui_object);}
    
    //??
    gui_properties *ui_properties;
    gui_properties *ui_default_properties;
    std::string class_name;
    
    //
//    int x_w;
//    int x_h;
//    bool x_selected;
    
    //
    t_atom ui_property_get(std::string name);
    t_float ui_property_get_float(std::string name);
    char* ui_property_get_c_str(std::string name);
    void ui_property_set(std::string name, t_atom value);
    void ui_property_set(std::string name, std::string value);
    void ui_property_set(std::string name, float value);
    bool ui_property_load(t_atom *values);          //true if ok
    void ui_property_copy(t_object *obj);
    
    void ui_properties_init();

    //
    
    
    ///
    // widget
    
    static  void w_getrect(t_gobj *z, t_glist *glist, int *x1, int *y1, int *x2, int *y2);
//    static  int w_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit);
    static  void w_displace(t_gobj *z, t_glist *glist, int dx, int dy);
//    static  void w_select(t_gobj *z, t_glist *glist, int selected);
//    static  void w_delete(t_gobj *z, t_glist *glist);
//    static  void w_draw(t_gobj *z, t_glist *glist);
//    static  void w_erase(t_gobj *z, t_glist *glist);
    
    //virtual void pd_instance_init(t_object *obj);
    
//    virtual void* pd_init_v(t_symbol *s, int argc, t_atom *argv);
//    virtual void pd_init_v(ceammc_gui_object *x);
    
    virtual t_newmethod get_pd_class_new();
    virtual t_method get_pd_class_free();
    
    //
    //ceammc_gui_object(){this->ui_properties_init();}
    
};



class draw_wrappers
{
private:
    static t_canvas *w_canvas;
    static t_object *w_obj;
public:
    static void dw_set_canvas(t_glist *glist);
    static void dw_set_object(t_object *obj);
    
    static void dw_rect (std::string obj, int x, int y, int w, int h, std::string stroke_color, std::string fill_color, float line_width);
    static void dw_text (std::string obj, int x, int y, std::string text, std::string text_color);
    static void dw_move (std::string obj, int x, int y, int w, int h);
    static void dw_set_width (std::string obj, int w);
    static void dw_delete(std::string obj);
    
};


#pragma mark -


#endif /* ceammc_gui_hpp */

