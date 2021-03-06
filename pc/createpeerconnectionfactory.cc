/*
 *  Copyright 2017 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "api/audio/echo_canceller3_factory.h"
#include "api/call/callfactoryinterface.h"
#include "api/peerconnectioninterface.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "logging/rtc_event_log/rtc_event_log_factory_interface.h"
#include "media/engine/webrtcmediaengine.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "rtc_base/bind.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "rtc_base/thread.h"
#include "system_wrappers/include/field_trial.h"

namespace webrtc {

#if defined(USE_BUILTIN_SW_CODECS)
rtc::scoped_refptr<PeerConnectionFactoryInterface> CreatePeerConnectionFactory(
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory) {
  return CreatePeerConnectionFactoryWithAudioMixer(
      nullptr /*network_thread*/, nullptr /*worker_thread*/,
      nullptr /*signaling_thread*/, nullptr /*default_adm*/,
      audio_encoder_factory, audio_decoder_factory,
      nullptr /*video_encoder_factory*/, nullptr /*video_decoder_factory*/,
      nullptr /*audio_mixer*/);
}

// Note: all the other CreatePeerConnectionFactory variants just end up calling
// this, ultimately.
rtc::scoped_refptr<PeerConnectionFactoryInterface> CreatePeerConnectionFactory(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    AudioDeviceModule* default_adm,
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory,
    cricket::WebRtcVideoEncoderFactory* video_encoder_factory,
    cricket::WebRtcVideoDecoderFactory* video_decoder_factory,
    rtc::scoped_refptr<AudioMixer> audio_mixer,
    rtc::scoped_refptr<AudioProcessing> audio_processing) {
  rtc::scoped_refptr<AudioProcessing> audio_processing_use = audio_processing;
  if (!audio_processing_use) {
     if (webrtc::field_trial::FindFullName("ICS-EchoCanceller3") == "Enabled") {
    webrtc::EchoCanceller3Config aec3_config;	
    // TODO(jianlin): AEC3 configurations should be exposed to application.	
    // Review the config items to decide the param customization set.	
    aec3_config.ep_strength.bounded_erl = false;	
    aec3_config.echo_removal_control.has_clock_drift = false;	
    audio_processing_use = AudioProcessingBuilder().SetEchoControlFactory(	
        std::unique_ptr<webrtc::EchoControlFactory>(	
            new webrtc::EchoCanceller3Factory(aec3_config))).Create();	
    } else {	
      audio_processing_use = AudioProcessingBuilder().Create();	
    }
  }

  std::unique_ptr<cricket::MediaEngineInterface> media_engine(
      cricket::WebRtcMediaEngineFactory::Create(
          default_adm, audio_encoder_factory, audio_decoder_factory,
          video_encoder_factory, video_decoder_factory, audio_mixer,
          audio_processing_use));

  std::unique_ptr<CallFactoryInterface> call_factory = CreateCallFactory();

  std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory =
      CreateRtcEventLogFactory();

  return CreateModularPeerConnectionFactory(
      network_thread, worker_thread, signaling_thread, std::move(media_engine),
      std::move(call_factory), std::move(event_log_factory));
}

rtc::scoped_refptr<PeerConnectionFactoryInterface> CreatePeerConnectionFactory(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    AudioDeviceModule* default_adm,
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory,
    cricket::WebRtcVideoEncoderFactory* video_encoder_factory,
    cricket::WebRtcVideoDecoderFactory* video_decoder_factory,
    rtc::scoped_refptr<AudioMixer> audio_mixer,
    rtc::scoped_refptr<AudioProcessing> audio_processing,
    std::unique_ptr<FecControllerFactoryInterface> fec_controller_factory,
    std::unique_ptr<NetworkControllerFactoryInterface>
        network_controller_factory) {

  rtc::scoped_refptr<AudioProcessing> audio_processing_use = audio_processing;
  if (!audio_processing_use) {
    audio_processing_use = AudioProcessingBuilder().Create();
  }

  std::unique_ptr<cricket::MediaEngineInterface> media_engine(
      cricket::WebRtcMediaEngineFactory::Create(
          default_adm, audio_encoder_factory, audio_decoder_factory,
          video_encoder_factory, video_decoder_factory, audio_mixer,
          audio_processing_use));

  std::unique_ptr<CallFactoryInterface> call_factory = CreateCallFactory();

  std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory =
      CreateRtcEventLogFactory();

  return CreateModularPeerConnectionFactory(
      network_thread, worker_thread, signaling_thread, std::move(media_engine),
      std::move(call_factory), std::move(event_log_factory),
      std::move(fec_controller_factory), std::move(network_controller_factory));
}
#endif

rtc::scoped_refptr<PeerConnectionFactoryInterface> CreatePeerConnectionFactory(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    rtc::scoped_refptr<AudioDeviceModule> default_adm,
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory,
    std::unique_ptr<VideoEncoderFactory> video_encoder_factory,
    std::unique_ptr<VideoDecoderFactory> video_decoder_factory,
    rtc::scoped_refptr<AudioMixer> audio_mixer,
    rtc::scoped_refptr<AudioProcessing> audio_processing) {

  if (!audio_processing)
    audio_processing = AudioProcessingBuilder().Create();

  std::unique_ptr<cricket::MediaEngineInterface> media_engine =
      cricket::WebRtcMediaEngineFactory::Create(
          default_adm, audio_encoder_factory, audio_decoder_factory,
          std::move(video_encoder_factory), std::move(video_decoder_factory),
          audio_mixer, audio_processing);


  std::unique_ptr<CallFactoryInterface> call_factory = CreateCallFactory();


  std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory =
      CreateRtcEventLogFactory();


  return CreateModularPeerConnectionFactory(
      network_thread, worker_thread, signaling_thread, std::move(media_engine),
      std::move(call_factory), std::move(event_log_factory));
}

#if defined(USE_BUILTIN_SW_CODECS)
rtc::scoped_refptr<PeerConnectionFactoryInterface>
CreatePeerConnectionFactoryWithAudioMixer(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    AudioDeviceModule* default_adm,
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory,
    cricket::WebRtcVideoEncoderFactory* video_encoder_factory,
    cricket::WebRtcVideoDecoderFactory* video_decoder_factory,
    rtc::scoped_refptr<AudioMixer> audio_mixer) {
  return CreatePeerConnectionFactory(
      network_thread, worker_thread, signaling_thread, default_adm,
      audio_encoder_factory, audio_decoder_factory, video_encoder_factory,
      video_decoder_factory, audio_mixer, nullptr);
}

rtc::scoped_refptr<PeerConnectionFactoryInterface> CreatePeerConnectionFactory(
    rtc::Thread* network_thread,
    rtc::Thread* worker_thread,
    rtc::Thread* signaling_thread,
    AudioDeviceModule* default_adm,
    rtc::scoped_refptr<AudioEncoderFactory> audio_encoder_factory,
    rtc::scoped_refptr<AudioDecoderFactory> audio_decoder_factory,
    cricket::WebRtcVideoEncoderFactory* video_encoder_factory,
    cricket::WebRtcVideoDecoderFactory* video_decoder_factory) {
  return CreatePeerConnectionFactoryWithAudioMixer(
      network_thread, worker_thread, signaling_thread, default_adm,
      audio_encoder_factory, audio_decoder_factory, video_encoder_factory,
      video_decoder_factory, nullptr);
}
#endif

}  // namespace webrtc
