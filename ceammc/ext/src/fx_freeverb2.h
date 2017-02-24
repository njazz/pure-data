//----------------------------------------------------------
//
// Code generated with Faust 0.9.92 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2.1 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/* Pd architecture file, written by Albert Graef <Dr.Graef@t-online.de>.
   This was derived from minimal.cpp included in the Faust distribution.
   Please note that this is to be compiled as a shared library, which is
   then loaded dynamically by Pd as an external. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {}
};

#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>


using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


#include "ceammc_atomlist.h"
#include <m_pd.h>

/******************************************************************************
*******************************************************************************

                                   VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

#ifdef FAUST_MACRO
// clang-format off
// clang-format on
#endif

#define sym(name) xsym(name)
#define xsym(name) #name

/***************************************************************************
   Pd UI interface
***************************************************************************/

// clang-format off
#ifndef FAUST_MACRO
struct freeverb2 : public dsp {
};
#endif
// clang-format on

#include "ceammc_faust.h"
using namespace ceammc::faust;


/******************************************************************************
*******************************************************************************

                FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifdef FAUST_MACRO
// clang-format off
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS freeverb2
#endif

class freeverb2 : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec10[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec12[2];
	float 	fRec11[2];
	int 	IOTA;
	float 	fVec0[8192];
	float 	fConst0;
	int 	iConst1;
	float 	fRec9[2];
	float 	fRec14[2];
	float 	fVec1[8192];
	int 	iConst2;
	float 	fRec13[2];
	float 	fRec16[2];
	float 	fVec2[8192];
	int 	iConst3;
	float 	fRec15[2];
	float 	fRec18[2];
	float 	fVec3[8192];
	int 	iConst4;
	float 	fRec17[2];
	float 	fRec20[2];
	float 	fVec4[8192];
	int 	iConst5;
	float 	fRec19[2];
	float 	fRec22[2];
	float 	fVec5[8192];
	int 	iConst6;
	float 	fRec21[2];
	float 	fRec24[2];
	float 	fVec6[8192];
	int 	iConst7;
	float 	fRec23[2];
	float 	fRec26[2];
	float 	fVec7[8192];
	int 	iConst8;
	float 	fRec25[2];
	float 	fVec8[1024];
	int 	iConst9;
	int 	iConst10;
	float 	fRec7[2];
	float 	fVec9[1024];
	int 	iConst11;
	int 	iConst12;
	float 	fRec5[2];
	float 	fVec10[1024];
	int 	iConst13;
	int 	iConst14;
	float 	fRec3[2];
	float 	fVec11[1024];
	int 	iConst15;
	int 	iConst16;
	float 	fRec1[2];
	float 	fRec36[2];
	float 	fVec12[8192];
	int 	iConst17;
	float 	fRec35[2];
	float 	fRec38[2];
	float 	fVec13[8192];
	int 	iConst18;
	float 	fRec37[2];
	float 	fRec40[2];
	float 	fVec14[8192];
	int 	iConst19;
	float 	fRec39[2];
	float 	fRec42[2];
	float 	fVec15[8192];
	int 	iConst20;
	float 	fRec41[2];
	float 	fRec44[2];
	float 	fVec16[8192];
	int 	iConst21;
	float 	fRec43[2];
	float 	fRec46[2];
	float 	fVec17[8192];
	int 	iConst22;
	float 	fRec45[2];
	float 	fRec48[2];
	float 	fVec18[8192];
	int 	iConst23;
	float 	fRec47[2];
	float 	fRec50[2];
	float 	fVec19[8192];
	int 	iConst24;
	float 	fRec49[2];
	float 	fVec20[1024];
	int 	iConst25;
	float 	fRec33[2];
	float 	fVec21[1024];
	int 	iConst26;
	float 	fRec31[2];
	float 	fVec22[1024];
	int 	iConst27;
	float 	fRec29[2];
	float 	fVec23[1024];
	int 	iConst28;
	float 	fRec27[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("ceammc.lib/name", "Ceammc PureData misc utils");
		m->declare("ceammc.lib/version", "0.1");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		iConst1 = int((0.036666665f * fConst0));
		iConst2 = int((0.035306122f * fConst0));
		iConst3 = int((0.033809524f * fConst0));
		iConst4 = int((0.0322449f * fConst0));
		iConst5 = int((0.030748298f * fConst0));
		iConst6 = int((0.028956916f * fConst0));
		iConst7 = int((0.026938776f * fConst0));
		iConst8 = int((0.025306122f * fConst0));
		iConst9 = int((0.0126077095f * fConst0));
		iConst10 = int((int((iConst9 + -1)) & 1023));
		iConst11 = int((0.01f * fConst0));
		iConst12 = int((int((iConst11 + -1)) & 1023));
		iConst13 = int((0.0077324263f * fConst0));
		iConst14 = int((int((iConst13 + -1)) & 1023));
		iConst15 = int((0.0051020407f * fConst0));
		iConst16 = int((int((iConst15 + -1)) & 1023));
		iConst17 = int((iConst1 + 22));
		iConst18 = int((iConst2 + 22));
		iConst19 = int((iConst3 + 22));
		iConst20 = int((iConst4 + 22));
		iConst21 = int((iConst5 + 22));
		iConst22 = int((iConst6 + 22));
		iConst23 = int((iConst7 + 22));
		iConst24 = int((iConst8 + 22));
		iConst25 = int((int((iConst9 + 21)) & 1023));
		iConst26 = int((int((iConst11 + 21)) & 1023));
		iConst27 = int((int((iConst13 + 21)) & 1023));
		iConst28 = int((int((iConst15 + 21)) & 1023));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.33f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<8192; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<8192; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<8192; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<8192; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<1024; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<1024; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<1024; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<8192; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<8192; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<8192; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<8192; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<8192; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<8192; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<8192; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<8192; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<1024; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<1024; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<1024; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<1024; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual freeverb2* clone() {
		return new freeverb2();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->addHorizontalSlider("damp", &fslider2, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("drywet", &fslider0, 0.33f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("roomsize", &fslider1, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.001f * float(fslider0));
		float 	fSlow1 = (0.001f * float(fslider1));
		float 	fSlow2 = (0.001f * float(fslider2));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			float fTemp0 = (float)input0[i];
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			float fTemp1 = (1 - fRec0[0]);
			float fTemp2 = (float)input1[i];
			float fTemp3 = (2 * (fTemp0 + fTemp2));
			fRec10[0] = (fSlow1 + (0.999f * fRec10[1]));
			fRec12[0] = (fSlow2 + (0.999f * fRec12[1]));
			float fTemp4 = (1 - fRec12[0]);
			fRec11[0] = ((fRec12[0] * fRec11[1]) + (fTemp4 * fRec9[1]));
			fVec0[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec11[0]));
			fRec9[0] = fVec0[(IOTA-iConst1)&8191];
			fRec14[0] = ((fRec12[0] * fRec14[1]) + (fTemp4 * fRec13[1]));
			fVec1[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec14[0]));
			fRec13[0] = fVec1[(IOTA-iConst2)&8191];
			fRec16[0] = ((fRec12[0] * fRec16[1]) + (fTemp4 * fRec15[1]));
			fVec2[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec16[0]));
			fRec15[0] = fVec2[(IOTA-iConst3)&8191];
			fRec18[0] = ((fRec12[0] * fRec18[1]) + (fTemp4 * fRec17[1]));
			fVec3[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec18[0]));
			fRec17[0] = fVec3[(IOTA-iConst4)&8191];
			fRec20[0] = ((fRec12[0] * fRec20[1]) + (fTemp4 * fRec19[1]));
			fVec4[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec20[0]));
			fRec19[0] = fVec4[(IOTA-iConst5)&8191];
			fRec22[0] = ((fRec12[0] * fRec22[1]) + (fTemp4 * fRec21[1]));
			fVec5[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec22[0]));
			fRec21[0] = fVec5[(IOTA-iConst6)&8191];
			fRec24[0] = ((fRec12[0] * fRec24[1]) + (fTemp4 * fRec23[1]));
			fVec6[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec24[0]));
			fRec23[0] = fVec6[(IOTA-iConst7)&8191];
			fRec26[0] = ((fRec26[1] * fRec12[0]) + (fRec25[1] * fTemp4));
			fVec7[IOTA&8191] = (fTemp3 + (fRec26[0] * fRec10[0]));
			fRec25[0] = fVec7[(IOTA-iConst8)&8191];
			float fTemp5 = (fRec9[0] + (fRec13[0] + (fRec15[0] + (fRec17[0] + (fRec19[0] + (fRec21[0] + (fRec23[0] + ((0.5f * fRec7[1]) + fRec25[0]))))))));
			fVec8[IOTA&1023] = fTemp5;
			fRec7[0] = fVec8[(IOTA-iConst10)&1023];
			float 	fRec8 = (0 - (0.5f * fVec8[IOTA&1023]));
			float fTemp6 = (fRec8 + ((0.5f * fRec5[1]) + fRec7[1]));
			fVec9[IOTA&1023] = fTemp6;
			fRec5[0] = fVec9[(IOTA-iConst12)&1023];
			float 	fRec6 = (0 - (0.5f * fVec9[IOTA&1023]));
			float fTemp7 = (fRec6 + ((0.5f * fRec3[1]) + fRec5[1]));
			fVec10[IOTA&1023] = fTemp7;
			fRec3[0] = fVec10[(IOTA-iConst14)&1023];
			float 	fRec4 = (0 - (0.5f * fVec10[IOTA&1023]));
			float fTemp8 = (fRec4 + ((0.5f * fRec1[1]) + fRec3[1]));
			fVec11[IOTA&1023] = fTemp8;
			fRec1[0] = fVec11[(IOTA-iConst16)&1023];
			float 	fRec2 = (0 - (0.5f * fVec11[IOTA&1023]));
			output0[i] = (FAUSTFLOAT)((fTemp0 * fTemp1) + (fRec0[0] * (fRec1[1] + fRec2)));
			fRec36[0] = ((fRec12[0] * fRec36[1]) + (fTemp4 * fRec35[1]));
			fVec12[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec36[0]));
			fRec35[0] = fVec12[(IOTA-iConst17)&8191];
			fRec38[0] = ((fRec12[0] * fRec38[1]) + (fTemp4 * fRec37[1]));
			fVec13[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec38[0]));
			fRec37[0] = fVec13[(IOTA-iConst18)&8191];
			fRec40[0] = ((fRec12[0] * fRec40[1]) + (fTemp4 * fRec39[1]));
			fVec14[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec40[0]));
			fRec39[0] = fVec14[(IOTA-iConst19)&8191];
			fRec42[0] = ((fRec12[0] * fRec42[1]) + (fTemp4 * fRec41[1]));
			fVec15[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec42[0]));
			fRec41[0] = fVec15[(IOTA-iConst20)&8191];
			fRec44[0] = ((fRec12[0] * fRec44[1]) + (fTemp4 * fRec43[1]));
			fVec16[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec44[0]));
			fRec43[0] = fVec16[(IOTA-iConst21)&8191];
			fRec46[0] = ((fRec12[0] * fRec46[1]) + (fTemp4 * fRec45[1]));
			fVec17[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec46[0]));
			fRec45[0] = fVec17[(IOTA-iConst22)&8191];
			fRec48[0] = ((fRec12[0] * fRec48[1]) + (fTemp4 * fRec47[1]));
			fVec18[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec48[0]));
			fRec47[0] = fVec18[(IOTA-iConst23)&8191];
			fRec50[0] = ((fRec12[0] * fRec50[1]) + (fTemp4 * fRec49[1]));
			fVec19[IOTA&8191] = (fTemp3 + (fRec10[0] * fRec50[0]));
			fRec49[0] = fVec19[(IOTA-iConst24)&8191];
			float fTemp9 = (fRec35[0] + (fRec37[0] + (fRec39[0] + (fRec41[0] + (fRec43[0] + (fRec45[0] + (fRec47[0] + ((0.5f * fRec33[1]) + fRec49[0]))))))));
			fVec20[IOTA&1023] = fTemp9;
			fRec33[0] = fVec20[(IOTA-iConst25)&1023];
			float 	fRec34 = (0 - (0.5f * fVec20[IOTA&1023]));
			float fTemp10 = (fRec34 + ((0.5f * fRec31[1]) + fRec33[1]));
			fVec21[IOTA&1023] = fTemp10;
			fRec31[0] = fVec21[(IOTA-iConst26)&1023];
			float 	fRec32 = (0 - (0.5f * fVec21[IOTA&1023]));
			float fTemp11 = (fRec32 + ((0.5f * fRec29[1]) + fRec31[1]));
			fVec22[IOTA&1023] = fTemp11;
			fRec29[0] = fVec22[(IOTA-iConst27)&1023];
			float 	fRec30 = (0 - (0.5f * fVec22[IOTA&1023]));
			float fTemp12 = (fRec30 + ((0.5f * fRec27[1]) + fRec29[1]));
			fVec23[IOTA&1023] = fTemp12;
			fRec27[0] = fVec23[(IOTA-iConst28)&1023];
			float 	fRec28 = (0 - (0.5f * fVec23[IOTA&1023]));
			output1[i] = (FAUSTFLOAT)((fTemp2 * fTemp1) + (fRec0[0] * (fRec27[1] + fRec28)));
			// post processing
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec47[1] = fRec47[0];
			fRec48[1] = fRec48[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec39[1] = fRec39[0];
			fRec40[1] = fRec40[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec7[1] = fRec7[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec9[1] = fRec9[0];
			IOTA = IOTA+1;
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec10[1] = fRec10[0];
			fRec0[1] = fRec0[0];
		}
	}
};


// clang-format on
#endif

// clang-format off
#define faust_setup(name) xfaust_setup(name)
#define xfaust_setup(name) name##_tilde_setup(void)
// time for "active" toggle xfades in secs
#define XFADE_TIME 0.1f
static t_class* faust_class;
// clang-format on

struct t_faust {
    t_object x_obj;
#ifdef __MINGW32__
    /* This seems to be necessary as some as yet undetermined Pd routine seems
     to write past the end of x_obj on Windows. */
    int fence; /* dummy field (not used) */
#endif
    freeverb2* dsp;
    PdUI<UI>* ui;
    int active, xfade, n_xfade, rate, n_in, n_out;
    t_sample **inputs, **outputs, **buf;
    t_outlet* out;
    t_sample f;
};

static inline void zero_samples(int k, int n, t_sample** out)
{
    for (int i = 0; i < k; i++)
#ifdef __STDC_IEC_559__
        /* IEC 559 a.k.a. IEEE 754 floats can be initialized faster like this */
        memset(out[i], 0, n * sizeof(t_sample));
#else
        for (int j = 0; j < n; j++)
            out[i][j] = 0.0f;
#endif
}

static inline void copy_samples(int k, int n, t_sample** out, t_sample** in)
{
    for (int i = 0; i < k; i++)
        memcpy(out[i], in[i], n * sizeof(t_sample));
}

static t_int* faust_perform(t_int* w)
{
    t_faust* x = reinterpret_cast<t_faust*>(w[1]);
    int n = static_cast<int>(w[2]);
    if (!x->dsp || !x->buf)
        return (w + 3);

    AVOIDDENORMALS;
    if (x->xfade > 0) {
        float d = 1.0f / x->n_xfade, f = (x->xfade--) * d;
        d = d / n;
        x->dsp->compute(n, x->inputs, x->buf);
        if (x->active) {
            if (x->n_in == x->n_out) {
                /* xfade inputs -> buf */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++)
                        x->outputs[i][j] = f * x->inputs[i][j] + (1.0f - f) * x->buf[i][j];
                }
            } else {
                /* xfade 0 -> buf */
                for (int j = 0; j < n; j++, f -= d) {
                    for (int i = 0; i < x->n_out; i++)
                        x->outputs[i][j] = (1.0f - f) * x->buf[i][j];
                }
            }
        } else if (x->n_in == x->n_out) {
            /* xfade buf -> inputs */
            for (int j = 0; j < n; j++, f -= d) {
                for (int i = 0; i < x->n_out; i++)
                    x->outputs[i][j] = f * x->buf[i][j] + (1.0f - f) * x->inputs[i][j];
            }
        } else {
            /* xfade buf -> 0 */
            for (int j = 0; j < n; j++, f -= d) {
                for (int i = 0; i < x->n_out; i++)
                    x->outputs[i][j] = f * x->buf[i][j];
            }
        }
    } else if (x->active) {
        x->dsp->compute(n, x->inputs, x->buf);
        copy_samples(x->n_out, n, x->outputs, x->buf);
    } else if (x->n_in == x->n_out) {
        copy_samples(x->n_out, n, x->buf, x->inputs);
        copy_samples(x->n_out, n, x->outputs, x->buf);
    } else
        zero_samples(x->n_out, n, x->outputs);

    return (w + 3);
}

static void faust_dsp(t_faust* x, t_signal** sp)
{
    const int n = sp[0]->s_n;
    const int sr = static_cast<int>(sp[0]->s_sr);

    if (x->rate <= 0) {
        /* default sample rate is whatever Pd tells us */
        PdUI<UI>* ui = x->ui;
        std::vector<FAUSTFLOAT> z = ui->uiValues();
        /* set the proper sample rate; this requires reinitializing the dsp */
        x->rate = sr;
        x->dsp->init(sr);
        ui->setUIValues(z);
    }
    if (n > 0)
        x->n_xfade = static_cast<int>(x->rate * XFADE_TIME / n);

    dsp_add(faust_perform, 2, x, n);

    for (int i = 0; i < x->n_in; i++)
        x->inputs[i] = sp[i]->s_vec;

    for (int i = 0; i < x->n_out; i++)
        x->outputs[i] = sp[x->n_in + i]->s_vec;

    if (x->buf != NULL) {
        for (int i = 0; i < x->n_out; i++) {
            x->buf[i] = static_cast<t_sample*>(malloc(n * sizeof(t_sample)));
            if (x->buf[i] == NULL) {
                for (int j = 0; j < i; j++)
                    free(x->buf[j]);
                free(x->buf);
                x->buf = NULL;
                break;
            }
        }
    }
}

static void faust_any(t_faust* x, t_symbol* s, int argc, t_atom* argv)
{
    if (!x->dsp)
        return;

    PdUI<UI>* ui = x->ui;
    if (s == &s_bang) {
        ui->dumpUI(x->out);
    } else if (isGetAllProperties(s)) {
        ui->outputAllProperties(x->out);
    } else if (isGetProperty(s)) {
        ui->outputProperty(s, x->out);
    } else {
        const char* label = s->s_name;
        int count = 0;
        for (size_t i = 0; i < ui->uiCount(); i++) {
            if (ui->uiAt(i)->pathcmp(label)) {
                if (argc == 0) {
                    ui->uiAt(i)->outputValue(x->out);
                    ++count;
                } else if (argc == 1 && (argv[0].a_type == A_FLOAT || argv[0].a_type == A_DEFFLOAT)) {
                    float f = atom_getfloat(argv);
                    UIElement* el = ui->uiAt(i);
                    el->setValue(f);
                    ++count;
                } else
                    pd_error(x, "[ceammc] %s: bad control argument: %s", ui->fullName().c_str(), label);
            }
        }

        if (count == 0 && strcmp(label, "active") == 0) {
            if (argc == 0) {
                t_atom arg;
                SETFLOAT(&arg, (float)x->active);
                if (x->out) {
                    outlet_anything(x->out, gensym("active"), 1, &arg);
                }
            } else if (argc == 1 && (argv[0].a_type == A_FLOAT || argv[0].a_type == A_DEFFLOAT)) {
                float f = atom_getfloat(argv);
                x->active = (int)f;
                x->xfade = x->n_xfade;
            }
        }
    }
}

static void faust_free_dsp(t_faust* x)
{
    delete x->dsp;
    x->dsp = NULL;
}

static void faust_free_ui(t_faust* x)
{
    delete x->ui;
    x->ui = NULL;
}

static void faust_free_inputs(t_faust* x)
{
    if (x->inputs)
        free(x->inputs);
    x->inputs = NULL;
}

static void faust_free_outputs(t_faust* x)
{
    if (x->outputs)
        free(x->outputs);
    x->outputs = NULL;
}

static void faust_free_buf(t_faust* x)
{
    if (x->buf) {
        for (int i = 0; i < x->n_out; i++) {
            if (x->buf[i])
                free(x->buf[i]);
        }

        free(x->buf);
    }
}

static void faust_free(t_faust* x)
{
    faust_free_dsp(x);
    faust_free_ui(x);
    faust_free_inputs(x);
    faust_free_outputs(x);
    faust_free_buf(x);
}

static bool faust_init_inputs(t_faust* x)
{
    x->inputs = NULL;
    x->n_in = x->dsp->getNumInputs();

    if (x->n_in > 0) {
        x->inputs = static_cast<t_sample**>(calloc(x->n_in, sizeof(t_sample*)));

        if (x->inputs == NULL) {
            error("[%s] faust_init_inputs failed", sym(freeverb2));
            return false;
        }
    }

    // creating sound inlets (except the first one!)
    for (int i = 0; i < (x->n_in - 1); i++) {
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    }

    return true;
}

static bool faust_init_outputs(t_faust* x, bool info_outlet)
{
    x->outputs = NULL;
    x->buf = NULL;

    x->n_out = x->dsp->getNumOutputs();

    if (x->n_out > 0) {
        x->outputs = static_cast<t_sample**>(calloc(x->n_out, sizeof(t_sample*)));
        if (x->outputs == NULL) {
            error("[%s] faust_init_outputs failed", sym(freeverb2));
            return false;
        }

        x->buf = static_cast<t_sample**>(calloc(x->n_out, sizeof(t_sample*)));
        if (x->buf == NULL) {
            error("[%s] faust_init_outputs failed", sym(freeverb2));
            faust_free_outputs(x);
            return false;
        }

        for (int i = 0; i < x->n_out; i++)
            x->buf[i] = NULL;
    }

    // creating sound outlets
    for (int i = 0; i < x->n_out; i++) {
        outlet_new(&x->x_obj, &s_signal);
    }

    // control outlet
    if (info_outlet)
        x->out = outlet_new(&x->x_obj, 0);
    else
        x->out = 0;

    return true;
}

static bool faust_new_internal(t_faust* x, const std::string& objId = "", bool info_outlet = true)
{
    int sr = 44100;
    x->active = 1;
    x->xfade = 0;
    x->rate = sr;
    x->n_xfade = static_cast<int>(sr * XFADE_TIME / 64);

    x->dsp = new freeverb2();
    x->ui = new PdUI<UI>(sym(freeverb2), objId);

    if (!faust_init_inputs(x)) {
        faust_free(x);
        return false;
    }

    if (!faust_init_outputs(x, info_outlet)) {
        faust_free(x);
        return false;
    }

    x->dsp->init(sr);
    x->dsp->buildUserInterface(x->ui);

    return true;
}

/**
 * find nth element that satisfies given predicate
 * @first - first element of sequence
 * @last - pointer behind last element of sequence
 * @Nth - searched element index
 * @pred - predicate
 * @return pointer to found element or pointer to @bold last, if not found
 */
template <class InputIterator, class NthOccurence, class UnaryPredicate>
InputIterator find_nth_if(InputIterator first, InputIterator last, NthOccurence Nth, UnaryPredicate pred)
{
    if (Nth > 0) {
        while (first != last) {
            if (pred(*first))
                if (!--Nth)
                    return first;
            ++first;
        }
    }
    return last;
}

/**
 * @return true if given atom is a float
 */
static bool atom_is_float(const t_atom& a)
{
    switch (a.a_type) {
    case A_FLOAT:
    case A_DEFFLOAT:
        return true;
    default:
        return false;
    }
}

/**
 * @return true if given atom is a symbol
 */
static bool atom_is_symbol(const t_atom& a)
{
    switch (a.a_type) {
    case A_DEFSYMBOL:
    case A_SYMBOL:
        return true;
    default:
        return false;
    }
}

/**
 * @brief find nth float in argument list. (arguments can be mixed)
 * @param argc argument count
 * @param argv pointer to argument vector
 * @param nth find position. nth should be > 0!
 * @param dest destination to write value
 * @return true if argument at given position was found, otherwise false
 */
static bool get_nth_float_arg(int argc, t_atom* argv, int nth, t_float* dest)
{
    t_atom* last = argv + argc;
    t_atom* res = find_nth_if(argv, last, nth, atom_is_float);
    if (last == res)
        return false;

    *dest = atom_getfloat(res);
    return true;
}

/**
 * @brief find nth symbol in argument list. (arguments can be mixed)
 * @param argc argument count
 * @param argv pointer to argument vector
 * @param nth find position. nth should be > 0!
 * @param dest destination to write found argument value
 * @return true if argument at given position was found, otherwise false
 */
static bool get_nth_symbol_arg(int argc, t_atom* argv, int nth, const char** dest)
{
    t_atom* last = argv + argc;
    t_atom* res = find_nth_if(argv, last, nth, atom_is_symbol);
    if (last == res)
        return false;

    t_symbol* s = atom_getsymbol(res);
    *dest = s->s_name;
    return true;
}

class PdArgParser {
    t_faust* x_;
    int argc_;
    t_atom* argv_;
    bool control_outlet_;

public:
    /**
     * @brief FaustArgParser
     * @param x pointer to faust class
     * @param argc arguments count
     * @param argv pointer to argument vector
     */
    PdArgParser(t_faust* x, int argc, t_atom* argv, bool info_outlet = true)
        : x_(x)
        , argc_(argc)
        , argv_(argv)
        , control_outlet_(info_outlet)
    {
        const char* id = NULL;
        std::string objId;
        if (get_nth_symbol_arg(argc_, argv_, 1, &id))
            objId = id;

        // init error
        if (!faust_new_internal(x, objId, control_outlet_)) {
            this->x_ = NULL;
        }
    }

    /**
     * @brief initFloatArg
     * @param name argument name
     * @param pos argument position among of @bold float(!) arguments. Position starts from @bold 1(!).
     * to select first argument - pass 1.
     */
    void initFloatArg(const char* name, int pos)
    {
        // object was not created
        if (!this->x_)
            return;

        t_float v = 0.0;
        if (get_nth_float_arg(this->argc_, this->argv_, pos, &v))
            this->x_->ui->setElementValue(name, v);
    }

    /**
     * @brief send creation argument to first signal inlet
     * @param name argument name
     * @param pos argument position among of @bold float(!) arguments. Position starts from @bold 1(!).
     * to select first argument - pass 1.
     */
    void signalFloatArg(const char* name, int pos)
    {
        // object was not created
        if (!this->x_)
            return;

        t_float arg = 0;
        if (get_nth_float_arg(this->argc_, this->argv_, pos, &arg))
            pd_float(reinterpret_cast<t_pd*>(this->x_), arg);
    }

    t_faust* pd_obj()
    {
        return this->x_;
    }
};

static void* faust_new(t_symbol* s, int argc, t_atom* argv);

static void internal_setup(t_symbol* s)
{
    faust_class = class_new(s, reinterpret_cast<t_newmethod>(faust_new),
        reinterpret_cast<t_method>(faust_free),
        sizeof(t_faust),
        CLASS_DEFAULT,
        A_GIMME, A_NULL);
    class_addmethod(faust_class, nullfn, &s_signal, A_NULL);
    class_addmethod(faust_class, reinterpret_cast<t_method>(faust_dsp), gensym("dsp"), A_NULL);
    CLASS_MAINSIGNALIN(faust_class, t_faust, f);
    class_addanything(faust_class, faust_any);
}
