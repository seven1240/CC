/*
 * Copyright 2002-2014 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      CC/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <switch.h>

#include <vector>

#include "common.h"
#include "ccl_record_handler.h"

static switch_thread_t* launch_task_thread();
static switch_thread_t* launch_failtask_thread();
static void* SWITCH_THREAD_FUNC task_thread_run(switch_thread_t* thread, void* obj);
static void* SWITCH_THREAD_FUNC failtask_thread_run(switch_thread_t* thread, void* obj);
static switch_status_t do_config(switch_bool_t reload);
/* Prototypes */
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_ccl_record_shutdown);
SWITCH_MODULE_RUNTIME_FUNCTION(mod_ccl_record_runtime);
SWITCH_MODULE_LOAD_FUNCTION(mod_ccl_record_load);

/* SWITCH_MODULE_DEFINITION(name, load, shutdown, runtime)
 * Defines a switch_loadable_module_function_table_t and a static const char[] modname
 */
SWITCH_MODULE_DEFINITION(mod_ccl_record, mod_ccl_record_load, mod_ccl_record_shutdown, NULL);

static global_info_t globals;

static void dump_global() {
    switch_thread_rwlock_rdlock(globals.rwlock);

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                      "ccl_record.conf rec_base=%s, max_thread=%d, dest_base=%s\n",
                      globals.rec_basedir, globals.max_thread, globals.dest_basedir);

    for (tasklist_t* s = globals.task; s; s = s->next) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                          "task(%s)\n",
                          s->task);
    }

    switch_thread_rwlock_unlock(globals.rwlock);
}

static void event_handler(switch_event_t* event) {
    if (!event) {
        return;
    }

    switch (event->event_id) {
    case SWITCH_EVENT_RECORD_START: {
        const char* uuid = switch_event_get_header(event, "Unique-ID");
        const char* file = switch_event_get_header(event, "Record-File-Path");

        if (switch_strlen_zero(uuid) || switch_strlen_zero(file)) {
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                              "record start invalid uuid=%s or file=%s ,omit\n", uuid, file);
        } else {
            if (ccl_record_handler_t::instance()->on_record_start(uuid, file)) {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                                  "record start deal success uuid=%s, file=%s\n", uuid, file);
            } else {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                                  "record start deal failed uuid=%s, file=%s\n", uuid, file);
            }
        }
    }
    break;

    case SWITCH_EVENT_RECORD_STOP: {
        const char* uuid = switch_event_get_header(event, "Unique-ID");

        if (switch_strlen_zero(uuid)) {
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                              "record end invalid uuid=%s ,omit\n", uuid);
        } else {
            if (ccl_record_handler_t::instance()->on_record_stop(uuid)) {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                                  "record stop deal success uuid=%s\n", uuid);
            } else {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                                  "record stop deal failed uuid=%s\n", uuid);
            }
        }

    }
    break;

    case SWITCH_EVENT_RELOADXML:
        if (do_config(SWITCH_TRUE) == SWITCH_STATUS_SUCCESS) {
            dump_global();
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                              "ccl_record reloadxml success\n");
        } else {
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                              "ccl_record reloadxml failed\n");
        }

        break;

    default:
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "receive unsubscribe event %s, omit\n",
                          switch_event_name(event->event_id));
        break;
    }

}


static switch_status_t do_config(switch_bool_t reload) {
    switch_xml_t xml = NULL, x_lists = NULL, x_list = NULL, cfg = NULL;

    if (!reload) {
        switch_thread_rwlock_create(&(globals.rwlock), globals.pool);
    }

    switch_thread_rwlock_wrlock(globals.rwlock);

    if (!(xml = switch_xml_open_cfg("ccl_record.conf", &cfg, NULL))) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING, "can't open ccl_record.conf");
        return SWITCH_STATUS_FALSE;
    }

    if (!reload && (x_lists = switch_xml_child(cfg, "settings"))) {
        for (x_list = switch_xml_child(x_lists, "param"); x_list; x_list = x_list->next) {
            char* var = (char*) switch_xml_attr_soft(x_list, "name");
            char* val = (char*) switch_xml_attr_soft(x_list, "value");

            if (switch_strlen_zero(var) || switch_strlen_zero(val)) {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                                  "ccl_record.conf var=%s,val=%s ,omit\n", var, val);
                continue;
            }

            if (!strcasecmp(var, "rec-basedir")) {
                strncpy(globals.rec_basedir, val, LEN_255);
            } else if (!strcasecmp(var, "max-thread")) {
                globals.max_thread = atoi(val);
            } else if (!strcasecmp(var, "dest-basedir")) {
                strncpy(globals.dest_basedir, val, LEN_255);
            }
        }
    }

    while (globals.task) {
        tasklist_t* pinfo = globals.task->next;
        switch_safe_free(globals.task);
        globals.task = pinfo;
    }

    if ((x_lists = switch_xml_child(cfg, "tasklist"))) {
        for (x_list = switch_xml_child(x_lists, "task"); x_list; x_list = x_list->next) {
            char* val = (char*) switch_xml_attr_soft(x_list, "value");
            void*  task = NULL;

            if (switch_strlen_zero(val)) {
                continue;
            }

            if (!strstr(val, "<srcfile>") || !strstr(val, "<dstfile>")) {
                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                                  "invalid task name ,no key workds:<srcfile> or <dstfile>\n");
                continue;
            }

            switch_zmalloc(task, sizeof(tasklist_t));

            strncpy(((tasklist_t*)task)->task, val, LEN_255 + LEN_255);

            ((tasklist_t*)task)->next = globals.task;
            globals.task = (tasklist_t*)task;
        }
    }

    if (xml) {
        switch_xml_free(xml);
    }

    if (globals.max_thread < 5) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "mod_ccl_record max thread adjust to %d\n", 5);
        globals.max_thread = 5;
    }

    if (globals.max_thread > 20) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "mod_ccl_record max thread adjust to %d\n", 20);
        globals.max_thread = 20;
    }

    globals.failthreads_count = (globals.max_thread / 5);

    if (globals.failthreads_count == 0) {
        globals.failthreads_count = 1;
    }

    switch_thread_rwlock_unlock(globals.rwlock);

    if (globals.task) {
        return SWITCH_STATUS_SUCCESS;
    } else {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "mod_ccl_record load failed(empty task list)\n");
        return SWITCH_STATUS_FALSE;
    }
}

SWITCH_STANDARD_API(ccl_record_reset_func) {
    return (ccl_record_handler_t::instance()->clear_failtask()
            ? (stream->write_function(stream, "+OK  failtask reset\n"), SWITCH_STATUS_SUCCESS)
            : (stream->write_function(stream, "-ERR failtask reset\n"), SWITCH_STATUS_FALSE)
           );
}

/* Macro expands to: switch_status_t mod_ccl_record_load(switch_loadable_module_interface_t **module_interface, switch_memory_pool_t *pool) */
SWITCH_MODULE_LOAD_FUNCTION(mod_ccl_record_load) {
    switch_api_interface_t* api_interface = NULL;
    *module_interface = switch_loadable_module_create_module_interface(pool, modname);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "load ccl_record module begin\n");

    memset(&globals, 0, sizeof(globals));
    globals.pool = pool;

    if (switch_event_bind_removable(modname, SWITCH_EVENT_RECORD_START, NULL, event_handler, NULL,
                                    &(globals.start_node)) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR,
                          "Couldn't bind(SWITCH_EVENT_RECORD_START)!\n");
        return SWITCH_STATUS_GENERR;
    }

    if (switch_event_bind_removable(modname, SWITCH_EVENT_RECORD_STOP, NULL, event_handler, NULL,
                                    &(globals.end_node)) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR,
                          "Couldn't bind(SWITCH_EVENT_RECORD_STOP)!\n");
        return SWITCH_STATUS_GENERR;
    }

    if ((switch_event_bind_removable(modname, SWITCH_EVENT_RELOADXML, NULL, event_handler, NULL,
                                     &(globals.reload_node)) != SWITCH_STATUS_SUCCESS)) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Couldn't bind(SWITCH_EVENT_RELOADXML)\n");
        return SWITCH_STATUS_FALSE;
    }

    if (do_config(SWITCH_FALSE) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "load ccl_record module fail\n");
        return SWITCH_STATUS_FALSE;
    }

    dump_global();

    //    start_task_dealer(globals.max_thread);

    globals.running = 1;
    {
        void* tmp = NULL;
        switch_zmalloc(tmp , sizeof(switch_thread_t*)*globals.max_thread);
        globals.threads = (switch_thread_t**)tmp;

        for (uint32_t n = 0; n < globals.max_thread; ++n) {
            globals.threads[n] = launch_task_thread();
        }
    }

    {
        void* tmp = NULL;
        switch_zmalloc(tmp , sizeof(switch_thread_t*)*globals.failthreads_count);

        globals.failthreads = (switch_thread_t**)tmp;

        for (uint32_t n = 0; n < globals.failthreads_count ; ++n) {
            globals.failthreads[n] = launch_failtask_thread();
        }
    }

    SWITCH_ADD_API(api_interface, "ccl_record_reset", "ccl_record reset fail task list",
                   ccl_record_reset_func, "ccl_record_reset");

    return SWITCH_STATUS_SUCCESS;
}

/*
   Called when the system shuts down
   Macro expands to: switch_status_t mod_ccl_record_shutdown() */
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_ccl_record_shutdown) {
    /* Cleanup dynamically allocated config settings */
    if (globals.running) {
        switch_thread_rwlock_wrlock(globals.rwlock);

        switch_event_unbind(&(globals.reload_node));
        switch_event_unbind(&(globals.start_node));
        switch_event_unbind(&(globals.end_node));

        while (globals.task) {
            tasklist_t* pinfo = globals.task->next;
            switch_safe_free(globals.task);
            globals.task = pinfo;
        }

        switch_thread_rwlock_unlock(globals.rwlock);
        switch_thread_rwlock_destroy(globals.rwlock);

        globals.running = 0;

        switch_status_t status;

        for (uint32_t n = 0; n < globals.max_thread; ++n) {
            switch_thread_join(&status, (globals.threads[n]));
        }

        for (uint32_t n = 0; n < globals.failthreads_count ; ++n) {
            switch_thread_join(&status, (globals.failthreads[n]));
        }

        switch_safe_free(globals.threads);
    }

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "unload ccl_record module end\n");
    return SWITCH_STATUS_SUCCESS;
}

static switch_thread_t* launch_task_thread() {
    switch_thread_t* thread;
    switch_thread_create(&thread, NULL, task_thread_run, NULL, globals.pool);
    return thread;
}

static switch_thread_t* launch_failtask_thread() {
    switch_thread_t* thread;
    switch_thread_create(&thread, NULL, failtask_thread_run, NULL, globals.pool);
    return thread;
}

static void* SWITCH_THREAD_FUNC failtask_thread_run(switch_thread_t* thread, void* obj) {
    std::string task;
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "faildeal thread normal start\n");

    while (globals.running) {
        task = ccl_record_handler_t::instance()->get_failtask();

        while (task.size()) { //如果能够处理异常任务，需要等任务结束之后在停止，及时running=1
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                              "begin deal (%s)\n", task.c_str());

            if (ccl_record_handler_t::instance()->execute_task(task.c_str())) {

                switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE,
                                  "succ to deal failtask %s\n", task.c_str());
                switch_sleep(20000);
                task = ccl_record_handler_t::instance()->get_failtask();
            } else {
                uint32_t n = 1;

                while (globals.running && n < 300) {
                    switch_sleep(200000);
                    ++n;
                }

                ccl_record_handler_t::instance()->add_failtask(task.c_str());

                break;
            }
        }

        switch_sleep(200000);
    }

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "faildeal thread ended\n");
}


static void* SWITCH_THREAD_FUNC task_thread_run(switch_thread_t* thread, void* obj) {
    std::string task;
    std::string dst;
    std::string src;

    std::vector<std::string> vectask;

    while (globals.running) {
        task = ccl_record_handler_t::instance()->get_task();

        if (task.size()) {
            switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                              "begin deal %s\n", task.c_str());

            vectask.clear();

            switch_thread_rwlock_rdlock(globals.rwlock);
            dst = globals.dest_basedir;
            src = globals.rec_basedir;
            tasklist_t* ptask = globals.task;

            while (ptask) {
                vectask.push_back(ptask->task);
                ptask = ptask->next;
            }

            switch_thread_rwlock_unlock(globals.rwlock);

            for (std::vector<std::string>::iterator it = vectask.begin(); it != vectask.end(); ++it) {
                std::string t = *it;

                while (t.find("srcfile") != std::string::npos) {
                    t.replace(t.find("<srcfile>"), strlen("<srcfile>"), task);
                }


                if (task.find(src) != std::string::npos) {
                    task.replace(task.find(src), src.size(), "");
                }

                while (t.find("dstfile") != std::string::npos) {
                    t.replace(t.find("<dstfile>"), strlen("<dstfile>"), dst + "/" + task);
                }

                if (!ccl_record_handler_t::instance()->execute_task(t.c_str())) {
                    ccl_record_handler_t::instance()->add_failtask(t.c_str());
                }
            }
        } else {
            switch_sleep(200000);
        }
    }

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, "thread normal ended\n");

    return NULL;
}


/* vim:set softtabstop=4 shiftwidth=4 tabstop=4 */
