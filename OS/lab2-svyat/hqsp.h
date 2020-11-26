//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_HQSP_H
#define LAB2_SVYAT_HQSP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


//returns 0 (false) or 1 (true)
int hqsp_is_method_get(const char * request);

//returns 0 (false) or 1 (true)
int hqsp_is_method_post(const char * request);

//get "string-pointer" to requested resource
//x will be set to the start of the string
//returns length of string
int hqsp_get_resource(const char * request, const char ** x);

//get "string-pointer" to requested resource
//x will be set to the start of the string
//returns length of string
int hqsp_get_post_content(const char * request, unsigned requestLen, const char ** x);

int hqsp_get_post_value(const char * request, unsigned requestLen, const char* parameter, const char ** x);


#ifdef __cplusplus
} /* end of extern "C" */
#endif


#endif //LAB2_SVYAT_HQSP_H
