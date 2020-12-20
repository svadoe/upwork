install_name_tool -id @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore eventlogger.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore                -- INSERT --
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore eventlogger.app/Contents/MacOs/logger

install_name_tool -id @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork eventlogger.app/Contents/Frameworks/QtCore.framework/Versions/5/QtNetwork                -- INSERT --
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork eventlogger.app/Contents/MacOs/logger

