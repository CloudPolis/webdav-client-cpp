#rem 1. Install [perl](https://www.perl.org/)
#rem 2. Install [nasm](http://www.nasm.us/)
#rem 3. Add nasm in environment variable PATH
#rem 4. Run VS Cross Tools Command Prompt

#rem 5. Download repositoty with requirements
#git clone https://github.com/designerror/webdav-client-cpp
#cd webdav-client-cpp
#git submodule update --init

#rem 6. Set the build options
#set BUILD_TYPE=Release # Release | Debug
#set BUILD_SHARED_LIBS=FALSE # FALSE | TRUE
#set OPENSSL_BUILD_PLATFORM=VC-WIN64A # VC-WIN32 | VC-WIN64A | VC-WIN64I | VC-CE
#set INSTALL_PREFIX=%cd$\build
#set CMAKE_COMMON_FLAGS=-DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DMSVC_SHRED_RT:BOOL=%BUILD_SHARED_LIBS%

rem 7. Build and local install openssl
cd vendor\openssl/
mkdir build && cd build
perl ../Configure --prefix=%INSTALL_PREFIX% --openssldir=%INSTALL_PREFIX%\ssl %OPENSSL_BUILD_PLATFORM% no-shared no-idea no-unit-test
nmake
nmake install
cd ../..

rem 8. Build and local install curl
cd curl
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% -DCURL_STATICLIB:BOOL=ON -DBUILD_TESTING:BOOL=OFF -DBUILD_CURL_TESTS:BOOL=OFF -DBUILD_CURL_EXE:BOOL=OFF -DCURL_DISABLE_LDAP:BOOL=ON -DCURL_DISABLE_LDAPS=ON %CMAKE_COMMON_FLAGS%
nmake
nmake install
cd ../..

rem 9. Build and local install pugixml
cd pugixml
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% %CMAKE_COMMON_FLAGS% 
nmake
nmake install
cd ../..
