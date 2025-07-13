#include "device/tree.hpp"

int
main()
{
    auto tree = device::tree::of();
    tree.toggle_sequence_.change_sequence(0xd);

    while (true)
    {
    }
}
