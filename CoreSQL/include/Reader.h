#pragma once
// std
#include <map>
// CoreSQL
#include "CoreSQL_Utils.h"
#include "Handle.h"
#include "SQLException.h"

NS_CORESQL_BEGIN

template <typename T>
class Reader
{
    //------------------------------------------------------------------------//
    // Getter Methods                                                         //
    //------------------------------------------------------------------------//
public:
    int GetInt(int col) const noexcept
    {
        COREASSERT_ONLY_IN_DEBUG({CheckColumnValidity(col);});
        return sqlite3_column_int(GetABI(), col);
    }

    double GetDouble(int col) const noexcept
    {
        COREASSERT_ONLY_IN_DEBUG({CheckColumnValidity(col);});
        return sqlite3_column_double(GetABI(), col);
    }

    const void* GetBlob(int col) const noexcept
    {
        COREASSERT_ONLY_IN_DEBUG({CheckColumnValidity(col);});
        return sqlite3_column_blob(GetABI(), col);
    }

    std::string GetText(int col) const noexcept
    {
        COREASSERT_ONLY_IN_DEBUG({CheckColumnValidity(col);});
        auto str_ptr = reinterpret_cast<const char *>(
            sqlite3_column_text(GetABI(), col)
        );

        return std::string((str_ptr) ? str_ptr : "");
    }


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    void CheckColumnValidity(int col) const
    {
        auto column_count = sqlite3_column_count(GetABI());
        COREASSERT_ASSERT(
            col >= 0 && col < column_count,
            "Column (%d) is out of bounds (0,%d]- stmt: (%s)",
            col,
            column_count,
            sqlite3_sql(GetABI())
        );
    }


    sqlite3_stmt* GetABI() const noexcept
    {
        return (static_cast<T const *>(this))->GetABI();
    }
};

NS_CORESQL_END
