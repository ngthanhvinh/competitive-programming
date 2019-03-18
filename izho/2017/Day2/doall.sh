echo [INFO]: Building problem 'gerland'.
cd problems/gerland
./doall.sh
cd -

echo [INFO]: Building problem 'bombs'.
cd problems/bombs
./doall.sh
cd -

echo [INFO]: Building problem 'perfect-leafs'.
cd problems/perfect-leafs
./doall.sh
cd -

echo [INFO]: Building english contest statement.
cd statements/english
./doall.sh
cd -

echo [INFO]: Building russian contest statement.
cd statements/russian
./doall.sh
cd -

