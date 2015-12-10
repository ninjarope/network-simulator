# Runs the tests and appends their results to a file (with durations)
echo "Running tests / wait a moment.."
echo "------------------------------------------------------------" >> tests.txt
echo "------------------------------------------------------------" >> tests.txt
echo "Starting a new batch of tests.." >> tests.txt
echo "------------------------------------------------------------" >> tests.txt
./ns -d yes >> tests.txt
tail -n2 tests.txt > TEST_STATUS.md
