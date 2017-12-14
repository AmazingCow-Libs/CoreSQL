#pragma once

// CoreHandle
#include "CoreHandle/CoreHandle.h"
// CoreSQL
#include "CoreSQL_Utils.h"
#include "SQLException.h"


NS_CORESQL_BEGIN

class Connection
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
private:
    struct ConnectionHandleTraits
        : CoreHandle::HandleTraits<sqlite3 *>
    {
        static void Close(Type value) noexcept
        {
            COREASSERT_VERIFY(
                sqlite3_close(value) == SQLITE_OK,
                "Failed to close sqlite3 connection - errcode: (%d) - errmsg: (%s)",
                sqlite3_errcode(value),
                sqlite3_errmsg(value)
            );
        }
    };


    //------------------------------------------------------------------------//
    // Type Aliases                                                           //
    //------------------------------------------------------------------------//
private:
    using ConnectionHandle = CoreHandle::Handle<ConnectionHandleTraits>;


    //------------------------------------------------------------------------//
    // Static Methods                                                         //
    //------------------------------------------------------------------------//
public:
    static Connection Memory();


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Connection() noexcept = default;

    explicit Connection(const std::string &connStr);


    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
public:
    explicit operator bool() const noexcept;


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    void Open(const std::string &connStr);

    long long RowId() const noexcept;

    sqlite3* GetABI() const noexcept;

    void ThrowLastError() const;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    ConnectionHandle m_handle;
};

NS_CORESQL_END
