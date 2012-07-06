/*
 *  MinimalVstPlugin.cpp
 *  MinimalVstPlugin
 *
 *  Created by hotwatermorning on 12/07/07.
 *  Copyright 2012 home. All rights reserved.
 *
 */

#include "./public.sdk/source/vst2.x/audioeffectx.h"

namespace hwm {

struct MinimalVstPlugin
	:	AudioEffectX
{
	MinimalVstPlugin	(audioMasterCallback audioMaster)
		:	AudioEffectX(
				audioMaster,
				0,	//プログラム数
				0	//パラメータ数
				)
	{
		setNumInputs(2);
		setNumOutputs(2);

		canProcessReplacing();
		isSynth(false);
		setUniqueID('hwm1');
	}
	
	//! 信号処理
	virtual	void		processReplacing(
							float		**	inputs,
							float		**	outputs,
							VstInt32		sampleFrames )
	{
		enum { left, right };
	
		//! 左右のチャンネルを入れ替えるだけ
		for(size_t fr = 0; fr < sampleFrames; ++fr) {
			float const tmp_l = inputs[right][fr];
			float const tmp_r = inputs[left][fr];
		
			outputs[left][fr] = tmp_l;
			outputs[right][fr] = tmp_r;
		}
	}
};

}	//namespace hwm

AudioEffect *
		createEffectInstance(audioMasterCallback audioMaster)
{
	return new hwm::MinimalVstPlugin(audioMaster);
}