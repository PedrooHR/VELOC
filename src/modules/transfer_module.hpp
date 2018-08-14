#ifndef __TRANSFER_MODULE_HPP
#define __TRANSFER_MODULE_HPP

#include "common/config.hpp"
#include "common/command.hpp"
#include "common/status.hpp"
#include "common/cache_strategy.hpp"
#include "common/chunk_stream.hpp"

#include <chrono>
#include <deque>
#include <map>

#include "axl.h"

class transfer_module_t {
    const config_t &cfg;
    bool use_axl = false;
    axl_xfer_t axl_type;
    int interval, max_versions;
    std::map<int, std::chrono::system_clock::time_point> last_timestamp;
    std::map<int, int> state;
    typedef std::map<std::string, std::deque<int> > checkpoint_history_t;
    std::map<int, checkpoint_history_t> checkpoint_history;
    cache_strategy_t cache_strategy;
    chunk_stream_t chunk_stream;

    int transfer_file(const std::string &source, const std::string &dest);
public:
    transfer_module_t(const config_t &c);
    ~transfer_module_t();
    int process_command(const command_t &c);
};

#endif //__TRANSFER_MODULE_HPP
