# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/educate/esp/esp-idf/components/bootloader/subproject"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix/tmp"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix/src/bootloader-stamp"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix/src"
  "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/educate/DATA/ESP32/MY_EXAMPLES/DSHT_600_1_CHANNEL/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
