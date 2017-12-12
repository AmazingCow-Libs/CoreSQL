// Header
#include "../include/RowIterator.h"
// CoreSQL
#include "../include/Statement.h"

// Usings
USING_NS_CORESQL;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
RowIterator::RowIterator(const Statement &statement)
{
    if(statement.Step())
    {
        m_pStatementRef = &statement;
    }
}


//------------------------------------------------------------------------//
// Operators                                                              //
//------------------------------------------------------------------------//
RowIterator& RowIterator::operator ++()
{
    //COWTODO(n2omatt): Should we handle the nullptr???

    if(!m_pStatementRef->Step())
        m_pStatementRef = nullptr;

    return *this;
}

bool RowIterator::operator !=(const RowIterator &other) const noexcept
{
    return m_pStatementRef != other.m_pStatementRef;
}

Row RowIterator::operator *() const noexcept
{
    COREASSERT_VERIFY(m_pStatementRef, "Cannot dereference null iterator");
    return Row(m_pStatementRef->GetABI());
}

//----------------------------------------------------------------------------//
// std Range Functions                                                        //
//----------------------------------------------------------------------------//
RowIterator CoreSQL::begin(const Statement &statement)
{
    return RowIterator(statement);
}

RowIterator CoreSQL::end(const Statement &statement) noexcept
{
    return RowIterator();
}
