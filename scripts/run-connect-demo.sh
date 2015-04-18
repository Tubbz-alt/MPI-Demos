#!/bin/sh

#  Set our MPI Arguments
MPI_ARGS='-envall -nameserver localhost'

#  Set our EXE
CLIENT_EXE=./release/bin/connect-client-demo
SERVER_EXE=./release/bin/connect-server-demo

#  Run Nameserver
echo 'Starting nameserver'
hydra_nameserver &
NAMESERVER_PID=$!
echo "-> Nameserver PID: $NAMESERVER_PID"

#  Run Server
mpiexec ${MPI_ARGS} -n 1 ${SERVER_EXE} &
SERVER_PID=$!
echo "-> Server PID: $SERVER_PID"

#  Sleep
sleep 1

#  Run Client 
mpiexec ${MPI_ARGS} -n 1 ${CLIENT_EXE} &
CLIENT_PID=$!
echo "-> Client PID: $CLIENT_PID"

echo 'Waiting for completion'
wait $SERVER_PID $CLIENT_PID

echo 'Shutting Down Nameserver'
kill $NAMESERVER_PID

