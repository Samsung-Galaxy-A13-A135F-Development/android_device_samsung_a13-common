/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cutils/log.h>
#include "TSPInit.h"

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

ndk::ScopedAStatus TSPInit::getEnabled(bool* _aidl_return) {
    std::ifstream file(TSP_CMD_RESULT_NODE);
    if (file.is_open()) {
        std::string line;
        getline(file, line);
        *_aidl_return = !line.compare("check_connection:NG");
        file.close();
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus TSPInit::setEnabled(bool enabled) {
    bool initialised = false;
    getEnabled(&initialised);
    if (!initialised) {
        std::ofstream file(TSP_CMD_NODE);
	ALOGI("TSPInit: initialising touchscreen");
        ALOGI("TSPInit: sending check_connection to TSP_CMD_NODE");
        file << "check_connection";
        file.close();
	ALOGI("TSPInit: sent check_connection to TSP_CMD_NODE");
	ALOGI("TSPInit: touchscreen initialised");

        std::ifstream result(TSP_CMD_RESULT_NODE);
        std::string discard;
        std::getline(result, discard);
    }
    return ndk::ScopedAStatus::ok();
}

void TSPInit::startScreenMonitor() {
    mMonitorThread = std::thread([this]() {
        FILE* pipe = popen("logcat -b all -s InputReader -v raw", "r");
        if (!pipe) {
            ALOGE("TSPInit: Failed to open logcat pipe");
            return;
        }

        char line[1024];
        while (fgets(line, sizeof(line), pipe)) {
            if (strstr(line, "sec_touchscreen")) {
                setEnabled(true);
                usleep(500000); // sleep .5 sec
            }
        }

        pclose(pipe);
    });
    mMonitorThread.detach();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
