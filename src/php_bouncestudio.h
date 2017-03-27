#ifndef PHP_BOUNCESTUDIO_H
#define PHP_BOUNCESTUDIO_H 1

#define PHP_BOUNCESTUDIO_VERSION "3.7"
#define PHP_BOUNCESTUDIO_EXTNAME "BounceStudio API"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "BounceStudio.h"

zend_class_entry *bouncestudio_ce;

extern zend_module_entry bouncestudio_module_entry;
#define phpext_bouncestudio_ptr &bouncestudio_module_entry

#endif
