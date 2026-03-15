/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.samsung.touch.sysinput-service"

#include "TSPInit.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::lineage::touch::TSPInit;

int main() {
    binder_status_t status = STATUS_OK;

    ABinderProcess_setThreadPoolMaxThreadCount(0);

    std::shared_ptr<TSPInit> gm = ndk::SharedRefBase::make<TSPInit>();
    gm->startScreenMonitor();
    const std::string gm_instance = std::string(TSPInit::descriptor) + "/default";
    AServiceManager_addService(gm->asBinder().get(), gm_instance.c_str());

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
