#include "linebot/data_store.hpp"

namespace linebot
{

data_store&
data_store::of()
{
    static data_store store;
    return store;
}

} // namespace linebot
