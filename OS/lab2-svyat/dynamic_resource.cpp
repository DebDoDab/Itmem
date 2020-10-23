//
// Created by vadim on 23.10.20.
//

//-----------------------------------------------------------------------------
/*!
   \file
   \brief Non blocking TCP connection class
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include <string>
#include "dynamic_resource.h"


/* -- Defines ------------------------------------------------------------- */

using namespace std;


/* -- Types --------------------------------------------------------------- */

/* -- (Module) Global Variables ------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */
extern "C" unsigned int xcrc32 (const unsigned char *buf, int len, unsigned int init);


/* -- Implementation ------------------------------------------------------ */

DynamicResource::DynamicResource(const string& uri, const string& statusCode)
{
    this->uri = uri;
    this->content = "";
    this->contentType = "text/plain";
    this->statusCode = statusCode;
    this->hash = 1; //this prevents an immediate load empty resources
}


void  DynamicResource::setContentType(const std::string& contentType)
{
    this->contentType = contentType;
}

void  DynamicResource::setContent(const std::string& content)
{
    this->content = content;
    this->hash = xcrc32((const unsigned char *)content.c_str(), content.length(), 0xFFFFFFFFuL);
    if (this->hash == 0)
    {
        this->hash = 1; //value of 0 is reserved, thats why it shall never be a regular hash
    }
}