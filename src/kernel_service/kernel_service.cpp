#include <arch/process.h>
#include <kernel_service/kernel_service.h>
#include <kernel_service/memory_service.h>
#include <kernel_service/print_service.h>
#include <loggging.h>

void add_kernel_service(func entry, const char *service_name)
{
    log("kernel service", LOG_INFO) << "launching service : " << service_name;

    process *service = init_process((func)entry, true, service_name);
    while (service->pid == 0)
    {
        service = init_process((func)entry, true, service_name);
    }
}
void load_kernel_service()
{
    log("kernel service", LOG_DEBUG) << "loading kernel service";
    add_kernel_service(print_service, "console_out");
    add_kernel_service(memory_service, "memory_service");
}
