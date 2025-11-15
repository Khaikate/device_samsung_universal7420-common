#include <android-base/strings.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"

#include "init_universal7420.h"

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
    "system_ext.",
};

void property_override(char const prop[], char const value[], bool add)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void gsm_properties(const char default_network[])
{
    // Dynamic GSM Properties
    property_override("ro.telephony.default_network", default_network);
    property_override("ro.vendor.sec.radio.def_network", default_network);

    // Static GSM Properties
    property_override("telephony.lteOnGsmDevice", "1");
}

void set_ro_product_prop(char const prop[], char const value[])
{
    for (const auto &source : ro_product_props_default_source_order) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value, false);
    }
}

void set_ro_build_prop(char const prop[], char const value[])
{
    for (const auto &source : ro_product_props_default_source_order) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value, false);
    }
};