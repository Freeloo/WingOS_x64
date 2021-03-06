#pragma once
#include <arch/64bit.h>
#include <int_value.h>
#define MAX_PROCESS 64
#define PROCESS_STACK_SIZE 8192
enum process_state
{
    PROCESS_AVAILABLE = 0,
    PROCESS_RUNNING = 1,
    PROCESS_WAITING = 2,
    PROCESS_CRASH = 3,
    PROCESS_NOT_STARTED = 4
};

#define MAX_PROCESS_MEMORY_DATA_MAP 64
struct process_memory_data_map
{
    uint64_t from;
    uint64_t to;
    uint64_t length;
    bool used = false;
};
struct process_message
{
    uint8_t message_id;
    uint64_t from_pid;
    uint64_t to_pid;
    uint64_t content_address; // NOTE IT COPY THE CONTENT
    uint64_t content_length;
    uint64_t response;
    bool has_been_readed;
    bool entry_free_to_use;
} __attribute__((packed));
#define MAX_PROCESS_MESSAGE_QUEUE 32
struct process
{

    uint64_t rsp = 0;
    process_state current_process_state;
    uint64_t upid = 0;
    uint64_t kpid = 0;
    uint8_t stack[PROCESS_STACK_SIZE];
    uint64_t entry_point = 0x0;
    uint64_t sse_context[128] __attribute__((aligned(16)));
    uint64_t page_directory = 0;
    process_memory_data_map mmap[MAX_PROCESS_MEMORY_DATA_MAP];
    char backed_name[128];
    char process_name[128];
    process_message msg_list[MAX_PROCESS_MESSAGE_QUEUE];
    uint64_t last_message_used;
    bool is_ORS = false;
    bool should_be_active = false; // used with ORS
    uint8_t processor_target;
    uint8_t *global_process_memory;
    uint64_t global_process_memory_length;
    uint64_t stopped_length = 0;
    bool is_on_interrupt_process = false;
    uint8_t interrupt_handle_list[8]; // max 8 interrupt per process
} __attribute__((packed));

struct message_identifier
{
    uint16_t pid; // process_id
    uint16_t mid; // message_id
} __attribute__((packed));

static process *process_array = nullptr;
// TODO: make a get_current_process() function
typedef void (*func)();
void add_thread_map(process *p, uint64_t from, uint64_t to, uint64_t length);

/* if cpu_target == -1
 *  select the current cpu
 * if cpu_target == -2
 *  process select the 'least' used cpu
 */

process *init_process(func entry_point, bool start_direct, const char *name, bool user, int cpu_target = -1);
void init_multi_process(func start);
void dump_process();
void unlock_process();
void lock_process();

extern "C" void task_update_switch(process *next);
extern "C" uint64_t irq_0_process_handler(InterruptStackFrame *isf);

process_message *send_message(uint64_t data_addr, uint64_t data_length, const char *to_process);
process_message *read_message();
uint64_t message_response(process_message *indentifier);

// todo : add ORS to user service, for the moment it is only for kernel
void set_on_request_service(bool is_ORS);
void set_on_request_service(bool is_ORS, uint64_t pid);
void on_request_service_update();
uint64_t get_pid_from_process_name(const char *name);

void *get_current_process_global_data(uint64_t offset, uint64_t length);

uint64_t get_process_global_data_copy(uint64_t offset, const char *process_name);
void rename_process(const char *name, uint64_t pid);

uint64_t upid_to_kpid(uint64_t upid);
