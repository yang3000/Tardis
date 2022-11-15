#include "SpdLog.h"
#include "stdio.h"

using namespace TARDIS::CORE;

int main()
{

    auto log = new SpdLog("demo");
    log->log(LogType::INFO, "3232");
    printf("432534534");
    return 1;
}