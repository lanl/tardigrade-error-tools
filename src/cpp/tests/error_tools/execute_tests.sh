make && ./test_error_tools && cat results.tex && cat results.tex | grep -i False || printf "\nNo failures\n"
