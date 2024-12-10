# Массив с флагами для grep
flags=("i" "c" "l" "n" "h" "s")

# Цикл по флагам
for flag in "${flags[@]}"; do
  # Выполнение команды с grep
  grep -$flag Flags s21_grep.h > 2
  # Выполнение команды с вашим скриптом
  ./s21_grep -$flag Flags s21_grep.h > 1
  
  # Сравнение результатов с помощью diff
  if diff 1 2 > /dev/null; then
    echo "flag $flag ok"
  else
    echo "flag $flag not ok"
  fi
done


grep -f regular.txt test.txt > 1
./s21_grep -f regular.txt test.txt > 2


  # Сравнение результатов с помощью diff
  if diff 1 2 > /dev/null; then
    echo "flag f  ok"
  else
    echo "flag f not ok"
  fi


grep -e z test.txt > 1
./s21_grep -e z test.txt > 2


  # Сравнение результатов с помощью diff
  if diff 1 2 > /dev/null; then
    echo "flag e  ok"
  else
    echo "flag e not ok"
  fi

