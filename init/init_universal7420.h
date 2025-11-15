#ifndef __INIT_UNIVERSAL7420__H__
#define __INIT_UNIVERSAL7420__H__

void gsm_properties(char const default_network[]);
void init_target_properties();
void property_override(char const prop[], char const value[], bool add=true);
void set_ro_product_prop(char const prop[], char const value[]);
void set_ro_build_prop(char const prop[], char const value[]);

#endif /* __INIT_UNIVERSAL7420__H__ */