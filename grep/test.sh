diff <(grep -e grep -e hello "test_files/test1.txt") <(./s21_grep -e grep -e hello "test_files/test1.txt") -s
diff <(grep -i hello "test_files/test1.txt") <(./s21_grep -i hello "test_files/test1.txt") -s
diff <(grep -v hello "test_files/test1.txt") <(./s21_grep -v hello "test_files/test1.txt") -s
diff <(grep -c hello "test_files/test1.txt") <(./s21_grep -c hello "test_files/test1.txt") -s
diff <(grep -l cat "test_files/test1.txt" "test_files/test2.txt") <(./s21_grep -l cat "test_files/test1.txt" "test_files/test2.txt") -s
diff <(grep -n hello "test_files/test1.txt") <(./s21_grep -n hello "test_files/test1.txt") -s
diff <(grep -h hello "test_files/test1.txt" "test_files/test2.txt") <(./s21_grep -h hello "test_files/test1.txt" "test_files/test2.txt") -s
diff <(grep -s hello "test_files/test.txt") <(./s21_grep -s hello "test_files/test.txt") -s
diff <(grep -f "test_files/pattern.txt" "test_files/test1.txt") <(./s21_grep -f "test_files/pattern.txt" "test_files/test1.txt") -s
diff <(grep -o hello "test_files/test2.txt") <(./s21_grep -o hello "test_files/test2.txt") -s
diff <(grep -in hello "test_files/test2.txt") <(./s21_grep -in hello "test_files/test2.txt") -s
diff <(grep -iv hello "test_files/test2.txt") <(./s21_grep -iv hello "test_files/test2.txt") -s
diff <(grep -cl hello "test_files/test1.txt" "test_files/test2.txt") <(./s21_grep -cl hello "test_files/test1.txt" "test_files/test2.txt") -s
diff <(grep for "s21_grep.c" -c -v -h) <(./s21_grep for "s21_grep.c" -c -v -h) -s
diff <(grep -e hello -e cat s21_grep.c s21_grep.h Makefile -n -o -h) <(./s21_grep -e hello -e cat s21_grep.c s21_grep.h Makefile -n -o -h) -s