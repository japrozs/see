#!/bin/bash

for N in {1..50}
do
	ruby client.rb $((($N % 6) + 1)) &
done

wait