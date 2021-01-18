/*
 *  Copyright (c) 2017 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MEDIA_BASE_H265_PROFILE_LEVEL_ID_H_
#define MEDIA_BASE_H265_PROFILE_LEVEL_ID_H_


namespace webrtc {

namespace H265 {

  // All values are equal to ten times the level number, except level 1b which is
  // special.
  enum Level {

    kLevel1 = 30,
    kLevel2 = 60,
    kLevel2_1 = 63,
    kLevel3 = 90,
    kLevel3_1 = 93,
    kLevel4 = 120,
    kLevel4_1 = 123,
    kLevel5 = 150,
    kLevel5_1 = 153,
    kLevel5_2 = 156,
    kLevel6 = 180,
    kLevel6_1 = 183,
    kLevel6_2 = 186

  };
} // name space H265

}  // namespace webrtc

#endif  // MEDIA_BASE_H265_PROFILE_LEVEL_ID_H_
