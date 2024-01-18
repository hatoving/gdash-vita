/*
 * reimpl/env.c
 *
 * Implementation for `getenv()`/`setenv()` functions with predefined
 * environment variables.
 *
 * Copyright (C) 2022-2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "reimpl/env.h"

#include <string.h>

#include "utils/logger.h"

typedef enum EnvVarsIds {
    ENV_VAR_UNKNOWN = 0,
    OPENSSL_CONF,
    NO_PROXY,
    HTTPS_PROXY,
    ALL_PROXY
} EnvVarsIds;

typedef struct {
    char *name;
    enum EnvVarsIds id;
} NameToEnvVarID;

static NameToEnvVarID name_to_env_var_ids[] = {
    { "UNK", ENV_VAR_UNKNOWN },
    { "OPENSSL_CONF", OPENSSL_CONF },
    { "NO_PROXY", NO_PROXY },
    { "HTTPS_PROXY", HTTPS_PROXY },
    { "ALL_PROXY", ALL_PROXY },
    { "no_proxy", NO_PROXY },
    { "https_proxy", HTTPS_PROXY },
    { "all_proxy", ALL_PROXY }
};

static inline int get_env_var_id(const char* name) {
    for(int i=0; i < sizeof(name_to_env_var_ids)/sizeof(NameToEnvVarID); i++) {
        if (strcmp(name, name_to_env_var_ids[i].name) == 0) {
            return name_to_env_var_ids[i].id;
        }
    }
    return ENV_VAR_UNKNOWN;
}

char * getenv_soloader(const char *var) {
    logv_debug("Requested getenv(\"%s\")", var);
    switch (get_env_var_id(var)) {
        case ENV_VAR_UNKNOWN:
            return NULL;
        case OPENSSL_CONF:
        case NO_PROXY:
        case HTTPS_PROXY:
        case ALL_PROXY:
            return NULL;
        default:
            logv_error("Requested unknown env var: %s", var);
            return NULL;
    }
}

int setenv_soloader(const char *name, const char *value, int overwrite) {
    logv_debug("Requested setenv(\"%s\", \"%s\", %i)", name, value, overwrite);
    return 0;
}
