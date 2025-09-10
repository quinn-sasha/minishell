./test_tokenize "ls -l"
./test_tokenize 'grep -nr "main" *'
./test_tokenize "grep -nr 'main' *"
./test_tokenize "echo 'abc' | cat > outfile.txt"
./test_tokenize "echo helloworld >> out"
./test_tokenize ""
./test_tokenize "< Makefile tr a-z A-Z | cat | "
./test_tokenize 'echo "hello '
