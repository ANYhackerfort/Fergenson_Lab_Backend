// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: message.proto
#ifndef GRPC_message_2eproto__INCLUDED
#define GRPC_message_2eproto__INCLUDED

#include "message.pb.h"

#include <functional>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

class MessageService final {
public:
  static constexpr char const *service_full_name() { return "MessageService"; }
  class StubInterface {
  public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SendMessage(::grpc::ClientContext *context,
                                       const ::MessageRequest &request,
                                       ::MessageResponse *response) = 0;
    std::unique_ptr<
        ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse>>
    AsyncSendMessage(::grpc::ClientContext *context,
                     const ::MessageRequest &request,
                     ::grpc::CompletionQueue *cq) {
      return std::unique_ptr<
          ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse>>(
          AsyncSendMessageRaw(context, request, cq));
    }
    std::unique_ptr<
        ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse>>
    PrepareAsyncSendMessage(::grpc::ClientContext *context,
                            const ::MessageRequest &request,
                            ::grpc::CompletionQueue *cq) {
      return std::unique_ptr<
          ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse>>(
          PrepareAsyncSendMessageRaw(context, request, cq));
    }
    class async_interface {
    public:
      virtual ~async_interface() {}
      virtual void SendMessage(::grpc::ClientContext *context,
                               const ::MessageRequest *request,
                               ::MessageResponse *response,
                               std::function<void(::grpc::Status)>) = 0;
      virtual void SendMessage(::grpc::ClientContext *context,
                               const ::MessageRequest *request,
                               ::MessageResponse *response,
                               ::grpc::ClientUnaryReactor *reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface *async() { return nullptr; }
    class async_interface *experimental_async() { return async(); }

  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse> *
    AsyncSendMessageRaw(::grpc::ClientContext *context,
                        const ::MessageRequest &request,
                        ::grpc::CompletionQueue *cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface<::MessageResponse> *
    PrepareAsyncSendMessageRaw(::grpc::ClientContext *context,
                               const ::MessageRequest &request,
                               ::grpc::CompletionQueue *cq) = 0;
  };
  class Stub final : public StubInterface {
  public:
    Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
         const ::grpc::StubOptions &options = ::grpc::StubOptions());
    ::grpc::Status SendMessage(::grpc::ClientContext *context,
                               const ::MessageRequest &request,
                               ::MessageResponse *response) override;
    std::unique_ptr<::grpc::ClientAsyncResponseReader<::MessageResponse>>
    AsyncSendMessage(::grpc::ClientContext *context,
                     const ::MessageRequest &request,
                     ::grpc::CompletionQueue *cq) {
      return std::unique_ptr<
          ::grpc::ClientAsyncResponseReader<::MessageResponse>>(
          AsyncSendMessageRaw(context, request, cq));
    }
    std::unique_ptr<::grpc::ClientAsyncResponseReader<::MessageResponse>>
    PrepareAsyncSendMessage(::grpc::ClientContext *context,
                            const ::MessageRequest &request,
                            ::grpc::CompletionQueue *cq) {
      return std::unique_ptr<
          ::grpc::ClientAsyncResponseReader<::MessageResponse>>(
          PrepareAsyncSendMessageRaw(context, request, cq));
    }
    class async final : public StubInterface::async_interface {
    public:
      void SendMessage(::grpc::ClientContext *context,
                       const ::MessageRequest *request,
                       ::MessageResponse *response,
                       std::function<void(::grpc::Status)>) override;
      void SendMessage(::grpc::ClientContext *context,
                       const ::MessageRequest *request,
                       ::MessageResponse *response,
                       ::grpc::ClientUnaryReactor *reactor) override;

    private:
      friend class Stub;
      explicit async(Stub *stub) : stub_(stub) {}
      Stub *stub() { return stub_; }
      Stub *stub_;
    };
    class async *async() override { return &async_stub_; }

  private:
    std::shared_ptr<::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader<::MessageResponse> *
    AsyncSendMessageRaw(::grpc::ClientContext *context,
                        const ::MessageRequest &request,
                        ::grpc::CompletionQueue *cq) override;
    ::grpc::ClientAsyncResponseReader<::MessageResponse> *
    PrepareAsyncSendMessageRaw(::grpc::ClientContext *context,
                               const ::MessageRequest &request,
                               ::grpc::CompletionQueue *cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendMessage_;
  };
  static std::unique_ptr<Stub>
  NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
          const ::grpc::StubOptions &options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
  public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendMessage(::grpc::ServerContext *context,
                                       const ::MessageRequest *request,
                                       ::MessageResponse *response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithAsyncMethod_SendMessage() { ::grpc::Service::MarkMethodAsync(0); }
    ~WithAsyncMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMessage(
        ::grpc::ServerContext *context, ::MessageRequest *request,
        ::grpc::ServerAsyncResponseWriter<::MessageResponse> *response,
        ::grpc::CompletionQueue *new_call_cq,
        ::grpc::ServerCompletionQueue *notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response,
                                         new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendMessage<Service> AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithCallbackMethod_SendMessage() {
      ::grpc::Service::MarkMethodCallback(
          0, new ::grpc::internal::CallbackUnaryHandler<::MessageRequest,
                                                        ::MessageResponse>(
                 [this](::grpc::CallbackServerContext *context,
                        const ::MessageRequest *request,
                        ::MessageResponse *response) {
                   return this->SendMessage(context, request, response);
                 }));
    }
    void SetMessageAllocatorFor_SendMessage(
        ::grpc::MessageAllocator<::MessageRequest, ::MessageResponse>
            *allocator) {
      ::grpc::internal::MethodHandler *const handler =
          ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler<::MessageRequest,
                                                         ::MessageResponse> *>(
          handler)
          ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor *
    SendMessage(::grpc::CallbackServerContext * /*context*/,
                const ::MessageRequest * /*request*/,
                ::MessageResponse * /*response*/) {
      return nullptr;
    }
  };
  typedef WithCallbackMethod_SendMessage<Service> CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithGenericMethod_SendMessage() { ::grpc::Service::MarkMethodGeneric(0); }
    ~WithGenericMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithRawMethod_SendMessage() { ::grpc::Service::MarkMethodRaw(0); }
    ~WithRawMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMessage(
        ::grpc::ServerContext *context, ::grpc::ByteBuffer *request,
        ::grpc::ServerAsyncResponseWriter<::grpc::ByteBuffer> *response,
        ::grpc::CompletionQueue *new_call_cq,
        ::grpc::ServerCompletionQueue *notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response,
                                         new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithRawCallbackMethod_SendMessage() {
      ::grpc::Service::MarkMethodRawCallback(
          0, new ::grpc::internal::CallbackUnaryHandler<::grpc::ByteBuffer,
                                                        ::grpc::ByteBuffer>(
                 [this](::grpc::CallbackServerContext *context,
                        const ::grpc::ByteBuffer *request,
                        ::grpc::ByteBuffer *response) {
                   return this->SendMessage(context, request, response);
                 }));
    }
    ~WithRawCallbackMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor *
    SendMessage(::grpc::CallbackServerContext * /*context*/,
                const ::grpc::ByteBuffer * /*request*/,
                ::grpc::ByteBuffer * /*response*/) {
      return nullptr;
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendMessage : public BaseClass {
  private:
    void BaseClassMustBeDerivedFromService(const Service * /*service*/) {}

  public:
    WithStreamedUnaryMethod_SendMessage() {
      ::grpc::Service::MarkMethodStreamed(
          0,
          new ::grpc::internal::StreamedUnaryHandler<::MessageRequest,
                                                     ::MessageResponse>(
              [this](::grpc::ServerContext *context,
                     ::grpc::ServerUnaryStreamer<::MessageRequest,
                                                 ::MessageResponse> *streamer) {
                return this->StreamedSendMessage(context, streamer);
              }));
    }
    ~WithStreamedUnaryMethod_SendMessage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendMessage(::grpc::ServerContext * /*context*/,
                               const ::MessageRequest * /*request*/,
                               ::MessageResponse * /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendMessage(
        ::grpc::ServerContext *context,
        ::grpc::ServerUnaryStreamer<::MessageRequest, ::MessageResponse>
            *server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SendMessage<Service> StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SendMessage<Service> StreamedService;
};

#endif // GRPC_message_2eproto__INCLUDED
