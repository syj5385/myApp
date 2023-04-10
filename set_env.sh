#!/bin/bash

export MYAPP_LOG="${PWD}/build/log"
export LOG_LEVEL=LOG_LEVEL_ERROR
export TCP_PORT=20000
export UDP_PORT=20001
echo "================================================================"
echo "Set Environments"
echo "----------------------------------------------------------------"
echo ""
echo " MYAPP_LOG = $MYAPP_LOG"
echo " LOG_LEVEL = $LOG_LEVEL"
echo " TCP_PORT = $TCP_PORT"
echo " UDP_PORT = $UDP_PORT"
echo "================================================================"