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

#include "modules/video_coding/codecs/h265/include/h265.h"

#include "api/video_codecs/sdp_video_format.h"
#include "media/base/h265_profile_level_id.h"

#ifndef DISABLE_H265	
#if defined(WEBRTC_USE_H265)
#include "modules/video_coding/codecs/h265/h265_decoder_impl.h"
#include "modules/video_coding/codecs/h265/h265_encoder_impl.h"
#endif
#endif

#include "absl/memory/memory.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"

namespace webrtc {

namespace {

#ifndef DISABLE_H265	
#if defined(WEBRTC_USE_H265)
bool g_rtc_use_h265 = true;
#endif
#endif

// If H.265 FFmpeg codec is supported.
bool IsH265CodecSupported() {
#ifndef DISABLE_H265	
#if defined(WEBRTC_USE_H265)
  return g_rtc_use_h265;
#else
  return false;
#endif
#else
  return false;
#endif
}

SdpVideoFormat CreateH265Format(H265::Level level) {
  return webrtc::SdpVideoFormat(
      cricket::kH265CodecName,
        {
          {cricket::kH265FmtpProfileSpace, "0"},
          {cricket::kH265FmtpProfileId, "1"},
          {cricket::kH265FmtpTierFlag, "0"},
          {cricket::kH265FmtpLevelId, std::to_string(int(level))}
        }
      );
}

}  // namespace

void DisableRtcUseH265() {
#ifndef DISABLE_H265	
#if defined(WEBRTC_USE_H265)
  g_rtc_use_h265 = false;
#endif
#endif
}


std::vector<SdpVideoFormat> SupportedH265Codecs() {
  if (!IsH265CodecSupported())
    return std::vector<SdpVideoFormat>();
  return {
      CreateH265Format(H265::kLevel6_1),
      CreateH265Format(H265::kLevel6_2)
    };
}

std::unique_ptr<H265Encoder> H265Encoder::Create(
    const cricket::VideoCodec& codec) {
#ifndef DISABLE_H265
#if defined(WEBRTC_USE_H265)
  RTC_LOG(LS_INFO) << "Creating H265EncoderImpl.";
  return absl::make_unique<H265EncoderImpl>(codec);
#else
  RTC_NOTREACHED();
  return nullptr;
#endif
#else
  RTC_NOTREACHED();
  return nullptr;
#endif
}

bool H265Encoder::IsSupported() {
  return IsH265CodecSupported();
}

std::unique_ptr<H265Decoder> H265Decoder::Create() {
  RTC_DCHECK(H265Decoder::IsSupported());
#ifndef DISABLE_H265
#if defined(WEBRTC_USE_H265)
  RTC_CHECK(g_rtc_use_h265);
  RTC_LOG(LS_INFO) << "Creating H265DecoderImpl.";
  return absl::make_unique<H265DecoderImpl>();
#else
  RTC_NOTREACHED();
  return nullptr;
#endif
#else
  RTC_NOTREACHED();
  return nullptr;
#endif
}

bool H265Decoder::IsSupported() {
  return IsH265CodecSupported();
}

}  // namespace webrtc
