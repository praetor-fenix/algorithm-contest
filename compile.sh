FILE=$1

g++ $FILE -lm -O2 -std=c++11 -pipe -DONLINE_JUDGE -Wall
./a.out < test/input.txt > test/result.txt
diff test/result.txt test/output.txt
rm a.out
