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

#ifndef MODULES_VIDEO_CODING_CODECS_H265_H265_ENCODER_IMPL_H_
#define MODULES_VIDEO_CODING_CODECS_H265_H265_ENCODER_IMPL_H_

#include <memory>
#include <vector>

#include "api/video_codecs/video_encoder.h"
#include "modules/video_coding/codecs/h265/include/h265.h"

namespace webrtc {

class H265EncoderImpl : public H265Encoder {

 public:
  explicit H265EncoderImpl(const cricket::VideoCodec& codec);
  ~H265EncoderImpl() override;

 
  int32_t InitEncode(const VideoCodec* codec_settings,
                     int32_t number_of_cores,
                     size_t max_payload_size) override;
  int32_t Release() override;

  int32_t RegisterEncodeCompleteCallback(EncodedImageCallback* callback) override;

  int32_t SetRateAllocation(const VideoBitrateAllocation& bitrate_allocation,
                            uint32_t framerate) override;

  int32_t Encode(const VideoFrame& frame,
                 const CodecSpecificInfo* codec_specific_info,
                 const std::vector<FrameType>* frame_types) override;

  const char* ImplementationName() const override;

  VideoEncoder::ScalingSettings GetScalingSettings() const override;

  // Unsupported / Do nothing.
  int32_t SetChannelParameters(uint32_t packet_loss, int64_t rtt) override;


};

}  // namespace webrtc

#endif  // MODULES_VIDEO_CODING_CODECS_H265_H265_ENCODER_IMPL_H_
