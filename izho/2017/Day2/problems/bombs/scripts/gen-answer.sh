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
wine files/towin.exe "$1" | wine files/validate.exe --testset "$3" --group "$4"
if [ "$?" -ne "0" ]; then
    read
fi
cp $1 bomb.in
echo "Running solution bomb.cpp"
wine solutions/bomb.exe
if [ "$?" -ne "0" ]; then
    echo "Solution returned non-zero exit code"
    read
fi
rm -f bomb.in
if [ ! -f "bomb.out" ]; then
    echo "Solution didn't produced output [bomb.out]"
    read
fi
mv "bomb.out" "$2"
echo "Running checker"
wine check.exe $1 $2 $2
if [ "$?" -ne "0" ] && [ "$?" -ne "7" ]; then
    echo "Checker exit code is not equal to 0 and 7"
    read
fi
