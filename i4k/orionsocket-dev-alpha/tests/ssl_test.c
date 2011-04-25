#include <openssl/ssl.h>

int main(int argc, char** argv)
{
    SSL_CTX *ssl_ctx = NULL;
    SSL* ssl = NULL;
    SSL_load_error_strings();
    SSL_library_init();

    ssl_ctx = SSL_CTX_new(SSLv23_method());
    ssl = SSL_new(ssl_ctx);

    SSL_CTX_free(ssl_ctx);
    SSL_free(ssl);

    return 0;
}
