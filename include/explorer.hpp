#include <iostream>
#include <future>
#include <fstream>
#include <map>
#include <cstring>
#include <string>
#include <thread>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <regex>

using namespace boost::filesystem;
using namespace boost::posix_time;
using namespace boost::program_options;
using namespace boost;
using namespace std;

class scheduler_t {
        std::vector<std::packaged_task<bool()> > v_task;
        std::vector<std::packaged_task<bool()> >::iterator iter;
    public:
        void add( std::packaged_task<bool()> & _task ) {
            v_task.push_back( std::move(_task) );
        }
        void run() {
            for(iter = v_task.begin(); iter != v_task.end(); iter++) {
                (*iter)();
            }
        }
        scheduler_t() {}
        ~scheduler_t() {}
};
