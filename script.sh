#!/bin/bash

SERVER="localhost"
PORT=6667
CHANNEL="#Room"
CLIENT_COUNT=500
PASS="pass"

# Function to clean up background processes
cleanup() {
    echo "Caught Ctrl+C. Terminating all background processes..."
    kill -- -$$  # Kill the entire process group
    exit 1
}

# Trap SIGINT (Ctrl+C) and call the cleanup function
trap cleanup SIGINT

# Spawn clients
for ((i=1; i<=CLIENT_COUNT; i++))
do
    (
    NICKNAME="TestUser_${i}"
    echo "PASS $PASS"
    sleep 0.25
    echo "NICK $NICKNAME"
    sleep 0.25
    echo "USER ${i} 0 * "
    sleep 0.25
    echo "JOIN $CHANNEL"
    sleep 500
    ) | nc $SERVER $PORT &
    
    sleep 0.5
done

# Wait for all background processes to finish
wait
echo "Disconnected all clients from the server."