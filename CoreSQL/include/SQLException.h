#pragma once

// std
#include <string>
#include <stdexcept>
// CoreString
#include "CoreString/CoreString.h"
// CoreSQL
#include "CoreSQL_Utils.h"


NS_CORESQL_BEGIN

struct Exception
    : public std::runtime_error
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Exception(sqlite3 *const pConnection) :
        Exception(
            sqlite3_errmsg          (pConnection),
            sqlite3_extended_errcode(pConnection)
        )
    {
        // Empty...
    }

    Exception(const std::string &msg, int errorCode) :
        // Base class.
        std::runtime_error(
            CoreString::Format(
                "Error: (%s) - Code: (%d)",
                msg,
                errorCode
            )
        )
    {
        // Empty...
    }
};

NS_CORESQL_END
