#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/http.h"
#include "../src/types.h"

#define SAY(format, x...) \
        fprintf(stderr, format, x)
#define SAY2(x) \
        fprintf(stderr, x)
        

#define IS_ON(b) \
        b ? "ON" : "OFF"
#define SAFE_PRINT(format, x) \
        if (x) \
            SAY(format, x)

#define DEBUG_COOKIE(c) \
        SAY2("=== DEBUG COOKIE ===\n"); \
        SAFE_PRINT("NAME=%s\n", c->name); \
        SAFE_PRINT("VALUE=%s\n", c->value); \
        SAFE_PRINT("COMMENT=%s\n", c->comment); \
        SAFE_PRINT("DOMAIN=%s\n", c->domain); \
        SAFE_PRINT("PATH=%s\n", c->path); \
        SAFE_PRINT("MAX-AGE=%s\n", c->max_age); \
        SAFE_PRINT("SECURE=%s\n", IS_ON(c->secure)); \
        SAFE_PRINT("VERSION=%s\n", c->version); \
        SAFE_PRINT("EXPIRES=%s\n", c->expires);


enum cookie_av_token {
    COOKIE_AV_COMMENT = 1,
    COOKIE_AV_DOMAIN,
    COOKIE_AV_MAXAGE,
    COOKIE_AV_PATH,
    COOKIE_AV_SECURE,
    COOKIE_AV_HTTPONLY,
    COOKIE_AV_VERSION,
    COOKIE_AV_EXPIRES
};

void parse_cookie(orion_cookie*,char*);
_u8 isValidCookieAttr(const char*);
void orion_setCookieAttrTk(orion_cookie* c, _u8 attr, const char* value);

char* ltrim(char* buffer)
{
    _u32 count = 0, len, i;

    len = strlen(buffer);
    while (*buffer == 0x20)
    {
        memmove(buffer, buffer+1, strlen(buffer+1));
        count++;
    }

    for (i = len - count; i < len; i++)
        buffer[i] = '\0';
    
    return buffer;
}

int main()
{
    orion_cookie *c = NULL;

    orion_initCookie(&c);

    parse_cookie(c, "PREF=ID=e52d156f7713a539:FF=0:TM=1294551749:LM=1294551749:S=oJ5bYafPIDsLW2zc; expires=Tue, 08-Jan-2013 05:42:29 GMT; path=/; domain=.google.com; httpOnly");

    DEBUG_COOKIE(c);

    orion_cleanupCookie(c);

    return 0;
}

_u8 isValidCookieAttr(const char* opt)
{
    _u8 i;

    typedef struct {
        char name[10];
        _u8 attr;
    } cookie_av2;

#define N_COOKIE_AV     7

    /**
     * Structure for optimized code.
     * In this mode we have less string comparison routines
     */
    static cookie_av2 cookiePair[N_COOKIE_AV] = {
        {"comment", COOKIE_AV_COMMENT},
        {"domain",  COOKIE_AV_DOMAIN},
        {"max-age", COOKIE_AV_MAXAGE},
        {"path",    COOKIE_AV_PATH},
        {"secure",  COOKIE_AV_SECURE},
        {"httpOnly",COOKIE_AV_HTTPONLY}, 
        {"version", COOKIE_AV_VERSION},
        {"expires", COOKIE_AV_EXPIRES}
    };

    for (i = 0; i < N_COOKIE_AV; i++)
    {
        if (!strcasecmp(cookiePair[i].name, opt))
            return cookiePair[i].attr;            
    }

    return -1;
}

void orion_setCookieAttrTk(orion_cookie* c, _u8 attr, const char* value)
{
    switch (attr)
    {
    case COOKIE_AV_COMMENT:
        c->comment = strdup(value);
        break;
    case COOKIE_AV_DOMAIN:
        c->domain = strdup(value);
        break;
    case COOKIE_AV_PATH:
        c->path = strdup(value);
        break;
    case COOKIE_AV_MAXAGE:
        c->max_age = strdup(value);
        break;
    case COOKIE_AV_SECURE:
        c->secure = strdup(value);
        break;
    case COOKIE_AV_VERSION:
        c->version = strdup(value);
        break;
    case COOKIE_AV_EXPIRES:
        c->expires = strdup(value);
        break;
    }
}

void parse_cookie(orion_cookie* c, char* cookie)
{
    char delim, ck, *name = NULL, *buffer = strdup(cookie);
    _i8 token, done = 0, cookie_tk;
    ssize_t i;

    if (!strlen(buffer))
        return;
    /**
     * Parsing Set-cookie string according with RFC 2109
     *
     * NAME=VALUE SHALL appear in the begin
     */
    i = strcspn(buffer, "=;");
    
    delim = buffer[i];
    buffer[i] = '\0';
    c->name = strdup(buffer);
#ifdef DEBUG
    SAY("NAME=%s\n", c->name);
#endif

    buffer += i + 1;

    if (delim == '=')
    {
        /* getting the value */
        i = strcspn(buffer, ";");
        if (i > 0)
        {
            delim = buffer[i];
            buffer[i] = '\0';
            c->value = strdup(buffer);
#ifdef DEBUG
            SAY("VALUE=%s\n", c->value);
#endif
            buffer += i + 1;
        }
    } 
    
    /* getting other options in any order */

#define T_INIT    0x01
#define T_ENDOPT  0x02
#define T_EQUAL   0x04
#define T_NAMEVAL 0x08

    token = T_NAMEVAL;
    i = 0;
    while (!done)
    {
        ck = buffer[i];
        switch (ck)
        {
        case '\0':
            /* end of string, getting what we need and exit ... */
            done = 1;
        case ';':
            /* ensures that the "name" was already caught. */
            if (token == (T_NAMEVAL | T_EQUAL))
            {
                buffer[i] = '\0';
#ifdef DEBUG
                SAY("VALUE FOUND1: %s\n", buffer);
#endif
                orion_setCookieAttrTk(c, cookie_tk, buffer);
                cookie_tk = 0;
                buffer += i + 1;
                i = 0;
            } else 
            if (token == T_NAMEVAL) 
            {
                buffer[i] = '\0';

                if ((cookie_tk = isValidCookieAttr(ltrim(buffer))) == -1)
                {
                    SAY("I DO NOT KNOW WHAT TO DO WITH THIS SHIT '%s'!\n", buffer);
                    return;
                }

                orion_setCookieAttrTk(c, cookie_tk, NULL);
                cookie_tk = 0;
#ifdef DEBUG
                SAY("NAME FOUND in ';' case: %s\n", buffer);
#endif
                buffer += i + 1;
                i = 0;
            }
            token = T_ENDOPT;
            break;
        case '=':
            if (token == T_NAMEVAL)
            {
                buffer[i] = '\0';
                
                if ((cookie_tk = isValidCookieAttr(ltrim(buffer))) == -1)
                {
                    SAY("attribute '%s' inexistent in Cookie RFC 2109 ... WTF\n", buffer);
                    SAY2("I DONT KNOW WHAT TO DO, FUCK!\n");
                    return;
                }

                buffer += i + 1;
                i = 0;
                token = T_NAMEVAL | T_EQUAL;
            } else
                token = T_EQUAL;

            break;
        default:
            token = token == T_ENDOPT ? T_NAMEVAL : token | T_NAMEVAL;
        }

        i++;
    }
}
