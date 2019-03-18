echo [INFO]: Building problem 'gerland'.
pushd problems\gerland
call doall.bat
popd

echo [INFO]: Building problem 'bombs'.
pushd problems\bombs
call doall.bat
popd

echo [INFO]: Building problem 'perfect-leafs'.
pushd problems\perfect-leafs
call doall.bat
popd

echo [INFO]: Building english contest statement.
pushd statements\english
call doall.bat
popd

echo [INFO]: Building russian contest statement.
pushd statements\russian
call doall.bat
popd

