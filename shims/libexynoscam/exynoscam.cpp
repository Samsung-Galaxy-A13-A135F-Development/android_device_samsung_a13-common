/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <string.h>

#include <utils/String8.h>
#include <camera/CameraMetadata.h>
#include <camera/CameraParameters.h>

using android::String8;
using android::status_t;

extern "C" int
_ZN7android12ExynosCamera13setParametersERKNS_8hardware6camera6common6helper16CameraParametersE(
        void*,
        const void*) {
    return 0;
}

extern "C" void
_ZN7android12ExynosCamera19checkAndSetMemBoostEPc(
        void*,
        char*) {
}

extern "C" void
_ZN7android18doCalMapConversionEv() {
}

extern "C" void
_ZN7android19SecCameraDeviceInfo22performCameraRomReloadEv(
        void*) {
}

extern "C" void
_ZN7android8hardware6camera6common6helper14CameraMetadataC1Ev(
        void*) {
}

extern "C" void
_ZN7android8hardware6camera6common6helper14CameraMetadataD1Ev(
        void*) {
}

extern "C" camera_metadata_entry_t
_ZNK7android8hardware6camera6common6helper14CameraMetadata4findEj(
        const void*,
        uint32_t) {
    camera_metadata_entry_t entry;
    memset(&entry, 0, sizeof(entry));
    return entry;
}

extern "C" void*
_ZN7android8hardware6camera6common6helper14CameraMetadataaSEPK15camera_metadata(
        void* thisptr,
        const camera_metadata_t*) {
    return thisptr;
}

extern "C" status_t
_ZN7android8hardware6camera6common6helper16CameraParameters9unflattenERKNS_7String8E(
        void*,
        const String8&) {
    return 0;
}

extern "C" void
_ZN7android8hardware6camera6common6helper16CameraParametersD1Ev(
        void*) {
}

