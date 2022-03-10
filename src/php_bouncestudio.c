
#include "php_bouncestudio.h"

/* {{{ BounceStudio::__construct(string license, string message, [string ignoreAddresses])
   Init the object */
PHP_METHOD(BounceStudio, __construct)
{
    zend_string *license = NULL;
    zend_string *message = NULL;
    zend_string *ignoreAddresses = NULL;
    zend_string *email = NULL;
    int code = 0;
    char *bounce;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "SS|S", &license, &message, &ignoreAddresses) == FAILURE) {
        return;
    }

    // set the properties
    zend_object *obj = Z_OBJ_P(getThis());
    zend_update_property_string(bouncestudio_ce, obj, "license", sizeof("license") -1, license->val);
    zend_update_property_string(bouncestudio_ce, obj, "message", sizeof("message") - 1, message->val);

    if (ignoreAddresses) {
        zend_update_property_string(bouncestudio_ce, obj, "ignoreAddresses", sizeof("ignoreAddresses") - 1, ignoreAddresses->val);
    } else {
        ignoreAddresses = zend_string_init("", 0, 0);
    }

    // do the bounce check
    code = bsBounceCheck(message->val, &bounce, ignoreAddresses->val, license->val);
    email = strpprintf(0, "%s", bounce);

    // save the results for later
    zend_update_property_long(bouncestudio_ce, obj, "code", sizeof("code") - 1, code);
    zend_update_property_string(bouncestudio_ce, obj, "email", sizeof("email") - 1, email->val);

    // clean up
    zend_string_free(license);
    zend_string_free(message);
    zend_string_free(ignoreAddresses);
    zend_string_free(email);
}
/* }}} */

/* {{{ BounceStudio::getBounceCode()
   Returns the bounce code */
PHP_METHOD(BounceStudio, getBounceCode)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    int code;

    str = zend_read_property(bouncestudio_ce, obj, "code", strlen("code"), 1, &rv);
    code = zval_get_long(str);

    RETURN_LONG(code);
}
/* }}} */

/* {{{ BounceStudio::getBounceEmail()
   Returns the bounced email address */
PHP_METHOD(BounceStudio, getBounceEmail)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *email = NULL;

    str = zend_read_property(bouncestudio_ce, obj, "email", strlen("email"), 1, &rv);
    email = strpprintf(0, "%s", Z_STRVAL_P(str));

    RETURN_STR(email);
}
/* }}} */

/* {{{ BounceStudio::getBody()
   Returns the email body */
PHP_METHOD(BounceStudio, getBody)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *body;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    // get the email body
    bsGetBody(message->val, &body);

    // release and
    zend_string_free(message);

    RETURN_STRING(body);
}
/* }}} */

/* {{{ BounceStudio::getHeaders()
   Returns the specified header */
PHP_METHOD(BounceStudio, getHeaders)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetHeader(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getHeader(string name)
   Returns the specified header */
PHP_METHOD(BounceStudio, getHeader)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    zend_string *name = NULL;
    char *header;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
        return;
    }

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetCustomHeader(message->val, &header, name->val);

    zend_string_free(message);
    zend_string_free(name);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getOriginalHeader(string name)
   Returns the specified header from the original email */
PHP_METHOD(BounceStudio, getOriginalHeader)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    zend_string *name = NULL;
    char *header;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
        return;
    }

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetOrigCustomHeader(message->val, &header, name->val);

    zend_string_free(message);
    zend_string_free(name);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getFromAddress()
   Returns the from email address */
PHP_METHOD(BounceStudio, getFromAddress)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetFromAddress(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getFromName()
   Returns the from name */
PHP_METHOD(BounceStudio, getFromName)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetFromFriendlyName(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getToAddress()
   Returns the to email address */
PHP_METHOD(BounceStudio, getToAddress)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetToAddress(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getToName()
   Returns the to name */
PHP_METHOD(BounceStudio, getToName)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetToFriendlyName(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getReplyToAddress()
   Returns the reply-to email address */
PHP_METHOD(BounceStudio, getReplyToAddress)
{
    zval rv;
    zval *str;    
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetReplyToAddress(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getReplyToName()
   Returns the reply-to name */
PHP_METHOD(BounceStudio, getReplyToName)
{
    zval rv;
    zval *str;
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetReplyToFriendlyName(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

/* {{{ BounceStudio::getSubject()
   Returns the subject */
PHP_METHOD(BounceStudio, getSubject)
{
    zval rv;
    zval *str;    
    zend_object *obj = Z_OBJ_P(getThis());
    zend_string *message = NULL;
    char *header;

    str = zend_read_property(bouncestudio_ce, obj, "message", strlen("message"), 1, &rv);
    message = strpprintf(0, "%s", Z_STRVAL_P(str));

    bsGetSubject(message->val, &header);

    zend_string_free(message);

    RETURN_STRING(header);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, license)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, ignoreAddresses)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getBounceCode, 0, 0, 0)
    ZEND_ARG_INFO(0, email)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getBounceEmail, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getBody, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getHeaders, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getHeader, 0, 0, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getOriginalHeader, 0, 0, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getFromAddress, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getFromName, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getToAddress, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getToName, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getReplyToAddress, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getReplyToName, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getSubject, 0, 0, 0)
ZEND_END_ARG_INFO()

const zend_function_entry bouncestudio_methods[] = {
    PHP_ME(BounceStudio, __construct, arginfo___construct, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getBounceCode, arginfo_getBounceCode, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getBounceEmail, arginfo_getBounceEmail, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getBody, arginfo_getBody, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getHeaders, arginfo_getHeaders, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getHeader, arginfo_getHeader, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getOriginalHeader, arginfo_getOriginalHeader, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getFromAddress, arginfo_getFromAddress, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getFromName, arginfo_getFromName, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getToAddress, arginfo_getToAddress, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getToName, arginfo_getToName, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getReplyToAddress, arginfo_getReplyToAddress, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getReplyToName, arginfo_getReplyToName, ZEND_ACC_PUBLIC)
    PHP_ME(BounceStudio, getSubject, arginfo_getSubject, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(bouncestudio)
{
    zend_class_entry temp_ce;
    INIT_CLASS_ENTRY(temp_ce, "BounceStudio", bouncestudio_methods);
    bouncestudio_ce = zend_register_internal_class(&temp_ce);

    // Declare the internal properties for the class
    zend_declare_property_string(bouncestudio_ce, "license", sizeof("license")-1, "", ZEND_ACC_PRIVATE);
    zend_declare_property_string(bouncestudio_ce, "message", sizeof("message")-1, "", ZEND_ACC_PRIVATE);
    zend_declare_property_string(bouncestudio_ce, "ignoreAddresses", sizeof("ignoreAddresses")-1, "", ZEND_ACC_PRIVATE);

    zend_declare_property_long(bouncestudio_ce, "code", sizeof("code")-1, 0, ZEND_ACC_PRIVATE);
    zend_declare_property_string(bouncestudio_ce, "email", sizeof("email")-1, "", ZEND_ACC_PRIVATE);

    // init bounce studio
    bsBounceStudio_init();

    return SUCCESS;
}

zend_module_entry bouncestudio_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_BOUNCESTUDIO_EXTNAME,
    bouncestudio_methods,
    PHP_MINIT(bouncestudio),
    NULL,
    NULL,
    NULL,
    NULL,

#if ZEND_MODULE_API_NO >= 20010901
    PHP_BOUNCESTUDIO_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BOUNCESTUDIO
ZEND_GET_MODULE(bouncestudio)
#endif