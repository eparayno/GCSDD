/*  ---------------------------------------------------------------------------
    HASHABLE.H
    Parent class for Comparable and Action
    Authors: Erika Parayno
    ---------------------------------------------------------------------------
    Hashable class: Base class for all items
        -- Has comparison printing funcitonalities */

#include "Hashable.h"

ostream& operator<<(ostream& out, const Hashable& foo)
{
    return foo.print(out);
}
