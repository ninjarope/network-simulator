# Runs the tests and appends their results to a file (with durations)
echo "Running tests / wait a moment.."
echo "------------------------------------------------------------\n" >> tests.txt
echo "Starting a new batch of tests..\n" >> tests.txt
./ns -d yes >> tests.txt
