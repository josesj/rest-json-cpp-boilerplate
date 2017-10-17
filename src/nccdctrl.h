#ifndef NCCDCTRL_NCCDCTRL_H
#define NCCDCTRL_NCCDCTRL_H

#include <algorithm>
#include <csignal>
#include <errno.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>
#include <process.h>
#else
#include <unistd.h>
#endif

using namespace std;
namespace spd = spdlog;

class nCcdCtrl {

private:

    static void sigtermHandler(int signal_number);
    void shutdown();

public:
    nCcdCtrl();
    virtual ~nCcdCtrl();
};

#endif // NCCDCTRL_NCCDCTRL_H
