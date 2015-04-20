#!/bin/sh

#  Set our MPI Arguments
MPI_ARGS=""

#  Port
PORT=1233

#  Set our EXE
CLIENT_EXE=./release/bin/connect-client-demo
SERVER_EXE=./release/bin/connect-server-demo

#  Run Nameserver
#echo 'Starting nameserver'
#hydra_nameserver &
#hydra_nameserver -port $PORT &
#NAMESERVER_PID=$!
#echo "-> Nameserver PID: $NAMESERVER_PID"

#sleep 1

#  Run Server
mpiexec ${MPI_ARGS} -n 1 ${SERVER_EXE} $PORT &
SERVER_PID=$!
echo "-> Server PID: $SERVER_PID"

sleep 1

#  Run Client 
mpirun ${MPI_ARGS} -n 1 ${CLIENT_EXE} $PORT &
CLIENT_PID=$!
echo "-> Client PID: $CLIENT_PID"

echo 'Waiting for completion'
wait $SERVER_PID $CLIENT_PID


