// Header
#include "../include/Connection.h"

// Usings
USING_NS_CORESQL;


//----------------------------------------------------------------------------//
// Static Methods                                                             //
//----------------------------------------------------------------------------//
Connection Connection::Memory()
{
    return Connection(":memory:");
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Connection::Connection(const std::string &connStr)
{
    Open(connStr);
}


//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//
Connection::operator bool() const noexcept
{
    return static_cast<bool>(m_handle);
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void Connection::Open(const std::string &connStr)
{
    auto temp = Connection();

    if(sqlite3_open(connStr.c_str(), temp.m_handle.Set()) != SQLITE_OK)
        temp.ThrowLastError();

    swap(m_handle, temp.m_handle);
}

long long Connection::RowId() const noexcept
{
    return sqlite3_last_insert_rowid(GetABI());
}

sqlite3* Connection::GetABI() const noexcept
{
    return m_handle.Get();
}


void Connection::ThrowLastError() const
{
    //GetABI();
    throw Exception(m_handle.Get());
}

