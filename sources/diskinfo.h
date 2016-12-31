/*Copyright 2016 Michael Osei

This file is part of Cysboard.

Cysbaord is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Cysboard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Cysboard.  If not, see <http://www.gnu.org/licenses/>.*/


#ifndef CYSBOARD_DISKINFO_H
#define CYSBOARD_DISKINFO_H

// TODO: DONT forget to clean up unnecessary headers
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <string>
#include <regex>
#include <cstdint>
#include <string>

#ifdef __linux__
    #define SYSFS_DIRECTORY "/sys/block/"
#endif

class DiskInformation
{
private:
#ifdef __linux__
    DIR* m_dirDisks;

    // holds information for a single partition
    struct PartitionInfo {
        std::string name; // name of a partition
        std::ifstream* statFile; // a reference to its stat file
    };

    std::map<std::string, std::list<PartitionInfo>> m_disksAndPartions;

    std::string getFullPath(const char* diskName);

#endif

public:
    DiskInformation();
    ~DiskInformation();

    std::list<std::string>& getPartitions(const char* diskName);
    uint64_t getTotalDiskSize(const char* diskName);
    uint64_t getFreeDiskSize(const char* diskName);
};

#endif // CYSBOARD_DISKINFO_H
