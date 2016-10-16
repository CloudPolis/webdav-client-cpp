rem 1. Download submodules
git submodule update --init

rem 2. Build and local install openssl
cd vendor\openssl/
mkdir build && cd build
perl ../Configure --prefix=%INSTALL_PREFIX% --openssldir=%INSTALL_PREFIX%\ssl %OPENSSL_BUILD_PLATFORM% no-shared no-idea no-unit-test
nmake
nmake install
cd ../..

rem 3. Build and local install curl
cd curl
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% -DCURL_STATICLIB:BOOL=ON -DBUILD_TESTING:BOOL=OFF -DBUILD_CURL_TESTS:BOOL=OFF -DBUILD_CURL_EXE:BOOL=OFF -DCURL_DISABLE_LDAP:BOOL=ON -DCURL_DISABLE_LDAPS=ON %CMAKE_COMMON_FLAGS%
nmake
nmake install
cd ../..

rem 4. Build and local install pugixml
cd pugixml
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% %CMAKE_COMMON_FLAGS% 
nmake
nmake install
cd ../..
