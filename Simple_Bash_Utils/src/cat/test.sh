
cat -b ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat -b ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat -b ./cat_test/cat.txt > orig_cat.txt
./s21_cat -b ./cat_test/cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat -e ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat -e ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat -n ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat -n ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat -s ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat -s ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat -t ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat -t ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt

cat ./cat_test/test_cat.txt > orig_cat.txt
./s21_cat ./cat_test/test_cat.txt > s21_cat.txt
diff orig_cat.txt s21_cat.txt