#include <explorer.hpp>

// name
void f1(const path& _path) {
    std::ofstream out( "log.txt", std::ios_base::app);
    out << "\tname:\t" << _path.filename() << std::endl;
    out.close();
}
// size
void f2(const path& _path) {
    std::ofstream out( "log.txt", std::ios_base::app);
    out << "\tsize:\t" << ( ( (double)(file_size(_path) ) ) / 1000 ) << std::endl;
    out.close();
}
// date
void f3(const path& _path) {
    std::time_t cftime = last_write_time(_path);
    std::ofstream out( "log.txt", std::ios_base::app);
    out << "\tdate:\t" << asctime(localtime(&cftime)) << std::endl;
    out.close();
}

bool print_info(const path& _path) {
    if(!exists(_path) )
        return false;

    f1(_path);
    f2(_path);
    f3(_path);

    return true;
}


int main(int argc, char const *argv[]) {
    try {
        options_description desc{"Options"};
        desc.add_options()
        ("help,h", "Help screen")
        ("regex,r", value<std::string>(), "Inter BRE for output");

        variables_map vm_console;
        
        store(parse_command_line(argc, argv, desc), vm_console);
        notify(vm_console);

        if (vm_console.count("help")) {
            std::cout << desc << '\n';

        } else if (vm_console.count("regex")) {
            cout << "REGEX OUTPUT" << endl;

            std::string regex_string = vm_console["regex"].as<std::string>(); //  "(f.*)+\\.dat" f.*.dat
            std::vector<std::string> fileList{"f1.dat", "f2.dat", "f3.dat"};
            std::vector<std::string> fileMatch;

            boost::regex rgx(regex_string);
            boost::smatch matcher;

            scheduler_t scheduler;
            std::map<const path, std::future<bool> > results;

            int counter_for_regex = 0;

            for (int i = 0; i < fileList.size(); i++) {
                if(boost::regex_match(fileList[i], matcher, rgx)) {
                    ++counter_for_regex;
                    fileMatch.push_back(matcher.str(0));
                }
            }

            if (counter_for_regex) {
                std::ofstream out("log.txt", std::ios_base::app);
                out << std::endl << "SESSION OF RECORDING INTO LOG.TXT:\t" << to_simple_string(second_clock::local_time()) << std::endl << std::endl;
                out.close();

                for (int i = 0; i < fileMatch.size(); i++) {
                    std::cout << "Output " << fileMatch[i] << " in >> " << "log.txt" << '\n';

                    std::string address = "explorer/";

                    const path p = address + fileMatch[i];

                    auto task = std::packaged_task<bool()> { std::bind(print_info, p) };
                    auto result = task.get_future();

                    scheduler.add( task );

                    results.emplace(p, std::move(result));
                }

                scheduler.run();

                for(auto & p : results) {
                    auto& result = p.second;
                    auto is_ok = result.get();
                    if (! is_ok) {
                        std::cerr << "\tBAD LINK:\t" << p.first << std::endl;
                    }
                }

            } else {
                std::cout << "\tHave no match any files..." << std::endl;
            }
            
        } else {
            cout << "DEFAULT OUTPUT" << endl;
            std::ofstream out( "log.txt", std::ios_base::app);
            out << std::endl << "SESSION OF RECORDING INTO LOG.TXT:\t" << to_simple_string(second_clock::local_time()) << std::endl << std::endl;
            out.close();

            std::string address = "explorer/";
            scheduler_t scheduler;

            std::map<const path, std::future<bool> > results;

            for (int i = 1; i < argc; i++) {

                const path p = address + argv[i];

                auto task = std::packaged_task<bool()> { std::bind(print_info, p) };
                auto result = task.get_future();

                scheduler.add( task );

                results.emplace(p, std::move(result));
            }

            scheduler.run();

            for(auto & p : results) {
                auto& result = p.second;
                auto is_ok = result.get();
                if (! is_ok) {
                    std::cerr << "\tBAD LINK:\t" << p.first << std::endl;
                }
            }
        }

    }  catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
