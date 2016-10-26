if(APPLE)
    set(CPACK_GENERATOR "ZIP;")
    SET(CPACK_SOURCE_GENERATOR "TGZ;")
endif()

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PureData")
set(CPACK_PACKAGE_VENDOR "http://ceammc.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${PD_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${PD_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH "${PD_BUGFIX_VERSION}_ceammc")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")

set(PD_DESKTOP_DIR "/usr/share/applications/")
set(PD_PIXMAPS_DIR "/usr/share/icons/")


find_program(XGD-MIME_EXECUTABLE xdg-mime)
find_program(XDG-DESKTOP-MENU_EXECUTABLE xdg-desktop-menu)
# Debian package
include(DpkgBuild)
if(DPKG_FOUND AND NOT WIN32)

set(CPACK_GENERATOR "DEB")


endif()

include(CPack)
