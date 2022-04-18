#include "proxy_wasm_intrinsics.h"

class PluginRootContext : public RootContext {
 public:
  explicit PluginRootContext(uint32_t id, std::string_view root_id)
      : RootContext(id, root_id) {}

  bool onConfigure(size_t) override;
};

class PluginContext : public Context {
 public:
  explicit PluginContext(uint32_t id, RootContext* root) : Context(id, root) {}

  FilterHeadersStatus onResponseHeaders(uint32_t, bool) override;

 private:
  inline PluginRootContext* rootContext() {
    return dynamic_cast<PluginRootContext*>(this->root());
  }
};


// Boilderplate code to register the extension implementation.
static RegisterContextFactory register_Example(CONTEXT_FACTORY(PluginContext),
                                               ROOT_FACTORY(PluginRootContext));

bool PluginRootContext::onConfigure(size_t) { return true; }

FilterHeadersStatus PluginContext::onResponseHeaders(uint32_t, bool) {
  addResponseHeader("header-added-by", "dbyin");
  return FilterHeadersStatus::Continue;
}
