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

#ifndef MODULES_VIDEO_CODING_CODECS_H265_INCLUDE_H265_H_
#define MODULES_VIDEO_CODING_CODECS_H265_INCLUDE_H265_H_

#include <memory>
#include <vector>

#include "media/base/codec.h"
#include "modules/video_coding/include/video_codec_interface.h"

namespace webrtc {

struct SdpVideoFormat;

// Set to disable the H.265 encoder/decoder implementations that are provided if
// |rtc_use_h265| build flag is true (if false, this function does nothing).
// This function should only be called before or during WebRTC initialization
// and is not thread-safe.
void DisableRtcUseH265();

// Returns a vector with all supported internal H265 profiles that we can
// negotiate in SDP, in order of preference.
std::vector<SdpVideoFormat> SupportedH265Codecs();

class H265Encoder : public VideoEncoder {
 public:
  static std::unique_ptr<H265Encoder> Create(const cricket::VideoCodec& codec);
  // If H.265 is supported (any implementation).
  static bool IsSupported();

  ~H265Encoder() override {}
};

class H265Decoder : public VideoDecoder {
 public:
  static std::unique_ptr<H265Decoder> Create();
  static bool IsSupported();

  ~H265Decoder() override {}
};

}  // namespace webrtc

#endif  // MODULES_VIDEO_CODING_CODECS_H265_INCLUDE_H265_H_
