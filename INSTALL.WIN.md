 - [ ] 1. Install [perl](https://www.perl.org/)
 - [ ] 2. Install [nasm](http://www.nasm.us/)
 - [ ] 3. Add nasm in environment variable `PATH`
 - [ ] 4. Run `VS Cross Tools Command Prompt`

 - [ ] 5. Download repositoty with requirements
```bash
> git clone https://github.com/designerror/webdav-client-cpp
> cd webdav-client-cpp
> git submodule update --init
```

 - [ ] 6. Set the build options
```bash
> set BUILD_TYPE=Release # Release | Debug
> set BUILD_SHARED_LIBS=FALSE # FALSE | TRUE
> set OPENSSL_BUILD_PLATFORM=VC-WIN64A # VC-WIN32 | VC-WIN64A | VC-WIN64I | VC-CE
> set INSTALL_PREFIX=%cd%\build
> set CMAKE_COMMON_FLAGS=-DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DMSVC_SHRED_RT:BOOL=%BUILD_SHARED_LIBS%
```

 - [ ] 7. Build and local install `openssl`

```bash
> cd vendor\openssl/
> mkdir build && cd build
> perl ../Configure --prefix=%INSTALL_PREFIX% --openssldir=%INSTALL_PREFIX%\ssl %OPENSSL_BUILD_PLATFORM% no-shared no-idea no-unit-test
> nmake
> nmake install
> cd ../..
```

 - [ ] 8. Build and local install `curl`

```bash
> cd curl
> mkdir build && cd build
> cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% -DCURL_STATICLIB:BOOL=ON -DBUILD_TESTING:BOOL=OFF -DBUILD_CURL_TESTS:BOOL=OFF -DBUILD_CURL_EXE:BOOL=OFF -DCURL_DISABLE_LDAP:BOOL=ON -DCURL_DISABLE_LDAPS=ON %CMAKE_COMMON_FLAGS%
> nmake
> nmake install
> cd ../..
```

 - [ ] 9. Build and local install `pugixml`

```bash
> cd pugixml
> mkdir build && cd build
> cmake .. -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX% %CMAKE_COMMON_FLAGS% 
> nmake
> nmake install
> cd ../..
```

 - [ ] 10. Build and local install `webdavclient`

```bash
> cd %INSTALL_PREFIX%
> set CURL_INCLUDE_DIR=%INSTALL_PREFIX%\include
> set CURL_LIBRARY=%INSTALL_PREFIX%\lib\libcurl.lib
> set CMAKE_PUGIXML_FLAGS=-DPUGIXML_LIBRARY=%INSTALL_PREFIX%\lib\pugixml.lib -DPUGIXML_INCLUDE_DIR=%INSTALL_PREFIX%\include
> set CMAKE_CURL_FLAGS=-DCURL_STATICLIB:BOOL=TRUE -DCURL_INCLUDE_DIR:STRING=%CURL_INCLUDE_DIR% -DCURL_LIBRARY=%CURL_LIBRARY%
> set CMAKE_OPENSSL_FLAGS=-DOPENSSL_LIBRARIES="%INSTALL_PREFIX%\lib\libcrypto.lib;%INSTALL_PREFIX%\lib\libssl.lib"
> cmake .. %CMAKE_PUGIXML_FLAGS% %CMAKE_CURL_FLAGS% %CMAKE_OPENSSL_FLAGS% %CMAKE_COMMON_FLAGS%
> nmake
> nmake install
```
