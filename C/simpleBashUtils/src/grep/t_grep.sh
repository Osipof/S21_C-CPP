#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test.txt"
TEST_PATTERN="ivan"

for var in -i -v -c -l -n -h -s -o
do
	TEST1="$var $TEST_PATTERN $TEST_FILE"
	./s21_grep $TEST1 > s21_grep.txt
	grep $TEST1 > grep.txt
	DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
	then
		COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
	else
		COUNTER_FAIL=$((COUNTER_FAIL+1))
		echo "$var"
	fi
	rm s21_grep.txt grep.txt
done

TEST1="-e '[0-9]' $TEST_FILE"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
then
  COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
else
  COUNTER_FAIL=$((COUNTER_FAIL+1))
  echo flag e
fi
rm s21_grep.txt grep.txt

TEST1="-f pattern.txt $TEST_FILE"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
then
  COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
else
  COUNTER_FAIL=$((COUNTER_FAIL+1))
  echo flag f
fi
rm s21_grep.txt grep.txt



for var in -i -v -c -l -n -h -s -o
do
	for var2 in -i -v -c -l -n -h -s -o
  do
    if [ $var != $var2 ]
    then
      TEST1="$var $var2 $TEST_PATTERN $TEST_FILE"
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
      else
        COUNTER_FAIL=$((COUNTER_FAIL+1))
        echo "$var $var2"
      fi
      rm s21_grep.txt grep.txt
  	fi
  done

  TEST1="$var -e '[0-9]' $TEST_FILE"
  ./s21_grep $TEST1 > s21_grep.txt
  grep $TEST1 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
  else
    COUNTER_FAIL=$((COUNTER_FAIL+1))
    echo flag e
  fi
  rm s21_grep.txt grep.txt

  TEST1="$var -f pattern.txt $TEST_FILE"
  ./s21_grep $TEST1 > s21_grep.txt
  grep $TEST1 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
  else
    COUNTER_FAIL=$((COUNTER_FAIL+1))
    echo flag f $var
  fi
  rm s21_grep.txt grep.txt
done

for var in i v c l n h s o
do
	for var2 in i v c l n h s o
  do
    if [ $var != $var2 ]
    then
      TEST1="-$var$var2 $TEST_PATTERN $TEST_FILE"
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
      else
        COUNTER_FAIL=$((COUNTER_FAIL+1))
        echo "$var $var2"
      fi
      rm s21_grep.txt grep.txt
  	fi
  done

  e="e '[0-9]'"
  TEST1="-$var$e $TEST_FILE"
  ./s21_grep $TEST1 > s21_grep.txt
  grep $TEST1 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
  else
    COUNTER_FAIL=$((COUNTER_FAIL+1))
    echo flag e
  fi
  rm s21_grep.txt grep.txt

  f="f pattern.txt"
  TEST1="-$var$f $TEST_FILE"
  ./s21_grep $TEST1 > s21_grep.txt
  grep $TEST1 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
  else
    COUNTER_FAIL=$((COUNTER_FAIL+1))
    echo flag f $var
  fi
  rm s21_grep.txt grep.txt
done



for var in -i -v -c -l -n -h -s -o
do
	for var2 in -i -v -c -l -n -h -s -o
  do
    for var3 in -i -v -c -l -n -h -s -o
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
      then
        TEST1="$var $var2 $var3 $TEST_PATTERN $TEST_FILE"
        ./s21_grep $TEST1 > s21_grep.txt
        grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
        else
          COUNTER_FAIL=$((COUNTER_FAIL+1))
          echo "$var $var2 $var3"
        fi
        rm s21_grep.txt grep.txt
      fi
    done

      TEST1="$var $var2 -e[0-9] $TEST_FILE"
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
      else
        COUNTER_FAIL=$((COUNTER_FAIL+1))
      fi
      rm s21_grep.txt grep.txt

      TEST1="$var $var2 -f pattern.txt $TEST_FILE"
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
      else
        COUNTER_FAIL=$((COUNTER_FAIL+1))
      fi
      rm s21_grep.txt grep.txt
  done
done

for var in i v c l n h s o
do
	for var2 in i v c l n h s o
  do
    for var3 in i v c l n h s o
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
      then
        TEST1="-$var$var2 $TEST_PATTERN $TEST_FILE"
        ./s21_grep $TEST1 > s21_grep.txt
        grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
        else
          COUNTER_FAIL=$((COUNTER_FAIL+1))
        fi
        rm s21_grep.txt grep.txt
  	  fi
  	done

    e="e[0-9]"
    TEST1="-$var$var2$e $TEST_FILE"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
    else
      COUNTER_FAIL=$((COUNTER_FAIL+1))
    fi
    rm s21_grep.txt grep.txt

    f="f pattern.txt"
    TEST1="-$var$var2$f $TEST_FILE"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      COUNTER_SUCCESS=$((COUNTER_SUCCESS+1))
    else
      COUNTER_FAIL=$((COUNTER_FAIL+1))
    fi
    rm s21_grep.txt grep.txt
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
