if [ "$#" -ne "4" ]; then
    read
fi
if [ "$1" = "" ]; then
    read
fi
if [ "$2" = "" ]; then
    read
fi
if [ ! -f "$1" ]; then
    read
fi
echo "Running validator"
wine files/towin.exe "$1" | wine files/validator.exe --testset "$3" --group "$4"
if [ "$?" -ne "0" ]; then
    read
fi
cp $1 road.in
echo "Running solution road_mi_ok.cpp"
wine solutions/road_mi_ok.exe
if [ "$?" -ne "0" ]; then
    echo "Solution returned non-zero exit code"
    read
fi
rm -f road.in
if [ ! -f "road.out" ]; then
    echo "Solution didn't produced output [road.out]"
    read
fi
mv "road.out" "$2"
echo "Running checker"
wine check.exe $1 $2 $2
if [ "$?" -ne "0" ] && [ "$?" -ne "7" ]; then
    echo "Checker exit code is not equal to 0 and 7"
    read
fi
