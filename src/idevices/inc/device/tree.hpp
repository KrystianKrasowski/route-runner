#ifndef _DEVICE_TREE_HH
#define _DEVICE_TREE_HH

#include "toggle_sequence.hpp"

namespace device
{

struct tree
{
    toggle_sequence& toggle_sequence_;

    static tree
    of();
};

} // namespace device

#endif
