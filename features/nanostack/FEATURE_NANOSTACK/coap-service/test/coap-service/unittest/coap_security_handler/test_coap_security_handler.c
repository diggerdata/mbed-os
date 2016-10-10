/*
 * Copyright (c) 2015-2016 ARM Limited. All Rights Reserved.
 */
#include "test_coap_security_handler.h"
#include "coap_security_handler.h"
#include <string.h>
#include "nsdynmemLIB_stub.h"
#include "mbedtls_stub.h"
#include "mbedtls/ssl.h"

static int send_to_socket(int8_t socket_id, uint8_t *address_ptr, uint16_t port, const unsigned char *buf, size_t len)
{

}

static int receive_from_socket(int8_t socket_id, unsigned char *buf, size_t len)
{

}

static void start_timer_callback(int8_t timer_id, uint32_t int_ms, uint32_t fin_ms)
{

}

static int timer_status_callback(int8_t timer_id)
{

}

bool test_thread_security_create()
{
    uint8_t buf[16];
    if( NULL != coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, NULL) )
        return false;

    if( NULL != coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback) )
        return false;

    nsdynmemlib_stub.returnCounter = 1;
    mbedtls_stub.expected_int = -1;
    if( NULL != coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback) )
        return false;

    mbedtls_stub.expected_int = 0;
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = -1;
    if( NULL != coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback) )
        return false;

    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    coap_security_destroy(handle);

    return true;
}

bool test_thread_security_destroy()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    coap_security_destroy(handle);
    return true;
}

bool test_coap_security_handler_connect()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    unsigned char pw = "pwd";
    coap_security_keys_t keys;
    keys._priv = &pw;
    keys._priv_len = 3;
    if( -1 != coap_security_handler_connect_non_blocking(NULL, true, DTLS, keys, 0, 1) )
        return false;
    mbedtls_stub.useCounter = true;
    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = -1;
    mbedtls_stub.retArray[1] = -1;
    mbedtls_stub.retArray[2] = -1;
    mbedtls_stub.retArray[3] = -1;
    mbedtls_stub.retArray[4] = -1;
    mbedtls_stub.retArray[5] = MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED;
    mbedtls_stub.retArray[6] = -1;
    mbedtls_stub.retArray[7] = -1;

    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = 0;
    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
//    mbedtls_stub.retArray[0] = 0;
    mbedtls_stub.retArray[1] = 0;
    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    simple_cookie_t c;
    memset(&c, 0, sizeof(simple_cookie_t));
    mbedtls_stub.cookie_obj = &c;
    memset(&mbedtls_stub.cookie_value, 1, 8);
    mbedtls_stub.cookie_len = 2;
    mbedtls_stub.counter = 0;
//    mbedtls_stub.retArray[0] = 0;
//    mbedtls_stub.retArray[1] = 0;
    mbedtls_stub.retArray[2] = 0;
    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    c.len = 8;
    memset(&c.value, 1, 8);
    mbedtls_stub.cookie_obj = &c;
    memset(&mbedtls_stub.cookie_value, 1, 8);

    mbedtls_stub.cookie_len = 8;
    mbedtls_stub.counter = 0;
//    mbedtls_stub.retArray[0] = 0;
//    mbedtls_stub.retArray[1] = 0;
//    mbedtls_stub.retArray[2] = 0;
    mbedtls_stub.retArray[3] = 0;
    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
//    mbedtls_stub.retArray[0] = 0;
//    mbedtls_stub.retArray[1] = 0;
//    mbedtls_stub.retArray[2] = 0;
//    mbedtls_stub.retArray[3] = 0;
    mbedtls_stub.retArray[4] = 0;
    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
//    mbedtls_stub.retArray[0] = 0;
//    mbedtls_stub.retArray[1] = 0;
//    mbedtls_stub.retArray[2] = 0;
//    mbedtls_stub.retArray[3] = 0;
//    mbedtls_stub.retArray[4] = 0;
    mbedtls_stub.retArray[6] = 0;
    mbedtls_stub.retArray[7] = 0;
    if( 1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[5] = MBEDTLS_ERR_SSL_BAD_HS_FINISHED;

    if( -1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[5] = HANDSHAKE_FINISHED_VALUE;

    if( 1 != coap_security_handler_connect_non_blocking(handle, true, DTLS, keys, 0, 1) )
        return false;

    coap_security_destroy(handle);
    return true;
}

bool test_coap_security_handler_continue_connecting()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    mbedtls_stub.useCounter = true;
    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED;
    mbedtls_stub.retArray[1] = -1;
    mbedtls_stub.retArray[2] = -1;

    if( -1 != coap_security_handler_continue_connecting(handle) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED;
    mbedtls_stub.retArray[1] = 0;
    mbedtls_stub.retArray[2] = 0;

    if( 1 != coap_security_handler_continue_connecting(handle) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = MBEDTLS_ERR_SSL_BAD_HS_FINISHED;

    if( MBEDTLS_ERR_SSL_BAD_HS_FINISHED != coap_security_handler_continue_connecting(handle) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = MBEDTLS_ERR_SSL_WANT_READ;

    if( 1 != coap_security_handler_continue_connecting(handle) )
        return false;

    mbedtls_stub.counter = 0;
    mbedtls_stub.retArray[0] = HANDSHAKE_FINISHED_VALUE_RETURN_ZERO;

    if( 0 != coap_security_handler_continue_connecting(handle) )
        return false;

    coap_security_destroy(handle);
    return true;
}

bool test_coap_security_handler_send_message()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    if( -1 != coap_security_handler_send_message(NULL, NULL, 0))
        return false;

    mbedtls_stub.expected_int = 6;
    unsigned char cbuf[6];
    if( 6 != coap_security_handler_send_message(handle, &cbuf, 6))
        return false;

    coap_security_destroy(handle);
    return true;
}

bool test_thread_security_send_close_alert()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    if( -1 != coap_security_send_close_alert(NULL))
        return false;

    mbedtls_stub.expected_int = 0;
    if( 0 != coap_security_send_close_alert(handle))
        return false;

    coap_security_destroy(handle);
    return true;
}

bool test_coap_security_handler_read()
{
    uint8_t buf[16];
    nsdynmemlib_stub.returnCounter = 2;
    mbedtls_stub.crt_expected_int = 0;
    coap_security_t *handle = coap_security_create(1,2,&buf,12,ECJPAKE,&send_to_socket, &receive_from_socket, &start_timer_callback, &timer_status_callback);
    if( NULL == handle )
        return false;

    if( -1 != coap_security_handler_read(NULL, NULL, 0))
        return false;

    mbedtls_stub.expected_int = 6;
    unsigned char cbuf[6];
    if( 6 != coap_security_handler_read(handle, &cbuf, 6))
        return false;

    coap_security_destroy(handle);
    return true;
}
