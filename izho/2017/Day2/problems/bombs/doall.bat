rem   *** validation ***
call scripts\run-validator-tests.bat
call scripts\run-checker-tests.bat

rem    *** tests ***
md tests
call scripts\gen-input-via-stdout.bat "files\gen.exe 20 20 4 5 uiaasd" "tests\09" 9
call scripts\gen-input-via-stdout.bat "files\gen.exe 20 20 5 6 55af0f81b8b6b9321b3d5b72040074ec" "tests\10" 10
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 4 3 14 13 hgyexbi" "tests\11" 11
call scripts\gen-input-via-stdout.bat "files\gen.exe 20 19 6 6 eb263ce24458d2e2e13eb8c57813b089" "tests\12" 12
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 4 2 15 15 aypyexn" "tests\13" 13
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 5 3 15 11 ravccbagt" "tests\14" 14
call scripts\gen-input-via-stdout.bat "files\gen.exe 18 18 5 5 c39bc6fe27368c1750426e6751e4f2a5" "tests\16" 16
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 6 4 70 62 wsusvzgpa" "tests\19" 19
call scripts\gen-input-via-stdout.bat "files\gen.exe 94 78 19 16 5352285d723c27a4cd7cc43c4dbac7c5" "tests\20" 20
call scripts\gen-input-via-stdout.bat "files\gen.exe 92 84 19 17 6831c70ad685bcf33e145cb3b3ffbf88" "tests\21" 21
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 4 4 53 89 jdqdqk" "tests\22" 22
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 6 6 76 93 kydcycbai" "tests\23" 23
call scripts\gen-input-via-stdout.bat "files\gen.exe 100 100 22 31 fb5aee977340af714e7fdaf17fbbb537" "tests\24" 24
call scripts\gen-input-via-stdout.bat "files\gen.exe 81 74 20 17 d4f6e54ddee7d39ba33788d92235d3f9" "tests\25" 25
call scripts\gen-input-via-stdout.bat "files\gen.exe 100 100 33 33 76e1636c0bf928312b39ccb85aedd582" "tests\26" 26
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 7 8 290 383 afcnymems" "tests\29" 29
call scripts\gen-input-via-stdout.bat "files\gen.exe 432 434 103 136 efc012d7989ad1db70a1ac6ef65a00f1" "tests\31" 31
call scripts\gen-input-via-stdout.bat "files\gen.exe 334 450 75 113 e67b42120c5438c7f675e0c486504ada" "tests\32" 32
call scripts\gen-input-via-stdout.bat "files\gen.exe 407 383 110 59 13a6e0edba128bd452421f9d1f8fba46" "tests\33" 33
call scripts\gen-input-via-stdout.bat "files\gen.exe 450 450 140 145 09b4884b970b7546ea8cac481027674a" "tests\34" 34
call scripts\gen-input-via-stdout.bat "files\gen_halfs_little.exe 8 12 356 231 wgcftf" "tests\35" 35
call scripts\gen-input-via-stdout.bat "files\gen.exe 450 450 20 148 1faa9c9d14ec2246b244aaeec0bd687b" "tests\36" 36
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 20 20248" "tests\38" 38
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 20 5305" "tests\40" 40
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 20 b" "tests\42" 42
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 100 20238" "tests\43" 43
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 450 b" "tests\45" 45
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 2500 a" "tests\46" 46
call scripts\gen-input-via-stdout.bat "files\gen_func.exe 2500 b" "tests\48" 48
call scripts\gen-input-via-stdout.bat "files\gen_halfs.exe 42 109 amravccba" "tests\49" 49
call scripts\gen-input-via-stdout.bat "files\gen_halfs.exe 44 195 beccwsu" "tests\51" 51
call scripts\gen-input-via-stdout.bat "files\gen_halfs.exe 43 183 gpasl" "tests\52" 52
call scripts\gen-input-via-stdout.bat "files\gen_halfs.exe 47 145 jdqdqk" "tests\53" 53
call scripts\gen-input-via-stdout.bat "files\gen_halfs.exe 45 128 fmkydcyc" "tests\54" 54
call scripts\gen-input-via-stdout.bat "files\gen_random.exe 49 131 memslmb" "tests\55" 55
call scripts\gen-input-via-stdout.bat "files\gen_random.exe 46 106 wxocogha" "tests\56" 56
call scripts\gen-input-via-stdout.bat "files\gen_random.exe 41 154 gcftft" "tests\58" 58
call scripts\gen-input-via-stdout.bat "files\gen_random.exe 49 176 lalwgj" "tests\59" 59
call scripts\gen-input-via-stdout.bat "files\gen_random.exe 47 117 zuamnl" "tests\60" 60
call scripts\gen-input-via-stdout.bat "files\gen.exe 2000 2000 393 356 1c31f36ebfac6a1dc5e30b2b7c1f6b02" "tests\71" 71
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 589 567 8de617e98e8776e1f6d6f5fa22bffebb" "tests\72" 72
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 650 808 dd4bfcd61b34df4a8662ab7f70ee6005" "tests\73" 73
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 716 819 02e506d1cf8275c223d3af966976b1bc" "tests\74" 74
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 678 811 f0ad00bae20475ded8c08296ce1f3dda" "tests\75" 75
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 723 807 f3af887e0e3f687901fa29bf76294fbd" "tests\76" 76
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 761 811 7600bf257b98259a61c5d526a59784f1" "tests\77" 77
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 800 811 75f862155fea8cb9968c22f77e85e1f2" "tests\78" 78
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 789 804 a2a5958f1dcffba67187c189ee933490" "tests\79" 79
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 214 26 343e04c8ee97103063158f7b898bf8b8" "tests\80" 80
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 270 20 46e070654ef30e113bafe4020cd3cd91" "tests\81" 81
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 226 285 2c73a64736422dd27cc91cf1f966443e" "tests\82" 82
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 828 2c37cf57e0d2d2bb3907c6bec6b5d9b7" "tests\83" 83
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 820 104c34bd38411b5e5476bbe04edb5142" "tests\84" 84
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 20 250 825ba6d91587b89c67d703041b675172" "tests\85" 85
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 523 521 b631e4c3910865574cc2a283b0f0f6a6" "tests\86" 86
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 34 80 d5bdc82b902a4328bb53d73caa720a95" "tests\87" 87
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 385 589 8d004a0702eea3535ba864fbc41ed77c" "tests\88" 88
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 820 fd82c3d503d2914276c9bc6034d57dcc" "tests\89" 89
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 268 346 6c17a8999e3eeed5a82790beb5b4c5b5" "tests\90" 90
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2000 2000 447 463 c640bf498a97cc58b011c8e60ade50cb" "tests\91" 91
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 418 458 38d259ef05464ef908eb986680e75ac1" "tests\92" 92
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 390 317 b3f6e319d1e145c856f913ed48910c9d" "tests\93" 93
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 65 62 12ddbdbc56fa7a9978bb589450918fef" "tests\94" 94
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 279 333 fd3de33a53e56f8c104f05d03c735de2" "tests\95" 95
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 824 88ea9d8c1fed9266c4fa56d680379d05" "tests\96" 96
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 823 05fccd748426c0b4786a993eba55e807" "tests\97" 97
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 38 62 eb948c39562eacab29e0205b6cd32e11" "tests\98" 98
call scripts\gen-input-via-stdout.bat "files\gen.exe 2500 2500 830 825 dc2d8c81a59722846d79546bd4d7ed29" "tests\99" 99
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 289 333 27c1fd0820bf27aa730957ce7c26befe" "tests\100" 100
call scripts\gen-input-via-stdout.bat "files\gen_max.exe 2500 2500 75 68 f3d0b77802af95f797e0910c0db9096b" "tests\101" 101
call scripts\gen-answer.bat tests\01 tests\01.a "tests" ""
call scripts\gen-answer.bat tests\02 tests\02.a "tests" ""
call scripts\gen-answer.bat tests\03 tests\03.a "tests" ""
call scripts\gen-answer.bat tests\04 tests\04.a "tests" ""
call scripts\gen-answer.bat tests\05 tests\05.a "tests" ""
call scripts\gen-answer.bat tests\06 tests\06.a "tests" ""
call scripts\gen-answer.bat tests\07 tests\07.a "tests" ""
call scripts\gen-answer.bat tests\08 tests\08.a "tests" ""
call scripts\gen-answer.bat tests\09 tests\09.a "tests" ""
call scripts\gen-answer.bat tests\10 tests\10.a "tests" ""
call scripts\gen-answer.bat tests\11 tests\11.a "tests" ""
call scripts\gen-answer.bat tests\12 tests\12.a "tests" ""
call scripts\gen-answer.bat tests\13 tests\13.a "tests" ""
call scripts\gen-answer.bat tests\14 tests\14.a "tests" ""
call scripts\gen-answer.bat tests\15 tests\15.a "tests" ""
call scripts\gen-answer.bat tests\16 tests\16.a "tests" ""
call scripts\gen-answer.bat tests\17 tests\17.a "tests" ""
call scripts\gen-answer.bat tests\18 tests\18.a "tests" ""
call scripts\gen-answer.bat tests\19 tests\19.a "tests" ""
call scripts\gen-answer.bat tests\20 tests\20.a "tests" ""
call scripts\gen-answer.bat tests\21 tests\21.a "tests" ""
call scripts\gen-answer.bat tests\22 tests\22.a "tests" ""
call scripts\gen-answer.bat tests\23 tests\23.a "tests" ""
call scripts\gen-answer.bat tests\24 tests\24.a "tests" ""
call scripts\gen-answer.bat tests\25 tests\25.a "tests" ""
call scripts\gen-answer.bat tests\26 tests\26.a "tests" ""
call scripts\gen-answer.bat tests\27 tests\27.a "tests" ""
call scripts\gen-answer.bat tests\28 tests\28.a "tests" ""
call scripts\gen-answer.bat tests\29 tests\29.a "tests" ""
call scripts\gen-answer.bat tests\30 tests\30.a "tests" ""
call scripts\gen-answer.bat tests\31 tests\31.a "tests" ""
call scripts\gen-answer.bat tests\32 tests\32.a "tests" ""
call scripts\gen-answer.bat tests\33 tests\33.a "tests" ""
call scripts\gen-answer.bat tests\34 tests\34.a "tests" ""
call scripts\gen-answer.bat tests\35 tests\35.a "tests" ""
call scripts\gen-answer.bat tests\36 tests\36.a "tests" ""
call scripts\gen-answer.bat tests\37 tests\37.a "tests" ""
call scripts\gen-answer.bat tests\38 tests\38.a "tests" ""
call scripts\gen-answer.bat tests\39 tests\39.a "tests" ""
call scripts\gen-answer.bat tests\40 tests\40.a "tests" ""
call scripts\gen-answer.bat tests\41 tests\41.a "tests" ""
call scripts\gen-answer.bat tests\42 tests\42.a "tests" ""
call scripts\gen-answer.bat tests\43 tests\43.a "tests" ""
call scripts\gen-answer.bat tests\44 tests\44.a "tests" ""
call scripts\gen-answer.bat tests\45 tests\45.a "tests" ""
call scripts\gen-answer.bat tests\46 tests\46.a "tests" ""
call scripts\gen-answer.bat tests\47 tests\47.a "tests" ""
call scripts\gen-answer.bat tests\48 tests\48.a "tests" ""
call scripts\gen-answer.bat tests\49 tests\49.a "tests" ""
call scripts\gen-answer.bat tests\50 tests\50.a "tests" ""
call scripts\gen-answer.bat tests\51 tests\51.a "tests" ""
call scripts\gen-answer.bat tests\52 tests\52.a "tests" ""
call scripts\gen-answer.bat tests\53 tests\53.a "tests" ""
call scripts\gen-answer.bat tests\54 tests\54.a "tests" ""
call scripts\gen-answer.bat tests\55 tests\55.a "tests" ""
call scripts\gen-answer.bat tests\56 tests\56.a "tests" ""
call scripts\gen-answer.bat tests\57 tests\57.a "tests" ""
call scripts\gen-answer.bat tests\58 tests\58.a "tests" ""
call scripts\gen-answer.bat tests\59 tests\59.a "tests" ""
call scripts\gen-answer.bat tests\60 tests\60.a "tests" ""
call scripts\gen-answer.bat tests\61 tests\61.a "tests" ""
call scripts\gen-answer.bat tests\62 tests\62.a "tests" ""
call scripts\gen-answer.bat tests\63 tests\63.a "tests" ""
call scripts\gen-answer.bat tests\64 tests\64.a "tests" ""
call scripts\gen-answer.bat tests\65 tests\65.a "tests" ""
call scripts\gen-answer.bat tests\66 tests\66.a "tests" ""
call scripts\gen-answer.bat tests\67 tests\67.a "tests" ""
call scripts\gen-answer.bat tests\68 tests\68.a "tests" ""
call scripts\gen-answer.bat tests\69 tests\69.a "tests" ""
call scripts\gen-answer.bat tests\70 tests\70.a "tests" ""
call scripts\gen-answer.bat tests\71 tests\71.a "tests" ""
call scripts\gen-answer.bat tests\72 tests\72.a "tests" ""
call scripts\gen-answer.bat tests\73 tests\73.a "tests" ""
call scripts\gen-answer.bat tests\74 tests\74.a "tests" ""
call scripts\gen-answer.bat tests\75 tests\75.a "tests" ""
call scripts\gen-answer.bat tests\76 tests\76.a "tests" ""
call scripts\gen-answer.bat tests\77 tests\77.a "tests" ""
call scripts\gen-answer.bat tests\78 tests\78.a "tests" ""
call scripts\gen-answer.bat tests\79 tests\79.a "tests" ""
call scripts\gen-answer.bat tests\80 tests\80.a "tests" ""
call scripts\gen-answer.bat tests\81 tests\81.a "tests" ""
call scripts\gen-answer.bat tests\82 tests\82.a "tests" ""
call scripts\gen-answer.bat tests\83 tests\83.a "tests" ""
call scripts\gen-answer.bat tests\84 tests\84.a "tests" ""
call scripts\gen-answer.bat tests\85 tests\85.a "tests" ""
call scripts\gen-answer.bat tests\86 tests\86.a "tests" ""
call scripts\gen-answer.bat tests\87 tests\87.a "tests" ""
call scripts\gen-answer.bat tests\88 tests\88.a "tests" ""
call scripts\gen-answer.bat tests\89 tests\89.a "tests" ""
call scripts\gen-answer.bat tests\90 tests\90.a "tests" ""
call scripts\gen-answer.bat tests\91 tests\91.a "tests" ""
call scripts\gen-answer.bat tests\92 tests\92.a "tests" ""
call scripts\gen-answer.bat tests\93 tests\93.a "tests" ""
call scripts\gen-answer.bat tests\94 tests\94.a "tests" ""
call scripts\gen-answer.bat tests\95 tests\95.a "tests" ""
call scripts\gen-answer.bat tests\96 tests\96.a "tests" ""
call scripts\gen-answer.bat tests\97 tests\97.a "tests" ""
call scripts\gen-answer.bat tests\98 tests\98.a "tests" ""
call scripts\gen-answer.bat tests\99 tests\99.a "tests" ""
call scripts\gen-answer.bat tests\100 tests\100.a "tests" ""
call scripts\gen-answer.bat tests\101 tests\101.a "tests" ""

