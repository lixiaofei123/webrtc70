/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 *
 */

#include "modules/video_coding/codecs/h265/h265_encoder_impl.h"

#include <limits>
#include <string>


namespace webrtc {

H265EncoderImpl::H265EncoderImpl(const cricket::VideoCodec& codec){

}

H265EncoderImpl::~H265EncoderImpl(){

}

 
  int32_t H265EncoderImpl::InitEncode(const VideoCodec* codec_settings,
                     int32_t number_of_cores,
                     size_t max_payload_size){
                       return 0;
                     };
  int32_t H265EncoderImpl::Release(){
    return 0;
  }

  int32_t H265EncoderImpl::RegisterEncodeCompleteCallback(EncodedImageCallback* callback){
    return 0;
  }

  int32_t H265EncoderImpl::SetRateAllocation(const VideoBitrateAllocation& bitrate_allocation,
                            uint32_t framerate){
                              return 0;
                            };

  int32_t H265EncoderImpl::Encode(const VideoFrame& frame,
                 const CodecSpecificInfo* codec_specific_info,
                 const std::vector<FrameType>* frame_types){
                   return 0;
                 };

  const char* H265EncoderImpl::ImplementationName() const{
    return "H265";
  };

  VideoEncoder::ScalingSettings H265EncoderImpl::GetScalingSettings() const {
    return VideoEncoder::ScalingSettings(0,0);
  }

  // Unsupported / Do nothing.
  int32_t H265EncoderImpl::SetChannelParameters(uint32_t packet_loss, int64_t rtt){
    return 0;
  }


}  // namespace webrtc
