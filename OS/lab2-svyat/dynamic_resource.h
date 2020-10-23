//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_DYNAMIC_RESOURCE_H
#define LAB2_SVYAT_DYNAMIC_RESOURCE_H

#include <string>
#include <stdint.h>


class DynamicResource {
public:
    DynamicResource(const std::string& uri, const std::string& statusCode="200 OK");
    void setContentType(const std::string& contentType);
    void setContent(const std::string& content);

    std::string uri;
    std::string content;
    std::string contentType;
    std::string statusCode;
    uint32_t hash;
};


#endif //LAB2_SVYAT_DYNAMIC_RESOURCE_H