//
// Copyright (c) 2010-2026 Antmicro
//
// This file is licensed under the MIT License.
// Full license text is available in 'licenses/MIT.txt'.
//
#pragma once

#include <cstdint>
#include <systemc>
#include <tlm>
#include "renode_bridge_native_export.h"

struct IRenodeBridge {
  virtual void reset() = 0;
  virtual tlm::tlm_fw_transport_if<> *tlm_route(std::uint64_t offset) = 0;
  virtual void gpio_port_write(int number, bool value) = 0;
  virtual ~IRenodeBridge() = default;
};

using renode_bridge_factory_t = IRenodeBridge* (*)();
void register_renode_bridge_factory(renode_bridge_factory_t);

extern "C" {
  RENODE_BRIDGE_API void systemc_init();
  RENODE_BRIDGE_API void systemc_reset();
  RENODE_BRIDGE_API void systemc_start_sim(int ns);
  
  RENODE_BRIDGE_API std::uint64_t tlm_read(std::size_t size, std::uint64_t offset);
  RENODE_BRIDGE_API void tlm_write(std::size_t size, std::int64_t value, std::uint64_t offset);

  RENODE_BRIDGE_API void gpio_write(int number, bool value);
  RENODE_BRIDGE_API void renode_gpio_update(int number, int value);
}
