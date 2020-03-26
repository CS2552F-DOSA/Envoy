#include <string>

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"s

#include "dosa-filter/http_filter.pb.h"
#include "dosa-filter/http_filter.pb.validate.h"

#include "extensions/filters/http/dosa/http_filter.h"

#include "extensions/filters/network/common/factory_base.h"
#include "extensions/filters/network/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Dosa {

class HttpSampleDecoderFilterConfig : public NamedHttpFilterConfigFactory {
public:
  Http::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                     const std::string&,
                                                     FactoryContext& context) override {

    return createFilter(Envoy::MessageUtil::downcastAndValidate<const sample::Decoder&>(
                            proto_config, context.messageValidationVisitor()),
                        context);
  }

  /**
   *  Return the Protobuf Message that represents your config incase you have config proto
   */
  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new sample::Decoder()};
  }

  std::string name() const override { return "sample"; }

private:
  Http::FilterFactoryCb createFilter(const sample::Decoder& proto_config, FactoryContext&) {
    Http::HttpSampleDecoderFilterConfigSharedPtr config =
        std::make_shared<Http::HttpSampleDecoderFilterConfig>(
            Http::HttpSampleDecoderFilterConfig(proto_config));

    return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::HttpSampleDecoderFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }
};

/**
 * Static registration for this sample filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<HttpSampleDecoderFilterConfig, NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy
