rem   *** validation ***
call scripts\run-validator-tests.bat
call scripts\run-checker-tests.bat

rem    *** tests ***
md tests
call scripts\gen-input-via-stdout.bat "files\gen1.exe 100 L6sAyAem9X3eX1H6oYQt" "tests\07" 7
call scripts\gen-input-via-stdout.bat "files\gen1.exe 100 qG378vm6u5050e8UuiXf" "tests\08" 8
call scripts\gen-input-via-stdout.bat "files\gen1.exe 100 98LZ19G7Nr0H713Ha9EZ" "tests\09" 9
call scripts\gen-input-via-stdout.bat "files\gen1.exe 100 S7ZSDtkedqwXUrQtiD2s" "tests\10" 10
call scripts\gen-input-via-stdout.bat "files\gen2.exe 100 YV7QzVh19xSt538qLk37" "tests\11" 11
call scripts\gen-input-via-stdout.bat "files\gen2.exe 100 LWrBwY7wPvYjjU2dbvd9" "tests\12" 12
call scripts\gen-input-via-stdout.bat "files\gen2.exe 100 1d1nJIpchB7ciqN0dkC6" "tests\13" 13
call scripts\gen-input-via-stdout.bat "files\gen2.exe 100 4fw4wuo1pjsbXCycTOLF" "tests\14" 14
call scripts\gen-input-via-stdout.bat "files\gen3.exe 100 Yru38WD1rt0fDJhEaCOC" "tests\15" 15
call scripts\gen-input-via-stdout.bat "files\gen3.exe 100 I3mzhM4rx9dwbCDgfkse" "tests\16" 16
call scripts\gen-input-via-stdout.bat "files\gen3.exe 100 bjkKnyXNmHT7GdHJi7Md" "tests\17" 17
call scripts\gen-input-via-stdout.bat "files\gen3.exe 100 X9fLJQqLkcdN9i1kPies" "tests\18" 18
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1 99 I3JTjevKQhVzG8aosaSW" "tests\19" 19
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 2 49 5EumFZ20lEkrDaiegS2Z" "tests\20" 20
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 4 24 8yMpX9eAy7VdcA4CXfCE" "tests\21" 21
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 5 19 xE16STYl5NpAF7aKHRP9" "tests\22" 22
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 13 7 nyZPRRsmqoUrVh3EKomg" "tests\23" 23
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 99 1 FCmUvji63IxCruAHByo6" "tests\24" 24
call scripts\gen-input-via-stdout.bat "files\gen1.exe 5000 9Ix6b1cOjJt6BXyHptsO" "tests\25" 25
call scripts\gen-input-via-stdout.bat "files\gen1.exe 5000 gkiw2jXA1ldMzCaHXLtG" "tests\26" 26
call scripts\gen-input-via-stdout.bat "files\gen1.exe 5000 Ymoy42cRRksNYlknz0tw" "tests\27" 27
call scripts\gen-input-via-stdout.bat "files\gen1.exe 5000 BKBbhrI0n7olDyucRHzJ" "tests\28" 28
call scripts\gen-input-via-stdout.bat "files\gen2.exe 5000 nvGAaqb2kzhIFcSG8AKc" "tests\29" 29
call scripts\gen-input-via-stdout.bat "files\gen2.exe 5000 60I5QnYYRXlYueJlEXom" "tests\30" 30
call scripts\gen-input-via-stdout.bat "files\gen2.exe 5000 G9w7OXYeUPu5OCX4cZG3" "tests\31" 31
call scripts\gen-input-via-stdout.bat "files\gen2.exe 5000 92G5vhBBTZzD2xVYcQj9" "tests\32" 32
call scripts\gen-input-via-stdout.bat "files\gen3.exe 5000 ec3PdYEAqcBx0ZxVIpb8" "tests\33" 33
call scripts\gen-input-via-stdout.bat "files\gen3.exe 5000 V0DQ5nyjGG4mhqPUAXs6" "tests\34" 34
call scripts\gen-input-via-stdout.bat "files\gen3.exe 5000 vcsLQ56WAXnmwYHst974" "tests\35" 35
call scripts\gen-input-via-stdout.bat "files\gen3.exe 5000 2LUzEOIbkzkRQteWskos" "tests\36" 36
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1 4999 nZtGXB1HEoAusQB1OYBr" "tests\37" 37
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 2 2499 a8akpvpWLuAykmKRfjv5" "tests\38" 38
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 5 999 miRQGj4KKSTO94tQe8S7" "tests\39" 39
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 10 499 wcqsLR97MukI9bDxwbi5" "tests\40" 40
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 20 249 iWw0kg5CE6kbHPQddfkB" "tests\41" 41
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 50 99 6UbZqMNZSYvR469wCYkp" "tests\42" 42
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 100 49 WW1amre6lAIkpqXHwcDi" "tests\43" 43
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 200 24 KN12XMzk3b2dCxF69II3" "tests\44" 44
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 500 9 KX5cOIWfQMDocGL8tABm" "tests\45" 45
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1000 4 JnXa6PoPvvKhErRDUzGl" "tests\46" 46
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 2400 2 EqZoqzoTOqWUBHKag3Kv" "tests\47" 47
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 4999 1 cvhgTnbfnPvIY9q1w7nu" "tests\48" 48
call scripts\gen-input-via-stdout.bat "files\gen1.exe 500000 fECBZyq4zfpjttAtaxgi" "tests\49" 49
call scripts\gen-input-via-stdout.bat "files\gen1.exe 500000 QT6cLcDQHwKD6aCGXl8g" "tests\50" 50
call scripts\gen-input-via-stdout.bat "files\gen1.exe 500000 b4sYyimbFPmVI2Jlz9EQ" "tests\51" 51
call scripts\gen-input-via-stdout.bat "files\gen1.exe 500000 viC1nXKporR4URjdsjfa" "tests\52" 52
call scripts\gen-input-via-stdout.bat "files\gen2.exe 500000 87WYtCcu5mvIYu1hK3OG" "tests\53" 53
call scripts\gen-input-via-stdout.bat "files\gen2.exe 500000 Olz6MfJqJ1WqNS7QztsW" "tests\54" 54
call scripts\gen-input-via-stdout.bat "files\gen2.exe 500000 cCZ0LC8q0WMnGUnoiMbK" "tests\55" 55
call scripts\gen-input-via-stdout.bat "files\gen2.exe 500000 bQFjzoeHcewmvJOTXMLX" "tests\56" 56
call scripts\gen-input-via-stdout.bat "files\gen3.exe 500000 qLWFtdGszaI5jghByJfZ" "tests\57" 57
call scripts\gen-input-via-stdout.bat "files\gen3.exe 500000 sMwIpETgEs6xEgHmYJu0" "tests\58" 58
call scripts\gen-input-via-stdout.bat "files\gen3.exe 500000 KdRJzVNh6vf608YcnGAg" "tests\59" 59
call scripts\gen-input-via-stdout.bat "files\gen3.exe 500000 6W5ZEVB0Lb752EUSIOly" "tests\60" 60
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1 499999 XAPs04B1h0Fk9ogK2nzJ" "tests\61" 61
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 2 249999 bdAMjuamLe5wznYdUBNv" "tests\62" 62
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 5 99999 ihLUJloSBBUWzJlgf8a9" "tests\63" 63
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 10 49999 tAQ6OZPnhzDFFUmoL0f3" "tests\64" 64
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 20 24999 pjMgyvp7uFM1ccjqR6nT" "tests\65" 65
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 50 9999 oEeIrtUIBN2VH6XKqfBg" "tests\66" 66
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 100 4999 Oef2IcduUJdug6tPh7w3" "tests\67" 67
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 200 2499 UtFHDUARq0n5jSsAnW65" "tests\68" 68
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 500 999 EvsmHaCM21wYkVCKHlCV" "tests\69" 69
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1000 499 S1EbrOvGrHls2O7jmXLo" "tests\70" 70
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 1999 249 LvaC1kgcMi5nrAn6fhRJ" "tests\71" 71
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 2499 200 8UokH9ulv2tTTWKqQwSn" "tests\72" 72
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 9999 50 UW9qJinNQFWfik4g7sqM" "tests\73" 73
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 19999 25 zI1WBZnoz0CnePykpGOD" "tests\74" 74
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 49999 10 CwD9URtwrJXJhSotVou4" "tests\75" 75
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 99999 5 eDEGPQ1YEo7SYjVQJhf1" "tests\76" 76
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 249999 2 wSaZZsdxAOyQpWEPy0jJ" "tests\77" 77
call scripts\gen-input-via-stdout.bat "files\gen_star.exe 499999 1 FZmoP8wVLX8Kl7cVsiau" "tests\78" 78
call scripts\gen-answer.bat tests\01 tests\01.a "tests" "A"
call scripts\gen-answer.bat tests\02 tests\02.a "tests" "A"
call scripts\gen-answer.bat tests\03 tests\03.a "tests" "A"
call scripts\gen-answer.bat tests\04 tests\04.a "tests" "A"
call scripts\gen-answer.bat tests\05 tests\05.a "tests" "A"
call scripts\gen-answer.bat tests\06 tests\06.a "tests" "A"
call scripts\gen-answer.bat tests\07 tests\07.a "tests" "A"
call scripts\gen-answer.bat tests\08 tests\08.a "tests" "A"
call scripts\gen-answer.bat tests\09 tests\09.a "tests" "A"
call scripts\gen-answer.bat tests\10 tests\10.a "tests" "A"
call scripts\gen-answer.bat tests\11 tests\11.a "tests" "A"
call scripts\gen-answer.bat tests\12 tests\12.a "tests" "A"
call scripts\gen-answer.bat tests\13 tests\13.a "tests" "A"
call scripts\gen-answer.bat tests\14 tests\14.a "tests" "A"
call scripts\gen-answer.bat tests\15 tests\15.a "tests" "A"
call scripts\gen-answer.bat tests\16 tests\16.a "tests" "A"
call scripts\gen-answer.bat tests\17 tests\17.a "tests" "A"
call scripts\gen-answer.bat tests\18 tests\18.a "tests" "A"
call scripts\gen-answer.bat tests\19 tests\19.a "tests" "A"
call scripts\gen-answer.bat tests\20 tests\20.a "tests" "A"
call scripts\gen-answer.bat tests\21 tests\21.a "tests" "A"
call scripts\gen-answer.bat tests\22 tests\22.a "tests" "A"
call scripts\gen-answer.bat tests\23 tests\23.a "tests" "A"
call scripts\gen-answer.bat tests\24 tests\24.a "tests" "A"
call scripts\gen-answer.bat tests\25 tests\25.a "tests" "B"
call scripts\gen-answer.bat tests\26 tests\26.a "tests" "B"
call scripts\gen-answer.bat tests\27 tests\27.a "tests" "B"
call scripts\gen-answer.bat tests\28 tests\28.a "tests" "B"
call scripts\gen-answer.bat tests\29 tests\29.a "tests" "B"
call scripts\gen-answer.bat tests\30 tests\30.a "tests" "B"
call scripts\gen-answer.bat tests\31 tests\31.a "tests" "B"
call scripts\gen-answer.bat tests\32 tests\32.a "tests" "B"
call scripts\gen-answer.bat tests\33 tests\33.a "tests" "B"
call scripts\gen-answer.bat tests\34 tests\34.a "tests" "B"
call scripts\gen-answer.bat tests\35 tests\35.a "tests" "B"
call scripts\gen-answer.bat tests\36 tests\36.a "tests" "B"
call scripts\gen-answer.bat tests\37 tests\37.a "tests" "B"
call scripts\gen-answer.bat tests\38 tests\38.a "tests" "B"
call scripts\gen-answer.bat tests\39 tests\39.a "tests" "B"
call scripts\gen-answer.bat tests\40 tests\40.a "tests" "B"
call scripts\gen-answer.bat tests\41 tests\41.a "tests" "B"
call scripts\gen-answer.bat tests\42 tests\42.a "tests" "B"
call scripts\gen-answer.bat tests\43 tests\43.a "tests" "B"
call scripts\gen-answer.bat tests\44 tests\44.a "tests" "B"
call scripts\gen-answer.bat tests\45 tests\45.a "tests" "B"
call scripts\gen-answer.bat tests\46 tests\46.a "tests" "B"
call scripts\gen-answer.bat tests\47 tests\47.a "tests" "B"
call scripts\gen-answer.bat tests\48 tests\48.a "tests" "B"
call scripts\gen-answer.bat tests\49 tests\49.a "tests" "C"
call scripts\gen-answer.bat tests\50 tests\50.a "tests" "C"
call scripts\gen-answer.bat tests\51 tests\51.a "tests" "C"
call scripts\gen-answer.bat tests\52 tests\52.a "tests" "C"
call scripts\gen-answer.bat tests\53 tests\53.a "tests" "C"
call scripts\gen-answer.bat tests\54 tests\54.a "tests" "C"
call scripts\gen-answer.bat tests\55 tests\55.a "tests" "C"
call scripts\gen-answer.bat tests\56 tests\56.a "tests" "C"
call scripts\gen-answer.bat tests\57 tests\57.a "tests" "C"
call scripts\gen-answer.bat tests\58 tests\58.a "tests" "C"
call scripts\gen-answer.bat tests\59 tests\59.a "tests" "C"
call scripts\gen-answer.bat tests\60 tests\60.a "tests" "C"
call scripts\gen-answer.bat tests\61 tests\61.a "tests" "C"
call scripts\gen-answer.bat tests\62 tests\62.a "tests" "C"
call scripts\gen-answer.bat tests\63 tests\63.a "tests" "C"
call scripts\gen-answer.bat tests\64 tests\64.a "tests" "C"
call scripts\gen-answer.bat tests\65 tests\65.a "tests" "C"
call scripts\gen-answer.bat tests\66 tests\66.a "tests" "C"
call scripts\gen-answer.bat tests\67 tests\67.a "tests" "C"
call scripts\gen-answer.bat tests\68 tests\68.a "tests" "C"
call scripts\gen-answer.bat tests\69 tests\69.a "tests" "C"
call scripts\gen-answer.bat tests\70 tests\70.a "tests" "C"
call scripts\gen-answer.bat tests\71 tests\71.a "tests" "C"
call scripts\gen-answer.bat tests\72 tests\72.a "tests" "C"
call scripts\gen-answer.bat tests\73 tests\73.a "tests" "C"
call scripts\gen-answer.bat tests\74 tests\74.a "tests" "C"
call scripts\gen-answer.bat tests\75 tests\75.a "tests" "C"
call scripts\gen-answer.bat tests\76 tests\76.a "tests" "C"
call scripts\gen-answer.bat tests\77 tests\77.a "tests" "C"
call scripts\gen-answer.bat tests\78 tests\78.a "tests" "C"

