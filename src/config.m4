PHP_ARG_ENABLE(bouncestudio, whether to enable bouncestudio support,
[ --enable-bouncestudio   Enable bouncestudio support])

if test "$PHP_BOUNCESTUDIO" = "yes"; then
  AC_DEFINE(HAVE_BOUNCESTUDIO, 1, [Whether you have bouncestudio support])
  PHP_SUBST(SAMPLE_SHARED_LIBADD)
  PHP_NEW_EXTENSION(bouncestudio, php_bouncestudio.c, $ext_shared)
fi
