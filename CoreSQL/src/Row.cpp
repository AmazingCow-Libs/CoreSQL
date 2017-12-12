// Header
#include "../include/Row.h"

// Usings
USING_NS_CORESQL;

//------------------------------------------------------------------------//
// CTOR / DTOR                                                            //
//------------------------------------------------------------------------//
Row::Row(sqlite3_stmt *pStatement) noexcept :
    m_pStatement(pStatement)
{
    // Empty...
}

//------------------------------------------------------------------------//
// Helper Methods                                                         //
//------------------------------------------------------------------------//
sqlite3_stmt* Row::GetABI() const noexcept
{
    return m_pStatement;
}

