#pragma once

//----------------------------------------------------------------------------//
// Namespaces                                                                 //
//----------------------------------------------------------------------------//
// All classes of this core is placed inside this namespace.
// We use MACROS so is easier to change if needed.
// Is (in our opinion) more explicit.
// And finally the editors will not reformat the code.
#define NS_CORESQL_BEGIN namespace CoreSQL {
#define NS_CORESQL_END   }
#define USING_NS_CORESQL using namespace CoreSQL


//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//
#define COW_CORESQL_VERSION_MAJOR    "0"
#define COW_CORESQL_VERSION_MINOR    "1"
#define COW_CORESQL_VERSION_REVISION "0"

#define COW_CORESQL_VERSION       \
    COW_CORESQL_VERSION_MAJOR "." \
    COW_CORESQL_VERSION_MINOR "." \
    COW_CORESQL_VERSION_REVISION


//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//
// sqlite3
#include "sqlite3.h"
