#include <string>
#include <unordered_map>

#include "proxy_wasm_intrinsics.h"

class ExampleContext : public Context {
public:
  explicit ExampleContext(uint32_t id, RootContext* root) : Context(id, root) {}

  FilterHeadersStatus onRequestHeaders(uint32_t headers, bool end_of_stream) override;
  void onDone() override;
  FilterHeadersStatus onResponseHeaders(uint32_t headers, bool end_of_stream) override;

};
static RegisterContextFactory register_ExampleContext(CONTEXT_FACTORY(ExampleContext));

FilterHeadersStatus ExampleContext::onRequestHeaders(uint32_t headers, bool end_of_stream) {
  logInfo(std::string("onRequestHeaders ") + std::to_string(id()));
  auto path = getRequestHeader(":path");
  logInfo(std::string("header path ") + std::string(path->view()));
  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus ExampleContext::onResponseHeaders(uint32_t, bool) {
  LOG_DEBUG(std::string("onResponseHeaders ") + std::to_string(id()));
  auto result = getResponseHeaderPairs();
  auto pairs = result->pairs();
  LOG_INFO(std::string("headers: ") + std::to_string(pairs.size()));
  for (auto &p : pairs) {
    LOG_INFO(std::string(p.first) + std::string(" -> ") + std::string(p.second));
  }
  addResponseHeader("header-added-by", "dbyin");
  replaceResponseHeader("content-type", "text/plain; charset=utf-8");
  removeResponseHeader("content-length");
  return FilterHeadersStatus::Continue;
}

void ExampleContext::onDone() { logInfo("onDone " + std::to_string(id())); }
