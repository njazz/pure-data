//
//  tl_object_common.cpp
//  pd_ext
//
//  Created by Alex on 10/12/16.
//
//

//#include <stdio.h>
#include "tl_lib.hpp"

//globals
std::vector<tl_t_ui_object> tl_ui_objects;
std::vector<tl_t_cue> tl_ui_cues;
tl_t_methods tl_methods;

#pragma mark list utils

EXTERN tl_t_list tll_list_createempty()
{
    tl_t_list ret;
    ret.size = 0;
    ret.data = nullptr;
    
    return ret;
}

#pragma mark cue

EXTERN int tll_cue_find_by_object(t_object* obj)
{
    int ret = -1;
    int i=0;
    
    std::vector<tl_t_cue>::iterator it;
    for (it = tl_ui_cues.begin(); it != tl_ui_cues.end(); ++it)
    {
        if (it->ui_obj == obj) {ret = i;};
        i++;
        
    }
    return ret;
}



static void tll_cue_assign_numbers()
{
    struct pred {
        bool operator()(tl_t_cue const& a, tl_t_cue const& b) const {
            return a.x_pos < b.x_pos;
        }
    } pred1;
    
    std::sort(tl_ui_cues.begin(), tl_ui_cues.end(), pred1);
    
}

EXTERN void tll_cue_delete(t_object *x)
{
    int erase_idx = tll_cue_find_by_object(x);
    
    if (erase_idx)
        tl_ui_cues.erase(tl_ui_cues.begin()+erase_idx);
    
    tll_cue_assign_numbers();
    
    printf("cue del");
}





EXTERN int tll_cue_getnumber(t_object* obj)
{
    return tll_cue_find_by_object(obj);
}
EXTERN void tll_cue_add(t_object *x, float x_pos)
{
    tl_t_cue new_c;
    
    new_c.cue_number = -1;//cue_number;
    new_c.x_pos = x_pos;
    new_c.ui_obj = x;
    
    tl_ui_cues.push_back(new_c);
    
    tll_cue_assign_numbers();
}



//TEMP
EXTERN void tll_cue_dump()
{
    std::vector<tl_t_cue>::iterator it;
    for (it=tl_ui_cues.begin(); it != tl_ui_cues.end(); ++it)
    {
        it->cue_number = tll_cue_getnumber(it->ui_obj);
        printf("cue %i pos %f\n", it->cue_number, it->x_pos);
        //logpost(NULL, 2, "cue %i pos %f\n", it->cue_number, it->x_pos);
    }
}

//TEMP
EXTERN void tll_cue_update_pos(t_object *x, float x_pos)
{
    std::vector<tl_t_cue>::iterator it;
    for (it=tl_ui_cues.begin(); it != tl_ui_cues.end(); ++it)
    {
        if (it->ui_obj)
        {
            t_object *x = it->ui_obj;
            float x_pos = x->te_xpix;
            it->x_pos = x_pos;
            
        }
    }
    
    tll_cue_assign_numbers();
}

#pragma mark ui objects

EXTERN void tll_ui_add(t_object *x, float x_pos)
{
    tl_t_ui_object new_u;
    
    new_u.x_pos = x_pos;
    new_u.ui_obj = (t_object*)x;
    
    tl_ui_objects.push_back(new_u);
}

//TEMP. todo: std::vector<std::string>
EXTERN void tll_ui_update_pos(t_object *x, float x_pos)
{
    std::vector<tl_t_ui_object>::iterator it;
    for (it=tl_ui_objects.begin(); it != tl_ui_objects.end(); ++it)
    {
        if (it->ui_obj)
        {
            t_object *x = (t_object*)it->ui_obj;
            float x_pos = x->te_xpix;
            it->x_pos = x_pos;
            printf("uiobj upd\n");
            
        }
    }
    
}


//stub
EXTERN void tll_cue_update_all_pos()
{
    
}
EXTERN void tll_ui_update_all_pos()
{
    
}

EXTERN void tll_ui_dump()
{
    std::vector<tl_t_ui_object>::iterator it;
    for (it=tl_ui_objects.begin(); it != tl_ui_objects.end(); ++it)
    {
        printf("ui pos %f\n", it->x_pos);
    }
}

#pragma mark -

EXTERN void tll_perform_actions_for_cue(int cue_number)
{
    printf("perform actions\n");
    
    if ( (cue_number>0) && (cue_number<tl_ui_cues.size()) )
    {
        printf("method call  %lu @ %lu", (long)tl_methods.ui_action, (long)tl_ui_objects[cue_number].ui_obj);
        
        int min_cue_x = tl_ui_cues[cue_number].x_pos;
        int max_cue_x = (cue_number<(tl_ui_cues.size()-1))?tl_ui_cues[cue_number+1].x_pos:65535;
        
        
        std::vector<tl_t_ui_object>::iterator it;
        for (it = tl_ui_objects.begin(); it != tl_ui_objects.end(); ++it)
        {
            if ( (it->x_pos >= min_cue_x) && (it->x_pos <max_cue_x) )
                tl_methods.ui_action( it->ui_obj ); //, tll_list_createempty() );
        }
    }
}

#pragma mark -

EXTERN void tll_set_ui_action (tl_ui_action method)
{
    tl_methods.ui_action = method;
    
}
