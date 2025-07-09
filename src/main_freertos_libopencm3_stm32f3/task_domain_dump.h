#ifndef _APPLICATION_TASK_DOMAIN_DUMP_H
#define _APPLICATION_TASK_DOMAIN_DUMP_H

#include "task_base.h"
namespace app
{

class task_domain_dump : public task_base<task_domain_dump, 128>
{
public:

    static task_domain_dump&
    of();

    task_domain_dump(task_domain_dump& other) = delete;

    task_domain_dump&
    operator=(task_domain_dump& other) = delete;

    void
    run();

private:

    task_domain_dump();
};

} // namespace app

#endif
