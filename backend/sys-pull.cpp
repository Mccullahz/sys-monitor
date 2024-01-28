/*1. Expose an API in sys-pull.cpp to retrieve system information, for example, using a lightweight web framework like cpp-httplib.

2. Make an HTTP GET endpoint in your C++ code to return the system information as JSON.

3. In your React app, use the fetch API or a library like axios to make a GET request to the endpoint exposed by your C++ backend.

4. Parse the JSON response in your React app and use the data to update the UI.*/


#include <httplib.h>
#include <iostream>
#include <sys/sysinfo.h>

using namespace std;
using namespace httplib;

class SystemInfo {
public:
    virtual json retrieveInfo() = 0;
};

class WindowsInfo : public SystemInfo {
public:
    json retrieveInfo() override {
        // Implement Windows system info retrieval and return JSON
        json data;
        data["message"] = "Windows system info not supported";
        return data;
    }
};

class LinuxInfo : public SystemInfo {
public:
    json retrieveInfo() override {
        struct sysinfo info;
        if (sysinfo(&info) != 0) {
            json data;
            data["error"] = "Failed to retrieve system info";
            return data;
        }

        json data;
        data["uptime"] = info.uptime;
        data["total_ram_mb"] = info.totalram / 1024 / 1024;
        data["free_ram_mb"] = info.freeram / 1024 / 1024;
        return data;
    }
};

void handleSystemInfoRequest(const Request& req, Response& res) {
    SystemInfo* sysInfo = nullptr;
    int userOS = 0;  // need real OS detection logic

    if (userOS == 0) {
        sysInfo = new WindowsInfo();
    } else {
        sysInfo = new LinuxInfo();
    }

    json data = sysInfo->retrieveInfo();
    delete sysInfo;

    res.set_content(data.dump(), "application/json");
}

int main() {
    Server svr;

    // Endpoint to retrieve system information
    svr.Get("/system-info", handleSystemInfoRequest);

    cout << "Server running at http://localhost:8080" << endl;
    svr.listen("localhost", 8080);

    return 0;
}