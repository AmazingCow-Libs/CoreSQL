#pragma once

// std
#include <string>
// CoreSQL
#include "CoreSQL_Utils.h"
#include "Connection.h"
#include "Statement.h"

NS_CORESQL_BEGIN

template <typename ...Values>
void Execute(
    const Connection  &connection,
    const std::string &statement,
    Values && ...values)
{
    Statement(
        connection,
        statement,
        std::forward<Values>(values)...
    ).Execute();
}
NS_CORESQL_END
