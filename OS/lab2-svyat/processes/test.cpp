//
// Created by vadim on 23.10.20.
//

#include "system_info.h"
#include "logger_wrapper.h"
#include <iostream>


int main() {
    std::vector<std::string> files_list;
    files_list.emplace_back("Testlog1");
    files_list.emplace_back("Testlog2");
    files_list.emplace_back("Testlog3");
    files_list.emplace_back("Testlog4");
    Log logger(files_list);
    logger.write_message("Testing log number 1\n", 1);
    logger.write_message("Testing log number 2\n", 2);
    logger.write_message("Testing log number 3\n", 3);
    logger.write_message("Testing log number 4\n", 4);
    logger.write_message("Other Testing log number 1 again\n", 1);
    logger.write_message("Other Testing log number 2 again\n", 2);
    logger.write_message("Other Testing log number 3 again\n", 3);
    logger.write_message("Other Testing log number 4 again\n", 4);
    sleep(1000);
}
