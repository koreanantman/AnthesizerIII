#include "rugosus_2db.h"

namespace rugosus_2db {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_RMSV_6;
	Delay m_delay_15;
	Phasor __m_phasor_18;
	SineCycle __m_cycle_19;
	SineData __sinedata;
	int __exception;
	int __loopcount;
	int vectorsize;
	t_sample m_RecRMS_5;
	t_sample m_ctrl_16;
	t_sample m_history_1;
	t_sample m_history_14;
	t_sample m_ctrl_17;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample m_history_4;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_7;
	t_sample m_history_3;
	t_sample m_history_12;
	t_sample m_history_8;
	t_sample m_history_2;
	t_sample m_history_9;
	t_sample m_history_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_RecRMS_5 = ((int)0);
		m_RMSV_6.reset("m_RMSV_6", (samplerate * ((t_sample)0.01)));
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_delay_15.reset("m_delay_15", ((int)44100));
		m_ctrl_16 = ((int)0);
		m_ctrl_17 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_18.reset(0);
		__m_cycle_19.reset(samplerate, 0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample div_6190 = safediv(((t_sample)942.47779607694), samplerate);
		t_sample cos_6189 = cos(div_6190);
		t_sample rsub_6184 = (((int)1) - cos_6189);
		t_sample gen_6192 = rsub_6184;
		t_sample div_6183 = (rsub_6184 * ((t_sample)0.5));
		t_sample gen_6191 = div_6183;
		t_sample div_6180 = (rsub_6184 * ((t_sample)0.5));
		t_sample gen_6193 = div_6180;
		t_sample mul_6182 = (cos_6189 * (-2));
		t_sample gen_6195 = mul_6182;
		t_sample sin_6188 = sin(div_6190);
		t_sample div_6187 = (sin_6188 * ((t_sample)1));
		t_sample add_6185 = (div_6187 + ((int)1));
		t_sample gen_6194 = add_6185;
		t_sample rsub_6181 = (((int)1) - div_6187);
		t_sample gen_6196 = rsub_6181;
		t_sample sub_6229 = (m_ctrl_17 - ((int)0));
		t_sample scale_6226 = ((safepow((sub_6229 * ((t_sample)1)), ((int)1)) * ((t_sample)0.9)) + ((int)0));
		t_sample mstosamps_6044 = (((int)5) * (samplerate * 0.001));
		t_sample sub_6233 = (m_ctrl_16 - ((int)0));
		t_sample scale_6230 = ((safepow((sub_6233 * ((t_sample)1)), ((int)1)) * ((int)24)) + ((int)1));
		samples_to_seconds = (1 / samplerate);
		int choice_20 = ((int)1);
		t_sample div_6142 = safediv(((t_sample)3141.5926535898), samplerate);
		t_sample cos_6141 = cos(div_6142);
		t_sample mul_6134 = (cos_6141 * (-2));
		t_sample gen_6147 = mul_6134;
		t_sample rsub_6136 = (((int)1) - cos_6141);
		t_sample gen_6144 = rsub_6136;
		t_sample div_6132 = (rsub_6136 * ((t_sample)0.5));
		t_sample gen_6145 = div_6132;
		t_sample div_6135 = (rsub_6136 * ((t_sample)0.5));
		t_sample gen_6143 = div_6135;
		t_sample sin_6140 = sin(div_6142);
		t_sample div_6139 = (sin_6140 * ((t_sample)0.83333333333333));
		t_sample rsub_6133 = (((int)1) - div_6139);
		t_sample gen_6148 = rsub_6133;
		t_sample add_6137 = (div_6139 + ((int)1));
		t_sample gen_6146 = add_6137;
		t_sample a_6109 = gen_6146;
		t_sample div_6110 = safediv(gen_6144, a_6109);
		t_sample a_6107 = a_6109;
		t_sample div_6108 = safediv(gen_6145, a_6107);
		t_sample a_6105 = a_6109;
		t_sample div_6106 = safediv(gen_6147, a_6105);
		t_sample a_6103 = a_6109;
		t_sample div_6104 = safediv(gen_6148, a_6103);
		t_sample a_6111 = a_6109;
		t_sample div_6112 = safediv(gen_6143, a_6111);
		t_sample div_6094 = safediv(((t_sample)3141.5926535898), samplerate);
		t_sample cos_6093 = cos(div_6094);
		t_sample rsub_6088 = (((int)1) - cos_6093);
		t_sample gen_6096 = rsub_6088;
		t_sample div_6087 = (rsub_6088 * ((t_sample)0.5));
		t_sample gen_6095 = div_6087;
		t_sample div_6084 = (rsub_6088 * ((t_sample)0.5));
		t_sample gen_6097 = div_6084;
		t_sample mul_6086 = (cos_6093 * (-2));
		t_sample gen_6099 = mul_6086;
		t_sample sin_6092 = sin(div_6094);
		t_sample div_6091 = (sin_6092 * ((t_sample)1));
		t_sample add_6089 = (div_6091 + ((int)1));
		t_sample gen_6098 = add_6089;
		t_sample rsub_6085 = (((int)1) - div_6091);
		t_sample gen_6100 = rsub_6085;
		t_sample a_6063 = gen_6098;
		t_sample div_6064 = safediv(gen_6095, a_6063);
		t_sample a_6059 = a_6063;
		t_sample div_6060 = safediv(gen_6097, a_6059);
		t_sample a_6057 = a_6063;
		t_sample div_6058 = safediv(gen_6099, a_6057);
		t_sample a_6055 = a_6063;
		t_sample div_6056 = safediv(gen_6100, a_6055);
		t_sample a_6061 = a_6063;
		t_sample div_6062 = safediv(gen_6096, a_6061);
		t_sample Size = (samplerate * ((t_sample)0.01));
		t_sample Period = (Size * ((t_sample)0.1));
		__loopcount = (__n * GENLIB_LOOPCOUNT_BAIL);
		t_sample a_6153 = gen_6194;
		t_sample div_6154 = safediv(gen_6195, a_6153);
		t_sample a_6155 = a_6153;
		t_sample div_6156 = safediv(gen_6193, a_6155);
		t_sample a_6151 = a_6153;
		t_sample div_6152 = safediv(gen_6196, a_6151);
		t_sample a_6159 = a_6153;
		t_sample div_6160 = safediv(gen_6191, a_6159);
		t_sample a_6157 = a_6153;
		t_sample div_6158 = safediv(gen_6192, a_6157);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample phasor_6035 = __m_phasor_18(scale_6230, samples_to_seconds);
			__m_cycle_19.phase(phasor_6035);
			t_sample cycle_6033 = __m_cycle_19(__sinedata);
			t_sample cycleindex_6034 = __m_cycle_19.phase();
			t_sample mul_6037 = (phasor_6035 * ((int)2));
			t_sample sub_6036 = (mul_6037 - ((int)1));
			t_sample triangle_6040 = triangle(phasor_6035, ((t_sample)0.5));
			t_sample mul_6032 = (triangle_6040 * ((int)2));
			t_sample sub_6031 = (mul_6032 - ((int)1));
			t_sample selector_6039 = ((choice_20 >= 3) ? sub_6031 : ((choice_20 >= 2) ? sub_6036 : ((choice_20 >= 1) ? cycle_6033 : 0)));
			t_sample mul_6046 = (selector_6039 * ((int)70));
			t_sample add_6043 = (mstosamps_6044 + mul_6046);
			t_sample tap_6048 = m_delay_15.read_cubic(add_6043);
			t_sample add_6026 = (tap_6048 + ((int)0));
			t_sample out1 = add_6026;
			t_sample mul_6030 = (tap_6048 * scale_6226);
			t_sample mul_6124 = (m_history_12 * div_6110);
			t_sample mul_6123 = (m_history_14 * div_6108);
			t_sample mul_6120 = (m_history_11 * div_6106);
			t_sample mul_6119 = (m_history_13 * div_6104);
			t_sample add_6113 = (mul_6120 + mul_6119);
			t_sample mul_6125 = (in1 * div_6112);
			t_sample add_6115 = (mul_6125 + mul_6124);
			t_sample add_6114 = (add_6115 + mul_6123);
			t_sample sub_6118 = (add_6114 - add_6113);
			t_sample gen_6130 = sub_6118;
			t_sample history_6121_next_6126 = fixdenorm(m_history_12);
			t_sample history_6116_next_6127 = fixdenorm(m_history_11);
			t_sample history_6122_next_6128 = fixdenorm(in1);
			t_sample history_6117_next_6129 = fixdenorm(sub_6118);
			t_sample mul_6077 = (in2 * div_6064);
			t_sample mul_6075 = (m_history_9 * div_6060);
			t_sample mul_6072 = (m_history_7 * div_6058);
			t_sample mul_6071 = (m_history_10 * div_6056);
			t_sample add_6065 = (mul_6072 + mul_6071);
			t_sample mul_6076 = (m_history_8 * div_6062);
			t_sample add_6067 = (mul_6077 + mul_6076);
			t_sample add_6066 = (add_6067 + mul_6075);
			t_sample sub_6070 = (add_6066 - add_6065);
			t_sample gen_6082 = sub_6070;
			t_sample history_6068_next_6078 = fixdenorm(m_history_7);
			t_sample history_6073_next_6079 = fixdenorm(m_history_8);
			t_sample history_6074_next_6080 = fixdenorm(in2);
			t_sample history_6069_next_6081 = fixdenorm(sub_6070);
			t_sample add_6052 = (gen_6130 + gen_6082);
			t_sample mul_6025 = (add_6052 * ((t_sample)0.6));
			t_sample atan_6024 = atan(mul_6025);
			t_sample mul_6023 = (atan_6024 * ((t_sample)6.2831853071796));
			t_sample RMS = ((int)0);
			// for loop initializer;
			t_sample Vn = ((int)0);
			// for loop condition;
			// abort processing if an infinite loop is suspected;
			if (((__loopcount--) <= 0)) {
				__exception = GENLIB_ERR_LOOP_OVERFLOW;
				break ;
				
			};
			while ((Vn < Size)) {
				// abort processing if an infinite loop is suspected;
				if (((__loopcount--) <= 0)) {
					__exception = GENLIB_ERR_LOOP_OVERFLOW;
					break ;
					
				};
				t_sample RMSin = m_RMSV_6.read_linear(Vn);
				RMS = (RMS + (RMSin * RMSin));
				// for loop increment;
				Vn = (Vn + Period);
				
			};
			t_sample expr_6198 = sqrt((safediv(RMS, Size) * Period));
			m_RMSV_6.write(mul_6023);
			t_sample out3 = expr_6198;
			t_sample mul_6051 = (add_6052 * ((int)5));
			t_sample atan_6050 = atan(mul_6051);
			t_sample mul_6049 = (atan_6050 * ((t_sample)6.2831853071796));
			t_sample mul_6168 = (m_history_1 * div_6154);
			t_sample mul_6171 = (m_history_4 * div_6156);
			t_sample mul_6167 = (m_history_3 * div_6152);
			t_sample add_6161 = (mul_6168 + mul_6167);
			t_sample mul_6173 = (mul_6049 * div_6160);
			t_sample mul_6172 = (m_history_2 * div_6158);
			t_sample add_6163 = (mul_6173 + mul_6172);
			t_sample add_6162 = (add_6163 + mul_6171);
			t_sample sub_6166 = (add_6162 - add_6161);
			t_sample gen_6178 = sub_6166;
			t_sample history_6169_next_6174 = fixdenorm(m_history_2);
			t_sample history_6164_next_6175 = fixdenorm(m_history_1);
			t_sample history_6170_next_6176 = fixdenorm(mul_6049);
			t_sample history_6165_next_6177 = fixdenorm(sub_6166);
			t_sample out2 = gen_6178;
			m_delay_15.write((mul_6030 + mul_6023));
			m_history_14 = history_6121_next_6126;
			m_history_11 = history_6117_next_6129;
			m_history_12 = history_6122_next_6128;
			m_history_13 = history_6116_next_6127;
			m_history_10 = history_6068_next_6078;
			m_history_7 = history_6069_next_6081;
			m_history_8 = history_6074_next_6080;
			m_history_9 = history_6073_next_6079;
			m_history_4 = history_6169_next_6174;
			m_history_1 = history_6165_next_6177;
			m_history_2 = history_6170_next_6176;
			m_history_3 = history_6164_next_6175;
			m_RMSV_6.step();
			m_delay_15.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 2; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "audio in1", "audio in2" };
const char *gen_kernel_outnames[] = { "Main Out", "Sub Out", "cv1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_ctrl1(value); break;
		case 1: self->set_ctrl2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_ctrl_16; break;
		case 1: *value = self->m_ctrl_17; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(2 * sizeof(ParamInfo));
	self->__commonstate.numparams = 2;
	// initialize parameter 0 ("m_ctrl_16")
	pi = self->__commonstate.params + 0;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_17")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // rugosus_2db::
