#pragma once

#include <string>

#include "envoy/extensions/filters/http/cache/v3/dosa.pb.h"

#include "extensions/filters/http/common/factory_base.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Dosa {

class HttpSampleDecoderFilterConfig {
public:
  HttpSampleDecoderFilterConfigFactory(const sample::Decoder& proto_config);

  // const std::string& key() const { return key_; }
  // const std::string& val() const { return val_; }

private:
  // const std::string key_;
  // const std::string val_;
};

typedef std::shared_ptr<HttpSampleDecoderFilterConfig> HttpSampleDecoderFilterConfigSharedPtr;

class HttpSampleDecoderFilter : public StreamDecoderFilter {
public:
  HttpSampleDecoderFilter(HttpSampleDecoderFilterConfigSharedPtr);
  ~HttpSampleDecoderFilter();

  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(RequestHeaderMap&, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(RequestTrailerMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks&) override;


private:
  const HttpSampleDecoderFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;

  // const LowerCaseString headerKey() const;
  // const std::string headerValue() const;
};

} // namespace DOSA
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
