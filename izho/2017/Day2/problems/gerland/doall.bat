rem   *** validation ***
call scripts\run-validator-tests.bat
call scripts\run-checker-tests.bat

rem    *** tests ***
md tests
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 1000 1000 1" "tests\02" 2
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 1000 1000 2" "tests\03" 3
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 1000 1000 3" "tests\04" 4
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 1000 1000 4" "tests\05" 5
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 1000 1000 5" "tests\06" 6
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 1000 16" "tests\07" 7
call scripts\gen-input-via-stdout.bat "files\gen_B_sub.exe 5 20 6" "tests\08" 8
call scripts\gen-input-via-stdout.bat "files\gen_B_sub.exe 1 1000000 7" "tests\09" 9
call scripts\gen-input-via-stdout.bat "files\gen_B_sub.exe 1 1000000 8" "tests\10" 10
call scripts\gen-input-via-stdout.bat "files\gen_B_sub.exe 1 2 9" "tests\11" 11
call scripts\gen-input-via-stdout.bat "files\gen_B_sub.exe 1 30000 10" "tests\12" 12
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 100000 100000 11" "tests\13" 13
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 100000 100000 12" "tests\14" 14
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 100000 100000 13" "tests\15" 15
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 100000 100000 14" "tests\16" 16
call scripts\gen-input-via-stdout.bat "files\gen_stup.exe 100000 100000 15" "tests\17" 17
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 100000 17" "tests\18" 18
call scripts\gen-answer.bat tests\01 tests\01.a "tests" "A"
call scripts\gen-answer.bat tests\02 tests\02.a "tests" "A"
call scripts\gen-answer.bat tests\03 tests\03.a "tests" "A"
call scripts\gen-answer.bat tests\04 tests\04.a "tests" "A"
call scripts\gen-answer.bat tests\05 tests\05.a "tests" "A"
call scripts\gen-answer.bat tests\06 tests\06.a "tests" "A"
call scripts\gen-answer.bat tests\07 tests\07.a "tests" "A"
call scripts\gen-answer.bat tests\08 tests\08.a "tests" "B"
call scripts\gen-answer.bat tests\09 tests\09.a "tests" "B"
call scripts\gen-answer.bat tests\10 tests\10.a "tests" "B"
call scripts\gen-answer.bat tests\11 tests\11.a "tests" "B"
call scripts\gen-answer.bat tests\12 tests\12.a "tests" "B"
call scripts\gen-answer.bat tests\13 tests\13.a "tests" "C"
call scripts\gen-answer.bat tests\14 tests\14.a "tests" "C"
call scripts\gen-answer.bat tests\15 tests\15.a "tests" "C"
call scripts\gen-answer.bat tests\16 tests\16.a "tests" "C"
call scripts\gen-answer.bat tests\17 tests\17.a "tests" "C"
call scripts\gen-answer.bat tests\18 tests\18.a "tests" "C"

