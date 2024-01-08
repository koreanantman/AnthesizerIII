#include "rugosus_2da.h"

namespace rugosus_2da {

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
	Delay m_delay_10;
	Delay m_delay_6;
	Delay m_delay_11;
	Delay m_delay_7;
	Delay m_delay_8;
	Delay m_delay_9;
	Delay m_RMSV_17;
	Delay m_delay_27;
	Delay m_delay_30;
	Delay m_delay_26;
	Delay m_delay_29;
	Delay m_delay_28;
	int __exception;
	int __loopcount;
	int vectorsize;
	t_sample m_history_25;
	t_sample m_history_3;
	t_sample m_history_12;
	t_sample m_history_24;
	t_sample m_history_23;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_ctrl_31;
	t_sample m_history_5;
	t_sample m_history_22;
	t_sample m_history_20;
	t_sample m_ctrl_32;
	t_sample m_history_14;
	t_sample m_history_13;
	t_sample m_history_21;
	t_sample m_RecRMS_16;
	t_sample m_history_18;
	t_sample m_history_4;
	t_sample m_history_19;
	t_sample m_history_15;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)7000));
		m_delay_7.reset("m_delay_7", ((int)16000));
		m_delay_8.reset("m_delay_8", ((int)15000));
		m_delay_9.reset("m_delay_9", ((int)12000));
		m_delay_10.reset("m_delay_10", ((int)10000));
		m_delay_11.reset("m_delay_11", ((int)6000));
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_RecRMS_16 = ((int)0);
		m_RMSV_17.reset("m_RMSV_17", (samplerate * ((t_sample)0.01)));
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_history_21 = ((int)0);
		m_history_22 = ((int)0);
		m_history_23 = ((int)0);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_delay_26.reset("m_delay_26", ((int)48000));
		m_delay_27.reset("m_delay_27", ((int)48000));
		m_delay_28.reset("m_delay_28", ((int)48000));
		m_delay_29.reset("m_delay_29", ((int)48000));
		m_delay_30.reset("m_delay_30", ((int)48000));
		m_ctrl_31 = ((t_sample)0.7);
		m_ctrl_32 = ((int)75);
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
		t_sample sub_365 = (m_ctrl_32 - ((t_sample)0.1));
		t_sample scale_362 = ((safepow((sub_365 * ((t_sample)1.1111111111111)), ((int)1)) * ((t_sample)79.9)) + ((t_sample)0.1));
		t_sample scale_8 = scale_362;
		t_sample expr_335 = ((scale_8 * samplerate) * ((t_sample)0.0029411764705882));
		t_sample add_76 = (expr_335 + ((int)5));
		t_sample mul_145 = (expr_335 * ((t_sample)0.63245));
		t_sample mul_148 = (expr_335 * ((int)1));
		t_sample mul_146 = (expr_335 * ((t_sample)0.7071));
		t_sample mul_147 = (expr_335 * ((t_sample)0.81649));
		t_sample mul_80 = (expr_335 * ((t_sample)0.155));
		t_sample add_77 = (mul_80 + ((int)5));
		t_sample mul_81 = (expr_335 * ((t_sample)0.3));
		t_sample add_78 = (mul_81 + ((int)5));
		t_sample mul_82 = (expr_335 * ((t_sample)0.41));
		t_sample add_79 = (mul_82 + ((int)5));
		t_sample expr_334 = safepow(((t_sample)0.001), safediv(((int)1), (((int)35) * samplerate)));
		t_sample expr_330 = safepow(expr_334, add_77);
		t_sample expr_329 = safepow(expr_334, add_76);
		t_sample expr_326 = (-safepow(expr_334, mul_145));
		t_sample expr_333 = (-safepow(expr_334, mul_148));
		t_sample expr_331 = safepow(expr_334, add_78);
		t_sample expr_332 = safepow(expr_334, add_79);
		t_sample expr_327 = (-safepow(expr_334, mul_146));
		t_sample expr_328 = (-safepow(expr_334, mul_147));
		t_sample div_318 = safediv(((t_sample)942.47779607694), samplerate);
		t_sample cos_317 = cos(div_318);
		t_sample mul_310 = (cos_317 * (-2));
		t_sample gen_323 = mul_310;
		t_sample rsub_312 = (((int)1) - cos_317);
		t_sample gen_320 = rsub_312;
		t_sample div_311 = (rsub_312 * ((t_sample)0.5));
		t_sample gen_319 = div_311;
		t_sample div_308 = (rsub_312 * ((t_sample)0.5));
		t_sample gen_321 = div_308;
		t_sample sin_316 = sin(div_318);
		t_sample div_315 = (sin_316 * ((t_sample)1));
		t_sample add_313 = (div_315 + ((int)1));
		t_sample gen_322 = add_313;
		t_sample rsub_309 = (((int)1) - div_315);
		t_sample gen_324 = rsub_309;
		t_sample div_222 = safediv(((t_sample)3141.5926535898), samplerate);
		t_sample cos_221 = cos(div_222);
		t_sample mul_214 = (cos_221 * (-2));
		t_sample gen_227 = mul_214;
		t_sample rsub_216 = (((int)1) - cos_221);
		t_sample gen_224 = rsub_216;
		t_sample div_215 = (rsub_216 * ((t_sample)0.5));
		t_sample gen_223 = div_215;
		t_sample div_212 = (rsub_216 * ((t_sample)0.5));
		t_sample gen_225 = div_212;
		t_sample sin_220 = sin(div_222);
		t_sample div_219 = (sin_220 * ((t_sample)1));
		t_sample add_217 = (div_219 + ((int)1));
		t_sample gen_226 = add_217;
		t_sample rsub_213 = (((int)1) - div_219);
		t_sample gen_228 = rsub_213;
		t_sample a_185 = gen_226;
		t_sample div_186 = safediv(gen_227, a_185);
		t_sample a_187 = a_185;
		t_sample div_188 = safediv(gen_225, a_187);
		t_sample a_183 = a_185;
		t_sample div_184 = safediv(gen_228, a_183);
		t_sample a_191 = a_185;
		t_sample div_192 = safediv(gen_223, a_191);
		t_sample a_189 = a_185;
		t_sample div_190 = safediv(gen_224, a_189);
		t_sample div_270 = safediv(((t_sample)3141.5926535898), samplerate);
		t_sample cos_269 = cos(div_270);
		t_sample rsub_264 = (((int)1) - cos_269);
		t_sample gen_272 = rsub_264;
		t_sample div_260 = (rsub_264 * ((t_sample)0.5));
		t_sample gen_273 = div_260;
		t_sample div_263 = (rsub_264 * ((t_sample)0.5));
		t_sample gen_271 = div_263;
		t_sample mul_262 = (cos_269 * (-2));
		t_sample gen_275 = mul_262;
		t_sample sin_268 = sin(div_270);
		t_sample div_267 = (sin_268 * ((t_sample)0.83333333333333));
		t_sample add_265 = (div_267 + ((int)1));
		t_sample gen_274 = add_265;
		t_sample rsub_261 = (((int)1) - div_267);
		t_sample gen_276 = rsub_261;
		t_sample a_233 = gen_274;
		t_sample div_234 = safediv(gen_275, a_233);
		t_sample a_235 = a_233;
		t_sample div_236 = safediv(gen_273, a_235);
		t_sample a_231 = a_233;
		t_sample div_232 = safediv(gen_276, a_231);
		t_sample a_239 = a_233;
		t_sample div_240 = safediv(gen_271, a_239);
		t_sample a_237 = a_233;
		t_sample div_238 = safediv(gen_272, a_237);
		t_sample Size = (samplerate * ((t_sample)0.01));
		t_sample Period = (Size * ((t_sample)0.1));
		__loopcount = (__n * GENLIB_LOOPCOUNT_BAIL);
		t_sample a_285 = gen_322;
		t_sample div_286 = safediv(gen_320, a_285);
		t_sample a_283 = a_285;
		t_sample div_284 = safediv(gen_321, a_283);
		t_sample a_281 = a_285;
		t_sample div_282 = safediv(gen_323, a_281);
		t_sample a_279 = a_285;
		t_sample div_280 = safediv(gen_324, a_279);
		t_sample a_287 = a_285;
		t_sample div_288 = safediv(gen_319, a_287);
		t_sample mul_142 = (expr_335 * ((t_sample)0.000527));
		int int_141 = int(mul_142);
		t_sample mul_140 = (expr_335 * ((t_sample)0.110732));
		t_sample mul_122 = (int_141 * ((t_sample)387.40262));
		t_sample mul_96 = (int_141 * ((t_sample)432.8267));
		t_sample mul_129 = (int_141 * ((t_sample)577.06492));
		t_sample mul_103 = (int_141 * ((t_sample)573.27526));
		t_sample mul_110 = (int_141 * ((t_sample)124.89804));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_153 = m_delay_30.read_linear(mul_148);
			t_sample mul_144 = (tap_153 * expr_333);
			t_sample mix_366 = (mul_144 + (m_ctrl_31 * (m_history_5 - mul_144)));
			t_sample mix_151 = mix_366;
			t_sample tap_56 = m_delay_29.read_linear(mul_146);
			t_sample mul_52 = (tap_56 * expr_327);
			t_sample mix_367 = (mul_52 + (m_ctrl_31 * (m_history_4 - mul_52)));
			t_sample mix_54 = mix_367;
			t_sample tap_62 = m_delay_28.read_linear(mul_147);
			t_sample mul_58 = (tap_62 * expr_328);
			t_sample mix_368 = (mul_58 + (m_ctrl_31 * (m_history_3 - mul_58)));
			t_sample mix_60 = mix_368;
			t_sample tap_50 = m_delay_27.read_linear(mul_145);
			t_sample mul_46 = (tap_50 * expr_326);
			t_sample mix_369 = (mul_46 + (m_ctrl_31 * (m_history_2 - mul_46)));
			t_sample mix_48 = mix_369;
			t_sample tap_64 = m_delay_26.read_linear(add_79);
			t_sample tap_65 = m_delay_26.read_linear(add_78);
			t_sample tap_66 = m_delay_26.read_linear(add_77);
			t_sample tap_67 = m_delay_26.read_linear(add_76);
			t_sample mul_74 = (tap_64 * expr_332);
			t_sample mul_70 = (tap_66 * expr_330);
			t_sample mul_72 = (tap_65 * expr_331);
			t_sample mul_68 = (tap_67 * expr_329);
			t_sample mul_200 = (m_history_22 * div_186);
			t_sample mul_203 = (m_history_25 * div_188);
			t_sample mul_199 = (m_history_24 * div_184);
			t_sample add_193 = (mul_200 + mul_199);
			t_sample mul_205 = (in2 * div_192);
			t_sample mul_204 = (m_history_23 * div_190);
			t_sample add_195 = (mul_205 + mul_204);
			t_sample add_194 = (add_195 + mul_203);
			t_sample sub_198 = (add_194 - add_193);
			t_sample gen_210 = sub_198;
			t_sample history_201_next_206 = fixdenorm(m_history_23);
			t_sample history_196_next_207 = fixdenorm(m_history_22);
			t_sample history_202_next_208 = fixdenorm(in2);
			t_sample history_197_next_209 = fixdenorm(sub_198);
			t_sample mul_7 = (gen_210 * ((int)2));
			t_sample atan_6 = atan(mul_7);
			t_sample mul_5 = (atan_6 * ((t_sample)6.2831853071796));
			t_sample mul_248 = (m_history_18 * div_234);
			t_sample mul_251 = (m_history_21 * div_236);
			t_sample mul_247 = (m_history_20 * div_232);
			t_sample add_241 = (mul_248 + mul_247);
			t_sample mul_253 = (in1 * div_240);
			t_sample mul_252 = (m_history_19 * div_238);
			t_sample add_243 = (mul_253 + mul_252);
			t_sample add_242 = (add_243 + mul_251);
			t_sample sub_246 = (add_242 - add_241);
			t_sample gen_258 = sub_246;
			t_sample history_249_next_254 = fixdenorm(m_history_19);
			t_sample history_244_next_255 = fixdenorm(m_history_18);
			t_sample history_250_next_256 = fixdenorm(in1);
			t_sample history_245_next_257 = fixdenorm(sub_246);
			t_sample mul_164 = (gen_258 * ((int)2));
			t_sample atan_163 = atan(mul_164);
			t_sample mul_162 = (atan_163 * ((t_sample)6.2831853071796));
			t_sample add_4 = (mul_5 + mul_162);
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
				t_sample RMSin = m_RMSV_17.read_linear(Vn);
				RMS = (RMS + (RMSin * RMSin));
				// for loop increment;
				Vn = (Vn + Period);
				
			};
			t_sample expr_336 = sqrt((safediv(RMS, Size) * Period));
			m_RMSV_17.write(add_4);
			t_sample out3 = expr_336;
			t_sample mul_10 = ((mul_5 + mul_162) * ((t_sample)0.707));
			t_sample mix_370 = (mul_10 + (((t_sample)0.2) * (m_history_1 - mul_10)));
			t_sample mix_155 = mix_370;
			t_sample add_180 = (gen_258 + gen_210);
			t_sample mul_179 = (add_180 * ((int)5));
			t_sample atan_178 = atan(mul_179);
			t_sample mul_177 = (atan_178 * ((t_sample)6.2831853071796));
			t_sample mul_300 = (m_history_13 * div_286);
			t_sample mul_299 = (m_history_15 * div_284);
			t_sample mul_296 = (m_history_12 * div_282);
			t_sample mul_295 = (m_history_14 * div_280);
			t_sample add_289 = (mul_296 + mul_295);
			t_sample mul_301 = (mul_177 * div_288);
			t_sample add_291 = (mul_301 + mul_300);
			t_sample add_290 = (add_291 + mul_299);
			t_sample sub_294 = (add_290 - add_289);
			t_sample gen_306 = sub_294;
			t_sample history_297_next_302 = fixdenorm(m_history_13);
			t_sample history_292_next_303 = fixdenorm(m_history_12);
			t_sample history_298_next_304 = fixdenorm(mul_177);
			t_sample history_293_next_305 = fixdenorm(sub_294);
			t_sample out2 = gen_306;
			t_sample add_40 = (mix_151 + mix_60);
			t_sample add_38 = (mix_54 + mix_48);
			t_sample sub_37 = (add_40 - add_38);
			t_sample mul_19 = (sub_37 * ((t_sample)0.5));
			t_sample add_44 = (mul_19 + mul_74);
			t_sample add_33 = (add_40 + add_38);
			t_sample mul_16 = (add_33 * ((t_sample)0.5));
			t_sample add_41 = (mul_16 + mul_68);
			t_sample sub_39 = (mix_151 - mix_60);
			t_sample sub_36 = (mix_54 - mix_48);
			t_sample sub_35 = (sub_39 - sub_36);
			t_sample mul_18 = (sub_35 * ((t_sample)0.5));
			t_sample add_43 = (mul_18 + mul_72);
			t_sample add_34 = (sub_39 + sub_36);
			t_sample rsub_32 = (((int)0) - add_34);
			t_sample mul_17 = (rsub_32 * ((t_sample)0.5));
			t_sample add_42 = (mul_17 + mul_70);
			t_sample tap_139 = m_delay_11.read_linear(mul_140);
			t_sample tap_121 = m_delay_10.read_linear(mul_122);
			t_sample mul_119 = (tap_121 * ((t_sample)0.625));
			t_sample tap_95 = m_delay_9.read_linear(mul_96);
			t_sample mul_93 = (tap_95 * ((t_sample)0.625));
			t_sample mul_137 = (tap_139 * ((t_sample)0.75));
			t_sample sub_136 = (mix_155 - mul_137);
			t_sample mul_135 = (sub_136 * ((t_sample)0.75));
			t_sample add_134 = (mul_135 + tap_139);
			t_sample tap_128 = m_delay_8.read_linear(mul_129);
			t_sample mul_126 = (tap_128 * ((t_sample)0.625));
			t_sample tap_102 = m_delay_7.read_linear(mul_103);
			t_sample mul_100 = (tap_102 * ((t_sample)0.625));
			t_sample tap_109 = m_delay_6.read_linear(mul_110);
			t_sample mul_107 = (tap_109 * ((t_sample)0.75));
			t_sample mul_31 = (mul_19 * ((t_sample)0.1));
			t_sample mul_29 = (mul_17 * ((t_sample)0.1));
			t_sample add_15 = (mul_31 + mul_29);
			t_sample mul_30 = (mul_18 * ((t_sample)0.1));
			t_sample mul_28 = (mul_16 * ((t_sample)0.1));
			t_sample add_14 = (mul_30 + mul_28);
			t_sample sub_22 = (add_15 - add_14);
			t_sample mul_26 = (mul_74 * ((t_sample)0.25));
			t_sample mul_24 = (mul_70 * ((t_sample)0.25));
			t_sample add_13 = (mul_26 + mul_24);
			t_sample mul_25 = (mul_72 * ((t_sample)0.25));
			t_sample mul_23 = (mul_68 * ((t_sample)0.25));
			t_sample add_12 = (mul_25 + mul_23);
			t_sample sub_21 = (add_13 - add_12);
			t_sample add_9 = (sub_22 + sub_21);
			t_sample add_20 = (add_9 + mul_162);
			t_sample sub_133 = (add_20 - ((int)0));
			t_sample mul_132 = (sub_133 * ((t_sample)0.75));
			t_sample add_131 = (mul_132 + ((int)0));
			t_sample sub_125 = (add_131 - mul_126);
			t_sample mul_124 = (sub_125 * ((t_sample)0.625));
			t_sample add_123 = (mul_124 + tap_128);
			t_sample sub_118 = (add_123 - mul_119);
			t_sample mul_117 = (sub_118 * ((t_sample)0.625));
			t_sample add_116 = (mul_117 + tap_121);
			t_sample add_2 = (mul_162 + add_116);
			t_sample add_11 = (add_9 + mul_5);
			t_sample sub_106 = (add_11 - mul_107);
			t_sample mul_105 = (sub_106 * ((t_sample)0.75));
			t_sample add_104 = (mul_105 + tap_109);
			t_sample sub_99 = (add_104 - mul_100);
			t_sample mul_98 = (sub_99 * ((t_sample)0.625));
			t_sample add_97 = (mul_98 + tap_102);
			t_sample sub_92 = (add_97 - mul_93);
			t_sample mul_91 = (sub_92 * ((t_sample)0.625));
			t_sample add_90 = (mul_91 + tap_95);
			t_sample add_165 = (mul_5 + add_90);
			t_sample add_1 = (add_2 + add_165);
			t_sample out1 = add_1;
			t_sample history_150_next_337 = fixdenorm(mix_151);
			t_sample history_53_next_338 = fixdenorm(mix_54);
			t_sample history_59_next_339 = fixdenorm(mix_60);
			t_sample history_47_next_340 = fixdenorm(mix_48);
			t_sample history_154_next_341 = fixdenorm(mix_155);
			m_delay_30.write(add_44);
			m_delay_29.write(add_42);
			m_delay_28.write(add_43);
			m_delay_27.write(add_41);
			m_delay_26.write(add_134);
			m_history_25 = history_201_next_206;
			m_history_22 = history_197_next_209;
			m_history_23 = history_202_next_208;
			m_history_24 = history_196_next_207;
			m_history_21 = history_249_next_254;
			m_history_18 = history_245_next_257;
			m_history_19 = history_250_next_256;
			m_history_20 = history_244_next_255;
			m_history_15 = history_297_next_302;
			m_history_12 = history_293_next_305;
			m_history_13 = history_298_next_304;
			m_history_14 = history_292_next_303;
			m_delay_11.write(sub_136);
			m_delay_10.write(sub_118);
			m_delay_9.write(sub_92);
			m_delay_8.write(sub_125);
			m_delay_7.write(sub_99);
			m_delay_6.write(sub_106);
			m_history_5 = history_150_next_337;
			m_history_4 = history_53_next_338;
			m_history_3 = history_59_next_339;
			m_history_2 = history_47_next_340;
			m_history_1 = history_154_next_341;
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_RMSV_17.step();
			m_delay_26.step();
			m_delay_27.step();
			m_delay_28.step();
			m_delay_29.step();
			m_delay_30.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_31 = (_value < 0.45 ? 0.45 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_32 = (_value < 0.1 ? 0.1 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_ctrl_32; break;
		case 1: *value = self->m_ctrl_31; break;
		
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
	// initialize parameter 0 ("m_ctrl_32")
	pi = self->__commonstate.params + 0;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_31")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.45;
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


} // rugosus_2da::
