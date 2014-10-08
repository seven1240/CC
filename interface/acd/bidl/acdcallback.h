#ifndef _BIDL2SL_ACDCALLBACK_H_
#define _BIDL2SL_ACDCALLBACK_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <bgcc.h>

#include "acdcommon.h"
namespace acd {
    class acdcallback : public bgcc::Shareable {
    public:
        virtual ~acdcallback() { }

        virtual void SendAgentEvent(
            const AgentEventT & event,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual void SendMediaEvent(
            const MediaEventT & event,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual void SendQueueEvent(
            const RouteEventT & event,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual void SendOtherEvent(
            const OtherEventT & event,
            const std::map<std::string, std::string>& ctx) = 0;

    };

    class acdcallback_SendAgentEvent_args {
    public:
        acdcallback_SendAgentEvent_args();
        virtual ~acdcallback_SendAgentEvent_args();

        AgentEventT event;

        bool operator==(const acdcallback_SendAgentEvent_args& rhs) const;
        bool operator!=(const acdcallback_SendAgentEvent_args& rhs) const;
        bool operator< (const acdcallback_SendAgentEvent_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdcallback_SendMediaEvent_args {
    public:
        acdcallback_SendMediaEvent_args();
        virtual ~acdcallback_SendMediaEvent_args();

        MediaEventT event;

        bool operator==(const acdcallback_SendMediaEvent_args& rhs) const;
        bool operator!=(const acdcallback_SendMediaEvent_args& rhs) const;
        bool operator< (const acdcallback_SendMediaEvent_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdcallback_SendQueueEvent_args {
    public:
        acdcallback_SendQueueEvent_args();
        virtual ~acdcallback_SendQueueEvent_args();

        RouteEventT event;

        bool operator==(const acdcallback_SendQueueEvent_args& rhs) const;
        bool operator!=(const acdcallback_SendQueueEvent_args& rhs) const;
        bool operator< (const acdcallback_SendQueueEvent_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdcallback_SendOtherEvent_args {
    public:
        acdcallback_SendOtherEvent_args();
        virtual ~acdcallback_SendOtherEvent_args();

        OtherEventT event;

        bool operator==(const acdcallback_SendOtherEvent_args& rhs) const;
        bool operator!=(const acdcallback_SendOtherEvent_args& rhs) const;
        bool operator< (const acdcallback_SendOtherEvent_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdcallback_SendAgentEvent_pargs {
    public:
        virtual ~acdcallback_SendAgentEvent_pargs();

        const AgentEventT* event;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendMediaEvent_pargs {
    public:
        virtual ~acdcallback_SendMediaEvent_pargs();

        const MediaEventT* event;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendQueueEvent_pargs {
    public:
        virtual ~acdcallback_SendQueueEvent_pargs();

        const RouteEventT* event;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendOtherEvent_pargs {
    public:
        virtual ~acdcallback_SendOtherEvent_pargs();

        const OtherEventT* event;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendAgentEvent_result {
    public:
        acdcallback_SendAgentEvent_result();
        virtual ~acdcallback_SendAgentEvent_result();


        bool operator==(const acdcallback_SendAgentEvent_result& rhs) const;
        bool operator!=(const acdcallback_SendAgentEvent_result& rhs) const;
        bool operator< (const acdcallback_SendAgentEvent_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendMediaEvent_result {
    public:
        acdcallback_SendMediaEvent_result();
        virtual ~acdcallback_SendMediaEvent_result();


        bool operator==(const acdcallback_SendMediaEvent_result& rhs) const;
        bool operator!=(const acdcallback_SendMediaEvent_result& rhs) const;
        bool operator< (const acdcallback_SendMediaEvent_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendQueueEvent_result {
    public:
        acdcallback_SendQueueEvent_result();
        virtual ~acdcallback_SendQueueEvent_result();


        bool operator==(const acdcallback_SendQueueEvent_result& rhs) const;
        bool operator!=(const acdcallback_SendQueueEvent_result& rhs) const;
        bool operator< (const acdcallback_SendQueueEvent_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendOtherEvent_result {
    public:
        acdcallback_SendOtherEvent_result();
        virtual ~acdcallback_SendOtherEvent_result();


        bool operator==(const acdcallback_SendOtherEvent_result& rhs) const;
        bool operator!=(const acdcallback_SendOtherEvent_result& rhs) const;
        bool operator< (const acdcallback_SendOtherEvent_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendAgentEvent_presult {
    public:
        virtual ~acdcallback_SendAgentEvent_presult();


        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendMediaEvent_presult {
    public:
        virtual ~acdcallback_SendMediaEvent_presult();


        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendQueueEvent_presult {
    public:
        virtual ~acdcallback_SendQueueEvent_presult();


        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallback_SendOtherEvent_presult {
    public:
        virtual ~acdcallback_SendOtherEvent_presult();


        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdcallbackProxy : public bgcc::BaseProxy {
    public:
        acdcallbackProxy(
            bgcc::ServerInfo serverinfo,
            int32_t maxConn,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        acdcallbackProxy(
            bgcc::ServerInfo serverinfo,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        acdcallbackProxy(
            const std::string& proxy_name,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        void SendAgentEvent(
            const AgentEventT& event,
            bool last = false);

        void SendMediaEvent(
            const MediaEventT& event,
            bool last = false);

        void SendQueueEvent(
            const RouteEventT& event,
            bool last = false);

        void SendOtherEvent(
            const OtherEventT& event,
            bool last = false);

    private:
        void send_SendAgentEvent(
            const AgentEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendAgentEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendMediaEvent(
            const MediaEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendMediaEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendQueueEvent(
            const RouteEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendQueueEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendOtherEvent(
            const OtherEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendOtherEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

    };

    class SSLacdcallbackProxy : public bgcc::SSLBaseProxy {
    public:
        SSLacdcallbackProxy(
            bgcc::ServerInfo serverinfo,
            int32_t maxConn,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        SSLacdcallbackProxy(
            bgcc::ServerInfo serverinfo,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        SSLacdcallbackProxy(
            const std::string& proxy_name,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        void SendAgentEvent(
            const AgentEventT& event,
            bool last = false);

        void SendMediaEvent(
            const MediaEventT& event,
            bool last = false);

        void SendQueueEvent(
            const RouteEventT& event,
            bool last = false);

        void SendOtherEvent(
            const OtherEventT& event,
            bool last = false);

    private:
        void send_SendAgentEvent(
            const AgentEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendAgentEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendMediaEvent(
            const MediaEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendMediaEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendQueueEvent(
            const RouteEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendQueueEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendOtherEvent(
            const OtherEventT& event,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void recv_SendOtherEvent(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

    };

    class acdcallbackProcessor : public bgcc::BaseProcessor {
    public:
        acdcallbackProcessor(bgcc::SharedPointer<acdcallback> intf);

        virtual ~acdcallbackProcessor(){ }

        virtual int32_t process(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto);

        virtual std::string get_name() const;

    protected:
        virtual int32_t do_function__(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            const std::string& fname, int32_t seqid);

        bgcc::SharedPointer<acdcallback> __intf;

    private:
        int32_t do_SendAgentEvent(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SendMediaEvent(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SendQueueEvent(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SendOtherEvent(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        typedef int32_t (acdcallbackProcessor::* do_function_ptr)(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        std::map<std::string, do_function_ptr> __fun_map;
    };
}


#endif
