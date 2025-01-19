SERVER="localhost"  
PORT=6667      
CHANNEL="#Room"
CLIENT_COUNT=500
PASS="pass"

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
wait 
echo "Disconnected all clients from the server."