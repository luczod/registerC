#include <string.h>
#include "ini.h"
#include "configuration.h"

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

static int handler(void *user, const char *section, const char *name, const char *value);

bool configuration_ini(CONFIGURATION_T *conf)
{
    bool status = false;

    if (conf != NULL)
    {
        memset(conf, 0, sizeof(CONFIGURATION_T));
        status = true;
    }

    return status;
}

bool configuration_load(CONFIGURATION_T *conf)
{
    bool status = true;

    if (conf == NULL || ini_parse(CONFIGURATION_FILE_PATH, handler, conf) < 0)
    {
        status = false;
    }

    return status;
}

static int handler(void *user, const char *section, const char *name, const char *value)
{
    CONFIGURATION_T *pconfig = (CONFIGURATION_T *)user;

    if (MATCH("repository", "type"))
    {
        strncpy(pconfig->repository_type, value, CONFIGURATION_REPOSITORY_MAX_LEN);
    }
    else if (MATCH("controller", "type"))
    {
        strncpy(pconfig->controller_type, value, CONFIGURATION_CONTROLLER_MAX_LEN);
    }
    else
    {
        return 0; /* unknown section/name, error */
    }
    return 1;
}