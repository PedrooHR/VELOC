#ifndef __COMMAND_HPP
#define __COMMAND_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>

#include <libgen.h>

class command_t {
public:
    static const size_t MAX_SIZE = 128;
    static const int INIT = 0, CHECKPOINT = 1, RESTART = 2, TEST = 3;
    
    int unique_id, command, version;
    char ckpt_name[MAX_SIZE] = "";

    command_t() { }
    command_t(int r, int c, int v, const std::string &s) : unique_id(r), command(c), version(v) {
	if (s.length() > MAX_SIZE)
	    throw std::runtime_error("checkpoint name '" + s + "' is longer than admissible size " + std::to_string(MAX_SIZE));
	std::strcpy(ckpt_name, s.c_str());
    }
    std::string basename() const {
	return std::string(::basename((char *)ckpt_name));
    }
    std::string stem() const {
	std::string base = basename();
	std::string::size_type pos = base.find('-');
	if (pos != std::string::npos)
	    return base.substr(0, pos);
	else	    
	    return base; 
    }
    friend std::ostream &operator<<(std::ostream &output, const command_t &c) {
	output << "(Rank = '" << c.unique_id << "', Command = '" << c.command
	       << "', Version = '" << c.version << "', File = '" << c.ckpt_name << "')";
	return output;
    }
};

#endif // __COMMAND_HPP
