#pragma once

// CoreSQL
#include "CoreSQL_Utils.h"
#include "SQLException.h"
#include "Reader.h"

NS_CORESQL_BEGIN

class Row
    : public Reader<Row>
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Row(sqlite3_stmt *pStatement) noexcept;


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
public:
    sqlite3_stmt* GetABI() const noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    sqlite3_stmt *m_pStatement = nullptr;
};



NS_CORESQL_END
