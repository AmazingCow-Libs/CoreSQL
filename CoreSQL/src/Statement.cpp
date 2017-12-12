// Header
#include "../include/Statement.h"

// Usings
USING_NS_CORESQL;


//------------------------------------------------------------------------//
// CTOR / DTOR                                                            //
//------------------------------------------------------------------------//
Statement::Statement(
    const Connection  &connection,
    const std::string &statement)
{
    Prepare(connection, statement);
}


//------------------------------------------------------------------------//
// Operators                                                              //
//------------------------------------------------------------------------//
Statement::operator bool() const noexcept
{
    return static_cast<bool>(m_handle);
}


//------------------------------------------------------------------------//
// Prepare Methods                                                        //
//------------------------------------------------------------------------//
void Statement::Prepare(
    const Connection &connection,
    const std::string &statement)
{
    auto result = sqlite3_prepare_v2(
        connection.GetABI(),
        statement.c_str(),
        -1,
        m_handle.Set(),
        nullptr
    );

    if(result != SQLITE_OK)
        connection.ThrowLastError();
}


//------------------------------------------------------------------------//
// Step Methods                                                           //
//------------------------------------------------------------------------//
bool Statement::Step() const
{
    switch(sqlite3_step(GetABI()))
    {
        case SQLITE_ROW  : return true;
        case SQLITE_DONE : return false;

        default:
            ThrowLastError();
    }

    return false;
}


//------------------------------------------------------------------------//
// Bind Methods                                                           //
//------------------------------------------------------------------------//
void Statement::Bind(const int index, const int value) const
{
    COREASSERT_VERIFY(index >= 1, "Invalid index (%d)", index);

    if(sqlite3_bind_int(GetABI(), index, value) != SQLITE_OK)
        ThrowLastError();
}

void Statement::Bind(const int index, const double value) const
{
    COREASSERT_VERIFY(index >= 1, "Invalid index (%d)", index);

    if(sqlite3_bind_double(GetABI(), index, value) != SQLITE_OK)
        ThrowLastError();
}

void Statement::Bind(const int index, const std::string &value) const
{
    COREASSERT_VERIFY(index >= 1, "Invalid index (%d)", index);

    if(sqlite3_bind_text(
        GetABI(),
        index,
        value.c_str(),
        value.size(),
        SQLITE_STATIC) != SQLITE_OK)
    {
        ThrowLastError();
    }
}

void Statement::Bind(const int index, std::string &&value) const
{
    COREASSERT_VERIFY(index >= 1, "Invalid index (%d)", index);

    if(sqlite3_bind_text(
        GetABI(),
        index,
        value.c_str(),
        value.size(),
        SQLITE_TRANSIENT) != SQLITE_OK)
    {
        ThrowLastError();
    }
}


//------------------------------------------------------------------------//
// Helper Methods                                                         //
//------------------------------------------------------------------------//
sqlite3_stmt* Statement::GetABI() const noexcept { return m_handle.Get(); }


//------------------------------------------------------------------------//
// Private Methods                                                        //
//------------------------------------------------------------------------//
void Statement::ThrowLastError() const
{
    //GetABI();
    throw Exception(sqlite3_db_handle(m_handle.Get()));
}

