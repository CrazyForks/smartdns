/*************************************************************************
 *
 * Copyright (C) 2018-2025 Ruilin Peng (Nick) <pymumu@gmail.com>.
 *
 * smartdns is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * smartdns is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

struct http_head;
struct http_head_fields;
struct http_params;

typedef enum HTTP_VERSION {
	HTTP_VERSION_INVALID = 0,
	HTTP_VERSION_1_1,
	HTTP_VERSION_2_0,
	HTTP_VERSION_3_0,
} HTTP_VERSION;

typedef enum HTTP_METHOD {
	HTTP_METHOD_INVALID = 0,
	HTTP_METHOD_GET,
	HTTP_METHOD_HEAD,
	HTTP_METHOD_POST,
	HTTP_METHOD_PUT,
	HTTP_METHOD_DELETE,
	HTTP_METHOD_TRACE,
	HTTP_METHOD_CONNECT,
} HTTP_METHOD;

typedef enum HTTP_HEAD_TYPE {
	HTTP_HEAD_INVALID = 0,
	HTTP_HEAD_REQUEST = 1,
	HTTP_HEAD_RESPONSE = 2,
} HTTP_HEAD_TYPE;

struct http_head *http_head_init(int buffsize, HTTP_VERSION version);

const char *http_method_str(HTTP_METHOD method);

int http_head_add_fields(struct http_head *http_head, const char *name, const char *value);

int http_head_add_param(struct http_head *http_head, const char *name, const char *value);

int http_head_set_url(struct http_head *http_head, const char *url);

int http_head_set_httpversion(struct http_head *http_head, const char *version);

int http_head_set_httpcode(struct http_head *http_head, int code, const char *msg);

int http_head_set_head_type(struct http_head *http_head, HTTP_HEAD_TYPE head_type);

int http_head_set_method(struct http_head *http_head, HTTP_METHOD method);

int http_head_set_data(struct http_head *http_head, const void *data, int len);

HTTP_HEAD_TYPE http_head_get_head_type(struct http_head *http_head);

HTTP_METHOD http_head_get_method(struct http_head *http_head);

const char *http_head_get_url(struct http_head *http_head);

const char *http_head_get_httpversion(struct http_head *http_head);

int http_head_get_httpcode(struct http_head *http_head);

const char *http_head_get_httpcode_msg(struct http_head *http_head);

const unsigned char *http_head_get_data(struct http_head *http_head);

int http_head_get_data_len(struct http_head *http_head);

struct http_head_fields *http_head_first_fields(struct http_head *http_head);

struct http_head_fields *http_head_next_fields(struct http_head_fields *fields);

const char *http_head_get_fields_value(struct http_head *http_head, const char *name);

const char *http_head_fields_get_name(struct http_head_fields *fields);

const char *http_head_fields_get_value(struct http_head_fields *fields);

const char *http_head_get_params_value(struct http_head *http_head, const char *name);

int http_head_lookup_fields(struct http_head_fields *fields, const char **name, const char **value);

/*
 * Returns:
 *  >=0  - success http data len
 *  -1   - Incomplete request
 *  -2   - parse failed
 *  -3   - buffer is small
 */
int http_head_parse(struct http_head *http_head, const unsigned char *data, int data_len);

int http_head_serialize(struct http_head *http_head, void *buffer, int buffer_len);

void http_head_destroy(struct http_head *http_head);

#ifdef __cplusplus
}
#endif

#endif // !HTTP_PARSER_H
