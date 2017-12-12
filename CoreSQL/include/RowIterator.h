
#pragma once

// CoreSQL
#include "CoreSQL_Utils.h"
#include "SQLException.h"
#include "Row.h"

NS_CORESQL_BEGIN

//-----------------------------------------------------------------------------
// Forward Declarations
class Statement;


class RowIterator
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    RowIterator() noexcept = default;
    explicit RowIterator(const Statement &statement);


    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
public:
    RowIterator& operator ++();

    bool operator !=(const RowIterator &other) const noexcept;

    Row operator *() const noexcept;

    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    const Statement *m_pStatementRef = nullptr;
};

//----------------------------------------------------------------------------//
// std Range Functions                                                        //
//----------------------------------------------------------------------------//
RowIterator begin(const Statement &statement);
RowIterator end  (const Statement &statement) noexcept;

NS_CORESQL_END
