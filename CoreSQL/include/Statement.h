#pragma once
// CoreHandle
#include "CoreHandle/CoreHandle.h"
// CoreSQL
#include "CoreSQL_Utils.h"
#include "SQLException.h"
#include "Reader.h"
#include "Connection.h"

NS_CORESQL_BEGIN

class Statement
    : public Reader<Statement>
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
private:
    struct StatementHandleTraits
        : CoreHandle::HandleTraits<sqlite3_stmt *>
    {
        static void Close(Type value) noexcept
        {
            COREASSERT_VERIFY(
                sqlite3_finalize(value) == SQLITE_OK,
                "Failed to finalize sqlite3 statement errcode: (%d) - errmsg: (%s)",
                sqlite3_errcode(sqlite3_db_handle(value)),
                sqlite3_errmsg (sqlite3_db_handle(value))
            );
        }
    };


    //------------------------------------------------------------------------//
    // Type Aliases                                                           //
    //------------------------------------------------------------------------//
private:
    using StatementHandle = CoreHandle::Handle<StatementHandleTraits>;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Statement() noexcept = default;

    Statement(const Connection &connection, const std::string &statement);

    template <typename ...Values>
    Statement(
        const Connection &connection,
        const std::string &statement,
        Values && ...values)
    {
        Prepare(connection, statement, std::forward<Values>(values)...);
    }

    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
public:
    explicit operator bool() const noexcept;


    //------------------------------------------------------------------------//
    // Prepare Methods                                                        //
    //------------------------------------------------------------------------//
public:
    template <typename ...Values>
    void Prepare(
        const Connection &connection,
        const std::string &statement,
        Values &&...values)
    {
        Prepare(connection, statement);
        BindAll(std::forward<Values>(values)...);
    }

    void Prepare(const Connection &connection, const std::string &statement);


    //------------------------------------------------------------------------//
    // "Action" Methods                                                       //
    //------------------------------------------------------------------------//
    bool Step   () const;
    void Execute() const;

    template <typename ...Values>
    void Reset(Values && ...values)
    {
        if(sqlite3_reset(GetABI()) != SQLITE_OK)
            ThrowLastError();

        BindAll(values...);
    }


    //------------------------------------------------------------------------//
    // Bind Methods                                                           //
    //------------------------------------------------------------------------//
    template <typename ...Values>
    void BindAll(Values && ...values) const
    {
        COREASSERT_ONLY_IN_DEBUG({
            constexpr auto values_count  = sizeof...(values);
            const auto stmt_params_count =  sqlite3_bind_parameter_count(GetABI());

            COREASSERT_VERIFY(
                values_count == stmt_params_count,
                "Count mismatch - Values: (%d) - Bind Parameters: (%d)",
                values_count,
                stmt_params_count
            );
        });

        BindHelper(1, std::forward<Values>(values) ...);
    }

    void Bind(const int index, const int value) const;

    void Bind(const int index, const double value) const;

    void Bind(const int index, const std::string &value) const;

    void Bind(const int index, std::string &&value) const;


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
public:
    sqlite3_stmt* GetABI() const noexcept;


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    void ThrowLastError() const;

    template <typename First, typename ...Rest>
    void BindHelper(int index, First &&first, Rest && ...rest) const
    {
        Bind(index, std::forward<First>(first));
        BindHelper(index +1, std::forward<Rest>(rest) ...);
    }

    void BindHelper(int) const noexcept
    {
        // Empty...
    }

    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    StatementHandle m_handle;
};

NS_CORESQL_END
