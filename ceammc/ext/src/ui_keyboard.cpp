//
//  ui_keyboard.cpp
//  pd_ext
//
//  Created by Alex Nadzharov on 17/12/16.
//
//

#include "lib/ceammc_gui.h"

#include "ceammc_atomlist.h"
#include "ceammc_format.h"

struct ui_keyboard : public ceammc_gui::BaseGuiObject
{
    t_ebox x_gui;
    
    float mouse_x;
    float mouse_y;
    int mouse_dn;
    bool _selected;
    
    t_outlet *out1;
    t_atom out_list[2];
    
    int keys;
    int shift;
    
    int _pitch;
    int _vel;
    int _pitch_prev;
    
    //t_rgba b_color_background;
    t_rgba b_color_border;
};

namespace ceammc_gui {
    
    struct kRect
    {
        int x,y,w,h;
        bool is_black;
    };
    
    kRect get_black_key_r(int offset, int kWidth, int kHeight)
    {
        kRect ret;
        
        int n_number = offset % 12;
        int n_octave = offset/12;
        
        
        ret.x = (offset + (n_number>4) + 2*n_octave)* kWidth + .5*kWidth;
        ret.y = 0;
        ret.w = kWidth;
        ret.h = kHeight*.6;
        ret.is_black = true;
        
        return ret;
    }
    
    kRect get_white_key_r(int offset, int kWidth, int kHeight)
    {
        kRect ret;
        
        int n_number = offset % 12;
        int n_octave = offset/12;
        
        ret.x = (offset + (n_number>4) + 2*n_octave)*   kWidth;
        ret.y = 0;
        ret.w = kWidth*2;
        ret.h = kHeight;
        ret.is_black = false;
        
        return ret;
        
    }
    
    kRect get_key_r(int number, int kWidth, int kHeight)
    {
        int n_number = number % 12;
        bool is_black = ((n_number -  (n_number<5)) % 2);
        
        kRect ret =
        (!is_black)? get_black_key_r( number,  kWidth,  kHeight ) : get_white_key_r( number  ,  kWidth,  kHeight );
        
        return ret;
    }
    
    bool mouse_in_rect(int x, int y, kRect kr)
    {
        return (x>kr.x) &&
        x<(kr.x+kr.w) &&
        y>(kr.y) &&
        y<(kr.y+kr.h);
        
    }
    
    
    
    UI_fun(ui_keyboard)::wx_paint(t_object *z, t_object *view)
    {
        //UI_Prop
        
        t_symbol *bgl = gensym("background_layer");
        //float size;
        t_rect rect;
        ebox_get_rect_for_view((t_ebox *)z, &rect);
        
        t_elayer *g = ebox_start_layer((t_ebox *)z, bgl, rect.width, rect.height);
        if(g)
        
        {
            ui_keyboard *zx = (ui_keyboard*)z;
        
            
            if (zx->keys < 3) zx->keys = 3;                         // rapper's piano meme
            if (zx->keys > 127) zx->keys = 127;
            
            float kWidth = floorf(rect.width/zx->keys)*.9;          // weird
            
            t_symbol *color_wh_f = gensym("#F0F0F0");
            t_symbol *color_wh_b = gensym("#C0C0C0");
            t_symbol *color_bl_f = gensym("#505050");
            t_symbol *color_bl_b = gensym("#C0C0C0");
            t_symbol *color_hv_b = gensym("#00C0FF");
            t_symbol *color_md_f = gensym("#00C0FF");
            
            
            // two pass draw
            for (int i = 0; i<zx->keys; i++)
            {
                kRect k = get_key_r(i, kWidth, rect.height);
                
                if (!k.is_black)
                {
                    char keyname[7];
                    sprintf(keyname, "KEY%d", i);
                    
                    //bool hover = ( i == int(UI_Pf("_pitch")) );
                    bool hover = ( i == int(zx->_pitch));
                    bool click = zx->mouse_dn; //( UI_Pf("_mouse_dn")==1 );
                    
                    egraphics_rectangle(g, k.x, k.y, k.w, k.h);
                    egraphics_set_color_hex(g, (hover) ? (click ? color_md_f : color_wh_f) : color_wh_f);
                    egraphics_fill(g);
                    
                    egraphics_rectangle(g, k.x, k.y, k.w, k.h);
                    egraphics_set_color_hex(g, (hover) ? (click ? color_hv_b : color_hv_b) : color_wh_b);
                    egraphics_stroke(g);
                    
                    if ((i + zx->shift) == 60)
                    {
                        egraphics_set_line_width(g, 2);
                        float w = k.w * .75;
                        egraphics_line(g, k.x, k.y, k.x+w/2, k.y+w/2);
                        egraphics_line(g, k.x+w, k.y, k.x+w/2, k.y+w/2);
                        egraphics_line(g, k.x, k.y, k.x+w, k.y);
                        egraphics_set_color_hex(g, gensym("#00C0FF"));
                        egraphics_stroke(g);
                        egraphics_set_line_width(g, 1);
                    }
                    
                }
            }
            
            for (int i = 0; i<zx->keys; i++)
            {
                kRect k = get_key_r(i, kWidth, rect.height);
                
                if (k.is_black)
                {
                    char keyname[7];
                    sprintf(keyname, "KEY%d", i);
                    
                    bool hover = ( i == int(zx->_pitch));
                    bool click = zx->mouse_dn; //( UI_Pf("_mouse_dn")==1 );
                    
                    egraphics_rectangle(g, k.x, k.y, k.w, k.h);
                    egraphics_set_color_hex(g, (hover) ? (click ? color_md_f : color_bl_f) : color_bl_f);
                    egraphics_fill(g);
                    
                    egraphics_rectangle(g, k.x, k.y, k.w, k.h);
                    egraphics_set_color_hex(g, (hover) ? (click ? color_hv_b : color_hv_b) : color_bl_b);
                    egraphics_stroke(g);

                }
            }
            
        }
        
        ebox_end_layer((t_ebox*)z, bgl);
        
        ebox_paint_layer((t_ebox *)z, bgl, 0., 0.);
        
    }
    
#pragma mark -
    
    UI_fun(ui_keyboard)::wx_mousemove_ext(t_object* z, t_object *view, t_pt pt, long modifiers)
    {
        ui_keyboard *zx = (ui_keyboard*)z;
        
        t_rect rect;
        ebox_get_rect_for_view((t_ebox *)z, &rect);
        
        float kWidth = floorf(rect.width/zx->keys)*.9;
        
        for (int i = 0; i<zx->keys; i++)
        {
            kRect k = get_key_r(i, kWidth, rect.height);
            
            if (!k.is_black)
            {
                if (mouse_in_rect(zx->mouse_x,zx->mouse_y, k))
                {
                    zx->_pitch = i;
                }
                
            }
        }
        
        for (int i = 0; i<zx->keys; i++)
        {
            kRect k = get_key_r(i, kWidth, rect.height);
            
            if (k.is_black)
            {
                if (mouse_in_rect(zx->mouse_x,zx->mouse_y, k))
                {
                    zx->_pitch = i;
                }
            }
        }
        
    }
    
    UI_fun(ui_keyboard)::wx_mousedown_ext(t_object* z, t_object *view, t_pt pt, long modifiers)
    {
        ui_keyboard *zx = (ui_keyboard*)z;
        
        t_rect rect;
        ebox_get_rect_for_view((t_ebox *)z, &rect);
        
        zx->_vel= int(pt.y/rect.height*127.);
        
        atom_setfloat(&((ui_keyboard*)z)->out_list[0], (float)zx->_pitch + (float)zx->shift);
        atom_setfloat(&((ui_keyboard*)z)->out_list[1], (float)zx->_vel);
        
        outlet_list( ((ui_keyboard*)z)->out1, &s_list, 2, ((ui_keyboard*)z)->out_list );
        
        ceammc_gui::GuiFactory<ceammc_gui::BaseGuiObject>::ws_redraw(z);
    }
    
    UI_fun(ui_keyboard)::wx_mouseup_ext(t_object* z, t_object *view, t_pt pt, long modifiers)
    {
        ui_keyboard *zx = (ui_keyboard*)z;
        
        t_rect rect;
        ebox_get_rect_for_view((t_ebox *)z, &rect);
        
        zx->_vel=0;
        
        atom_setfloat(&((ui_keyboard*)z)->out_list[0], (float)zx->_pitch + (float)zx->shift);
        atom_setfloat(&((ui_keyboard*)z)->out_list[1], (float)zx->_vel);
        
        outlet_list( ((ui_keyboard*)z)->out1, &s_list, 2, ((ui_keyboard*)z)->out_list );
        
        ceammc_gui::GuiFactory<ceammc_gui::BaseGuiObject>::ws_redraw(z);
    }
    
    UI_fun(ui_keyboard)::wx_mousedrag_ext(t_object* z, t_object *view, t_pt pt, long modifiers)
    {

        ui_keyboard *zx = (ui_keyboard*)z;
        
        ceammc_gui::GuiFactory<ui_keyboard>::wx_mousemove_ext(z,view,pt,modifiers);
        
        if (zx->_pitch_prev != zx->_pitch )
        {

            zx->_pitch_prev = zx->_pitch;
            
            atom_setfloat(&((ui_keyboard*)z)->out_list[0], (float)zx->_pitch + (float)zx->shift);
            atom_setfloat(&((ui_keyboard*)z)->out_list[1], (float)zx->_vel);
            
            outlet_list( ((ui_keyboard*)z)->out1, &s_list, 2, ((ui_keyboard*)z)->out_list );
            
        }
        
        ceammc_gui::GuiFactory<ceammc_gui::BaseGuiObject>::ws_redraw(z);
    }
    
    UI_fun(ui_keyboard)::wx_mouseleave_ext(t_object *z, t_object *view, t_pt pt, long modifiers)
    {
        ui_keyboard *zx = (ui_keyboard*)z;
        zx->_pitch = -1;
        
        ceammc_gui::GuiFactory<ceammc_gui::BaseGuiObject>::ws_redraw(z);
    }

    // yet disabled
    
//    UI_fun(ui_keyboard)::wx_oksize(t_object *z, t_rect *newrect)
//    {
//        ui_keyboard *zx = (ui_keyboard*)z;
//        
//        float kWidth = floorf(newrect->width/zx->keys)*.9;
//        
//        if (kWidth<3) kWidth = 3;
//        
//        newrect->width = kWidth * zx->keys/.9;
//    }
    
    static void ui_k_getdrawparams(ui_keyboard *x, t_object *patcherview, t_edrawparams *params)
    {
        params->d_borderthickness   = 1;
        params->d_cornersize        = 2;
        params->d_bordercolor       = x->b_color_border;
        //params->d_boxfillcolor      = x->b_color_background;
    }
    
#pragma mark -
    
    UI_fun(ui_keyboard)::init_ext(t_eclass *z)
    {
        CLASS_ATTR_DEFAULT (z, "size", 0, "433. 60.");
        
        CLASS_ATTR_INT(z, "shift", 0, ui_keyboard, shift);
        CLASS_ATTR_DEFAULT(z, "shift", 0, "36");
        CLASS_ATTR_LABEL(z, "shift", 0, "shift");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(z, "shift", 0, "36");
        
        CLASS_ATTR_INT(z, "keys", 0, ui_keyboard, keys);
        CLASS_ATTR_DEFAULT(z, "keys", 0, "61");
        CLASS_ATTR_LABEL(z, "keys", 0, "keys");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(z, "keys", 0, "61");
        
//        CLASS_ATTR_RGBA                 (z, "bgcolor", 0, ui_keyboard, b_color_background);
//        CLASS_ATTR_LABEL                (z, "bgcolor", 0, "Background Color");
//        CLASS_ATTR_ORDER                (z, "bgcolor", 0, "1");
//        CLASS_ATTR_DEFAULT_SAVE_PAINT   (z, "bgcolor", 0, "0.93 0.93 0.93 1.");
//        CLASS_ATTR_STYLE                (z, "bgcolor", 0, "color");
        
        CLASS_ATTR_RGBA                 (z, "bdcolor", 0, ui_keyboard, b_color_border);
        CLASS_ATTR_LABEL                (z, "bdcolor", 0, "Border Color");
        CLASS_ATTR_ORDER                (z, "bdcolor", 0, "2");
        CLASS_ATTR_DEFAULT_SAVE_PAINT   (z, "bdcolor", 0, "0. 0. 0. 1.");
        CLASS_ATTR_STYLE                (z, "bdcolor", 0, "color");
        
        eclass_addmethod(z, (method) ui_k_getdrawparams,   "getdrawparams",    A_NULL, 0);
        
    }
    
    UI_fun(ui_keyboard)::new_ext(t_object *x, t_symbol *s, int argcl, t_atom *argv)
    {
        ((ui_keyboard*)x)->out1 = outlet_new(x, &s_bang);
    }
        
}

extern "C" void setup_ui0x2ekeyboard()
{
    ceammc_gui::GuiFactory<ui_keyboard> class1;
    class1.setup("ui.keyboard");
}