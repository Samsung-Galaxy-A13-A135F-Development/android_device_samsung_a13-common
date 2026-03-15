/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include <aidl/vendor/lineage/touch/BnGloveMode.h>
#include <thread>
#include "samsung_touch.h"

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class TSPInit : public BnGloveMode {
  public:
    void startScreenMonitor();
    ndk::ScopedAStatus getEnabled(bool* _aidl_return) override;
    ndk::ScopedAStatus setEnabled(bool enabled) override;
  private:
    std::thread mMonitorThread;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
