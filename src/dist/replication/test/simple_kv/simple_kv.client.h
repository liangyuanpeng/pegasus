/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Microsoft Corporation
 *
 * -=- Robust Distributed System Nucleus (rDSN) -=-
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <iostream>
#include <dsn/dist/replication.h>
#include "simple_kv.code.definition.h"
#include "simple_kv.types.h"
#include "case.h"

namespace dsn {
namespace replication {
namespace test {
class simple_kv_client : public virtual ::dsn::clientlet
{
public:
    simple_kv_client(::dsn::rpc_address server) { _server = server; }
    simple_kv_client() {}
    virtual ~simple_kv_client() {}

    // ---------- call RPC_SIMPLE_KV_SIMPLE_KV_READ ------------
    // - synchronous
    std::pair<::dsn::error_code, std::string>
    read_sync(const std::string &key,
              std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
              int thread_hash = 0,
              uint64_t partition_hash = 0,
              dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::wait_and_unwrap<std::string>(
            ::dsn::rpc::call(server_addr.unwrap_or(_server),
                             RPC_SIMPLE_KV_SIMPLE_KV_READ,
                             key,
                             nullptr,
                             empty_callback,
                             timeout,
                             thread_hash,
                             partition_hash));
    }

    // - asynchronous with on-stack std::string and std::string
    template <typename TCallback>
    ::dsn::task_ptr read(const std::string &key,
                         TCallback &&callback,
                         std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
                         int thread_hash = 0,
                         uint64_t partition_hash = 0,
                         int reply_thread_hash = 0,
                         dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::call(server_addr.unwrap_or(_server),
                                RPC_SIMPLE_KV_SIMPLE_KV_READ,
                                key,
                                nullptr,
                                std::forward<TCallback>(callback),
                                timeout,
                                thread_hash,
                                partition_hash,
                                reply_thread_hash);
    }

    // ---------- call RPC_SIMPLE_KV_SIMPLE_KV_WRITE ------------
    // - synchronous
    std::pair<::dsn::error_code, int32_t>
    write_sync(const kv_pair &pr,
               std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
               int thread_hash = 0,
               uint64_t partition_hash = 0,
               dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::wait_and_unwrap<int32_t>(::dsn::rpc::call(server_addr.unwrap_or(_server),
                                                                     RPC_SIMPLE_KV_SIMPLE_KV_WRITE,
                                                                     pr,
                                                                     nullptr,
                                                                     empty_callback,
                                                                     timeout,
                                                                     thread_hash,
                                                                     partition_hash,
                                                                     0));
    }

    // - asynchronous with on-stack kv_pair and int32_t
    template <typename TCallback>
    ::dsn::task_ptr write(const kv_pair &pr,
                          TCallback &&callback,
                          std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
                          int thread_hash = 0,
                          uint64_t partition_hash = 0,
                          int reply_thread_hash = 0,
                          dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::call(server_addr.unwrap_or(_server),
                                RPC_SIMPLE_KV_SIMPLE_KV_WRITE,
                                pr,
                                nullptr,
                                std::forward<TCallback>(callback),
                                timeout,
                                thread_hash,
                                partition_hash,
                                reply_thread_hash);
    }

    // ---------- call RPC_SIMPLE_KV_SIMPLE_KV_APPEND ------------
    // - synchronous
    std::pair<::dsn::error_code, int32_t>
    append_sync(const kv_pair &pr,
                std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
                int thread_hash = 0,
                uint64_t partition_hash = 0,
                dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::wait_and_unwrap<int32_t>(::dsn::rpc::call(server_addr.unwrap_or(_server),
                                                                     RPC_SIMPLE_KV_SIMPLE_KV_APPEND,
                                                                     pr,
                                                                     nullptr,
                                                                     empty_callback,
                                                                     timeout,
                                                                     thread_hash,
                                                                     partition_hash));
    }

    // - asynchronous with on-stack kv_pair and int32_t
    template <typename TCallback>
    ::dsn::task_ptr append(const kv_pair &pr,
                           TCallback &&callback,
                           std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
                           int thread_hash = 0,
                           uint64_t partition_hash = 0,
                           int reply_thread_hash = 0,
                           dsn::optional<::dsn::rpc_address> server_addr = dsn::none)
    {
        return ::dsn::rpc::call(server_addr.unwrap_or(_server),
                                RPC_SIMPLE_KV_SIMPLE_KV_APPEND,
                                pr,
                                this,
                                std::forward<TCallback>(callback),
                                timeout,
                                thread_hash,
                                partition_hash,
                                reply_thread_hash);
    }

private:
    ::dsn::rpc_address _server;
};
}
}
}
