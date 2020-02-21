

#include "FilesManagement.h"
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

#define STR_VALUE(val) #val
#define STR(name) STR_VALUE(name)

#define PATH_LEN 256
#define MD5_LEN 32

FilesManagement::FilesManagement() {
}

FilesManagement::~FilesManagement() {
}

std::string FilesManagement::computeMD5(const std::string & file_name) {
#define MD5SUM_CMD_FMT "md5sum %." STR(PATH_LEN) "s 2>/dev/null"
    char cmd[PATH_LEN + sizeof (MD5SUM_CMD_FMT)];
    sprintf(cmd, MD5SUM_CMD_FMT, file_name.c_str());
#undef MD5SUM_CMD_FMT

    std::string md5_sum;
    FILE *p = popen(cmd, "r");
    if (p == 0) return 0;

    int i, ch;
    for (i = 0; i < MD5_LEN && isxdigit(ch = fgetc(p)); i++) {
        md5_sum += ch;
    }

    pclose(p);
    //std::cout << "md5 of " << file_name << " is " << md5_sum << std::endl;
    return md5_sum;
}

int FilesManagement::tryGetLock(char const *lockName) const {
    mode_t m = umask(0);
    int fd = open(lockName, O_RDWR | O_CREAT, 0666);
    umask(m);
    if (fd >= 0 && flock(fd, LOCK_EX) < 0) {
        close(fd);
        fd = -1;
    }
    return fd;
}

void FilesManagement::releaseLock(int fd, const std::string & path) const {
    std::string lock = path + ".lock";
    releaseLock(fd, lock.c_str());
}

void FilesManagement::releaseLock(int fd, char const *lockName) const {
    if (fd < 0)
        return;
    remove(lockName);
    close(fd);
}

int FilesManagement::tryGetLock(const std::string& path) const {
    std::string lock = path + ".lock";
    int fd = tryGetLock(lock.c_str());
    if (fd < 0) {
        throw std::runtime_error(lock + " lock failed");
    }
    return fd;
}

bool FilesManagement::exists(const std::string& name) const {
    std::ifstream f(name.c_str());
    return f.good();
}
