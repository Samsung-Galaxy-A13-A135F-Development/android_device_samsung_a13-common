#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.fixups_lib import (
    lib_fixup_vendorcompat,
    lib_fixups_user_type,
    libs_proto_3_9_1,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

namespace_imports = [
    'device/samsung/a13-common',
    'hardware/samsung',
    'hardware/samsung_slsi-linaro/exynos',
    'hardware/samsung_slsi-linaro/graphics',
    'hardware/samsung_slsi-linaro/exynos/gralloc/gralloc3',
]

def lib_fixup_vendor_suffix(lib: str, partition: str, *args, **kwargs):
    return f'{lib}_{partition}' if partition == 'vendor' else None

lib_fixups: lib_fixups_user_type = {
    libs_proto_3_9_1: lib_fixup_vendorcompat,
    (
        'libuuid',
    ) : lib_fixup_vendor_suffix
} # fmt: skip

blob_fixups: blob_fixups_user_type = {
    'vendor/bin/hw/gpsd': blob_fixup()
        .binary_regex_replace(b'libcrypto.so', b'libcryptx.so')
        .binary_regex_replace(b'libssl.so', b'libssx.so'),
    'vendor/lib64/libssx.so': blob_fixup()
        .replace_needed('libcrypto.so', 'libcryptx.so'),
    'vendor/lib/nfc_nci_nxpsn.so': blob_fixup()
        .binary_regex_replace(b'ro.boot.flash.locked', b'ro.camera.notify_nfc'),
    'vendor/lib/libexynoscamera3.so': blob_fixup()
        .add_needed('libshim_camera.so'),
    (
    'vendor/lib/libsensorlistener.so',
    ) : blob_fixup()
        .add_needed('libshim_sensorndkbridge.so'),
    (
        'vendor/lib64/libkeymaster_helper.so',
        'vendor/lib64/libskeymaster4device.so',
    ) : blob_fixup()
        .replace_needed('libcrypto.so', 'libcryptx.so')
        .add_needed('libshim_crypto.so'),
    (
        'vendor/lib/sensors.grip.so',
        'vendor/lib/sensors.sensorhub.so',
        'vendor/lib/sensors.inputvirtual.so',
    ) : blob_fixup()
	.add_needed('libutils-v32.so'),
    'vendor/lib/libsynaFpSensorTestNwd.so': blob_fixup()
        .add_needed('libshim_idiv0.so'),
}  # fmt: skip

module = ExtractUtilsModule(
    'a13-common',
    'samsung',
    namespace_imports=namespace_imports,
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
