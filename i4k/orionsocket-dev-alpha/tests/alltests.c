#include <stdio.h>
#include "CUnit/Basic.h"
#include "CUnit/CUCurses.h"   /* only on systems having curses */
#include <orion/socket/http.h>
#include <orion/socket/cookie.h>

#define TRUE 1
#define FALSE 0


orion_httpRequest* req = NULL;

int init_suite_socket() 
{
    return 0;
}

int clean_suite_socket() 
{
    return 0; 
}

int init_suite_cookie()
{
    return 0;
}

int clean_suite_cookie()
{
    return 0;
}

void test_parseCookie()
{
    orion_cookie* c = NULL;
    char set_cookie1[2048];
    
    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "PREF=ID=e52d156f7713a539:FF=0:TM=1294551749:LM=1294551749:S=oJ5bYafPIDsLW2zc; expires=Tue, 08-Jan-2013 05:42:29 GMT; path=/; domain=.google.com; httpOnly");

    orion_initCookie(&c);
    orion_parseCookie(c, set_cookie1);

    CU_ASSERT_STRING_EQUAL(c->name, "PREF");
    CU_ASSERT_STRING_EQUAL(c->value, "ID=e52d156f7713a539:FF=0:TM=1294551749:LM=1294551749:S=oJ5bYafPIDsLW2zc");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_STRING_EQUAL(c->domain, ".google.com");
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_STRING_EQUAL(c->path, "/");
    CU_ASSERT(c->httpOnly == 1);
    CU_ASSERT(c->secure == 0);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_STRING_EQUAL(c->expires,"Tue, 08-Jan-2013 05:42:29 GMT");

    orion_cleanupCookie(c);

    orion_initCookie(&c);
    bzero(set_cookie1,2048);

    strcpy(set_cookie1,"CUSTOMER=WILE_E_COYOTE; path=/; expires=Wednesday, 09-Nov-99 23:12:40 GMT");
    orion_parseCookie(c, set_cookie1);

    /* Testing cookie */
    CU_ASSERT_STRING_EQUAL(c->name, "CUSTOMER");
    CU_ASSERT_STRING_EQUAL(c->value, "WILE_E_COYOTE");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_PTR_NULL(c->domain);
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_STRING_EQUAL(c->path, "/");
    CU_ASSERT(c->secure == 0);
    CU_ASSERT(c->httpOnly == 0);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_STRING_EQUAL(c->expires, "Wednesday, 09-Nov-99 23:12:40 GMT");

    orion_cleanupCookie(c);

    orion_initCookie(&c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "PART_NUMBER=ROCKET_LAUNCHER_0001; path=/");

    orion_parseCookie(c, set_cookie1);

    /* Testing cookie */
    CU_ASSERT_STRING_EQUAL(c->name, "PART_NUMBER");
    CU_ASSERT_STRING_EQUAL(c->value, "ROCKET_LAUNCHER_0001");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_PTR_NULL(c->domain);
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_STRING_EQUAL(c->path, "/");
    CU_ASSERT(c->secure == 0);
    CU_ASSERT(c->httpOnly == 0);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_PTR_NULL(c->expires);

    orion_cleanupCookie(c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "SHIPPING=FEDEX; path=/foo");

    orion_initCookie(&c);
    orion_parseCookie(c, set_cookie1);

    /* Testing cookie */
    CU_ASSERT_STRING_EQUAL(c->name, "SHIPPING");
    CU_ASSERT_STRING_EQUAL(c->value, "FEDEX");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_PTR_NULL(c->domain);
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_STRING_EQUAL(c->path, "/foo");
    CU_ASSERT(c->secure == 0);
    CU_ASSERT(c->httpOnly == 0);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_PTR_NULL(c->expires);

    orion_cleanupCookie(c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "ORIONSOCKET=1.1.0; domain=.universemachine.wordpress.com; path=/orionsocket; expires=Tuesday, 12-Dec-2012 12:12:12 GMT; secure; httpOnly");

    orion_initCookie(&c);
    orion_parseCookie(c, set_cookie1);

    /* Testing cookie */
    CU_ASSERT_STRING_EQUAL(c->name, "ORIONSOCKET");
    CU_ASSERT_STRING_EQUAL(c->value, "1.1.0");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_STRING_EQUAL(c->domain, ".universemachine.wordpress.com");
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_STRING_EQUAL(c->path, "/orionsocket");
    CU_ASSERT(c->secure == 1);
    CU_ASSERT(c->httpOnly == 1);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_STRING_EQUAL(c->expires, "Tuesday, 12-Dec-2012 12:12:12 GMT");

    orion_cleanupCookie(c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "ORIONSOCKET");

    orion_initCookie(&c);
    orion_parseCookie(c, set_cookie1);

    CU_ASSERT_STRING_EQUAL(c->name, "ORIONSOCKET");
    CU_ASSERT_PTR_NULL(c->value);
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_PTR_NULL(c->domain);
    CU_ASSERT_PTR_NULL(c->path);
    CU_ASSERT(c->secure == 0);
    CU_ASSERT(c->httpOnly == 0);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_PTR_NULL(c->expires);

    orion_cleanupCookie(c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "LANGUAGE=C; Comment=Don't be afraid.; domain=.c-faq.com; path=/struct; httpOnly");

    orion_initCookie(&c);
    orion_parseCookie(c, set_cookie1);
    
    CU_ASSERT_STRING_EQUAL(c->name, "LANGUAGE");
    CU_ASSERT_STRING_EQUAL(c->value, "C");
    CU_ASSERT_STRING_EQUAL(c->comment, "Don't be afraid.");
    CU_ASSERT_STRING_EQUAL(c->domain, ".c-faq.com");
    CU_ASSERT_STRING_EQUAL(c->path, "/struct");
    CU_ASSERT(c->secure == 0);
    CU_ASSERT(c->httpOnly == 1);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_PTR_NULL(c->expires);

    orion_cleanupCookie(c);

    bzero(set_cookie1, 2048);
    strcpy(set_cookie1, "PHILOSOPHY=TH3 M4TR1X; CommentURL=http://en.wikipedia.org/wiki/The_Matrix; domain=.whatisthematrix.warnerbros.com; httpOnly; secure");
    orion_initCookie(&c);

    orion_parseCookie(c, set_cookie1);

    /* Testing cookie */
    CU_ASSERT_STRING_EQUAL(c->name, "PHILOSOPHY");
    CU_ASSERT_STRING_EQUAL(c->value, "TH3 M4TR1X");
    CU_ASSERT_PTR_NULL(c->comment);
    CU_ASSERT_STRING_EQUAL(c->commentURL, "http://en.wikipedia.org/wiki/The_Matrix");
    CU_ASSERT_STRING_EQUAL(c->domain, ".whatisthematrix.warnerbros.com");
    CU_ASSERT_PTR_NULL(c->max_age);
    CU_ASSERT_PTR_NULL(c->path);
    CU_ASSERT(c->secure == 1);
    CU_ASSERT(c->httpOnly == 1);
    CU_ASSERT_PTR_NULL(c->version);
    CU_ASSERT_PTR_NULL(c->expires);

    orion_cleanupCookie(c);
}

void test_getHostByName_ip(void)
{

#define IPv4_LEN ORION_IPv4_MAXLENGTH

    int error = ORION_OK;
    char ip[IPv4_LEN] = "127.0.0.1";
    char buffer[IPv4_LEN];

    error = orion_getHostByName(ip, buffer);
    CU_ASSERT(error == ORION_OK);
    CU_ASSERT_STRING_EQUAL(ip, buffer);
   
    bzero(ip, IPv4_LEN);
    bzero(buffer, IPv4_LEN);

    strncpy(ip, "10.10.10.10", IPv4_LEN);

    error = orion_getHostByName(ip, buffer);
    CU_ASSERT(error == ORION_OK);
    CU_ASSERT_STRING_EQUAL(ip, buffer);

    bzero(ip, IPv4_LEN);
    bzero(buffer, IPv4_LEN);
    /* INVALID IP, #FAILLL */
    strncpy(ip, "256.256.256.256", IPv4_LEN);

    error = orion_getHostByName(ip, buffer);
    CU_ASSERT(error == ORION_EAI_NONAME);
    CU_ASSERT_STRING_NOT_EQUAL(ip, buffer);

    bzero(ip, IPv4_LEN);
    bzero(buffer, IPv4_LEN);

    strncpy(ip, "255.255.255.255", IPv4_LEN);

    error = orion_getHostByName(ip, buffer);
    CU_ASSERT(error == ORION_OK);
    CU_ASSERT_STRING_EQUAL(ip, buffer);
    
}

void orion_getHostByName_Domain()
{
    const char* domain = "www.bugsec.com.br";
    char buffer[ORION_DNS_MAXLENGTH];
    _i8 error;

    error = orion_getHostByName(domain, buffer);

    CU_ASSERT(error = ORION_OK);
    CU_ASSERT_STRING_EQUAL("189.38.80.195", buffer);
}

int main()
{
   CU_pSuite pSuite = NULL, pCookieSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("OrionSocket tests: socket.h", init_suite_socket, clean_suite_socket);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "orion_getHostByName()", test_getHostByName_ip)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pCookieSuite = CU_add_suite("OrionSocket tests: cookie.h", init_suite_cookie, clean_suite_cookie);
   if (NULL == pCookieSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pCookieSuite, "orion_parseCookie", test_parseCookie)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* Run all tests using the basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   /* Run all tests using the automated interface */
   /* CU_automated_run_tests(); */
   /* CU_list_tests_to_file(); */

   /* Run all tests using the curses interface */
   /* (only on systems having curses) */
   CU_curses_run_tests();

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}

