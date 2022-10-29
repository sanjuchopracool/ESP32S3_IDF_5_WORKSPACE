# Install script for directory: /home/educate/esp/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/educate/.espressif/tools/xtensa-esp32s3-elf/esp-2022r1-11.2.0/xtensa-esp32s3-elf/bin/xtensa-esp32s3-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/home/educate/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

